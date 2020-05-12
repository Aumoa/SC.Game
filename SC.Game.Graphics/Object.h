#pragma once

namespace SC::Game::Graphics::DXGI
{
	/// <summary>
	/// DXGI 개체에 관한 공통 기능을 제공합니다.
	/// </summary>
	public ref class Object
	{
	internal:
		Object^ mParent;

	public:
		/// <summary>
		/// 현재 개체의 부모 개체를 가져옵니다.
		/// </summary>
		virtual Object^ GetParent();
	};
}