using namespace FbxSDK;

using namespace System;
using namespace System::Drawing;
using namespace System::IO;

Material::Material( FbxSurfaceMaterial* material )
{
	auto materialId = material->GetClassId();

	if ( materialId.Is( FbxSurfacePhong::ClassId ) )
	{
		auto surfacePhong = ( FbxSurfacePhong* )material;
		mAmbient = ( float )surfacePhong->AmbientFactor;
		mDiffuse = ( float )surfacePhong->DiffuseFactor;
		mSpecular = ( float )surfacePhong->SpecularFactor;
		mShininess = ( float )surfacePhong->Shininess;
		FbxDouble3 diffuse = surfacePhong->Diffuse;
		mColor = Color::FromArgb( 255, ( int )( diffuse[0] * 255.0 ), ( int )( diffuse[1] * 255.0 ), ( int )( diffuse[2] * 255.0 ) );
	}
	else if ( materialId.Is( FbxSurfaceLambert::ClassId ) )
	{
		auto surfaceLambert = ( FbxSurfaceLambert* )material;
		mAmbient = ( float )surfaceLambert->AmbientFactor;
		mDiffuse = ( float )surfaceLambert->DiffuseFactor;
		FbxDouble3 diffuse = surfaceLambert->Diffuse;
		mColor = Color::FromArgb( 255, ( int )( diffuse[0] * 255.0 ), ( int )( diffuse[1] * 255.0 ), ( int )( diffuse[2] * 255.0 ) );
	}

	auto diffuseTexture = material->FindProperty( FbxSurfaceMaterial::sDiffuse );
	if ( diffuseTexture.IsValid() )
	{
		auto numTextures = diffuseTexture.GetSrcObjectCount<FbxFileTexture>();
		if ( numTextures != 0 )
		{
			auto fileTexture = diffuseTexture.GetSrcObject<FbxFileTexture>();
			mDiffuseMap = gcnew String( fileTexture->GetRelativeFileName() );
		}
	}

	auto normalTexture = material->FindProperty( FbxSurfaceMaterial::sNormalMap );
	if ( normalTexture.IsValid() )
	{
		auto numTextures = normalTexture.GetSrcObjectCount<FbxFileTexture>();
		if ( numTextures != 0 )
		{
			auto fileTexture = normalTexture.GetSrcObject<FbxFileTexture>();
			mNormalMap = gcnew String( fileTexture->GetRelativeFileName() );
		}
	}
}

float Material::Ambient::get()
{
	return mAmbient;
}

float Material::Diffuse::get()
{
	return mDiffuse;
}

float Material::Specular::get()
{
	return mSpecular;
}

float Material::Shininess::get()
{
	return mShininess;
}

Color Material::DiffuseColor::get()
{
	return mColor;
}

String^ Material::DiffuseMap::get()
{
	return mDiffuseMap;
}

String^ Material::NormalMap::get()
{
	return mNormalMap;
}