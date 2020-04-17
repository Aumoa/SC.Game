#pragma once

namespace SC::Game
{
	struct Material_Constants
	{
		int Index;
		int DiffuseMap;
		int NormalMap;
		int AlphaClip;
		XMFLOAT4X4 TexWorld;
		XMFLOAT4 Color;
	};

	struct Material_Reflection
	{
		float Ambient;
		float Diffuse;
		float Specular;
		float SpecExp;
	};

	/// <summary>
	/// ������ ǥ�� ������ ���� �⺻ �Լ��� �����մϴ�. �� Ŭ������ ��ӵ� �� �����ϴ�.
	/// </summary>
	public ref class Material : public Asset
	{
	private:
		static int Lock( Material^ ptr );
		static void Realloc( int capacity );
		void UpdateReflection();
		void UpdateConstants();

	internal:
		static LargeHeap* mReflectionBuffer;
		static int mCapacity;
		static int mGeneration;
		static CShaderResourceView* mNullSrv;
		static Material^ mDefault;

		Heap* mConstantBuffer = nullptr;
		int mLockIndex = -1;

		Material_Reflection* mReflectionData = nullptr;
		Material_Constants* mConstantData = nullptr;

		Texture2D^ mDiffuseMap;
		Texture2D^ mDiffuseLayerMap;
		Texture2D^ mNormalMap;

		int mLastGeneration = 0;
		bool mFreezed = false;

	internal:
		static void Initialize();

		void SetConstantBuffer( CDeviceContext& deviceContext );

	public:
		/// <summary>
		/// <see cref="Material"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="xName"> ������ �ڻ��� �ĺ��� �̸��� �����մϴ�. </param>
		Material( System::String^ xName );
		~Material();
		!Material();

		/// <summary>
		/// �ش� ��ü�� �����մϴ�. �Ӽ��� ������ �� �����ϴ�.
		/// </summary>
		void Freeze();

		/// <summary>
		/// �ش� ��ü�� ����Ǿ����� ��Ÿ���� ���� �����ɴϴ�.
		/// </summary>
		property bool IsFreezed
		{
			bool get();
		}

		/// <summary>
		/// ǥ���� �ֺ��� ������ �����ϰų� �����ɴϴ�.
		/// </summary>
		property System::Drawing::Color Color
		{
			System::Drawing::Color get();
			void set( System::Drawing::Color value );
		}

		/// <summary>
		/// ǥ���� �ֺ��� �ݻ� ������ �����ϰų� �����ɴϴ�.
		/// </summary>
		property float Ambient
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// ǥ���� �л걤 �ݻ� ������ �����ϰų� �����ɴϴ�.
		/// </summary>
		property float Diffuse
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// ǥ���� �ݿ��� �ݻ� ������ �����ϰų� �����ɴϴ�.
		/// </summary>
		property float Specular
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// ǥ���� �ݿ��� �ݻ� ���⸦ �����ϰų� �����ɴϴ�.
		/// </summary>
		property float SpecExp
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// ǥ���� �л걤 �ݻ� ������ ��Ÿ���� �ؽ�ó ��ü�� �����ϰų� �����ɴϴ�.
		/// </summary>
		property Texture2D^ DiffuseMap
		{
			Texture2D^ get();
			void set( Texture2D^ value );
		}

		/// <summary>
		/// ǥ���� �л걤 �ݻ� ������ ���̾ ��Ÿ���� �ؽ�ó ��ü�� �����ϰų� �����ɴϴ�.
		/// </summary>
		property Texture2D^ DiffuseLayerMap
		{
			Texture2D^ get();
			void set( Texture2D^ value );
		}

		/// <summary>
		/// ǥ���� ������ �������� ��Ÿ���� �ؽ�ó ��ü�� �����ϰų� �����ɴϴ�.
		/// </summary>
		property Texture2D^ NormalMap
		{
			Texture2D^ get();
			void set( Texture2D^ value );
		}

		/// <summary>
		/// �ؽ�ó ���� ��ġ�� �����ϰų� �����ɴϴ�.
		/// </summary>
		property System::Numerics::Matrix3x2 Transform
		{
			System::Numerics::Matrix3x2 get();
			void set( System::Numerics::Matrix3x2 value );
		}
	};
}