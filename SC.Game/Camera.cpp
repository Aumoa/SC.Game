using namespace SC;
using namespace SC::Game;

using namespace System;
using namespace System::Drawing;
using namespace System::Numerics;

using namespace std;

void Camera::Update()
{
	if ( Transform->IsUpdated || mUpdated )
	{
		float asp = mAspectRatio;
		if ( asp == 0 )
		{
			asp = ( float )Application::mWidth / ( float )Application::mHeight;
		}

		auto rot = Transform->Rotation;

		auto eye = Transform->Position;
		auto dir = Vector3::Transform( Vector3::UnitZ, rot );
		auto up = Vector3::Transform( Vector3::UnitY, rot );

		auto view = LookToLH( eye, dir, up );
		Matrix4x4 viewInv; Matrix4x4::Invert( view, viewInv );
		auto proj = PerspectiveFovLH( 0.25f * 3.14f, asp, mMaxDepth * 0.0001f, mMaxDepth );
		Matrix4x4 projInv; Matrix4x4::Invert( proj, projInv );
		auto viewproj = Matrix4x4::Multiply( view, proj );

		Assign( mFrameResource->ViewProj, viewproj );
		Assign( mFrameResource->ViewInv, viewInv );
		Assign( mFrameResource->ProjInv, projInv );
		Assign( mFrameResource->Pos, Transform->Position );

		auto block = mConstantBuffer->Map();
		memcpy( block, mFrameResource, sizeof( *mFrameResource ) );
		mConstantBuffer->Unmap();

		mUpdated = false;
	}
}

Camera::Camera() : Component()
{
	mConstantBuffer = HeapAllocator::Alloc( sizeof( Camera_Constants ) ).Detach();
	mFrameResource = new Camera_Constants();

	mPlanes = gcnew cli::array<Plane>( 6 );
}

Camera::~Camera()
{
	this->!Camera();
}

Camera::!Camera()
{
	if ( mConstantBuffer )
	{
		ComPtr<IUnknown> pUnknown;
		pUnknown.Attach( mConstantBuffer );
		App::GCAdd( move( pUnknown ) );
	}

	if ( mFrameResource )
	{
		delete mFrameResource;
		mFrameResource = nullptr;
	}

	if ( mPlanes )
	{
		delete mPlanes;
		mPlanes = nullptr;
	}
}

Object^ Camera::Clone()
{
	auto clone = gcnew Camera();
	*clone->mFrameResource = *mFrameResource;
	mPlanes->CopyTo( clone->mPlanes, 0 );
	clone->mAspectRatio = mAspectRatio;
	clone->mMaxDepth = mMaxDepth;
	return clone;
}

Ray Camera::ScreenPointToRay( Point screenPoint )
{
	auto world = Transform->World;
	Matrix4x4 worldInv;
	Matrix4x4::Invert( world, worldInv );
	Matrix4x4::Invert( world, worldInv );

	float asp = mAspectRatio;
	if ( asp == 0 )
	{
		asp = ( float )Application::mWidth / ( float )Application::mHeight;
	}

	auto view = worldInv;
	auto viewInv = world;
	auto proj = PerspectiveFovLH( 0.25f * 3.14f, asp, mMaxDepth * 0.0001f, mMaxDepth );

	Vector3 viewSpace;
	viewSpace.X = ( ( ( float )screenPoint.X / ( float )Application::mWidth ) * 2.0f - 1.0f - proj.M31 ) / proj.M11;
	viewSpace.Y = ( ( ( float )screenPoint.Y / ( float )Application::mHeight ) * -2.0f + 1.0f - proj.M32 ) / proj.M22;
	viewSpace.Z = 1.0;

	Vector3 dir;
	Vector3 org;

	dir.X = viewSpace.X * viewInv.M11 + viewSpace.Y * viewInv.M21 + viewSpace.Z * viewInv.M31;
	dir.Y = viewSpace.X * viewInv.M12 + viewSpace.Y * viewInv.M22 + viewSpace.Z * viewInv.M32;
	dir.Z = viewSpace.X * viewInv.M13 + viewSpace.Y * viewInv.M23 + viewSpace.Z * viewInv.M33;

	org.X = viewInv.M41;
	org.Y = viewInv.M42;
	org.Z = viewInv.M43;

	Ray ray;
	ray.Origin = org;
	ray.Direction = Vector3::Normalize( dir );
	ray.MaxDepth = mMaxDepth;

	return ray;
}

float Camera::AspectRatio::get()
{
	return mAspectRatio;
}

void Camera::AspectRatio::set( float value )
{
	mAspectRatio = value;
	mUpdated = true;
}

Texture2D^ Camera::Skybox::get()
{
	return mSkyboxTexture;
}

void Camera::Skybox::set( Texture2D^ value )
{
	mSkyboxTexture = value;
}