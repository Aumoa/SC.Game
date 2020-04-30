#pragma once

namespace SC::Game::UI
{
	/// <summary>
	/// �̹����� ǥ���ϴ� UI ����Դϴ�.
	/// </summary>
	public ref class Image : public Element
	{
		Texture2D^ mSource;
		float mOpacity = 1.0f;
		Heap* mShaderInfoHeap = nullptr;

	protected:
		/// <summary>
		/// (<see cref="Element"/> Ŭ�������� ��� ��.) ��Ұ� ���ŵ� �� ȣ��Ǵ� �Լ��Դϴ�.
		/// </summary>
		/// <param name="clientRect"> �θ� ����� ������ ������ ������ ���޵˴ϴ�. </param>
		/// <returns> �ش� ����� ���� ������ ������ ��ȯ�մϴ�. </returns>
		System::Drawing::RectangleF OnUpdate( System::Drawing::RectangleF clientRect ) override;

	internal:
		void Render( CDeviceContext& deviceContext ) override;

	public:
		/// <summary>
		/// <see cref="Image"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="xName"> ��ü�� ���� �̸��� �����մϴ�. </param>
		Image( System::String^ xName );
		~Image();
		!Image();

		/// <summary>
		/// �̹��� ���� ��ü�� �����ϰų� �����ɴϴ�.
		/// </summary>
		property Texture2D^ Source
		{
			Texture2D^ get();
			void set( Texture2D^ value );
		}

		/// <summary>
		/// �̹��� ������ �������� �����ϰų� �����ɴϴ�.
		/// </summary>
		property float Opacity
		{
			float get();
			void set( float value );
		}
	};
}