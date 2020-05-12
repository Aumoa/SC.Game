#pragma once

namespace FbxSDK
{
	/// <summary>
	/// ������ ǥ���մϴ�.
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
		/// �ֺ��� �׸� ���� ����� �����ɴϴ�.
		/// </summary>
		property float Ambient
		{
			float get();
		}

		/// <summary>
		/// �л걤 �׸� ���� ����� �����ɴϴ�.
		/// </summary>
		property float Diffuse
		{
			float get();
		}

		/// <summary>
		/// ���ݻ籤 �׸� ���� ����� �����ɴϴ�.
		/// </summary>
		property float Specular
		{
			float get();
		}

		/// <summary>
		/// ���ݻ籤 �׸��� ��¦�� ����� �����ɴϴ�.
		/// </summary>
		property float Shininess
		{
			float get();
		}

		/// <summary>
		/// �л걤 �⺻ ���� �����ɴϴ�.
		/// </summary>
		property System::Drawing::Color DiffuseColor
		{
			System::Drawing::Color get();
		}

		/// <summary>
		/// �л걤 �ؽ�ó�� �����ɴϴ�.
		/// </summary>
		property System::String^ DiffuseMap
		{
			System::String^ get();
		}

		/// <summary>
		/// �븻 �ؽ�ó�� �����ɴϴ�.
		/// </summary>
		property System::String^ NormalMap
		{
			System::String^ get();
		}
	};
}