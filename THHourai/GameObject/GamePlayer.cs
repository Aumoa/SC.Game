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

		PhysicsMaterial physicsMaterial;

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

			physicsMaterial = new PhysicsMaterial( "GamePlayer.physicsMaterial" );
			physicsMaterial.Restitution = 0.0f;

			rigidbody.Mass = 1.0f;
			capsule.Material = physicsMaterial;

			var animator = GetComponentInChildren<Animator>();
			var controller = animator.Controller;

			//
			// walkSpeed 변수
			controller.AddVar( "walkSpeed", 0.0f );

			//
			// ToWalk 트랜지션
			controller.AddTransition( "Stand", new AnimationTransitionCondition( "Walk", "walkSpeed", 0.3f, ( object animVar ) =>
			{
				if ( animVar is float value )
				{
					if ( value >= 0.1f )
					{
						return true;
					}
				}

				return false;
			} ) );

			//
			// ToStand 트랜지션
			controller.AddTransition( "Walk", new AnimationTransitionCondition( "Stand", "walkSpeed", 0.3f, ( object animVar ) =>
			{
				if ( animVar is float value )
				{
					if ( value <= 0.9f )
					{
						return true;
					}
				}

				return false;
			} ) );
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
