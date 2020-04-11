#pragma once

namespace SC::Game
{
	/// <summary>
	/// 3���� ���� ������ ǥ���մϴ�.
	/// </summary>
	public value struct Ray
	{
		/// <summary>
		/// ������ ���� ��ġ�� �����մϴ�.
		/// </summary>
		System::Numerics::Vector3 Origin;

		/// <summary>
		/// ������ ����ȭ�� ���� ���� ���͸� �����մϴ�.
		/// </summary>
		System::Numerics::Vector3 Direction;

		/// <summary>
		/// ������ �ִ� ���̸� �����մϴ�. 0�� ��� ���� ������ ��Ÿ���ϴ�.
		/// </summary>
		float MaxDepth;

	public:
		/// <summary>
		/// <see cref="Ray"/> ����ü�� �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="origin"> ������ ���� ��ġ�� �����մϴ�. </param>
		/// <param name="direction"> ������ ����ȭ�� ���� ���� ���͸� �����մϴ�. </param>
		Ray( System::Numerics::Vector3 origin, System::Numerics::Vector3 direction );

		/// <summary>
		/// <see cref="Ray"/> ����ü�� �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="origin"> ������ ���� ��ġ�� �����մϴ�. </param>
		/// <param name="direction"> ������ ����ȭ�� ���� ���� ���͸� �����մϴ�. </param>
		/// <param name="maxDepth"> ������ �ִ� ���̸� �����մϴ�. 0�� ��� ���� ������ ��Ÿ���ϴ�. </param>
		Ray( System::Numerics::Vector3 origin, System::Numerics::Vector3 direction, float maxDepth );

		/// <summary>
		/// (<see cref="System::Object"/> Ŭ�������� ��� ��.) ������ ������ ����ȭ�� �ؽ�Ʈ�� �����ɴϴ�.
		/// </summary>
		System::String^ ToString() override;

		/// <summary>
		/// ���� ���� �������� �Ÿ���ŭ �̵����� ���� ��ġ�� �����ɴϴ�.
		/// </summary>
		/// <param name="distance"> �Ÿ��� �����մϴ�. </param>
		System::Numerics::Vector3 GetPoint( float distance );
	};
}