#pragma once

namespace SC::Game::UI
{
	/// <summary>
	/// UI 요소 레이아웃을 표현하는 페이지를 정의합니다.
	/// </summary>
	public ref class Page : public Element
	{
	protected:
		/// <summary>
		/// <see cref="Page"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="xName"> 개체의 참조 이름을 전달합니다. </param>
		Page( System::String^ xName );

	public:
		/// <summary>
		/// 페이지가 외부에서 탐색되었을 때 호출됩니다.
		/// </summary>
		/// <param name="args"> 페이지 탐색 매개변수가 젼달됩니다. </param>
		virtual void OnNavigatedTo( NavigationEventArgs^ args );

		/// <summary>
		/// 페이지가 외부로 탐색될 때 호출됩니다.
		/// </summary>
		/// <param name="args"> 페이지 탐색 매개변수가 젼달됩니다. </param>
		virtual void OnNavigatedFrom( NavigationEventArgs^ args );
	};
}