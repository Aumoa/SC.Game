#pragma once

namespace SC::Game::UI
{
	struct alignas( 256 ) Brush_Constants
	{
		int Type;
		float Opacity;
		float padding[2];
		float Attribute0[4];
		float Attribute1[4];
	};

	/// <summary>
	/// �׷��� ��ü�� �׸��� �� ����� ��ü�� �����մϴ�. �Ļ��� Ŭ������ ������ �׸��� ����� �����մϴ�.
	/// </summary>
	public ref class Brush
	{
		bool mFreezed = false;

	internal:
		Heap* mConstantBuffer = nullptr;
		Brush_Constants* mConstants = nullptr;

	internal:
		Brush( int type );

		void UpdateBuffer();

	public:
		~Brush();
		!Brush();

		/// <summary>
		/// �ش� ��ü�� �����մϴ�. �Ӽ��� ������ �� �����ϴ�.
		/// </summary>
		void Freeze();

		/// <summary> 
		/// �귯�� ��ü�� ������ �����ϰų� �����ɴϴ�.
		/// </summary>
		property float Opacity
		{
			float get();
			void set( float value );
		}

		/// <summary>
		/// �ش� ��ü�� ����Ǿ����� ���θ� ��Ÿ���� ���� �����ɴϴ�.
		/// </summary>
		property bool IsFreezed
		{
			bool get();
		}
	};
}