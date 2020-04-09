#pragma once

namespace SC::Game::UI
{
	/// <summary> ��ȣ ������ ��ġ�� ����Ͽ� ����� ��ġ�� �����ϴ� �г� �����Դϴ�. </summary>
	public ref class RelativePanel : public Panel
	{
	protected:
		/// <summary>
		/// (<see cref="Element"/> Ŭ�������� ��� ��.) ��Ҹ� �����մϴ�. 
		/// </summary>
		/// <param name="clientRect"> �θ��� ������ �簢 ������ ���޵˴ϴ�. </param>
		System::Drawing::RectangleF OnUpdate( System::Drawing::RectangleF clientRect ) override;

	public:
		///
		/// <summary> <see cref="RelativePanel"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="xName"> ��ü �̸��� �����մϴ�. </param>
		RelativePanel( System::String^ xName );

		/// <summary>
		/// �� Ŭ������ �̸� �ؽ� ���� �����ɴϴ�.
		/// </summary>
		static const int ClassName = ( gcnew System::String( "relativepanel" ) )->GetHashCode();

		/// <summary>
		/// ���� �гο� �Ҽӵ� ����� ���ʿ� ��ġ�ϵ��� �����ϴ� �Ӽ��� �ؽ� ���� �����ɴϴ�.
		/// </summary>
		static const int LeftOf = ( gcnew System::String( "leftof" ) )->GetHashCode();

		/// <summary>
		/// ���� �гο� �Ҽӵ� ����� ���ʿ� ��ġ�ϵ��� �����ϴ� �Ӽ��� �ؽ� ���� �����ɴϴ�.
		/// </summary>
		static const int Above = ( gcnew System::String( "above" ) )->GetHashCode();

		/// <summary>
		/// ���� �гο� �Ҽӵ� ����� �����ʿ� ��ġ�ϵ��� �����ϴ� �Ӽ��� �ؽ� ���� �����ɴϴ�.
		/// </summary>
		static const int RightOf = ( gcnew System::String( "rightof" ) )->GetHashCode();

		/// <summary>
		/// ���� �гο� �Ҽӵ� ����� �Ʒ��� ��ġ�ϵ��� �����ϴ� �Ӽ��� �ؽ� ���� �����ɴϴ�.
		/// </summary>
		static const int Below = ( gcnew System::String( "below" ) )->GetHashCode();

		/// <summary>
		/// ���� �гο� �Ҽӵ� ����� ������ ��ġ�ϵ��� �����ϴ� �Ӽ��� �ؽ� ���� �����ɴϴ�.
		/// </summary>
		static const int AlignLeftWith = ( gcnew System::String( "alignleftwith" ) )->GetHashCode();

		/// <summary>
		/// ���� �гο� �Ҽӵ� ����� ������ ��ġ�ϵ��� �����ϴ� �Ӽ��� �ؽ� ���� �����ɴϴ�.
		/// </summary>
		static const int AlignTopWith = ( gcnew System::String( "aligntopwith" ) )->GetHashCode();

		/// <summary>
		/// ���� �гο� �Ҽӵ� ����� �������� ��ġ�ϵ��� �����ϴ� �Ӽ��� �ؽ� ���� �����ɴϴ�.
		/// </summary>
		static const int AlignRightWith = ( gcnew System::String( "alignrightwith" ) )->GetHashCode();

		/// <summary>
		/// ���� �гο� �Ҽӵ� ����� �Ʒ����� ��ġ�ϵ��� �����ϴ� �Ӽ��� �ؽ� ���� �����ɴϴ�.
		/// </summary>
		static const int AlignBottomWith = ( gcnew System::String( "alignbottomwith" ) )->GetHashCode();

	private:
		void ComputeRect( int index, std::vector<gcroot<System::Drawing::RectangleF>>& computedRects, std::vector<bool>& computed );
	};
}