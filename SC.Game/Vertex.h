#pragma once

namespace SC::Game
{
	/// <summary>
	/// ������ ���� ����� ǥ���մϴ�.
	/// </summary>
	public value struct BoneIndices
	{
		/// <summary>
		/// ù ��° ������ ǥ���մϴ�.
		/// </summary>
		int X;

		/// <summary>
		/// �� ��° ������ ǥ���մϴ�.
		/// </summary>
		int Y;

		/// <summary>
		/// �� ��° ������ ǥ���մϴ�.
		/// </summary>
		int Z;

		/// <summary>
		/// �� ��° ������ ǥ���մϴ�.
		/// </summary>
		int W;
	};

	/// <summary>
	/// ���� ������ ǥ���մϴ�.
	/// </summary>
	public value struct Vertex
	{
		/// <summary>
		/// ������ ��ġ�� ǥ���մϴ�.
		/// </summary>
		System::Numerics::Vector3 Pos;

		/// <summary>
		/// ������ ���� ǥ���մϴ�.
		/// </summary>
		System::Numerics::Vector4 Color;

		/// <summary>
		/// ������ �ؽ�ó ��ǥ�� ǥ���մϴ�.
		/// </summary>
		System::Numerics::Vector2 Tex;

		/// <summary>
		/// ������ ������ ǥ���մϴ�.
		/// </summary>
		System::Numerics::Vector3 Normal;

		/// <summary>
		/// ������ ź��Ʈ�� ǥ���մϴ�.
		/// </summary>
		System::Numerics::Vector3 Tangent;

		/// <summary>
		/// <see cref="Vertex"/> ����ü�� �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="pos"> ������ ��ġ�� �����մϴ�. </param>
		/// <param name="color"> ������ ���� �����մϴ�. </param>
		/// <param name="tex"> ������ �ؽ�ó ��ǥ�� �����մϴ�. </param>
		/// <param name="normal"> ������ ������ �����մϴ�. </param>
		/// <param name="tangent"> ������ ź��Ʈ�� �����մϴ�. </param>
		Vertex( System::Numerics::Vector3 pos, System::Numerics::Vector4 color, System::Numerics::Vector2 tex, System::Numerics::Vector3 normal, System::Numerics::Vector3 tangent )
		{
			Pos = pos;
			Color = color;
			Tex = tex;
			Normal = normal;
			Tangent = tangent;
		}

		/// <summary>
		/// <see cref="Vertex"/> ����ü�� �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="pos"> ������ ��ġ�� �����մϴ�. </param>
		/// <param name="tex"> ������ �ؽ�ó ��ǥ�� �����մϴ�. </param>
		/// <param name="normal"> ������ ������ �����մϴ�. </param>
		/// <param name="tangent"> ������ ź��Ʈ�� �����մϴ�. </param>
		Vertex( System::Numerics::Vector3 pos, System::Numerics::Vector2 tex, System::Numerics::Vector3 normal, System::Numerics::Vector3 tangent ) : Vertex( pos, System::Numerics::Vector4::One, tex, normal, tangent )
		{

		}

		/// <summary>
		/// <see cref="Vertex"/> ����ü�� �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="pos"> ������ ��ġ�� �����մϴ�. </param>
		/// <param name="tex"> ������ �ؽ�ó ��ǥ�� �����մϴ�. </param>
		/// <param name="normal"> ������ ������ �����մϴ�. </param>
		Vertex( System::Numerics::Vector3 pos, System::Numerics::Vector2 tex, System::Numerics::Vector3 normal ) : Vertex( pos, System::Numerics::Vector4::One, tex, normal, System::Numerics::Vector3::Zero )
		{

		}

		/// <summary>
		/// <see cref="Vertex"/> ����ü�� �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="pos"> ������ ��ġ�� �����մϴ�. </param>
		/// <param name="color"> ������ ���� �����մϴ�. </param>
		/// <param name="normal"> ������ ������ �����մϴ�. </param>
		Vertex( System::Numerics::Vector3 pos, System::Numerics::Vector4 color, System::Numerics::Vector3 normal ) : Vertex( pos, color, System::Numerics::Vector2::Zero, normal, System::Numerics::Vector3::Zero )
		{

		}
	};

	/// <summary>
	/// ��Ű�� ������ �����ϴ� ���� ������ ǥ���մϴ�.
	/// </summary>
	public value struct SkinnedVertex
	{
		/// <summary>
		/// ������ ��ġ�� ǥ���մϴ�.
		/// </summary>
		System::Numerics::Vector3 Pos;

		/// <summary>
		/// ������ ���� ǥ���մϴ�.
		/// </summary>
		System::Numerics::Vector4 Color;

		/// <summary>
		/// ������ �ؽ�ó ��ǥ�� ǥ���մϴ�.
		/// </summary>
		System::Numerics::Vector2 Tex;

		/// <summary>
		/// ������ ������ ǥ���մϴ�.
		/// </summary>
		System::Numerics::Vector3 Normal;

		/// <summary>
		/// ������ ź��Ʈ�� ǥ���մϴ�.
		/// </summary>
		System::Numerics::Vector3 Tangent;

		/// <summary>
		/// ������ ����ġ�� ǥ���մϴ�.
		/// </summary>
		System::Numerics::Vector3 Weights;

		/// <summary>
		/// ������ ���� ���� ����� ǥ���մϴ�.
		/// </summary>
		BoneIndices Indices;

		/// <summary>
		/// <see cref="Vertex"/> ����ü�� �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="pos"> ������ ��ġ�� �����մϴ�. </param>
		/// <param name="color"> ������ ���� �����մϴ�. </param>
		/// <param name="tex"> ������ �ؽ�ó ��ǥ�� �����մϴ�. </param>
		/// <param name="normal"> ������ ������ �����մϴ�. </param>
		/// <param name="tangent"> ������ ź��Ʈ�� �����մϴ�. </param>
		SkinnedVertex( System::Numerics::Vector3 pos, System::Numerics::Vector4 color, System::Numerics::Vector2 tex, System::Numerics::Vector3 normal, System::Numerics::Vector3 tangent )
		{
			Pos = pos;
			Color = color;
			Tex = tex;
			Normal = normal;
			Tangent = tangent;
		}

		/// <summary>
		/// <see cref="Vertex"/> ����ü�� �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="pos"> ������ ��ġ�� �����մϴ�. </param>
		/// <param name="tex"> ������ �ؽ�ó ��ǥ�� �����մϴ�. </param>
		/// <param name="normal"> ������ ������ �����մϴ�. </param>
		/// <param name="tangent"> ������ ź��Ʈ�� �����մϴ�. </param>
		SkinnedVertex( System::Numerics::Vector3 pos, System::Numerics::Vector2 tex, System::Numerics::Vector3 normal, System::Numerics::Vector3 tangent ) : SkinnedVertex( pos, System::Numerics::Vector4::One, tex, normal, tangent )
		{

		}

		/// <summary>
		/// <see cref="Vertex"/> ����ü�� �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="pos"> ������ ��ġ�� �����մϴ�. </param>
		/// <param name="tex"> ������ �ؽ�ó ��ǥ�� �����մϴ�. </param>
		/// <param name="normal"> ������ ������ �����մϴ�. </param>
		SkinnedVertex( System::Numerics::Vector3 pos, System::Numerics::Vector2 tex, System::Numerics::Vector3 normal ) : SkinnedVertex( pos, System::Numerics::Vector4::One, tex, normal, System::Numerics::Vector3::Zero )
		{

		}

		/// <summary>
		/// <see cref="Vertex"/> ����ü�� �� �ν��Ͻ��� �ʱ�ȭ�մϴ�.
		/// </summary>
		/// <param name="pos"> ������ ��ġ�� �����մϴ�. </param>
		/// <param name="color"> ������ ���� �����մϴ�. </param>
		/// <param name="normal"> ������ ������ �����մϴ�. </param>
		SkinnedVertex( System::Numerics::Vector3 pos, System::Numerics::Vector4 color, System::Numerics::Vector3 normal ) : SkinnedVertex( pos, color, System::Numerics::Vector2::Zero, normal, System::Numerics::Vector3::Zero )
		{

		}
	};
}