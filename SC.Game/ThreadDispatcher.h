#pragma once

namespace SC::Game
{
	/// <summary>
	/// 스레드 작업 분배 힌트 컴포넌트입니다.
	/// </summary>
	/// <remarks>
	/// <para> 이 힌트를 적용하여 스레드 분리 가능성을 제시할 수 있습니다. </para>
	/// <para> 힌트는 반드시 스레드 분리가 적용됨을 의미하진 않습니다. </para>
	/// <para> 컴포넌트가 적용 된 게임 오브젝트의 하위 오브젝트는 모두 같은 스레드 분리 ID를 가집니다. </para>
	/// </remarks>
	public ref class ThreadDispatcher : public Component
	{
	internal:
		int mID = 0;

	public:
		/// <summary>
		/// <see cref="ThreadDispatcher"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		ThreadDispatcher();

		/// <summary>
		/// 스레드 ID를 전달합니다. 0은 주 스레드를 의미합니다.
		/// </summary>
		/// <remarks>
		/// <para> 여기서 지정하는 ID는 스레드 분리 힌트이며, 실제 작업 스레드의 ID를 의미하지 않습니다. </para>
		/// </remarks>
		property int ID
		{
			int get();
			void set( int value );
		}
	};
}