using System;
using System.Collections.Generic;
using System.Text;
using System.Numerics;
using SC.Game;

namespace Project_SLOW
{
	class TargetPositionMove : Behaviour
	{
		Animator animator;
		CharacterController cc;

		Vector3 target;
		bool targetAccepted = false;

		public TargetPositionMove() : base()
		{

		}

		public override void Start()
		{
			animator = GetComponentInChildren<Animator>();
			cc = GetComponentInChildren<CharacterController>();

			target = Transform.LocalPosition;
		}

		public override void FixedUpdate()
		{
			if ( targetAccepted )
			{
				var position = Transform.Position;
				var vec = target - position;
				vec.Y = 0.0f;

				if ( vec.Length() >= 0.1f )
				{
					// 원래의 벡터와 회전 이후 벡터를 계산합니다.
					var fromV = Transform.Forward;
					var toV = Vector3.Normalize( vec );

					// 대상 지점까지의 거리를 계산합니다.
					var distance = Vector3.Distance( position, target );

					// 거리만큼 이동합니다.
					var move = toV * Math.Min( speed * Time.FixedDeltaTime, distance );
					cc.MovePosition( position + move );

					// 대상 방향의 회전 각도를 계산합니다.
					var dot = Vector3.Dot( fromV, toV );
					var axis = Vector3.Cross( fromV, toV );
					var angle = MathF.Acos( dot );

					// 회전 각도를 제한합니다.
					angle = Math.Min( Time.FixedDeltaTime * rotateSpeed, angle );

					if ( axis.Length() < 0.01f )
					{
						axis = Vector3.UnitY;
					}

					axis.X = 0;
					axis.Z = 0;

					axis = Vector3.Normalize( axis );
					Transform.Rotation = Quaternion.CreateFromAxisAngle( axis, angle ) * Transform.Rotation;

					animator.SetVar( "walkSpeed", 1.0f );

					BasePage.Debug = Transform.Position.ToString();
				}
				else
				{
					animator.SetVar( "walkSpeed", 0.0f );
					targetAccepted = false;
				}
			}
		}

		public Vector3 Target
		{
			get
			{
				if ( targetAccepted )
				{
					return Transform.Position;
				}
				else
				{
					return target;
				}
			}
			set
			{
				target = value;
				targetAccepted = true;
			}
		}

		public float speed = 3.0f;
		public float rotateSpeed = 8.0f;
	}
}
