#pragma once

namespace FbxSDK
{
	/// <summary>
	/// 재질을 표현합니다.
	/// </summary>
	public ref class Material
	{
	internal:
		FbxSurfaceMaterial* mMaterial = nullptr;

		float mAmbient = 0.0f;
		float mDiffuse = 0.0f;
		float mSpecular = 0.0f;
		float mShininess = 0.0f;
		System::Drawing::Color mColor;

		System::String^ mDiffuseMap;
		System::String^ mNormalMap;

	internal:
		Material( FbxSurfaceMaterial* material );

	public:
		/// <summary>
		/// 주변광 항목에 대한 계수를 가져옵니다.
		/// </summary>
		property float Ambient
		{
			float get();
		}

		/// <summary>
		/// 분산광 항목에 대한 계수를 가져옵니다.
		/// </summary>
		property float Diffuse
		{
			float get();
		}

		/// <summary>
		/// 정반사광 항목에 대한 계수를 가져옵니다.
		/// </summary>
		property float Specular
		{
			float get();
		}

		/// <summary>
		/// 정반사광 항목의 반짝임 계수를 가져옵니다.
		/// </summary>
		property float Shininess
		{
			float get();
		}

		/// <summary>
		/// 분산광 기본 색을 가져옵니다.
		/// </summary>
		property System::Drawing::Color DiffuseColor
		{
			System::Drawing::Color get();
		}

		/// <summary>
		/// 분산광 텍스처를 가져옵니다.
		/// </summary>
		property System::String^ DiffuseMap
		{
			System::String^ get();
		}

		/// <summary>
		/// 노말 텍스처를 가져옵니다.
		/// </summary>
		property System::String^ NormalMap
		{
			System::String^ get();
		}
	};
}