#pragma once

namespace SC::Game
{
	/// <summary>
	/// 구 형태의 기본 충돌체를 나타냅니다. 이 클래스는 상속될 수 없습니다.
	/// </summary>
	public ref class SphereCollider sealed : public Collider
	{
	internal:
		float mRadius = 1.0f;

		void Update() override;

	public:
		/// <summary>
		/// <see cref="SphereCollider"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		SphereCollider();

		/// <summary>
		/// 구의 반지름을 나타내는 값을 설정하거나 가져옵니다. 개체의 로컬 좌표로 측정됩니다.
		/// </summary>
		property float Radius
		{
			float get();
			void set( float value );
		}
	};
}