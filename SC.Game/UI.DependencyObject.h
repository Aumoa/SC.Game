#pragma once

namespace SC::Game::UI
{
	/// <summary>
	/// 의존 관계에 의한 속성 시스템에 참여하는 모든 UI 개체에 대한 공통 함수를 제공합니다.
	/// </summary>
	public ref class DependencyObject
	{
	internal:
		using Items = System::Collections::Generic::Dictionary<int, System::String^>;
		using Classes = System::Collections::Generic::Dictionary<int, Items^>;

		Classes^ mProperties;

	protected:
		/// <summary>
		/// <see cref="DependencyObject"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		DependencyObject();

	public:
		/// <summary> 새 의존 관계 속성을 추가합니다. </summary>
		/// <param name="value"> 속성 개체를 전달합니다. </param>
		void AddDependencyProperty( DependencyProperty value );

		/// <summary> 새 의존 관계 속성을 추가합니다. </summary>
		/// <param name="value"> 파싱 가능한 속성 텍스트를 전달합니다. </param>
		void AddDependencyProperty( System::String^ value )
		{
			return AddDependencyProperty( DependencyProperty( value ) );
		}

		/// <summary> 의존 관계 속성을 제거합니다. </summary>
		/// <param name="className"> 제거할 속성의 소유 클래스 이름을 전달합니다. </param>
		/// <param name="propertyName"> 제거할 속성의 이름을 전달합니다. </param>
		void RemoveDependencyProperty( int className, int propertyName );

		/// <summary> 의존 관계 속성을 제거합니다. </summary>
		/// <param name="className"> 제거할 속성의 소유 클래스 이름을 전달합니다. </param>
		void RemoveDependencyProperty( int className );
	};
}