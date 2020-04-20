#pragma once

namespace SC::Game
{
	value struct ContactPoint;
	ref class GameObject;

	/// <summary>
	/// �浹 ������ ��Ÿ���ϴ�.
	/// </summary>
	public value struct Collision
	{
		/// <summary>
		/// ���� ������ ���� �����Ǵ� �浹�� ����� ��Ÿ���ϴ�.
		/// </summary>
		System::Collections::Generic::IList<ContactPoint>^ Contacts;

		/// <summary>
		/// �浹�� ������ �浹ü�� ���� ��ü�� ��Ÿ���ϴ�.
		/// </summary>
		GameObject^ Object;

		/// <summary>
		/// �浹�� �ذ��ϴ� �� ����Ǵ� �� ���� ��Ÿ���ϴ�.
		/// </summary>
		System::Numerics::Vector3 Impulse;

		/// <summary>
		/// �浹�ϴ� �� ������Ʈ�� ����� ���� �ӵ��� ��Ÿ���ϴ�.
		/// </summary>
		System::Numerics::Vector3 RelativeVelocity;

		/// <summary>
		/// �浹�� ������ ��� �浹ü�� ���� ��ü�� ��Ÿ���ϴ�.
		/// </summary>
		GameObject^ Target;
	};
}