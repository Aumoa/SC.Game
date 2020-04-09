#pragma once

namespace SC::Game::UI
{
	/// <summary> 
	/// ���� ���谡 �ʿ��� �Ӽ� ������ �����մϴ�.
	/// </summary>
	public value struct DependencyProperty : public System::IEquatable<DependencyProperty>
	{
		/// <summary>
		/// ���� ��� Ŭ���� �̸��� �ؽ� ���� �����մϴ�.
		/// </summary>
		int ClassName;

		/// <summary>
		/// ���� ��� Ŭ������ �Ӽ� �̸� �ؽ� ���� �����մϴ�.
		/// </summary>
		int PropertyName;

		/// <summary>
		/// ���� ��� Ŭ������ �Ӽ� ���� �����մϴ�.
		/// </summary>
		System::String^ Value;

		/// <summary>
		/// <see cref="DependencyProperty"/> ����ü�� �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="hyperText"> ���� �ؽ�Ʈ�� <c>"ClassName.PropertyName=Value"</c> �������� �����մϴ�. </param>
		DependencyProperty( System::String^ hyperText )
		{
			auto firstDot = hyperText->IndexOf( L'.' );
			auto secondDot = hyperText->IndexOf( L'=' );

#if defined( _DEBUG )
			if ( firstDot == -1 || secondDot == -1 )
			{
				throw gcnew System::ArgumentException( "SC.Game.UI.DependencyProperty(): �ùٸ��� ���� ���� �ؽ�Ʈ�Դϴ�." );
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
		/// <see cref="DependencyProperty"/> ����ü�� �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="className"> Ŭ���� �̸��� �����մϴ�. </param>
		/// <param name="propertyName"> �Ӽ� �̸��� �����մϴ�. </param>
		/// <param name="value"> ���� �����մϴ�. </param>
		DependencyProperty( System::String^ className, System::String^ propertyName, System::String^ value )
		{
			className = className->ToLower();
			propertyName = propertyName->ToLower();

			ClassName = className->GetHashCode();
			PropertyName = propertyName->GetHashCode();
			Value = value;
		}

		/// <summary>
		/// <see cref="DependencyProperty"/> ����ü�� �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="className"> Ŭ���� �̸��� �ؽ� �ڵ带 �����մϴ�. </param>
		/// <param name="propertyName"> �Ӽ� �̸��� �ؽ� �ڵ带 �����մϴ�. </param>
		/// <param name="value"> ���� �����մϴ�. </param>
		DependencyProperty( int className, int propertyName, System::String^ value )
		{
			ClassName = className;
			PropertyName = propertyName;
			Value = value;
		}

		/// <summary>
		/// (<see cref="System::Object"/> Ŭ�������� ��� ��.) �� ��ü�� ������ ���մϴ�.
		/// </summary>
		/// <param name="right"> ���� ��ü�� �����մϴ�. </param>
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
		/// (<see cref="System::IEquatable"/> �������̽����� ���� ��.) �� ��ü�� ������ ���մϴ�.
		/// </summary>
		/// <param name="right"> ���� ��ü�� �����մϴ�. </param>
		virtual bool Equals( DependencyProperty right )
		{
			return ClassName == right.ClassName
				&& PropertyName == right.PropertyName
				&& Value == right.Value;
		}
	};
}