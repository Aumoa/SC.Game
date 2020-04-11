#pragma once

namespace SC::Game
{
	/// <summary>
	/// ���� ��ü�� Ư���� �ൿ�� �߰��ϴ� Ȯ�� ���� ��ҿ� ���� �⺻ �Լ��� �����մϴ�.
	/// </summary>
	public ref class Behaviour abstract : public Component
	{
	internal:
		bool mIsEnabled = true;
		bool mIsFirst = true;

		void InternalUpdate();

	protected:
		/// <summary>
		/// <see cref="Behaviour"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		Behaviour();

	public:
		/// <summary>
		/// ������Ʈ�� ��ü�� ����� �� ȣ��˴ϴ�.
		/// </summary>
		virtual void Awake();

		/// <summary>
		/// ������Ʈ�� ���� ���� ó������ ������ �� ȣ��˴ϴ�.
		/// </summary>
		/// <remarks> �Ϲ�������, �� �Լ��� �ش� ������Ʈ�� ù ��° Update �Լ� ȣ�� ���� ����˴ϴ�. </remarks>
		virtual void Start();

		/// <summary>
		/// �ൿ ������Ʈ�� Ȱ��ȭ ������ �� �� ������ ȣ��˴ϴ�.
		/// </summary>
		virtual void Update();

		/// <summary>
		/// �ൿ ������Ʈ�� Ȱ��ȭ ������ �� �� ���� ������ �ֱ�� ȣ��˴ϴ�.
		/// </summary>
		/// <remarks> ���� ������ �ֱ⸦ �����Ϸ��� <see cref="AppConfiguration"/> Ŭ������ �����Ͻʽÿ�. </remarks>
		virtual void FixedUpdate();

		/// <summary>
		/// �ൿ ������Ʈ�� Ȱ��ȭ ������ �� �� ������ ����� ��� ��ü�� Update�� �Ϸ�� �� ȣ��˴ϴ�.
		/// </summary>
		virtual void LateUpdate();
	};
}