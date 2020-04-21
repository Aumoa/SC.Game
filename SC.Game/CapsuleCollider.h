#pragma once

namespace SC::Game
{
	/// <summary>
	/// ĸ�� ������ �⺻ �浹ü�� ��Ÿ���ϴ�. �� Ŭ������ ��ӵ� �� �����ϴ�.
	/// </summary>
	public ref class CapsuleCollider sealed : public Collider
	{
	internal:
		float mHalfHeight = 1.0f;
		float mRadius = 1.0f;

		void Update() override;

	public:
		/// <summary>
		/// <see cref="BoxCollider"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		CapsuleCollider();

		/// <summary>
		/// (<see cref="Component"/> Ŭ�������� ��� ��.) �ش� ������Ʈ�� ���� ���纻�� �����Ͽ� ��ȯ�մϴ�.
		/// </summary>
		System::Object^ Clone() override;

		/// <summary>
		/// ĸ���� X�� ���̸� ��Ÿ���� ���� �����ϰų� �����ɴϴ�. ��ü�� ���� ��ǥ�� �����˴ϴ�.
		/// </summary>
		/// <remarks> Y���� ���̷� ����ϴ� ��ǥ�迡�� <see cref="Collider::Rotation"/> �Ӽ��� ����Ͽ� ȸ������ ����մϴ�. </remarks>
		property float Height
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// ĸ���� �������� ��Ÿ���� ���� �����ϰų� �����ɴϴ�. ��ü�� ���� ��ǥ�� �����˴ϴ�.
		/// </summary>
		/// <remarks> ĸ���� �������� 0.25�踸ŭ ĸ���� ���̰� Ŀ���ϴ�. </remarks>
		property float Radius
		{
			float get();
			void set( float value );
		}
	};
}