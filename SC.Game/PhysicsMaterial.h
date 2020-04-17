#pragma once

namespace SC::Game
{
	/// <summary>
	/// ���� ������ ��Ÿ���ϴ�.
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
		/// <see cref="PhysicsMaterial"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="xName"> �ĺ��� �̸��� �����մϴ�. </param>
		PhysicsMaterial( System::String^ xName );
		~PhysicsMaterial();
		!PhysicsMaterial();

		/// <summary>
		/// ������ ���� ���� ����� �����ϰų� �����ɴϴ�.
		/// </summary>
		property float StaticFriction
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// ������ ���� ���� ����� �����ϰų� �����ɴϴ�.
		/// </summary>
		property float DynamicFriction
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// ������ �ݹ� ����� �����ϰų� �����ɴϴ�.
		/// </summary>
		property float Restitution
		{
			float get();
			void set( float value );
		}
	};
}