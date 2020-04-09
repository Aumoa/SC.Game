#pragma once

namespace SC::Game::UI
{
	/// <summary>
	/// �ܻ����� ������ �׸��ϴ�.
	/// </summary>
	public ref class SolidColorBrush : public Brush
	{
	public:
		/// <summary>
		/// <see cref="SolidColorBrush"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="color"> �귯���� ���� �����մϴ�. </param>
		SolidColorBrush( System::Drawing::Color color );

		/// <summary>
		/// �ܻ� �귯���� ���� �����ϰų� �����ɴϴ�.
		/// </summary>
		property System::Drawing::Color Color
		{
			System::Drawing::Color get();
			void set( System::Drawing::Color value );
		}
	};
}