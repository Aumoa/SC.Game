#pragma once

namespace SC::Game::UI
{
	/// <summary>
	/// ���� ���迡 ���� �Ӽ� �ý��ۿ� �����ϴ� ��� UI ��ü�� ���� ���� �Լ��� �����մϴ�.
	/// </summary>
	public ref class DependencyObject
	{
	internal:
		using Items = System::Collections::Generic::Dictionary<int, System::String^>;
		using Classes = System::Collections::Generic::Dictionary<int, Items^>;

		Classes^ mProperties;

	protected:
		/// <summary>
		/// <see cref="DependencyObject"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		DependencyObject();

	public:
		/// <summary> �� ���� ���� �Ӽ��� �߰��մϴ�. </summary>
		/// <param name="value"> �Ӽ� ��ü�� �����մϴ�. </param>
		void AddDependencyProperty( DependencyProperty value );

		/// <summary> �� ���� ���� �Ӽ��� �߰��մϴ�. </summary>
		/// <param name="value"> �Ľ� ������ �Ӽ� �ؽ�Ʈ�� �����մϴ�. </param>
		void AddDependencyProperty( System::String^ value )
		{
			return AddDependencyProperty( DependencyProperty( value ) );
		}

		/// <summary> ���� ���� �Ӽ��� �����մϴ�. </summary>
		/// <param name="className"> ������ �Ӽ��� ���� Ŭ���� �̸��� �����մϴ�. </param>
		/// <param name="propertyName"> ������ �Ӽ��� �̸��� �����մϴ�. </param>
		void RemoveDependencyProperty( int className, int propertyName );

		/// <summary> ���� ���� �Ӽ��� �����մϴ�. </summary>
		/// <param name="className"> ������ �Ӽ��� ���� Ŭ���� �̸��� �����մϴ�. </param>
		void RemoveDependencyProperty( int className );
	};
}