#pragma once

namespace SC::Game
{
	/// <summary>
	/// 물리 재질을 나타냅니다.
	/// </summary>
	public ref class PhysicsMaterial : public Asset
	{
	internal:
		physx::PxMaterial* mMaterial = nullptr;
		float mStaticFriction = 0.5f;
		float mDynamicFriction = 0.5f;
		float mRestitution = 0.6f;

	public:
		/// <summary>
		/// <see cref="PhysicsMaterial"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="xName"> 식별자 이름을 전달합니다. </param>
		PhysicsMaterial( System::String^ xName );
		~PhysicsMaterial();
		!PhysicsMaterial();

		/// <summary>
		/// 재질의 정적 마찰 계수를 설정하거나 가져옵니다.
		/// </summary>
		property float StaticFriction
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// 재질의 동적 마찰 계수를 설정하거나 가져옵니다.
		/// </summary>
		property float DynamicFriction
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// 재질의 반발 계수를 설정하거나 가져옵니다.
		/// </summary>
		property float Restitution
		{
			float get();
			void set( float value );
		}
	};
}