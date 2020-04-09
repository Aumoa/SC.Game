#pragma once

namespace SC::Game::UI
{
	/// <summary>
	/// ����� �������� ����Ǿ��� ��� �߻��ϴ� �̺�Ʈ�� �븮�� �����Դϴ�.
	/// </summary>
	public delegate void ContentChangedDelegate( System::Object^ content );

	/// <summary>
	/// UI ��� ���� ���� ������ ��Ʈ�Դϴ�. �Ļ� Ŭ������ UI �⺻ ����� �����մϴ�.
	/// </summary>
	public ref class Element : public DependencyObject
	{
		System::String^ mName;
		float mWidth;
		float mHeight;
		System::Object^ mContent;
		Thickness mMargin;
		Anchor mAnchor;
		System::Drawing::RectangleF mActualRenderingRect;

	protected:
		/// <summary>
		/// <see cref="Element"/> Ŭ������ �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="xName"> ��ü�� ���� �̸��� �����մϴ�. </param>
		Element( System::String^ xName );

		/// <summary>
		/// ��Ұ� ���ŵ� �� ȣ��Ǵ� �Լ��Դϴ�.
		/// </summary>
		/// <param name="clientRect"> �θ� ����� ������ ������ ������ ���޵˴ϴ�. </param>
		/// <returns> �ش� ����� ���� ������ ������ ��ȯ�մϴ�. </returns>
		virtual System::Drawing::RectangleF OnUpdate( System::Drawing::RectangleF clientRect );

	internal:
		virtual void Render( CDeviceContext& deviceContext );

	public:
		/// <summary>
		/// (<see cref="Object"/> Ŭ�������� ��� ��.) ��ü�� ��� ������ �ؽ�Ʈ �������� ��ȯ�մϴ�.
		/// </summary>
		System::String^ ToString() override;

		/// <summary>
		/// UI ��Ҹ� ������Ʈ�մϴ�.
		/// </summary>
		/// <param name="clientRect"> �� ����� ������Ʈ�� ȣ���� UI ���̾ƿ��� Ŭ���̾�Ʈ ������ �����մϴ�. </param>
		virtual void Update( System::Drawing::RectangleF clientRect );

		/// <summary>
		/// ����� ���� �β��� �����ϰų� �����ɴϴ�.
		/// </summary>
		property Thickness Margin
		{
			Thickness get();
			void set( Thickness value );
		}

		/// <summary>
		/// ����� ���� �̸��� �����ɴϴ�.
		/// </summary>
		property System::String^ Name
		{
			System::String^ get();
		}

		/// <summary>
		/// UI ������ ��Ҹ� �����ϰų� �����ɴϴ�.
		/// </summary>
		property System::Object^ Content
		{
			System::Object^ get();
			void set( System::Object^ value );
		}

		/// <summary>
		/// ����� �ʺ� �����ϰų� �����ɴϴ�.
		/// </summary>
		property float Width
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// ����� ���̸� �����ϰų� �����ɴϴ�.
		/// </summary>
		property float Height
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// ����� �������� �����ϰų� �����ɴϴ�.
		/// </summary>
		property UI::Anchor Anchor
		{
			UI::Anchor get();
			void set( UI::Anchor value );
		}

		/// <summary>
		/// ����� ���� ������ ������ �����ɴϴ�.
		/// </summary>
		property System::Drawing::RectangleF ActualRenderingRect
		{
			System::Drawing::RectangleF get();
		}

		/// <summary>
		/// ����� ������ ��ü�� ����Ǿ��� ��� �߻��ϴ� �̺�Ʈ�Դϴ�.
		/// </summary>
		event ContentChangedDelegate^ ContentChanged;
	};
}