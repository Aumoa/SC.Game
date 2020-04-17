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
	/// 개체의 변환 상태를 표현합니다. 이 클래스는 상속될 수 없습니다.
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
		/// <see cref="Transform"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		Transform();
		~Transform();
		!Transform();

		/// <summary>
		/// (<see cref="Component"/> 클래스에서 상속 됨.) 해당 컴포넌트의 완전 복사본을 생성하여 반환합니다.
		/// </summary>
		System::Object^ Clone() override;

		/// <summary>
		/// 대상을 바라보도록 방향을 설정합니다.
		/// </summary>
		/// <param name="target"> 대상 위치를 지정합니다. </param>
		/// <param name="up"> 상향 벡터를 지정합니다. </param>
		void LookAt( System::Numerics::Vector3 target, System::Numerics::Vector3 up );

		/// <summary>
		/// 대상을 바라보도록 방향을 설정합니다.
		/// </summary>
		/// <param name="target"> 대상 위치를 지정합니다. </param>
		void LookAt( System::Numerics::Vector3 target )
		{
			LookAt( target, System::Numerics::Vector3::UnitY );
		}

		/// <summary>
		/// 지역 공간에서 대상을 바라보도록 방향을 설정합니다.
		/// </summary>
		/// <param name="target"> 대상 위치를 지정합니다. </param>
		/// <param name="up"> 상향 벡터를 지정합니다. </param>
		void LocalLookAt( System::Numerics::Vector3 target, System::Numerics::Vector3 up );

		/// <summary>
		/// 지역 공간에서 대상을 바라보도록 방향을 설정합니다.
		/// </summary>
		/// <param name="target"> 대상 위치를 지정합니다. </param>
		void LocalLookAt( System::Numerics::Vector3 target )
		{
			LocalLookAt( target, System::Numerics::Vector3::UnitY );
		}

		/// <summary>
		/// 방향을 바라보도록 방향을 설정합니다.
		/// </summary>
		/// <param name="direction"> 방향 벡터를 전달합니다. </param>
		/// <param name="up"> 상향 벡터를 지정합니다. </param>
		void LookTo( System::Numerics::Vector3 direction, System::Numerics::Vector3 up );

		/// <summary>
		/// 방향을 바라보도록 방향을 설정합니다.
		/// </summary>
		/// <param name="direction"> 방향 벡터를 전달합니다. </param>
		void LookTo( System::Numerics::Vector3 direction )
		{
			LookTo( direction, System::Numerics::Vector3::UnitY );
		}

		/// <summary>
		/// 지역 공간에서 방향을 바라보도록 방향을 설정합니다.
		/// </summary>
		/// <param name="direction"> 방향 벡터를 전달합니다. </param>
		/// <param name="up"> 상향 벡터를 지정합니다. </param>
		void LocalLookTo( System::Numerics::Vector3 direction, System::Numerics::Vector3 up );

		/// <summary>
		/// 지역 공간에서 방향을 바라보도록 방향을 설정합니다.
		/// </summary>
		/// <param name="direction"> 방향 벡터를 전달합니다. </param>
		void LocalLookTo( System::Numerics::Vector3 direction )
		{
			LocalLookTo( direction, System::Numerics::Vector3::UnitY );
		}

		/// <summary>
		/// 해당 변환 개체의 부모 변환을 설정하거나 가져옵니다. 개체의 전역 변환 설정이 유지됩니다.
		/// </summary>
		property Transform^ Parent
		{
			Transform^ get();
			void set( Transform^ value );
		}

		/// <summary>
		/// 개체의 전역 변환 행렬을 설정하거나 가져옵니다.
		/// </summary>
		property System::Numerics::Matrix4x4 World
		{
			System::Numerics::Matrix4x4 get();
			void set( System::Numerics::Matrix4x4 value );
		}

		/// <summary>
		/// 개체의 지역 변환 행렬을 설정하거나 가져옵니다.
		/// </summary>
		property System::Numerics::Matrix4x4 LocalWorld
		{
			System::Numerics::Matrix4x4 get();
			void set( System::Numerics::Matrix4x4 value );
		}

		/// <summary>
		/// 개체의 전역 위치 변환을 설정하거나 가져옵니다.
		/// </summary>
		property System::Numerics::Vector3 Position
		{
			System::Numerics::Vector3 get();
			void set( System::Numerics::Vector3 value );
		}

		/// <summary>
		/// 개체의 지역 위치 변환을 설정하거나 가져옵니다.
		/// </summary>
		property System::Numerics::Vector3 LocalPosition
		{
			System::Numerics::Vector3 get();
			void set( System::Numerics::Vector3 value );
		}

		/// <summary>
		/// 개체의 전역 크기 변환을 설정하거나 가져옵니다.
		/// </summary>
		property System::Numerics::Vector3 Scale
		{
			System::Numerics::Vector3 get();
			void set( System::Numerics::Vector3 value );
		}

		/// <summary>
		/// 개체의 지역 크기 변환을 설정하거나 가져옵니다.
		/// </summary>
		property System::Numerics::Vector3 LocalScale
		{
			System::Numerics::Vector3 get();
			void set( System::Numerics::Vector3 value );
		}

		/// <summary>
		/// 개체의 전역 회전 변환을 설정하거나 가져옵니다.
		/// </summary>
		property System::Numerics::Quaternion Rotation
		{
			System::Numerics::Quaternion get();
			void set( System::Numerics::Quaternion value );
		}

		/// <summary>
		/// 개체의 지역 회전 변환을 설정하거나 가져옵니다.
		/// </summary>
		property System::Numerics::Quaternion LocalRotation
		{
			System::Numerics::Quaternion get();
			void set( System::Numerics::Quaternion value );
		}

		/// <summary>
		/// 개체가 현재 바라보는 방향을 설정하거나 가져옵니다. 이 설정은 전역 변환에 한정합니다.
		/// </summary>
		property System::Numerics::Vector3 Forward
		{
			System::Numerics::Vector3 get();
			void set( System::Numerics::Vector3 value );
		}

		/// <summary>
		/// 개체가 현재 프레임 Update를 진행하기 전 수정된 이력이 있는 것을 나타내는 값을 가져옵니다.
		/// </summary>
		property bool IsUpdated
		{
			bool get();
		}
	};
}