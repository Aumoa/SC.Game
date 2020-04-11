#pragma once

namespace SC::Game::UI
{
	/// <summary>
	/// UI 요소를 정리하는 패널 형식 계층 구조의 루트입니다. 파생 클래스에 패널 형식의 기본 기능을 제공합니다.
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
		/// (<see cref="Element"/> 클래스에서 상속 됨.) 요소를 갱신합니다. 
		/// </summary>
		/// <param name="clientRect"> 부모의 컨텐츠 사각 영역이 전달됩니다. </param>
		System::Drawing::RectangleF OnUpdate( System::Drawing::RectangleF clientRect ) override;

	public:
		/// <summary>
		/// <see cref="Panel"/> 클래스의 새 인스턴스를 초기화합니다. 
		/// </summary>
		/// <param name="xName"> 개체 이름을 전달합니다. </param>
		Panel( System::String^ xName );

		/// <summary>
		/// (<see cref="System::Collections::Generic::IEnumerable"/> 인터페이스에서 구현 됨.) 컬렉션 전체를 반복하는 열거자를 반환합니다.
		/// </summary>
		virtual System::Collections::Generic::IEnumerator<Element^>^ GetEnumerator();

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> 인터페이스에서 구현 됨.) 항목을 추가합니다.
		/// </summary>
		/// <param name="value"> 추가할 개체를 전달합니다. </param>
		/// <returns> 새 요소를 삽입한 위치를 반환합니다. 실패하였을 경우 -1을 반환합니다. </returns>
		/// <exception cref="System::NotSupportedException">
		/// <para> 개체가 읽기 전용 리스트인 경우 발생합니다. </para>
		/// <para> 개체가 고정 크기일 경우 발생합니다. </para>
		/// </exception>
		virtual void Add( Element^ value );

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> 인터페이스에서 구현 됨.) 항목을 모두 제거합니다.
		/// </summary>
		/// <exception cref="System::NotSupportedException">
		/// <para> 개체가 읽기 전용 리스트인 경우 발생합니다. </para>
		/// <para> 개체가 고정 크기일 경우 발생합니다. </para>
		/// </exception>
		virtual void Clear();

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> 인터페이스에서 구현 됨.) 특정 항목이 존재하는지 여부를 확인합니다.
		/// </summary>
		/// <param name="value"> 찾을 개체를 전달합니다. </param>
		/// <returns> 개체가 리스트에 있으면 true, 그렇지 않다면 false를 반환합니다. </returns>
		virtual bool Contains( Element^ value );

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> 인터페이스에서 구현 됨.) 특정 인덱스부터 시작하여 요소를 지정한 배열에 복사합니다.
		/// </summary>
		/// <param name="array"> 복사 대상 배열 포인터입니다. 충분한 크기가 준비되어야 합니다. </param>
		/// <param name="index"> 복사가 시작되는 인덱스입니다. </param>
		/// <exception cref="System::ArgumentNullException"> <paramref name="array"/>가 nullptr인 경우 발생합니다. </exception>
		/// <exception cref="System::ArgumentOutOfRangeException"> <paramref name="index"/>가 0보다 작거나 배열의 크기보다 크거나 같을 경우 경우 발생합니다. </exception>
		virtual void CopyTo( cli::array<Element^>^ array, int index );

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> 인터페이스에서 구현 됨.) 특정 인덱스부터 시작하여 요소를 지정한 배열에 복사합니다.
		/// </summary>
		/// <param name="array"> 복사 대상 배열 포인터입니다. 충분한 크기가 준비되어야 합니다. </param>
		/// <exception cref="System::ArgumentNullException"> <paramref name="array"/>가 nullptr인 경우 발생합니다. </exception>
		void CopyTo( cli::array<Element^>^ array )
		{
			CopyTo( array, 0 );
		}

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> 인터페이스에서 구현 됨.) 특정 항목의 인덱스를 검색합니다.
		/// </summary>
		/// <param name="value"> 찾을 개체를 전달합니다. </param>
		/// <returns> 목록에 개체가 존재하면 개체의 인덱스를, 그렇지 않다면 -1을 반환합니다. </returns>
		virtual int IndexOf( Element^ value );

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> 인터페이스에서 구현 됨.) 리스트에 새 요소를 지정한 인덱스에 삽입합니다.
		/// </summary>
		/// <param name="index"> 삽입할 인덱스를 전달합니다. </param>
		/// <param name="value"> 삽입할 개체를 전달합니다. </param>
		/// <exception cref="System::ArgumentOutOfRangeException"> <paramref name="index"/>가 0보다 작거나 배열의 크기보다 클 경우 경우 발생합니다. </exception>
		/// <exception cref="System::NotSupportedException">
		/// <para> 개체가 읽기 전용 리스트인 경우 발생합니다. </para>
		/// <para> 개체가 고정 크기일 경우 발생합니다. </para>
		/// </exception>
		virtual void Insert( int index, Element^ value );

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> 인터페이스에서 구현 됨.) 리스트에서 제일 처음 발견되는 특정 개체를 제거합니다.
		/// </summary>
		/// <param name="value"> 제거할 개체를 전달합니다. </param>
		/// <exception cref="System::NotSupportedException">
		/// <para> 개체가 읽기 전용 리스트인 경우 발생합니다. </para>
		/// <para> 개체가 고정 크기일 경우 발생합니다. </para>
		/// </exception>
		virtual bool Remove( Element^ value );

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> 인터페이스에서 구현 됨.) 리스트에서 제일 처음 발견되는 특정 개체를 제거합니다.
		/// </summary>
		/// <param name="index"> 제거할 항목의 인덱스를 전달합니다. </param>
		/// <exception cref="System::ArgumentOutOfRangeException"> <paramref name="index"/>가 0보다 작거나 배열의 크기보다 크거나 같을 경우 경우 발생합니다. </exception>
		/// <exception cref="System::NotSupportedException">
		/// <para> 개체가 읽기 전용 리스트인 경우 발생합니다. </para>
		/// <para> 개체가 고정 크기일 경우 발생합니다. </para>
		/// </exception>
		virtual void RemoveAt( int index );

		/// <summary>
		/// 특정 항목의 인덱스를 검색합니다.
		/// </summary>
		/// <param name="xName"> 찾을 개체의 이름을 전달합니다. </param>
		/// <returns> 목록에 개체가 존재하면 개체의 인덱스를, 그렇지 않다면 -1을 반환합니다. </returns>
		int IndexOf( System::String^ xName );

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> 인터페이스에서 구현 됨.) 포함된 요소 수를 가져옵니다.
		/// </summary>
		property int Count
		{
			virtual int get();
		}

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> 인터페이스에서 구현 됨.) 크기가 고정되어 있는지 여부를 나타내는 값을 가져옵니다.
		/// </summary>
		property bool IsFixedSize
		{
			virtual bool get();
		}

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> 인터페이스에서 구현 됨.) 해당 개체가 읽기 전용 개체인지 여부를 나타내는 값을 가져옵니다.
		/// </summary>
		property bool IsReadOnly
		{
			virtual bool get();
		}

		/// <summary>
		/// (<see cref="System::Collections::Generic::IList"/> 인터페이스에서 구현 됨.) 지정한 인덱스에 있는 요소를 설정하거나 가져옵니다.
		/// </summary>
		property Element^ default[int]
		{
			virtual Element^ get( int index );
			virtual void set( int index, Element^ value );
		}

		/// <summary>
		/// 이 클래스의 이름 해시 값을 가져옵니다.
		/// </summary>
		static const int ClassName = ( gcnew System::String( "panel" ) )->GetHashCode();

		/// <summary>
		/// 패널에 포함된 요소의 Z 순서를 지정하는 속성의 해시 값을 가져옵니다.
		/// </summary>
		static const int ZOrder = ( gcnew System::String( "zorder" ) )->GetHashCode();
	};
}