using System;
using System.Collections.Generic;
using System.Text;
using System.Numerics;
using SC.Game;

namespace THHourai
{
	partial class GamePlayer : SingletonGameObject<GamePlayer>
	{
		PhysicsMaterial physicsMaterial;

		public GamePlayer() : base( "GamePlayer" )
		{
			var task = AssetBundle.LoadAssetAsync( @"Assets\Model\Syameimaru_Aya\Syameimaru_Aya.mdl" );
			var results = task.Result.Clone() as GameObject;

			results.Transform.Parent = Transform;
			results.Transform.LocalScale = new Vector3( 0.01f, 0.01f, 0.01f );
			results.Transform.LocalPosition = new Vector3( 0.0f, 0.0f, 0.0f );

			var rigidbody = AddComponent<Rigidbody>();
			var collider = AddComponent<CapsuleCollider>();

			rigidbody.Constraints = RigidbodyConstraints.Rotation;
			collider.Radius = 0.3f;

			physicsMaterial = new PhysicsMaterial( "GamePlayer.physicsMaterial" );
			physicsMaterial.Restitution = 0.0f;

			InitializeComponents();
		}

		void InitializeComponents()
		{
			AddComponent<TargetPositionMove>();

			InitializeAnimator();
		}

		void InitializeAnimator()
		{
			// 애니메이션 설정
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
	}
}
