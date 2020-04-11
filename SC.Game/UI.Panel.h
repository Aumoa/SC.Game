#pragma once

namespace SC::Game::UI
{
	/// <summary>
	/// UI ��Ҹ� �����ϴ� �г� ���� ���� ������ ��Ʈ�Դϴ�. �Ļ� Ŭ������ �г� ������ �⺻ ����� �����մϴ�.
	/// </summary>
	public ref class Panel : public Element, public System::Collections::Generic::IList<Element^>
	{
	internal:
		using ContentType = System::Collections::Generic::List<Element^>;

		ContentType^ mContentType;

	internal:
		void Render( CDeviceContext& deviceContext ) override;

		virtual System::Collections::IEnumerator^ GetEnumerator2() = System::Collections::IEnumerable::GetEnumerator;

	protected:
		/// <summary>
		/// (<see cref="Element"/> Ŭ�������� ��� ��.) ��Ҹ� �����մϴ�. 
		/// </summary>
		/// <param name="clientRect"> �θ��� ������ �簢 ������ ���޵˴ϴ�. </param>
		System::Drawing::RectangleF OnUpdate( System::Drawing::RectangleF clientRect ) override;

	public:
		/// <summary>
		/// <see cref="Panel"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�. 
		/// </summary>
		/// <param name="xName"> ��ü �̸��� �����մϴ�. </param>
		Panel( System::String^ xName );

		/// <summary>
		/// (<see cref="System::Collections::Generic::IEnumerable"/> �������̽����� ���� ��.) �÷��� ��ü�� �ݺ��ϴ� �����ڸ� ��ȯ�մϴ�.
		/// </summary>
		virtual System::Collections::Generic::IEnumerator<Element^>^ GetEnumerator();

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> �������̽����� ���� ��.) �׸��� �߰��մϴ�.
		/// </summary>
		/// <param name="value"> �߰��� ��ü�� �����մϴ�. </param>
		/// <returns> �� ��Ҹ� ������ ��ġ�� ��ȯ�մϴ�. �����Ͽ��� ��� -1�� ��ȯ�մϴ�. </returns>
		/// <exception cref="System::NotSupportedException">
		/// <para> ��ü�� �б� ���� ����Ʈ�� ��� �߻��մϴ�. </para>
		/// <para> ��ü�� ���� ũ���� ��� �߻��մϴ�. </para>
		/// </exception>
		virtual void Add( Element^ value );

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> �������̽����� ���� ��.) �׸��� ��� �����մϴ�.
		/// </summary>
		/// <exception cref="System::NotSupportedException">
		/// <para> ��ü�� �б� ���� ����Ʈ�� ��� �߻��մϴ�. </para>
		/// <para> ��ü�� ���� ũ���� ��� �߻��մϴ�. </para>
		/// </exception>
		virtual void Clear();

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> �������̽����� ���� ��.) Ư�� �׸��� �����ϴ��� ���θ� Ȯ���մϴ�.
		/// </summary>
		/// <param name="value"> ã�� ��ü�� �����մϴ�. </param>
		/// <returns> ��ü�� ����Ʈ�� ������ true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�. </returns>
		virtual bool Contains( Element^ value );

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> �������̽����� ���� ��.) Ư�� �ε������� �����Ͽ� ��Ҹ� ������ �迭�� �����մϴ�.
		/// </summary>
		/// <param name="array"> ���� ��� �迭 �������Դϴ�. ����� ũ�Ⱑ �غ�Ǿ�� �մϴ�. </param>
		/// <param name="index"> ���簡 ���۵Ǵ� �ε����Դϴ�. </param>
		/// <exception cref="System::ArgumentNullException"> <paramref name="array"/>�� nullptr�� ��� �߻��մϴ�. </exception>
		/// <exception cref="System::ArgumentOutOfRangeException"> <paramref name="index"/>�� 0���� �۰ų� �迭�� ũ�⺸�� ũ�ų� ���� ��� ��� �߻��մϴ�. </exception>
		virtual void CopyTo( cli::array<Element^>^ array, int index );

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> �������̽����� ���� ��.) Ư�� �ε������� �����Ͽ� ��Ҹ� ������ �迭�� �����մϴ�.
		/// </summary>
		/// <param name="array"> ���� ��� �迭 �������Դϴ�. ����� ũ�Ⱑ �غ�Ǿ�� �մϴ�. </param>
		/// <exception cref="System::ArgumentNullException"> <paramref name="array"/>�� nullptr�� ��� �߻��մϴ�. </exception>
		void CopyTo( cli::array<Element^>^ array )
		{
			CopyTo( array, 0 );
		}

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> �������̽����� ���� ��.) Ư�� �׸��� �ε����� �˻��մϴ�.
		/// </summary>
		/// <param name="value"> ã�� ��ü�� �����մϴ�. </param>
		/// <returns> ��Ͽ� ��ü�� �����ϸ� ��ü�� �ε�����, �׷��� �ʴٸ� -1�� ��ȯ�մϴ�. </returns>
		virtual int IndexOf( Element^ value );

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> �������̽����� ���� ��.) ����Ʈ�� �� ��Ҹ� ������ �ε����� �����մϴ�.
		/// </summary>
		/// <param name="index"> ������ �ε����� �����մϴ�. </param>
		/// <param name="value"> ������ ��ü�� �����մϴ�. </param>
		/// <exception cref="System::ArgumentOutOfRangeException"> <paramref name="index"/>�� 0���� �۰ų� �迭�� ũ�⺸�� Ŭ ��� ��� �߻��մϴ�. </exception>
		/// <exception cref="System::NotSupportedException">
		/// <para> ��ü�� �б� ���� ����Ʈ�� ��� �߻��մϴ�. </para>
		/// <para> ��ü�� ���� ũ���� ��� �߻��մϴ�. </para>
		/// </exception>
		virtual void Insert( int index, Element^ value );

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> �������̽����� ���� ��.) ����Ʈ���� ���� ó�� �߰ߵǴ� Ư�� ��ü�� �����մϴ�.
		/// </summary>
		/// <param name="value"> ������ ��ü�� �����մϴ�. </param>
		/// <exception cref="System::NotSupportedException">
		/// <para> ��ü�� �б� ���� ����Ʈ�� ��� �߻��մϴ�. </para>
		/// <para> ��ü�� ���� ũ���� ��� �߻��մϴ�. </para>
		/// </exception>
		virtual bool Remove( Element^ value );

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> �������̽����� ���� ��.) ����Ʈ���� ���� ó�� �߰ߵǴ� Ư�� ��ü�� �����մϴ�.
		/// </summary>
		/// <param name="index"> ������ �׸��� �ε����� �����մϴ�. </param>
		/// <exception cref="System::ArgumentOutOfRangeException"> <paramref name="index"/>�� 0���� �۰ų� �迭�� ũ�⺸�� ũ�ų� ���� ��� ��� �߻��մϴ�. </exception>
		/// <exception cref="System::NotSupportedException">
		/// <para> ��ü�� �б� ���� ����Ʈ�� ��� �߻��մϴ�. </para>
		/// <para> ��ü�� ���� ũ���� ��� �߻��մϴ�. </para>
		/// </exception>
		virtual void RemoveAt( int index );

		/// <summary>
		/// Ư�� �׸��� �ε����� �˻��մϴ�.
		/// </summary>
		/// <param name="xName"> ã�� ��ü�� �̸��� �����մϴ�. </param>
		/// <returns> ��Ͽ� ��ü�� �����ϸ� ��ü�� �ε�����, �׷��� �ʴٸ� -1�� ��ȯ�մϴ�. </returns>
		int IndexOf( System::String^ xName );

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> �������̽����� ���� ��.) ���Ե� ��� ���� �����ɴϴ�.
		/// </summary>
		property int Count
		{
			virtual int get();
		}

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> �������̽����� ���� ��.) ũ�Ⱑ �����Ǿ� �ִ��� ���θ� ��Ÿ���� ���� �����ɴϴ�.
		/// </summary>
		property bool IsFixedSize
		{
			virtual bool get();
		}

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> �������̽����� ���� ��.) �ش� ��ü�� �б� ���� ��ü���� ���θ� ��Ÿ���� ���� �����ɴϴ�.
		/// </summary>
		property bool IsReadOnly
		{
			virtual bool get();
		}

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> �������̽����� ���� ��.) ������ �ε����� �ִ� ��Ҹ� �����ϰų� �����ɴϴ�.
		/// </summary>
		property Element^ default[int]
		{
			virtual Element^ get( int index );
			virtual void set( int index, Element^ value );
		}

		/// <summary>
		/// �� Ŭ������ �̸� �ؽ� ���� �����ɴϴ�.
		/// </summary>
		static const int ClassName = ( gcnew System::String( "panel" ) )->GetHashCode();

		/// <summary>
		/// �гο� ���Ե� ����� Z ������ �����ϴ� �Ӽ��� �ؽ� ���� �����ɴϴ�.
		/// </summary>
		static const int ZOrder = ( gcnew System::String( "zorder" ) )->GetHashCode();
	};
}