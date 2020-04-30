#pragma once

namespace SC::Game::UI
{
	/// <summary>
	/// 이미지를 표시하는 UI 요소입니다.
	/// </summary>
	public ref class Image : public Element
	{
		Texture2D^ mSource;
		float mOpacity = 1.0f;
		Heap* mShaderInfoHeap = nullptr;

	protected:
		/// <summary>
		/// (<see cref="Element"/> 클래스에서 상속 됨.) 요소가 갱신될 때 호출되는 함수입니다.
		/// </summary>
		/// <param name="clientRect"> 부모 요소의 컨텐츠 렌더링 영역이 전달됩니다. </param>
		/// <returns> 해당 요소의 실제 렌더링 영역을 반환합니다. </returns>
		System::Drawing::RectangleF OnUpdate( System::Drawing::RectangleF clientRect ) override;

	internal:
		void Render( CDeviceContext& deviceContext ) override;

	public:
		/// <summary>
		/// <see cref="Image"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="xName"> 개체의 참조 이름을 전달합니다. </param>
		Image( System::String^ xName );
		~Image();
		!Image();

		/// <summary>
		/// 이미지 원본 개체를 설정하거나 가져옵니다.
		/// </summary>
		property Texture2D^ Source
		{
			Texture2D^ get();
			void set( Texture2D^ value );
		}

		/// <summary>
		/// 이미지 렌더링 불투명도를 설정하거나 가져옵니다.
		/// </summary>
		property float Opacity
		{
			float get();
			void set( float value );
		}
	};
}