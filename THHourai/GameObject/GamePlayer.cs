using System;
using System.Collections.Generic;
using System.Text;
using System.Numerics;
using SC.Game;

namespace THHourai
{
	class GamePlayer : GameObject
	{
		static GamePlayer instance;

		public GamePlayer() : base( "GamePlayer" )
		{
			var task = AssetBundle.LoadAssetAsync( @"Assets\Model\Syameimaru_Aya\Syameimaru_Aya.mdl" );
			var results = task.Result;

			results.Transform.Parent = Transform;
			results.Transform.LocalScale = new Vector3( 0.01f, 0.01f, 0.01f );
			results.Transform.LocalPosition = new Vector3( 0.0f, 0.0f, 0.0f );

			var rigidbody = AddComponent<Rigidbody>();
			var capsule = AddComponent<CapsuleCollider>();
			AddComponent<WASDMove>();

			rigidbody.Constraints = RigidbodyConstraints.Rotation;

			capsule.Center = new Vector3( 0.0f, 1.0f, 0.0f );
			capsule.Radius = 0.25f;
			capsule.Height = 1.5f;
			capsule.Rotation = Quaternion.CreateFromAxisAngle( Vector3.UnitZ, 3.14159f * 0.5f );
		}

		public static GamePlayer Instance
		{
			get
			{
				if ( instance == null )
				{
					instance = new GamePlayer();
				}

				return instance;
			}
		}
	}
}
