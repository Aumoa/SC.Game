#pragma once

namespace SC::Game
{
	/// <summary>
	/// �� ������ �⺻ �浹ü�� ��Ÿ���ϴ�. �� Ŭ������ ��ӵ� �� �����ϴ�.
	/// </summary>
	public ref class SphereCollider sealed : public Collider
	{
	internal:
		float mRadius = 1.0f;

		void Update() override;

	public:
		/// <summary>
		/// <see cref="SphereCollider"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		SphereCollider();

		/// <summary>
		/// ���� �������� ��Ÿ���� ���� �����ϰų� �����ɴϴ�. ��ü�� ���� ��ǥ�� �����˴ϴ�.
		/// </summary>
		property float Radius
		{
			float get();
			void set( float value );
		}
	};
}