#pragma once

namespace SC::Game
{
	struct tag_Bone
	{
		XMFLOAT4X4 Offset;
		XMFLOAT4X4 ToRoot;
	};

	struct tag_BoneTransform
	{
		XMFLOAT4X4 World;
	};

	/// <summary>
	/// ���� ������ �����ϴ� ��ü�� ���� �ִϸ��̼� ������ �����մϴ�. �� Ŭ������ ��ӵ� �� �����ϴ�.
	/// </summary>
	public ref class Animator sealed : public Component
	{
	internal:
		AnimatorController^ mController;
		System::Collections::Generic::IDictionary<System::String^, System::Object^>^ mAnimVars;

		StateMachine mCurrentState;
		StateMachine mPrevState;
		float mBlendTime = 0.0f;

		std::vector<tag_Bone>* mBoneTransform = nullptr;
		std::vector<tag_BoneTransform>* mFinalTransform = nullptr;
		LargeHeap* mFinalTransformBuffer = nullptr;

		bool mKeyframeUpdated = false;
		bool mRefreshed = false;

	internal:
		void SetInput( CDeviceContext& deviceContext );

		void Start();
		void FixedUpdate();

	public:
		/// <summary>
		/// <see cref="Animator"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		Animator();
		~Animator();
		!Animator();

		/// <summary>
		/// (<see cref="Component"/> Ŭ�������� ��� ��.) ���� �ν��Ͻ��� ���纻�� �� ��ü�� �����մϴ�.
		/// </summary>
		System::Object^ Clone() override;

		/// <summary>
		/// <see cref="SC::Game::AnimatorController"/> Ŭ�������� ����ϴ� �ִϸ��̼� �Ű������� ���� �����ɴϴ�. 
		/// </summary>
		/// <param name="vName"> �Ű����� �̸��� �����մϴ�. </param>
		System::Object^ GetVar( System::String^ vName );

		/// <summary>
		/// <see cref="SC::Game::AnimatorController"/> Ŭ�������� ����ϴ� �ִϸ��̼� �Ű������� ���� �����մϴ�. 
		/// </summary>
		/// <param name="vName"> �Ű����� �̸��� �����մϴ�. </param>
		/// <param name="value"> ������ ���� �����մϴ�. </param>
		void SetVar( System::String^ vName, System::Object^ value );

		/// <summary>
		/// �ִϸ��̼� ��Ʈ�ѷ� ��ü�� �����ϰų� �����ɴϴ�.
		/// </summary>
		property AnimatorController^ Controller
		{
			AnimatorController^ get();
			void set( AnimatorController^ value );
		}

	private:
		void InitializeOffset( GameObject^ gameObject, int parent );

		void UpdateToRoot( GameObject^ gameObject, int parent );
		void ReplaceToRoot();

		void Transistor();
		void UpdateBlend( float timeDelta );
		StateMachine MakeStateMachine( System::String^ name );
	};
}