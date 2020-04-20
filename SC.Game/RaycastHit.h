#pragma once

namespace SC::Game
{
	/// <summary>
	/// ���� ���� �Լ��� ����� ǥ���մϴ�.
	/// </summary>
	public value struct RaycastHit
	{
		/// <summary>
		/// �浹ü ��ü�� �浹�ߴ��� ���θ� ��Ÿ���ϴ�.
		/// </summary>
		bool Hit;

		/// <summary>
		/// �浹 ���������� �Ÿ��� ��Ÿ���ϴ�.
		/// </summary>
		float Distance;

		/// <summary>
		/// �浹�� ǥ���� ������ ��Ÿ���ϴ�.
		/// </summary>
		System::Numerics::Vector3 Normal;
		
		/// <summary>
		/// �浹�� ������ ���� ��ǥ�� ��Ÿ���ϴ�.
		/// </summary>
		System::Numerics::Vector3 Point;

		/// <summary>
		/// �浹�� �ݶ��̴� ��ü�� �����ɴϴ�.
		/// </summary>
		Collider^ Collider;
	};
}