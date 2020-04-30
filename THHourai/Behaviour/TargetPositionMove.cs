using System;
using System.Collections.Generic;
using System.Numerics;
using System.Text;
using SC.Game;

namespace THHourai
{
	class TargetPositionMove : Behaviour
	{
		Animator animator;
		Rigidbody rigidbody;

		public TargetPositionMove() : base()
		{

		}

		public override void Start()
		{
			animator = GetComponentInChildren<Animator>();
			rigidbody = GetComponentInChildren<Rigidbody>();
		}

		public override void FixedUpdate()
		{
			var position = Transform.Position;
			var vec = target - position;

			if ( vec.Length() >= 0.01f )
			{
				// 원래의 벡터와 회전 이후 벡터를 계산합니다.
				var fromV = Transform.Forward;
				var toV = Vector3.Normalize( vec );

				// 대상 지점까지의 거리를 계산합니다.
				var distance = Vector3.Distance( position, target );

				// 거리만큼 이동합니다.
				var move = toV * Math.Min( speed * Time.FixedDeltaTime, distance );
				rigidbody.MovePosition( position + move );

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
				axis = Vector3.Normalize( axis );
				Transform.Rotation = Quaternion.CreateFromAxisAngle( axis, angle ) * Transform.Rotation;

				animator.SetVar( "walkSpeed", 1.0f );
			}
			else
			{
				animator.SetVar( "walkSpeed", 0.0f );
			}
		}

		public Vector3 target;
		public float speed = 3.0f;
		public float rotateSpeed = 8.0f;
	}
}