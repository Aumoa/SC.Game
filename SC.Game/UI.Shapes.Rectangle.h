#pragma once

namespace SC::Game::UI::Shapes
{
	/// <summary>
	/// �簢�� ����� ǥ���ϴ� UI ����Դϴ�.
	/// </summary>
	public ref class Rectangle : public Shape
	{
		Heap* mShaderInfoHeap = nullptr;

	protected:
		/// <summary>
		/// (<see cref="Element"/> Ŭ�������� ��� ��.) ��Ҹ� �����մϴ�.
		/// </summary>
		/// <param name="clientRect"> �θ��� ������ �簢 ������ ���޵˴ϴ�. </param>
		System::Drawing::RectangleF OnUpdate( System::Drawing::RectangleF clientRect ) override;

	internal:
		void Render( CDeviceContext& deviceContext ) override;

	public:
		/// <summary>
		/// <see cref="Rectangle"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="xName"> ��ü �̸��� �����մϴ�. </param>
		Rectangle( System::String^ xName );
		~Rectangle();
		!Rectangle();
	};
}