using System;
using System.Collections.Generic;
using System.Numerics;
using System.Text;
using SC.Game;

namespace THHourai
{
	class AshenTree : GameObject
	{
		static GameObject[] models;

		public AshenTree( string xName ) : base( xName )
		{
			var random = new Random();
			var index = random.Next( 0, 10 );

			var gameObject = models[index].Clone() as GameObject;
			gameObject.Transform.Parent = Transform;

			var capsuleCollider = AddComponent<CapsuleCollider>();
			capsuleCollider.Rotation = Quaternion.CreateFromAxisAngle( Vector3.UnitZ, 3.141592f * 0.5f );
			capsuleCollider.Radius = 100.0f;
			capsuleCollider.Height = 100.0f;
		}

		static AshenTree()
		{
			models = new GameObject[10];
			for ( int i = 0; i < models.Length; ++i )
			{
				models[i] = AssetBundle.LoadAssetAsync( @"Assets/Model/Trees/AshenTree" + i + ".mdl" ).Result;
			}
		}
	}
}
