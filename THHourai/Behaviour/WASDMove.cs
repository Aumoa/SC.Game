using System;
using System.Numerics;

using SC.Game;

namespace THHourai
{
	class WASDMove : Behaviour
	{
		Rigidbody rigidbody;

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

			base.Start();
		}

		public override void Update()
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
				mov += right * Speed;
			}

			if ( Input.GetKey( KeyCode.A ) )
			{
				mov -= right * Speed;
			}

			if ( Input.GetKey( KeyCode.W ) )
			{
				mov += forward * Speed;
			}

			if ( Input.GetKey( KeyCode.S ) )
			{
				mov -= forward * Speed;
			}

			if ( mov.Length() > 0.001f )
			{
				rigidbody.Velocity = mov;
			}
		}

		public float Speed
		{
			get;
			set;
		} = 1.0f;

		public static CameraFollow cam;
	}
}