using namespace SC;
using namespace SC::Game;

using namespace System;
using namespace System::Numerics;

using namespace std;

namespace
{
	Mutex mLocker;
	vector<bool> mLocked;
	queue<int> mQueue;
	bool mDisposed;
}

void OnDisposing()
{
	if ( Material::mReflectionBuffer )
	{
		Material::mReflectionBuffer->Release();
		Material::mReflectionBuffer = nullptr;
	}

	if ( Material::mNullSrv )
	{
		delete Material::mNullSrv;
		Material::mNullSrv = nullptr;
	}

	mDisposed = true;
}

int Material::Lock( Material^ ptr )
{
	if ( !mQueue.size() )
	{
		// 빈 공간이 없을 경우 전체 크기를 늘립니다.
		Realloc( mCapacity + 256 );
	}

	auto idx = mQueue.front();
	mQueue.pop();

	mLocked[idx] = true;

	return idx;
}

void Material::Realloc( int capacity )
{
	auto pDevice = Graphics::mDevice->pDevice.Get();
	mReflectionBuffer = new LargeHeap( D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, sizeof( Material_Reflection ) * capacity );

	// 버퍼에 대한 셰이더 자원 서술자를 생성합니다.
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{ };
	srvDesc.Format = DXGI_FORMAT_UNKNOWN;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Buffer.NumElements = capacity;
	srvDesc.Buffer.StructureByteStride = sizeof( Material_Reflection );

	// 캐퍼시티를 다시 설정합니다.
	mLocked.resize( capacity, false );

	for ( int i = mCapacity; i < capacity; ++i )
	{
		mQueue.push( i );
	}

	mCapacity = capacity;
}

void Material::UpdateReflection()
{
	D3D12_RANGE range;

	range.Begin = sizeof( Material_Reflection ) * mLockIndex;
	range.End = range.Begin + sizeof( Material_Reflection );

	Material_Reflection* pBlock = ( Material_Reflection* )mReflectionBuffer->Map();
	pBlock[mLockIndex] = *mReflectionData;
	mReflectionBuffer->Unmap( range );
}

void Material::UpdateConstants()
{
	for ( int i = 0; i < 2; ++i )
	{
		auto block = mConstantBuffer->Map( i );
		memcpy( block, mConstantData, sizeof( *mConstantData ) );
		mConstantBuffer->Unmap( i );
	}
}

void Material::Initialize()
{
	App::Disposing.push_front( OnDisposing );

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{ };
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Texture2D.MipLevels = 1;

	mNullSrv = new CShaderResourceView( DescriptorAllocator::CreateShaderResourceView( nullptr, &srvDesc ) );

	Realloc( 256 );

	mDefault = gcnew Material( "Material.mDefault" );
	mDefault->Freeze();
}

void Material::SetConstantBuffer( CDeviceContext& deviceContext )
{
	if ( mLastGeneration != mGeneration )
	{
		UpdateConstants();
		mLastGeneration = mGeneration;
	}

	deviceContext.SetGraphicsRootConstantBufferView( Slot_3D_Material, mConstantBuffer->GetGPUVirtualAddress() );

	CShaderResourceView* ppSRVs[3]{ };

	if ( mDiffuseMap )
	{
		ppSRVs[0] = mDiffuseMap->mShaderResourceView;
	}
	else ppSRVs[0] = mNullSrv;

	if ( mDiffuseLayerMap )
	{
		ppSRVs[1] = mDiffuseMap->mShaderResourceView;
	}
	else ppSRVs[1] = mNullSrv;

	if ( mNormalMap )
	{
		ppSRVs[2] = mNormalMap->mShaderResourceView;
	}
	else ppSRVs[2] = mNullSrv;

	deviceContext.SetGraphicsRootShaderResource( ( int )Slot_3D_Textures, ARRAYSIZE( ppSRVs ), ppSRVs );
}

Material::Material( String^ xName ) : Asset( xName )
{
	{
		auto lock = mLocker.Lock();
		mLockIndex = Lock( this );
		mLastGeneration = mGeneration;
	}

	mConstantBuffer = HeapAllocator::Alloc( sizeof( Material_Constants ) ).Detach();
	mReflectionData = new Material_Reflection();
	mConstantData = new Material_Constants();

	*mConstantData = { };
	Assign( mConstantData->TexWorld, Matrix4x4::Identity );
	mConstantData->Color = { 1.0f, 1.0f, 1.0f, 1.0f };

	mReflectionData->Ambient = 1.0f;
	mReflectionData->Diffuse = 1.0f;
	mReflectionData->Specular = 1.0f;
	mReflectionData->SpecExp = 32.0f;

	UpdateConstants();
	UpdateReflection();
}

Material::~Material()
{
	this->!Material();
}

Material::!Material()
{
	if ( !mDisposed )
	{
		auto lock = mLocker.Lock();
		mLocked[mLockIndex] = false;
		mQueue.push( mLockIndex );
	}

	if ( mConstantBuffer )
	{
		mConstantBuffer->Release();
		mConstantBuffer = nullptr;
	}

	if ( mReflectionData )
	{
		delete mReflectionData;
		mReflectionData = nullptr;
	}

	if ( mConstantData )
	{
		delete mConstantData;
		mConstantData = nullptr;
	}
}

void Material::Freeze()
{
	mFreezed = true;
}

bool Material::IsFreezed::get()
{
	return mFreezed;
}

System::Drawing::Color Material::Color::get()
{
	System::Drawing::Color left;
	Assign( left, mConstantData->Color );
	return left;
}

void Material::Color::set( System::Drawing::Color value )
{
	Assign( mConstantData->Color, value );
	UpdateConstants();
}

float Material::Ambient::get()
{
	return mReflectionData->Ambient;
}

void Material::Ambient::set( float value )
{
	if ( IsFreezed ) throw gcnew System::AccessViolationException( "Material 개체가 동결되었습니다. 값을 수정하는 것은 접근 위반에 해당합니다." );
	mReflectionData->Ambient = value;
	UpdateReflection();
}

float Material::Diffuse::get()
{
	return mReflectionData->Diffuse;
}

void Material::Diffuse::set( float value )
{
	if ( IsFreezed ) throw gcnew System::AccessViolationException( "Material 개체가 동결되었습니다. 값을 수정하는 것은 접근 위반에 해당합니다." );
	mReflectionData->Diffuse = value;
	UpdateReflection();
}

float Material::Specular::get()
{
	return mReflectionData->Specular;
}

void Material::Specular::set( float value )
{
	if ( IsFreezed ) throw gcnew System::AccessViolationException( "Material 개체가 동결되었습니다. 값을 수정하는 것은 접근 위반에 해당합니다." );
	mReflectionData->Specular = value;
	UpdateReflection();
}

float Material::SpecExp::get()
{
	return mReflectionData->SpecExp;
}

void Material::SpecExp::set( float value )
{
	if ( IsFreezed ) throw gcnew System::AccessViolationException( "Material 개체가 동결되었습니다. 값을 수정하는 것은 접근 위반에 해당합니다." );
	mReflectionData->SpecExp = value;
	UpdateReflection();
}

Texture2D^ Material::DiffuseMap::get()
{
	return mDiffuseMap;
}

void Material::DiffuseMap::set( Texture2D^ value )
{
	if ( IsFreezed ) throw gcnew System::AccessViolationException( "Material 개체가 동결되었습니다. 값을 수정하는 것은 접근 위반에 해당합니다." );
	if ( ( mDiffuseMap != nullptr ) != ( value != nullptr ) )
	{
		mConstantData->DiffuseMap += ( value != nullptr ) ? 1 : -1;
	}

	mDiffuseMap = value;
	UpdateConstants();
}

Texture2D^ Material::DiffuseLayerMap::get()
{
	return mDiffuseLayerMap;
}

void Material::DiffuseLayerMap::set( Texture2D^ value )
{
	if ( IsFreezed ) throw gcnew System::AccessViolationException( "Material 개체가 동결되었습니다. 값을 수정하는 것은 접근 위반에 해당합니다." );
	if ( ( mDiffuseLayerMap != nullptr ) != ( value != nullptr ) )
	{
		mConstantData->DiffuseMap += ( value != nullptr ) ? 1 : -1;
	}

	mDiffuseLayerMap = value;
	UpdateConstants();
}

Texture2D^ Material::NormalMap::get()
{
	return mNormalMap;
}

void Material::NormalMap::set( Texture2D^ value )
{
	if ( IsFreezed ) throw gcnew System::AccessViolationException( "Material 개체가 동결되었습니다. 값을 수정하는 것은 접근 위반에 해당합니다." );

	mConstantData->NormalMap = ( value != nullptr );
	mNormalMap = value;
	UpdateConstants();
}

Matrix3x2 Material::Transform::get()
{
	Matrix3x2 transform;
	Assign( transform, mConstantData->TexWorld );
	return transform;
}

void Material::Transform::set( Matrix3x2 value )
{
	if ( IsFreezed ) throw gcnew System::AccessViolationException( "Material 개체가 동결되었습니다. 값을 수정하는 것은 접근 위반에 해당합니다." );

	Assign( mConstantData->TexWorld, value );
	UpdateConstants();
}