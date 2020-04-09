#pragma once

namespace SC::Game::UI
{
	/// <summary>
	/// �簢�� �������� �β��� ǥ���մϴ�.
	/// </summary>
	public value struct Thickness : public System::IEquatable<Thickness>, System::IComparable<Thickness>
	{
		/// <summary>
		/// ���� �β��� �����մϴ�.
		/// </summary>
		float Left;

		/// <summary>
		/// ���� �β��� �����մϴ�.
		/// </summary>
		float Top;

		/// <summary>
		/// ������ �β��� �����մϴ�.
		/// </summary>
		float Right;

		/// <summary>
		/// �Ʒ��� �β��� �����մϴ�.
		/// </summary>
		float Bottom;

		/// <summary>
		/// �� ���� ������ ä���� <see cref="Thickness"/> ����ü�� �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="value"> ���� �����մϴ�. </param>
		Thickness( float value )
		{
			Left = value;
			Top = value;
			Right = value;
			Bottom = value;
		}

		/// <summary>
		/// ����� ���� ���� ä���� <see cref="Thickness"/> ����ü�� �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="horz"> ���� ���� �����մϴ�. </param>
		/// <param name="vert"> ���� ���� �����մϴ�. </param>
		Thickness( float horz, float vert )
		{
			Left = horz;
			Right = horz;
			Top = vert;
			Bottom = vert;
		}

		/// <summary>
		/// <see cref="Thickness"/> ����ü�� �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="left"> ���� �β��� �����մϴ�. </param>
		/// <param name="top"> ���� �β��� �����մϴ�. </param>
		/// <param name="right"> ������ �β��� �����մϴ�. </param>
		/// <param name="bottom"> �Ʒ��� �β��� �����մϴ�. </param>
		Thickness( float left, float top, float right, float bottom )
		{
			Left = left;
			Top = top;
			Right = right;
			Bottom = bottom;
		}

		/// <summary>
		/// (<see cref="System::Object"/> Ŭ�������� ��� ��.) �ش� ��ü�� �ؽ�Ʈ ǥ���� �����ɴϴ�.
		/// </summary>
		System::String^ ToString() override
		{
			return System::String::Format( "({0}, {1}, {2}, {3})", Left, Top, Right, Bottom );
		}

		/// <summary>
		/// (<see cref="System::Object"/> Ŭ�������� ��� ��.) �� ��ü�� ������ ���մϴ�.
		/// </summary>
		/// <param name="right"> ���� ��ü�� �����մϴ�. </param>
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
		/// (<see cref="System::IEquatable"/> �������̽����� ���� ��.) �� ��ü�� ������ ���մϴ�.
		/// </summary>
		/// <param name="right"> ���� ��ü�� �����մϴ�. </param>
		virtual bool Equals( Thickness right )
		{
			return Left == right.Left
				&& Top == right.Top
				&& Right == right.Right
				&& Bottom == right.Bottom;
		}

		/// <summary>
		/// (<see cref="System::IComparable"/> �������̽����� ���� ��.) �� ��ü�� ���������� ���մϴ�.
		/// </summary>
		/// <param name="right"> ���� ��ü�� �����մϴ�. </param>
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
		/// �β��� ���� ũ�⸦ �����ɴϴ�.
		/// </summary>
		property float Width
		{
			float get()
			{
				return Left + Right;
			}
		}

		/// <summary>
		/// �β��� ���� ũ�⸦ �����ɴϴ�.
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