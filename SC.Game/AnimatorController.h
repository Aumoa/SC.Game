#pragma once

namespace SC::Game
{
	/// <summary>
	/// �ִϸ��̼� ���¸� �����ϴ� �ִϸ��̼� ���� ������ ǥ���մϴ�. �� Ŭ������ ��ӵ� �� �����ϴ�.
	/// </summary>
	public ref class AnimatorController sealed : public Asset
	{
	internal:
		System::Collections::Generic::IDictionary<System::String^, AnimationState^>^ mStates;
		System::Collections::Generic::IDictionary<System::String^, System::Object^>^ mParameters;
		System::Collections::Generic::IDictionary<System::String^, System::Collections::Generic::IList<AnimationTransitionCondition>^>^ mTransitionCondition;

		System::String^ mDefaultState;

		System::Collections::Generic::IDictionary<System::String^, System::Object^>^ MakeParameters();

	public:
		/// <summary>
		/// <see cref="AnimatorController"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="xName"> ������ �ڻ� �̸��� �����մϴ�. </param>
		AnimatorController( System::String^ xName );

		/// <summary>
		/// �ִϸ��̼� ���� ��ü�� �߰��մϴ�.
		/// </summary>
		/// <param name="state"> ���� ��ü�� �����մϴ�. ��ü�� <see cref="Asset::Name"/> ���� �̸����� ���˴ϴ�. </param>
		/// <param name="isDefault"> ��ü�� �⺻ ���·� ����մϴ�. </param>
		void AddState( AnimationState^ state, bool isDefault );

		/// <summary>
		/// �ִϸ��̼� ���� ��ü�� �߰��մϴ�.
		/// </summary>
		/// <param name="state"> ���� ��ü�� �����մϴ�. ��ü�� <see cref="Asset::Name"/> ���� �̸����� ���˴ϴ�. </param>
		void AddState( AnimationState^ state ) { AddState( state, false ); }

		/// <summary>
		/// �ִϸ��̼� ���� ��ü�� �߰��մϴ�.
		/// </summary>
		/// <param name="stateNameOverride"> ��� ���ο� ���� ��ü �̸��� �����մϴ�. </param>
		/// <param name="state"> ���� ��ü�� �����մϴ�. </param>
		/// <param name="isDefault"> ��ü�� �⺻ ���·� ����մϴ�. </param>
		void AddState( System::String^ stateNameOverride, AnimationState^ state, bool isDefault );

		/// <summary>
		/// �ִϸ��̼� ���� ��ü�� �߰��մϴ�.
		/// </summary>
		/// <param name="stateNameOverride"> ��� ���ο� ���� ��ü �̸��� �����մϴ�. </param>
		/// <param name="state"> ���� ��ü�� �����մϴ�. </param>
		void AddState( System::String^ stateNameOverride, AnimationState^ state ) { AddState( stateNameOverride, state, false ); }

		/// <summary>
		/// �ִϸ��̼� ���� ��ü�� �����մϴ�.
		/// </summary>
		/// <param name="stateName"> ���� ��ü �̸��� �����մϴ�. </param>
		void RemoveState( System::String^ stateName );

		/// <summary>
		/// �ִϸ��̼� ���� ��ü�� �����ɴϴ�.
		/// </summary>
		/// <param name="stateName"> ���� ��ü �̸��� �����մϴ�. </param>
		AnimationState^ GetState( System::String^ stateName );

		/// <summary>
		/// �� �ִϸ��̼� �Ű������� �߰��մϴ�.
		/// </summary>
		/// <param name="stateName"> ���� ��ü �̸��� �����մϴ�. </param>
		/// <param name="value"> �ʱ�ȭ ���� ���Ե� �Ű����� ���� �����մϴ�. </param>
		void AddVar( System::String^ stateName, System::Object^ value );

		/// <summary>
		/// �ִϸ��̼� �Ű������� �����մϴ�.
		/// </summary>
		/// <param name="stateName"> ���� ��ü �̸��� �����մϴ�. </param>
		void RemoveVar( System::String^ stateName );

		/// <summary>
		/// �ִϸ��̼� �Ű����� ���� �����ɴϴ�.
		/// </summary>
		/// <param name="varName"> �Ű����� �̸��� �����մϴ�. </param>
		System::Object^ GetVar( System::String^ varName );

		/// <summary>
		/// �ִϸ��̼� ��ȯ ���¸� �߰��մϴ�.
		/// </summary>
		/// <param name="from"> ���� �ִϸ��̼� ���� ��ü�� ��� �̸��� �����մϴ�. </param>
		/// <param name="value"> �ִϸ��̼� ��ȯ ���� ����ü�� �����մϴ�. </param>
		void AddTransition( System::String^ from, AnimationTransitionCondition value );

		/// <summary>
		/// �ִϸ��̼� ��ȯ ���¸� �����մϴ�.
		/// </summary>
		/// <param name="from"> ���� �ִϸ��̼� ���� ��ü�� ��� �̸��� �����մϴ�. </param>
		/// <param name="value"> �ִϸ��̼� ��ȯ ���� ����ü�� �����մϴ�. ���� ������� ��� �ֻ��� Ž�� ��Ҹ� ����մϴ�. </param>
		void RemoveTransition( System::String^ from, AnimationTransitionCondition value );

		/// <summary>
		/// �ִϸ��̼� ��ȯ ���¸� �����մϴ�.
		/// </summary>
		/// <param name="from"> ���� �ִϸ��̼� ���� ��ü�� ��� �̸��� �����մϴ�. </param>
		void RemoveTransition( System::String^ from ) { RemoveTransition( from, AnimationTransitionCondition() ); }

		/// <summary>
		/// �ִϸ��̼� ��ȯ ���¸� �����ɴϴ�.
		/// </summary>
		/// <param name="from"> ���� �ִϸ��̼� ���� ��ü�� ��� �̸��� �����մϴ�. </param>
		System::Collections::Generic::IList<AnimationTransitionCondition>^ GetTransition( System::String^ from );

		/// <summary>
		/// �⺻ �ִϸ��̼� ���� ��ü �̸��� �����ɴϴ�.
		/// </summary>
		property System::String^ DefaultState
		{
			System::String^ get();
		}
	};
}