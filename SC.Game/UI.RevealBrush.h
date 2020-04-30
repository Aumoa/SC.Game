#pragma once

namespace SC::Game::UI
{
	/// <summary>
	/// Ŀ���� ��ġ�� ���� �̵��ϴ� �׶���Ʈ Ÿ������ ������ �׸��ϴ�.
	/// </summary>
	public ref class RevealBrush : public Brush
	{
	public:
		/// <summary>
		/// <see cref="RevealBrush"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="color"> �귯���� ���� �����մϴ�. </param>
		RevealBrush( System::Drawing::Color color );

		/// <summary>
		/// �귯���� ���� �����ϰų� �����ɴϴ�.
		/// </summary>
		property System::Drawing::Color Color
		{
			System::Drawing::Color get();
			void set( System::Drawing::Color value );
		}

		/// <summary>
		/// �귯�ð� ��Ÿ���� �Ÿ��� �����ϰų� �����ɴϴ�.
		/// </summary>
		property float Distance
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// �귯���� �ּ� �������� �����ϰų� �����ɴϴ�.
		/// </summary>
		property float MinOpacity
		{
			float get();
			void set( float value );
		}
	};
}