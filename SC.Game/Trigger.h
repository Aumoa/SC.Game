#pragma once

namespace SC::Game
{
	/// <summary>
	/// �ִϸ��̼� �Ű������� ����ϴ� Ʈ���� �ڷ����� ǥ���մϴ�.
	/// </summary>
	public value struct Trigger
	{
	private:
		bool mValue;

	public:
		/// <summary> <see cref="Trigger"/>
		/// ����ü�� �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		Trigger( bool initialTrigger )
		{
			mValue = initialTrigger;
		}

		/// <summary>
		/// ���� ���¸� ��������, ���°� Ȱ��ȭ ���¶�� ��Ȱ��ȭ ���·� �����մϴ�.
		/// </summary>
		bool Action()
		{
			auto ret = mValue;
			mValue = false;
			return ret;
		}

		/// <summary>
		/// ���� ���¸� �����ϰų� �����ɴϴ�.
		/// </summary>
		property bool IsActive
		{
			bool get()
			{
				return mValue;
			}

			void set( bool value )
			{
				mValue = value;
			}
		}
	};
}