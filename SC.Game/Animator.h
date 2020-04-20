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
	/// 뼈대 정보가 존재하는 개체에 대해 애니메이션 갱신을 진행합니다. 이 클래스는 상속될 수 없습니다.
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
		/// <see cref="Animator"/> 클래스의 새 인스턴스를 초기화합니다.
		/// </summary>
		Animator();
		~Animator();
		!Animator();

		/// <summary>
		/// (<see cref="Component"/> 클래스에서 상속 됨.) 현재 인스턴스의 복사본인 새 개체를 생성합니다.
		/// </summary>
		System::Object^ Clone() override;

		/// <summary>
		/// <see cref="SC::Game::AnimatorController"/> 클래스에서 사용하는 애니메이션 매개변수의 값을 가져옵니다. 
		/// </summary>
		/// <param name="vName"> 매개변수 이름을 전달합니다. </param>
		System::Object^ GetVar( System::String^ vName );

		/// <summary>
		/// <see cref="SC::Game::AnimatorController"/> 클래스에서 사용하는 애니메이션 매개변수의 값을 설정합니다. 
		/// </summary>
		/// <param name="vName"> 매개변수 이름을 전달합니다. </param>
		/// <param name="value"> 설정할 값을 전달합니다. </param>
		void SetVar( System::String^ vName, System::Object^ value );

		/// <summary>
		/// 애니메이션 컨트롤러 개체를 설정하거나 가져옵니다.
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