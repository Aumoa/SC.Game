using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SC.Game.Assets
{
	/// <summary>
	/// 데이터 자산의 불러오기 정보를 표현합니다.
	/// </summary>
	public struct LoadedInfo
	{
		/// <summary>
		/// 조립 완성된 게임 오브젝트 형식을 표현합니다.
		/// </summary>
		public GameObject Composed;

		/// <summary>
		/// 데이터 자산에 포함된 모든 메쉬 개체에 대한 목록입니다.
		/// </summary>
		public IList<Mesh> Meshes;

		/// <summary>
		/// 데이터 자산에 포함된 모든 재질 개체에 대한 목록입니다.
		/// </summary>
		public IList<Material> Materials;

		/// <summary>
		/// 데이터 자산에 포함된 애니메이션 클립에 대한 목록입니다.
		/// </summary>
		public IList<AnimationClip> AnimationClips;

		/// <summary>
		/// 데이터 자산에 포함된 모든 텍스처에 대한 목록입니다.
		/// </summary>
		public IList<Texture2D> Textures;
	}
}
