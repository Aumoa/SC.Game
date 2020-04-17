#pragma once

namespace SC::Game
{
	struct Transform_Constants
	{
		XMFLOAT4X4 World;
		XMFLOAT4X4 WorldInvTranspose;

		void Initialize();
	};

	/// <summary>
	/// ��ü�� ��ȯ ���¸� ǥ���մϴ�. �� Ŭ������ ��ӵ� �� �����ϴ�.
	/// </summary>
	public ref class Transform sealed : public Component
	{
	internal:
		Transform^ mParent;

		System::Numerics::Vector3 mLocalPosition;
		System::Numerics::Vector3 mLocalScale;
		System::Numerics::Quaternion mLocalRotation;

		Heap* mConstants = nullptr;
		Transform_Constants* mFrameResource = nullptr;

		bool mBufferUpdated = false;

	private:
		void WriteRigid( System::Numerics::Vector3 p, System::Numerics::Quaternion q );

	internal:
		void CreateBuffer();
		void Update();

	public:
		/// <summary>
		/// <see cref="Transform"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		Transform();
		~Transform();
		!Transform();

		/// <summary>
		/// (<see cref="Component"/> Ŭ�������� ��� ��.) �ش� ������Ʈ�� ���� ���纻�� �����Ͽ� ��ȯ�մϴ�.
		/// </summary>
		System::Object^ Clone() override;

		/// <summary>
		/// ����� �ٶ󺸵��� ������ �����մϴ�.
		/// </summary>
		/// <param name="target"> ��� ��ġ�� �����մϴ�. </param>
		/// <param name="up"> ���� ���͸� �����մϴ�. </param>
		void LookAt( System::Numerics::Vector3 target, System::Numerics::Vector3 up );

		/// <summary>
		/// ����� �ٶ󺸵��� ������ �����մϴ�.
		/// </summary>
		/// <param name="target"> ��� ��ġ�� �����մϴ�. </param>
		void LookAt( System::Numerics::Vector3 target )
		{
			LookAt( target, System::Numerics::Vector3::UnitY );
		}

		/// <summary>
		/// ���� �������� ����� �ٶ󺸵��� ������ �����մϴ�.
		/// </summary>
		/// <param name="target"> ��� ��ġ�� �����մϴ�. </param>
		/// <param name="up"> ���� ���͸� �����մϴ�. </param>
		void LocalLookAt( System::Numerics::Vector3 target, System::Numerics::Vector3 up );

		/// <summary>
		/// ���� �������� ����� �ٶ󺸵��� ������ �����մϴ�.
		/// </summary>
		/// <param name="target"> ��� ��ġ�� �����մϴ�. </param>
		void LocalLookAt( System::Numerics::Vector3 target )
		{
			LocalLookAt( target, System::Numerics::Vector3::UnitY );
		}

		/// <summary>
		/// ������ �ٶ󺸵��� ������ �����մϴ�.
		/// </summary>
		/// <param name="direction"> ���� ���͸� �����մϴ�. </param>
		/// <param name="up"> ���� ���͸� �����մϴ�. </param>
		void LookTo( System::Numerics::Vector3 direction, System::Numerics::Vector3 up );

		/// <summary>
		/// ������ �ٶ󺸵��� ������ �����մϴ�.
		/// </summary>
		/// <param name="direction"> ���� ���͸� �����մϴ�. </param>
		void LookTo( System::Numerics::Vector3 direction )
		{
			LookTo( direction, System::Numerics::Vector3::UnitY );
		}

		/// <summary>
		/// ���� �������� ������ �ٶ󺸵��� ������ �����մϴ�.
		/// </summary>
		/// <param name="direction"> ���� ���͸� �����մϴ�. </param>
		/// <param name="up"> ���� ���͸� �����մϴ�. </param>
		void LocalLookTo( System::Numerics::Vector3 direction, System::Numerics::Vector3 up );

		/// <summary>
		/// ���� �������� ������ �ٶ󺸵��� ������ �����մϴ�.
		/// </summary>
		/// <param name="direction"> ���� ���͸� �����մϴ�. </param>
		void LocalLookTo( System::Numerics::Vector3 direction )
		{
			LocalLookTo( direction, System::Numerics::Vector3::UnitY );
		}

		/// <summary>
		/// �ش� ��ȯ ��ü�� �θ� ��ȯ�� �����ϰų� �����ɴϴ�. ��ü�� ���� ��ȯ ������ �����˴ϴ�.
		/// </summary>
		property Transform^ Parent
		{
			Transform^ get();
			void set( Transform^ value );
		}

		/// <summary>
		/// ��ü�� ���� ��ȯ ����� �����ϰų� �����ɴϴ�.
		/// </summary>
		property System::Numerics::Matrix4x4 World
		{
			System::Numerics::Matrix4x4 get();
			void set( System::Numerics::Matrix4x4 value );
		}

		/// <summary>
		/// ��ü�� ���� ��ȯ ����� �����ϰų� �����ɴϴ�.
		/// </summary>
		property System::Numerics::Matrix4x4 LocalWorld
		{
			System::Numerics::Matrix4x4 get();
			void set( System::Numerics::Matrix4x4 value );
		}

		/// <summary>
		/// ��ü�� ���� ��ġ ��ȯ�� �����ϰų� �����ɴϴ�.
		/// </summary>
		property System::Numerics::Vector3 Position
		{
			System::Numerics::Vector3 get();
			void set( System::Numerics::Vector3 value );
		}

		/// <summary>
		/// ��ü�� ���� ��ġ ��ȯ�� �����ϰų� �����ɴϴ�.
		/// </summary>
		property System::Numerics::Vector3 LocalPosition
		{
			System::Numerics::Vector3 get();
			void set( System::Numerics::Vector3 value );
		}

		/// <summary>
		/// ��ü�� ���� ũ�� ��ȯ�� �����ϰų� �����ɴϴ�.
		/// </summary>
		property System::Numerics::Vector3 Scale
		{
			System::Numerics::Vector3 get();
			void set( System::Numerics::Vector3 value );
		}

		/// <summary>
		/// ��ü�� ���� ũ�� ��ȯ�� �����ϰų� �����ɴϴ�.
		/// </summary>
		property System::Numerics::Vector3 LocalScale
		{
			System::Numerics::Vector3 get();
			void set( System::Numerics::Vector3 value );
		}

		/// <summary>
		/// ��ü�� ���� ȸ�� ��ȯ�� �����ϰų� �����ɴϴ�.
		/// </summary>
		property System::Numerics::Quaternion Rotation
		{
			System::Numerics::Quaternion get();
			void set( System::Numerics::Quaternion value );
		}

		/// <summary>
		/// ��ü�� ���� ȸ�� ��ȯ�� �����ϰų� �����ɴϴ�.
		/// </summary>
		property System::Numerics::Quaternion LocalRotation
		{
			System::Numerics::Quaternion get();
			void set( System::Numerics::Quaternion value );
		}

		/// <summary>
		/// ��ü�� ���� �ٶ󺸴� ������ �����ϰų� �����ɴϴ�. �� ������ ���� ��ȯ�� �����մϴ�.
		/// </summary>
		property System::Numerics::Vector3 Forward
		{
			System::Numerics::Vector3 get();
			void set( System::Numerics::Vector3 value );
		}

		/// <summary>
		/// ��ü�� ���� ������ Update�� �����ϱ� �� ������ �̷��� �ִ� ���� ��Ÿ���� ���� �����ɴϴ�.
		/// </summary>
		property bool IsUpdated
		{
			bool get();
		}
	};
}