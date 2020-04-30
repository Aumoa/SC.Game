using System;
using System.Collections.Generic;
using System.Text;
using System.Xml.Linq;
using System.Numerics;
using SC.Game;

namespace Project_SLOW
{
	class Unit : GameObject
	{
		float speed = 0.0f;
		float radius = 0.15f;

		public Unit( string xName ) : base( xName )
		{
			LoadComponents();

			Tag = ( Tag )CustomTag.AbilityTarget;
		}

		public float Speed
		{
			get
			{
				return speed;
			}
		}

		public float Radius
		{
			get
			{
				return radius;
			}
		}

		void LoadComponents()
		{
			//var rigidbody = AddComponent<Rigidbody>();
			//var collider = AddComponent<CapsuleCollider>();
			var cc = AddComponent<CharacterController>();

			//rigidbody.Constraints = RigidbodyConstraints.Rotation;
			//collider.Radius = radius;
			//collider.Height = 1.0f;
			//collider.Center = new Vector3( 0.0f, 0.2f, 0.0f );

			AddComponent<Properties>();
			AddComponent<MoveAbility>();
			AddComponent<TargetPositionMove>();
		}

		protected void InitializeAnimator()
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
