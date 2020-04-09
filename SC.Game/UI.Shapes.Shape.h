#pragma once

namespace SC::Game::UI::Shapes
{
	/// <summary>
	/// ����� ǥ���ϴ� UI ��� ���� ���� ������ ��Ʈ�Դϴ�.
	/// </summary>
	public ref class Shape : public Element
	{
		Brush^ mBrush;

	internal:
		Shape( System::String^ xName );

	public:
		/// <summary>
		/// ����� ä��� �귯�ø� �����ϰų� �����ɴϴ�.
		/// </summary>
		property Brush^ Fill
		{
			Brush^ get();
			void set( Brush^ value );
		}
	};
}