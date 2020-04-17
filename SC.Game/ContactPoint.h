#pragma once

namespace SC::Game
{
	/// <summary>
	/// �浹�� �߻��� �浹���� ��Ÿ���ϴ�.
	/// </summary>
	public value struct ContactPoint
	{
		/// <summary>
		/// �浹 ������ ��� ���� ��Ÿ���ϴ�.
		/// </summary>
		System::Numerics::Vector3 Normal;

		/// <summary>
		/// �浹�� ������ ù ��° �浹ü�� ��Ÿ���ϴ�.
		/// </summary>
		Collider^ ThisCollider;

		/// <summary>
		/// �浹�� ������ �� ��° �浹ü�� ��Ÿ���ϴ�.
		/// </summary>
		Collider^ OtherCollider;

		/// <summary>
		/// �浹 ��ġ�� ��Ÿ���ϴ�.
		/// </summary>
		System::Numerics::Vector3 Point;
	};
}