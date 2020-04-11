#pragma once

namespace SC::Game
{
	/// <summary>
	/// <see cref="MeshFilter"/> 컴포넌트에서 지정된 메쉬 개체를 화면에 렌더링합니다. 이 클래스는 상속될 수 없습니다.
	/// </summary>
	public ref class MeshRenderer : public Component
	{
	internal:
		void Render( CDeviceContext& deviceContext );

	public:
		/// <summary>
		/// <see cref="MeshRenderer"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		MeshRenderer();

		/// <summary>
		/// (<see cref="Component"/> 클래스에서 상속 됨.) 해당 컴포넌트의 완전 복사본을 생성하여 반환합니다.
		/// </summary>
		System::Object^ Clone() override;
	};
}