#pragma once

namespace SC::Game::UI
{
	struct alignas( 256 ) Brush_Constants
	{
		int Type;
		float Opacity;
		float padding[2];
		float Attribute0[4];
		float Attribute1[4];
	};

	/// <summary>
	/// 그래픽 개체를 그리는 데 사용할 개체를 정의합니다. 파생된 클래스는 영역을 그리는 방법을 설명합니다.
	/// </summary>
	public ref class Brush
	{
		bool mFreezed = false;

	internal:
		Heap* mConstantBuffer = nullptr;
		Brush_Constants* mConstants = nullptr;

	internal:
		Brush( int type );

		void UpdateBuffer();

	public:
		~Brush();
		!Brush();

		/// <summary>
		/// 해당 개체를 동결합니다. 속성을 변경할 수 없습니다.
		/// </summary>
		void Freeze();

		/// <summary> 
		/// 브러시 개체의 투명도를 설정하거나 가져옵니다.
		/// </summary>
		property float Opacity
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// 해당 개체가 동결되었는지 여부를 나타내는 값을 가져옵니다.
		/// </summary>
		property bool IsFreezed
		{
			bool get();
		}
	};
}