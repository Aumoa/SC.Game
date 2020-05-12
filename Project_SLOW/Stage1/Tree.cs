using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;
using SC.Game;
using SC.Game.Assets;

namespace Project_SLOW.Stage1
{
	class Tree : GameObject
	{
		static LoadedInfo loadInfo;

		public Tree( string xName ) : base( xName )
		{
			InitializeAssets();

			var go = loadInfo.Composed.Clone() as GameObject;
			go.Transform.Parent = Transform;
			go.Transform.LocalScale = new Vector3( 0.5f );
			go.GetChild( 0 ).GetChild( 0 ).GetChild( 0 ).AddComponent<MeshCollider>();
			go.GetChild( 0 ).GetChild( 0 ).GetChild( 1 ).AddComponent<MeshCollider>();
		}

		void InitializeAssets()
		{
			loadInfo = AssetBundle.LoadAsset( @"Assets\Model\tree_1\tree_1.fbx" );
			loadInfo.Composed.GetChild( 0 ).GetChild( 1 ).Transform.Parent = null;
			loadInfo.Composed.GetChild( 0 ).GetChild( 1 ).Transform.Parent = null;
		}
	}
}
