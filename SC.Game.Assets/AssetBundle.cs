using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SC.Game.Assets
{
	/// <summary>
	/// 게임 데이터 자산에 대한 인터페이스를 제공합니다.
	/// </summary>
	public static class AssetBundle
	{
		/// <summary>
		/// 데이터 자산을 불러옵니다.
		/// </summary>
		/// <param name="filepath"> 파일 경로를 전달합니다. </param>
		/// <returns> 불러오기 완료된 데이터 형식을 반환합니다. </returns>
		public static LoadedInfo LoadAsset( string filepath )
		{
			var ext = Path.GetExtension( filepath );
			ext = ext.ToUpper();

			IParser parser;

			switch ( ext )
			{
				case ".MDL":
					parser = new MDL.Parser( filepath );
					break;
				case ".FBX":
					parser = new FBX.Parser( filepath );
					break;
				default:
					parser = new Assimp.Parser( filepath );
					break;
			}

			parser.TryParse();
			return parser.Compose();
		}

		/// <summary>
		/// 데이터 자산을 비동기 형식으로 불러옵니다.
		/// </summary>
		/// <param name="filepath"> 파일 경로를 전달합니다. </param>
		/// <returns> 불러오기 완료된 데이터 형식의 스레드 작업 식별자를 반환합니다. </returns>
		public static Task<LoadedInfo> LoadAssetAsync( string filepath )
		{
			var task = new Task<LoadedInfo>( () => { return LoadAsset( filepath ); } );
			return task;
		}
	}
}
