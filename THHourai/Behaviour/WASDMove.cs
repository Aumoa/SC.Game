using System;
using System.Numerics;

using SC.Game;

namespace THHourai
{
	class WASDMove : Behaviour
	{
		public WASDMove() : base()
		{

		}

		public override object Clone()
		{
			return new WASDMove();
		}

		public override void Update()
		{
			var forward = -Vector3.UnitZ;
			var right = Vector3.UnitX;

			Vector3 mov = Vector3.Zero;
			if ( Input.GetKey( KeyCode.D ) )
			{
				mov += right * Time.DeltaTime * Speed;
			}

			if ( Input.GetKey( KeyCode.A ) )
			{
				mov -= right * Time.DeltaTime * Speed;
			}

			if ( Input.GetKey( KeyCode.W ) )
			{
				mov += forward * Time.DeltaTime * Speed;
			}

			if ( Input.GetKey( KeyCode.S ) )
			{
				mov -= forward * Time.DeltaTime * Speed;
			}

			if ( mov.Length() > 0.001f )
			{
				Transform.LocalPosition += mov;
			}
		}

		public float Speed
		{
			get;
			set;
		} = 1.0f;
	}
}