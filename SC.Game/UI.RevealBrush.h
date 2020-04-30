#pragma once

namespace SC::Game::UI
{
	/// <summary>
	/// 커서의 위치에 따라 이동하는 그라디언트 타원으로 영역을 그립니다.
	/// </summary>
	public ref class RevealBrush : public Brush
	{
	public:
		/// <summary>
		/// <see cref="RevealBrush"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="color"> 브러시의 색을 설정합니다. </param>
		RevealBrush( System::Drawing::Color color );

		/// <summary>
		/// 브러시의 색을 설정하거나 가져옵니다.
		/// </summary>
		property System::Drawing::Color Color
		{
			System::Drawing::Color get();
			void set( System::Drawing::Color value );
		}

		/// <summary>
		/// 브러시가 나타나는 거리를 설정하거나 가져옵니다.
		/// </summary>
		property float Distance
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// 브러시의 최소 불투명도를 설정하거나 가져옵니다.
		/// </summary>
		property float MinOpacity
		{
			float get();
			void set( float value );
		}
	};
}