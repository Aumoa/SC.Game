#pragma once

namespace SC::Game::UI
{
	ref class Page;

	/// <summary>
	/// 탐색 요청을 취소할 수 없는 탐색 함수 및 이벤트 핸들러에 대한 매개변수를 제공합니다.
	/// </summary>
	public ref class NavigationEventArgs : public System::EventArgs
	{
		Page^ mPageFrom;
		Page^ mPageTo;

	public:
		/// <summary>
		/// <see cref="NavigationEventArgs"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="pageFrom"> 탐색 이전 페이지를 전달합니다. </param>
		/// <param name="pageTo"> 탐색 이후 페이지를 전달합니다. </param>
		NavigationEventArgs( Page^ pageFrom, Page^ pageTo );

		/// <summary> 탐색 이전 페이지를 가져옵니다. </summary>
		property Page^ PageFrom
		{
			Page^ get();
		}

		/// <summary> 탐색 이후 페이지를 가져옵니다. </summary>
		property Page^ PageTo
		{
			Page^ get();
		}
	};
}