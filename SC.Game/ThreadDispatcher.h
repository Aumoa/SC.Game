#pragma once

namespace SC::Game
{
	/// <summary>
	/// ������ �۾� �й� ��Ʈ ������Ʈ�Դϴ�.
	/// </summary>
	/// <remarks>
	/// <para> �� ��Ʈ�� �����Ͽ� ������ �и� ���ɼ��� ������ �� �ֽ��ϴ�. </para>
	/// <para> ��Ʈ�� �ݵ�� ������ �и��� ������� �ǹ����� �ʽ��ϴ�. </para>
	/// <para> ������Ʈ�� ���� �� ���� ������Ʈ�� ���� ������Ʈ�� ��� ���� ������ �и� ID�� �����ϴ�. </para>
	/// </remarks>
	public ref class ThreadDispatcher : public Component
	{
	internal:
		int mID = 0;

	public:
		/// <summary>
		/// <see cref="ThreadDispatcher"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		ThreadDispatcher();

		/// <summary>
		/// ������ ID�� �����մϴ�. 0�� �� �����带 �ǹ��մϴ�.
		/// </summary>
		/// <remarks>
		/// <para> ���⼭ �����ϴ� ID�� ������ �и� ��Ʈ�̸�, ���� �۾� �������� ID�� �ǹ����� �ʽ��ϴ�. </para>
		/// </remarks>
		property int ID
		{
			int get();
			void set( int value );
		}
	};
}