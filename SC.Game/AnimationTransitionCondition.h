#pragma once

namespace SC::Game
{
	public delegate bool AnimVarConditionDelegate( System::Object^ value );

	/// <summary>
	/// �ִϸ��̼� ���� ��ȯ�� ���� �Ű����� �� ������ ǥ���մϴ�.
	/// </summary>
	public value struct AnimationTransitionCondition
	{
		/// <summary>
		/// ��ȯ�� �ִϸ��̼� ���� �̸��� �����մϴ�.
		/// </summary>
		System::String^ To;

		/// <summary>
		/// ���� �Ű����� �̸��� �����մϴ�.
		/// </summary>
		System::String^ VarName;

		/// <summary>
		/// ������ �׽�Ʈ�� �Լ��� �����մϴ�.
		/// </summary>
		AnimVarConditionDelegate^ Condition;

		/// <summary>
		/// �ִϸ��̼� ��� �ð��� ����� ��� ��ȯ�� �����ϴ�.
		/// </summary>
		bool HasExitTime;

		/// <summary>
		/// �� ��ȯ�� ����Ǵ� �ð��� �����մϴ�.
		/// </summary>
		float BlendTime;

		/// <summary>
		/// <see cref="AnimationTransitionCondition"/> ����ü�� �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="to"> ��ȯ�� �ִϸ��̼� ���� �̸��� �����մϴ�. </param>
		/// <param name="varName"> ���� �Ű����� �̸��� �����մϴ�. </param>
		/// <param name="blendTime"> �� ��ȯ�� ����Ǵ� �ð��� �����մϴ�. </param>
		/// <param name="condition"> ������ �׽�Ʈ�� �Լ��� �����մϴ�. </param>
		AnimationTransitionCondition( System::String^ to, System::String^ varName, float blendTime, AnimVarConditionDelegate^ condition )
		{
			this->To = to;
			this->VarName = varName;
			this->Condition = condition;
			this->HasExitTime = false;
			this->BlendTime = blendTime;
		}
	};
}