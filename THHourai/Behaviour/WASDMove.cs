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
			var forward = Vector3.UnitZ;
			var right = Vector3.UnitX;

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
	}
}