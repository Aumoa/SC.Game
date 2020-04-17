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

		/// <summary>
		/// �ٸ� ��ü�� �浹�� ���۵Ǿ��� ��� ȣ��˴ϴ�.
		/// </summary>
		/// <param name="collision"> �浹 ������ ���޵˴ϴ�. </param>
		virtual void OnCollisionEnter( Collision collision );

		/// <summary>
		/// �ٸ� ��ü�� �浹�� ����Ǿ��� ��� ȣ��˴ϴ�.
		/// </summary>
		/// <param name="collision"> �浹 ������ ���޵˴ϴ�. </param>
		virtual void OnCollisionExit( Collision collision );

		/// <summary>
		/// �ٸ� ��ü�� �浹���� ��� ȣ��˴ϴ�.
		/// </summary>
		/// <param name="collision"> �浹 ������ ���޵˴ϴ�. </param>
		virtual void OnCollisionStay( Collision collision );

		/// <summary>
		/// �ٸ� Ʈ���� �߻� �ö��̴� ��ü�� �浹�Ͽ��� ��� �߻��մϴ�.
		/// </summary>
		/// <param name="collider"> �浹�� �ö��̴� ��ü�� ���޵˴ϴ�. </param>
		virtual void OnTriggerEnter( Collider^ collider );

		/// <summary>
		/// �ٸ� Ʈ���� �߻� �ö��̴� ��ü�� �浹�� ����Ǿ��� ��� �߻��մϴ�.
		/// </summary>
		/// <param name="collider"> �浹�� �ö��̴� ��ü�� ���޵˴ϴ�. </param>
		virtual void OnTriggerExit( Collider^ collider );
	};
}