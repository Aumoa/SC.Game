#pragma once

namespace SC::Game
{
	/// <summary>
	/// �ڽ� ������ �⺻ �浹ü�� ��Ÿ���ϴ�. �� Ŭ������ ��ӵ� �� �����ϴ�.
	/// </summary>
	public ref class BoxCollider sealed : public Collider
	{
	internal:
		System::Numerics::Vector3 mHalfExtents;

		void Update() override;

	public:
		/// <summary>
		/// <see cref="BoxCollider"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		BoxCollider();

		/// <summary>
		/// (<see cref="Component"/> Ŭ�������� ��� ��.) �ش� ������Ʈ�� ���� ���纻�� �����Ͽ� ��ȯ�մϴ�.
		/// </summary>
		System::Object^ Clone() override;

		/// <summary>
		/// �ڽ��� Ȯ�� ũ�⸦ ��Ÿ���� ���� �����ϰų� �����ɴϴ�.
		/// </summary>
		property System::Numerics::Vector3 HalfExtents
		{
			System::Numerics::Vector3 get();
			void set( System::Numerics::Vector3 value );
		}
	};
}