#pragma once

namespace SC::Game
{
	/// <summary>
	/// 게임 개체에 포함되는 확장 구성 요소에 대한 기본 함수를 제공합니다.
	/// </summary>
	public ref class Component abstract : public System::ICloneable
	{
	internal:
		GameObject^ mGameObject;

	protected:
		/// <summary>
		/// <see cref="Component"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		Component();

	public:
		/// <summary>
		/// (<see cref="System::ICloneable"/> 인터페이스에서 구현 됨.) 해당 컴포넌트의 완전 복사본을 생성하여 반환합니다. 재정의하지 않을 경우 <see cref="System::Object::MemberwiseClone"/> 기본 함수가 사용됩니다.
		/// </summary>
		virtual System::Object^ Clone();

		/// <summary>
		/// 연결된 개체에 확장 컴포넌트를 추가합니다.
		/// </summary>
		/// <typeparam name="T"> 추가할 확장 컴포넌트 클래스 타입을 전달합니다. 이 클래스는 Component 클래스를 상속 받아야 합니다. </typeparam>
		/// <returns> 컴포넌트 추가에 성공하였을 경우 추가된 컴포넌트를, 그렇지 않을 경우 null을 반환합니다. </returns>
		generic< class T > where T : Component, gcnew()
			T AddComponent();

		/// <summary>
		/// 연결된 개체에 포함된 확장 컴포넌트를 가져옵니다.
		/// </summary>
		/// <typeparam name="T"> 가져올 확장 컴포넌트 클래스 타입을 전달합니다. 이 클래스는 Component 클래스를 상속 받아야 합니다. </typeparam>
		/// <returns> 컴포넌트가 존재할 경우 컴포넌트 개체를, 그렇지 않을 경우 null을 반환합니다. </returns>
		generic< class T > where T : Component
			T GetComponent();

		/// <summary>
		/// 연결된 개체에 포함된 확장 컴포넌트를 제거합니다.
		/// </summary>
		/// <typeparam name="T"> 제거할 확장 컴포넌트 클래스 타입을 전달합니다. 이 클래스는 Component 클래스를 상속 받아야 합니다. </typeparam>
		/// <returns> 컴포넌트 제거에 성공하였을 경우 <c>true</c>를, 그렇지 않을 경우 <c>false</c>를 반환합니다. </returns>
		generic< class T > where T : Component
			bool RemoveComponent();

		/// <summary>
		/// 깊이 우선 탐색 모드를 사용하여 연결된 개체를 포함한 하위 오브젝트에서 가장 처음으로 발견하는 확장 컴포넌트를 가져옵니다.
		/// </summary>
		/// <typeparam name="T"> 가져올 확장 컴포넌트 클래스 타입을 전달합니다. 이 클래스는 Component 클래스를 상속 받아야 합니다. </typeparam>
		/// <returns> 컴포넌트가 모든 개체에서 하나 이상 존재할 경우 컴포넌트 개체를, 그렇지 않을 경우 null을 반환합니다. </returns>
		generic< class T > where T : Component
			T GetComponentInChildren();

		/// <summary>
		/// 연결된 개체를 포함한 하위 오브젝트에서 발견하는 모든 확장 컴포넌트를 가져옵니다.
		/// </summary>
		/// <typeparam name="T"> 가져올 확장 컴포넌트 클래스 타입을 전달합니다. 이 클래스는 Component 클래스를 상속 받아야 합니다. </typeparam>
		/// <returns> 컴포넌트가 모든 개체에서 하나 이상 존재할 경우 컴포넌트 개체 목록을, 그렇지 않을 경우 null을 반환합니다. </returns>
		generic< class T > where T : Component
			System::Collections::Generic::IList<T>^ GetComponentsInChildren();

		/// <summary>
		/// 연결된 개체를 가져옵니다.
		/// </summary>
		property GameObject^ Object
		{
			Game::GameObject^ get();
		}

		/// <summary>
		/// 연결된 개체의 식별 이름을 가져옵니다.
		/// </summary>
		property System::String^ Name
		{
			System::String^ get();
		}

		/// <summary>
		/// 연결된 개체의 변환 개체를 가져옵니다.
		/// </summary>
		property Game::Transform^ Transform
		{
			Game::Transform^ get();
		}
	};
}