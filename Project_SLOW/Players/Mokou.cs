using System;
using System.Collections.Generic;
using System.Text;
using System.Numerics;
using SC.Game;

namespace Project_SLOW
{
	class Mokou : Unit
	{
		static GameObject modelAsset;

		public Mokou( string xName ) : base( xName )
		{
			LoadAssets();

			var go = modelAsset.Clone() as GameObject;
			go.Transform.Parent = Transform;
			go.Transform.LocalScale = new Vector3( 0.01f, 0.01f, 0.01f );

			InitializeAnimator();
			LoadComponents();
		}

		void LoadAssets()
		{
			modelAsset = AssetBundle.LoadAssetAsync( "Assets/Model/Mokou/mokou.mdl" ).Result;
		}

		void LoadComponents()
		{
			AddComponent<MokouAttackWeapon>();
			AddComponent<AttackAbility>();
		}
	}
}
