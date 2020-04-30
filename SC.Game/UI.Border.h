#pragma once

namespace SC::Game::UI
{
	ref class Brush;

	/// <summary>
	/// UI ��ҿ��� ��踦 ǥ���մϴ�.
	/// </summary>
	public ref class Border : public Element
	{
		float mStrokeWidth = 0.0f;
		Thickness mPadding = Thickness( 0 );

		Brush^ mBrush;
		Heap* mHeap = nullptr;

	protected:
		/// <summary>
		/// (<see cref="Panel"/> Ŭ�������� ��� ��.) ��Ҹ� �����մϴ�. 
		/// </summary>
		/// <param name="clientRect"> �θ��� ������ �簢 ������ ���޵˴ϴ�. </param>
		System::Drawing::RectangleF OnUpdate( System::Drawing::RectangleF clientRect ) override;

	internal:
		void Render( CDeviceContext& deviceContext ) override;

	public:
		~Border();
		!Border();

		/// <summary>
		/// <see cref="Border"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="xName"> ��ü �̸��� �����մϴ�. </param>
		Border( System::String^ xName );

		/// <summary>
		/// ��� ������ ���⸦ �����ϰų� �����ɴϴ�.
		/// </summary>
		property float StrokeWidth
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// ��� ������ ���� ũ�⸦ �����ϰų� �����ɴϴ�.
		/// </summary>
		property Thickness Padding
		{
			Thickness get();
			void set( Thickness value );
		}

		/// <summary>
		/// �氳 ������ ĥ�� �귯�ø� �����ϰų� �����ɴϴ�.
		/// </summary>
		property Brush^ Fill
		{
			Brush^ get();
			void set( Brush^ value );
		}
	};
}