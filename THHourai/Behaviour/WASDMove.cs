using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;

using SC.Game;

namespace THHourai
{
	class WASDMove : Behaviour
	{
		Rigidbody rigidbody;
		Animator animator;

		public WASDMove() : base()
		{

		}

		public override object Clone()
		{
			return new WASDMove();
		}

		public override void Start()
		{
			rigidbody = GetComponent<Rigidbody>();
			animator = GetComponentInChildren<Animator>();

			base.Start();
		}

		public override void FixedUpdate()
		{
			Vector3 up = Vector3.UnitY;
			Vector3 forward;
			Vector3 right;

			Physics.RayCast( new Ray( new Vector3( 0.0f, 5.0f, 0.0f ), new Vector3( 0.0f, -1.0f, 0.0f ) ) );

			if ( cam != null )
			{
				forward = cam.Direction;
				right = Vector3.Cross( up, forward );
			}
			else
			{
				forward = Vector3.UnitZ;
				right = Vector3.UnitX;
			}

			Vector3 mov = Vector3.Zero;
			if ( Input.GetKey( KeyCode.D ) )
			{
				mov += right;
			}

			if ( Input.GetKey( KeyCode.A ) )
			{
				mov -= right;
			}

			if ( Input.GetKey( KeyCode.W ) )
			{
				mov += forward;
			}

			if ( Input.GetKey( KeyCode.S ) )
			{
				mov -= forward;
			}

			if ( mov.Length() > 0.001f )
			{
				mov = Vector3.Normalize( mov );

				var rotateFrom = Transform.Rotation;
				Transform.LookTo( mov );
				var rotateTo = Transform.Rotation;

				var rotate = Quaternion.Slerp( rotateFrom, rotateTo, Math.Clamp( Time.FixedDeltaTime * rotateSpeed, 0.0f, 1.0f ) );
				Transform.Rotation = rotate;

				var position = rigidbody.Position;
				position += mov * speed * Time.FixedDeltaTime;
				position.Y = 0.0f;
				rigidbody.Position = position;

				animator.SetVar( "walkSpeed", 1.0f );
			}
			else
			{
				animator.SetVar( "walkSpeed", 0.0f );
			}
		}

		public float speed = 4.0f;
		public float rotateSpeed = 10.0f;

		public static CameraFollow cam;
	}
}