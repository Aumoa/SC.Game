#pragma once

namespace SC::Game::Graphics::DXGI
{
	/// <summary>
	/// DXGI ��ü�� ���� ���� ����� �����մϴ�.
	/// </summary>
	public ref class Object
	{
	internal:
		Object^ mParent;

	public:
		/// <summary>
		/// ���� ��ü�� �θ� ��ü�� �����ɴϴ�.
		/// </summary>
		virtual Object^ GetParent();
	};
}