#pragma once

namespace SC::Game
{
	/// <summary>
	/// 계층 구조 뼈대를 표현합니다. 이 클래스는 상속될 수 없습니다.
	/// </summary>
	public ref class Bone sealed : public Component
	{
		System::String^ mName;
		int mIndex = 0;

	public:
		/// <summary>
		/// <see cref="Bone"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		Bone();

		/// <summary>
		/// (<see cref="Component"/> 클래스에서 상속 됨.) 해당 컴포넌트의 완전 복사본을 생성하여 반환합니다.
		/// </summary>
		System::Object^ Clone() override;

		/// <summary>
		/// 뼈대의 이름을 설정하거나 가져옵니다.
		/// </summary>
		property System::String^ Name
		{
			System::String^ get();
			void set( System::String^ value );
		}

		/// <summary>
		/// 뼈대의 색인 번호를 설정하거나 가져옵니다.
		/// </summary>
		property int Index
		{
			int get();
			void set( int value );
		}
	};
}