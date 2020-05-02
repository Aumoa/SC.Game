#pragma once

namespace SC::Game
{
	/// <summary>
	/// 뼈대의 색인 목록을 표현합니다.
	/// </summary>
	public value struct BoneIndices
	{
		/// <summary>
		/// 첫 번째 색인을 표현합니다.
		/// </summary>
		int X;

		/// <summary>
		/// 두 번째 색인을 표현합니다.
		/// </summary>
		int Y;

		/// <summary>
		/// 세 번째 색인을 표현합니다.
		/// </summary>
		int Z;

		/// <summary>
		/// 네 번째 색인을 표현합니다.
		/// </summary>
		int W;
	};

	/// <summary>
	/// 단일 정점을 표현합니다.
	/// </summary>
	public value struct Vertex
	{
		/// <summary>
		/// 정점의 위치를 표현합니다.
		/// </summary>
		System::Numerics::Vector3 Pos;

		/// <summary>
		/// 정점의 색을 표현합니다.
		/// </summary>
		System::Numerics::Vector4 Color;

		/// <summary>
		/// 정점의 텍스처 좌표를 표현합니다.
		/// </summary>
		System::Numerics::Vector2 Tex;

		/// <summary>
		/// 정점의 법선을 표현합니다.
		/// </summary>
		System::Numerics::Vector3 Normal;

		/// <summary>
		/// 정점의 탄젠트를 표현합니다.
		/// </summary>
		System::Numerics::Vector3 Tangent;

		/// <summary>
		/// <see cref="Vertex"/> 구조체의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="pos"> 정점의 위치를 전달합니다. </param>
		/// <param name="color"> 정점의 색을 전달합니다. </param>
		/// <param name="tex"> 정점의 텍스처 좌표를 전달합니다. </param>
		/// <param name="normal"> 정점의 법선을 전달합니다. </param>
		/// <param name="tangent"> 정점의 탄젠트를 전달합니다. </param>
		Vertex( System::Numerics::Vector3 pos, System::Numerics::Vector4 color, System::Numerics::Vector2 tex, System::Numerics::Vector3 normal, System::Numerics::Vector3 tangent )
		{
			Pos = pos;
			Color = color;
			Tex = tex;
			Normal = normal;
			Tangent = tangent;
		}

		/// <summary>
		/// <see cref="Vertex"/> 구조체의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="pos"> 정점의 위치를 전달합니다. </param>
		/// <param name="tex"> 정점의 텍스처 좌표를 전달합니다. </param>
		/// <param name="normal"> 정점의 법선을 전달합니다. </param>
		/// <param name="tangent"> 정점의 탄젠트를 전달합니다. </param>
		Vertex( System::Numerics::Vector3 pos, System::Numerics::Vector2 tex, System::Numerics::Vector3 normal, System::Numerics::Vector3 tangent ) : Vertex( pos, System::Numerics::Vector4::One, tex, normal, tangent )
		{

		}

		/// <summary>
		/// <see cref="Vertex"/> 구조체의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="pos"> 정점의 위치를 전달합니다. </param>
		/// <param name="tex"> 정점의 텍스처 좌표를 전달합니다. </param>
		/// <param name="normal"> 정점의 법선을 전달합니다. </param>
		Vertex( System::Numerics::Vector3 pos, System::Numerics::Vector2 tex, System::Numerics::Vector3 normal ) : Vertex( pos, System::Numerics::Vector4::One, tex, normal, System::Numerics::Vector3::Zero )
		{

		}

		/// <summary>
		/// <see cref="Vertex"/> 구조체의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="pos"> 정점의 위치를 전달합니다. </param>
		/// <param name="color"> 정점의 색을 전달합니다. </param>
		/// <param name="normal"> 정점의 법선을 전달합니다. </param>
		Vertex( System::Numerics::Vector3 pos, System::Numerics::Vector4 color, System::Numerics::Vector3 normal ) : Vertex( pos, color, System::Numerics::Vector2::Zero, normal, System::Numerics::Vector3::Zero )
		{

		}
	};

	/// <summary>
	/// 스키닝 정보를 포함하는 단일 정점을 표현합니다.
	/// </summary>
	public value struct SkinnedVertex
	{
		/// <summary>
		/// 정점의 위치를 표현합니다.
		/// </summary>
		System::Numerics::Vector3 Pos;

		/// <summary>
		/// 정점의 색을 표현합니다.
		/// </summary>
		System::Numerics::Vector4 Color;

		/// <summary>
		/// 정점의 텍스처 좌표를 표현합니다.
		/// </summary>
		System::Numerics::Vector2 Tex;

		/// <summary>
		/// 정점의 법선을 표현합니다.
		/// </summary>
		System::Numerics::Vector3 Normal;

		/// <summary>
		/// 정점의 탄젠트를 표현합니다.
		/// </summary>
		System::Numerics::Vector3 Tangent;

		/// <summary>
		/// 정점의 가중치를 표현합니다.
		/// </summary>
		System::Numerics::Vector3 Weights;

		/// <summary>
		/// 정점의 뼈대 색인 목록을 표현합니다.
		/// </summary>
		BoneIndices Indices;

		/// <summary>
		/// <see cref="Vertex"/> 구조체의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="pos"> 정점의 위치를 전달합니다. </param>
		/// <param name="color"> 정점의 색을 전달합니다. </param>
		/// <param name="tex"> 정점의 텍스처 좌표를 전달합니다. </param>
		/// <param name="normal"> 정점의 법선을 전달합니다. </param>
		/// <param name="tangent"> 정점의 탄젠트를 전달합니다. </param>
		SkinnedVertex( System::Numerics::Vector3 pos, System::Numerics::Vector4 color, System::Numerics::Vector2 tex, System::Numerics::Vector3 normal, System::Numerics::Vector3 tangent )
		{
			Pos = pos;
			Color = color;
			Tex = tex;
			Normal = normal;
			Tangent = tangent;
		}

		/// <summary>
		/// <see cref="Vertex"/> 구조체의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="pos"> 정점의 위치를 전달합니다. </param>
		/// <param name="tex"> 정점의 텍스처 좌표를 전달합니다. </param>
		/// <param name="normal"> 정점의 법선을 전달합니다. </param>
		/// <param name="tangent"> 정점의 탄젠트를 전달합니다. </param>
		SkinnedVertex( System::Numerics::Vector3 pos, System::Numerics::Vector2 tex, System::Numerics::Vector3 normal, System::Numerics::Vector3 tangent ) : SkinnedVertex( pos, System::Numerics::Vector4::One, tex, normal, tangent )
		{

		}

		/// <summary>
		/// <see cref="Vertex"/> 구조체의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="pos"> 정점의 위치를 전달합니다. </param>
		/// <param name="tex"> 정점의 텍스처 좌표를 전달합니다. </param>
		/// <param name="normal"> 정점의 법선을 전달합니다. </param>
		SkinnedVertex( System::Numerics::Vector3 pos, System::Numerics::Vector2 tex, System::Numerics::Vector3 normal ) : SkinnedVertex( pos, System::Numerics::Vector4::One, tex, normal, System::Numerics::Vector3::Zero )
		{

		}

		/// <summary>
		/// <see cref="Vertex"/> 구조체의 새 인스턴스를 초기화합니다.
		/// </summary>
		/// <param name="pos"> 정점의 위치를 전달합니다. </param>
		/// <param name="color"> 정점의 색을 전달합니다. </param>
		/// <param name="normal"> 정점의 법선을 전달합니다. </param>
		SkinnedVertex( System::Numerics::Vector3 pos, System::Numerics::Vector4 color, System::Numerics::Vector3 normal ) : SkinnedVertex( pos, color, System::Numerics::Vector2::Zero, normal, System::Numerics::Vector3::Zero )
		{

		}
	};
}