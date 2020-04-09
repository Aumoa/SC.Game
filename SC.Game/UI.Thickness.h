#pragma once

namespace SC::Game::UI
{
	/// <summary>
	/// 사각형 프레임의 두께를 표현합니다.
	/// </summary>
	public value struct Thickness : public System::IEquatable<Thickness>, System::IComparable<Thickness>
	{
		/// <summary>
		/// 왼쪽 두께를 설정합니다.
		/// </summary>
		float Left;

		/// <summary>
		/// 위쪽 두께를 설정합니다.
		/// </summary>
		float Top;

		/// <summary>
		/// 오른쪽 두께를 설정합니다.
		/// </summary>
		float Right;

		/// <summary>
		/// 아래쪽 두께를 설정합니다.
		/// </summary>
		float Bottom;

		/// <summary>
		/// 한 가지 값으로 채워서 <see cref="Thickness"/> 구조체의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="value"> 값을 전달합니다. </param>
		Thickness( float value )
		{
			Left = value;
			Top = value;
			Right = value;
			Bottom = value;
		}

		/// <summary>
		/// 수평과 수직 값을 채워서 <see cref="Thickness"/> 구조체의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="horz"> 수평 값을 전달합니다. </param>
		/// <param name="vert"> 수직 값을 전달합니다. </param>
		Thickness( float horz, float vert )
		{
			Left = horz;
			Right = horz;
			Top = vert;
			Bottom = vert;
		}

		/// <summary>
		/// <see cref="Thickness"/> 구조체의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="left"> 왼쪽 두께를 전달합니다. </param>
		/// <param name="top"> 위쪽 두께를 전달합니다. </param>
		/// <param name="right"> 오른쪽 두께를 전달합니다. </param>
		/// <param name="bottom"> 아래쪽 두께를 전달합니다. </param>
		Thickness( float left, float top, float right, float bottom )
		{
			Left = left;
			Top = top;
			Right = right;
			Bottom = bottom;
		}

		/// <summary>
		/// (<see cref="System::Object"/> 클래스에서 상속 됨.) 해당 개체의 텍스트 표현을 가져옵니다.
		/// </summary>
		System::String^ ToString() override
		{
			return System::String::Format( "({0}, {1}, {2}, {3})", Left, Top, Right, Bottom );
		}

		/// <summary>
		/// (<see cref="System::Object"/> 클래스에서 상속 됨.) 두 개체가 같은지 비교합니다.
		/// </summary>
		/// <param name="right"> 비교할 개체를 전달합니다. </param>
		bool Equals( System::Object^ right ) override
		{
			if ( right && right->GetType() == Thickness::typeid )
			{
				return Equals( ( Thickness )right );
			}
			else
			{
				return false;
			}
		}

		/// <summary>
		/// (<see cref="System::IEquatable"/> 인터페이스에서 구현 됨.) 두 개체가 같은지 비교합니다.
		/// </summary>
		/// <param name="right"> 비교할 개체를 전달합니다. </param>
		virtual bool Equals( Thickness right )
		{
			return Left == right.Left
				&& Top == right.Top
				&& Right == right.Right
				&& Bottom == right.Bottom;
		}

		/// <summary>
		/// (<see cref="System::IComparable"/> 인터페이스에서 구현 됨.) 두 개체를 사전순으로 비교합니다.
		/// </summary>
		/// <param name="right"> 비교할 개체를 전달합니다. </param>
		virtual int CompareTo( Thickness right )
		{
			if ( Left == right.Left )
				if ( Top == right.Top )
					if ( Right == right.Right )
						if ( Bottom == right.Bottom )
							return 0;
						else
							return Bottom < right.Bottom ? -1 : 1;
					else
						return Right < right.Right ? -1 : 1;
				else
					return Top < right.Top ? -1 : 1;
			else
				return Left < right.Left ? -1 : 1;
		}

		/// <summary>
		/// 두께의 수평 크기를 가져옵니다.
		/// </summary>
		property float Width
		{
			float get()
			{
				return Left + Right;
			}
		}

		/// <summary>
		/// 두께의 수직 크기를 가져옵니다.
		/// </summary>
		property float Height
		{
			float get()
			{
				return Top + Bottom;
			}
		}
	};
}