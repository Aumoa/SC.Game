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
	/// 렌더링 표면 재질에 대한 기본 함수를 제공합니다. 이 클래스는 상속될 수 없습니다.
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
		/// <see cref="Material"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="xName"> 데이터 자산의 식별자 이름을 전달합니다. </param>
		Material( System::String^ xName );
		~Material();
		!Material();

		/// <summary>
		/// 해당 개체를 동결합니다. 속성을 변경할 수 없습니다.
		/// </summary>
		void Freeze();

		/// <summary>
		/// 해당 개체가 동결되었는지 나타내는 값을 가져옵니다.
		/// </summary>
		property bool IsFreezed
		{
			bool get();
		}

		/// <summary>
		/// 표면의 주변광 색상을 설정하거나 가져옵니다.
		/// </summary>
		property System::Drawing::Color Color
		{
			System::Drawing::Color get();
			void set( System::Drawing::Color value );
		}

		/// <summary>
		/// 표면의 주변광 반사 정도를 설정하거나 가져옵니다.
		/// </summary>
		property float Ambient
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// 표면의 분산광 반사 정도를 설정하거나 가져옵니다.
		/// </summary>
		property float Diffuse
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// 표면의 반영광 반사 정도를 설정하거나 가져옵니다.
		/// </summary>
		property float Specular
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// 표면의 반영광 반사 세기를 설정하거나 가져옵니다.
		/// </summary>
		property float SpecExp
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// 표면의 분산광 반사 정도를 나타내는 텍스처 개체를 설정하거나 가져옵니다.
		/// </summary>
		property Texture2D^ DiffuseMap
		{
			Texture2D^ get();
			void set( Texture2D^ value );
		}

		/// <summary>
		/// 표면의 분산광 반사 정도의 레이어를 나타내는 텍스처 개체를 설정하거나 가져옵니다.
		/// </summary>
		property Texture2D^ DiffuseLayerMap
		{
			Texture2D^ get();
			void set( Texture2D^ value );
		}

		/// <summary>
		/// 표면의 방향의 디테일을 나타내는 텍스처 개체를 설정하거나 가져옵니다.
		/// </summary>
		property Texture2D^ NormalMap
		{
			Texture2D^ get();
			void set( Texture2D^ value );
		}

		/// <summary>
		/// 텍스처 추출 위치를 설정하거나 가져옵니다.
		/// </summary>
		property System::Numerics::Matrix3x2 Transform
		{
			System::Numerics::Matrix3x2 get();
			void set( System::Numerics::Matrix3x2 value );
		}
	};
}