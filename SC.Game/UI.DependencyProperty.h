#pragma once

namespace SC::Game::UI
{
	/// <summary> 
	/// 의존 관계가 필요한 속성 설정을 수행합니다.
	/// </summary>
	public value struct DependencyProperty : public System::IEquatable<DependencyProperty>
	{
		/// <summary>
		/// 의존 대상 클래스 이름의 해시 값을 설정합니다.
		/// </summary>
		int ClassName;

		/// <summary>
		/// 의존 대상 클래스의 속성 이름 해시 값을 설정합니다.
		/// </summary>
		int PropertyName;

		/// <summary>
		/// 의존 대상 클래스의 속성 값을 설정합니다.
		/// </summary>
		System::String^ Value;

		/// <summary>
		/// <see cref="DependencyProperty"/> 구조체의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="hyperText"> 구문 텍스트를 <c>"ClassName.PropertyName=Value"</c> 형식으로 제공합니다. </param>
		DependencyProperty( System::String^ hyperText )
		{
			auto firstDot = hyperText->IndexOf( L'.' );
			auto secondDot = hyperText->IndexOf( L'=' );

#if defined( _DEBUG )
			if ( firstDot == -1 || secondDot == -1 )
			{
				throw gcnew System::ArgumentException( "SC.Game.UI.DependencyProperty(): 올바르지 않은 구문 텍스트입니다." );
			}
#endif

			auto className = hyperText->Substring( 0, firstDot )->ToLower();
			auto propertyName = hyperText->Substring( firstDot + 1, secondDot - firstDot - 1 )->ToLower();
			auto value = hyperText->Substring( secondDot + 1 );

			this->ClassName = className->GetHashCode();
			this->PropertyName = propertyName->GetHashCode();
			this->Value = value;
		}

		/// <summary>
		/// <see cref="DependencyProperty"/> 구조체의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="className"> 클래스 이름을 전달합니다. </param>
		/// <param name="propertyName"> 속성 이름을 전달합니다. </param>
		/// <param name="value"> 값을 전달합니다. </param>
		DependencyProperty( System::String^ className, System::String^ propertyName, System::String^ value )
		{
			className = className->ToLower();
			propertyName = propertyName->ToLower();

			ClassName = className->GetHashCode();
			PropertyName = propertyName->GetHashCode();
			Value = value;
		}

		/// <summary>
		/// <see cref="DependencyProperty"/> 구조체의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="className"> 클래스 이름의 해시 코드를 전달합니다. </param>
		/// <param name="propertyName"> 속성 이름의 해시 코드를 전달합니다. </param>
		/// <param name="value"> 값을 전달합니다. </param>
		DependencyProperty( int className, int propertyName, System::String^ value )
		{
			ClassName = className;
			PropertyName = propertyName;
			Value = value;
		}

		/// <summary>
		/// (<see cref="System::Object"/> 클래스에서 상속 됨.) 두 개체가 같은지 비교합니다.
		/// </summary>
		/// <param name="right"> 비교할 개체를 전달합니다. </param>
		bool Equals( System::Object^ right ) override
		{
			if ( right && right->GetType() == DependencyProperty::typeid )
			{
				return Equals( ( DependencyProperty )right );
			}
			else
			{
				return false;
			}
		}

		/// <summary>
		/// (<see cref="System::IEquatable"/> 인터페이스에서 구현 됨.) 두 개체가 같은지 비교합니다.
		/// </summary>
		/// <param name="right"> 비교할 개체를 전달합니다. </param>
		virtual bool Equals( DependencyProperty right )
		{
			return ClassName == right.ClassName
				&& PropertyName == right.PropertyName
				&& Value == right.Value;
		}
	};
}