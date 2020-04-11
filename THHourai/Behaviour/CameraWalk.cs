using System;
using System.Numerics;

using SC.Game;

namespace THHourai
{
	class CameraWalk : Behaviour
	{
		public CameraWalk() : base()
		{

		}

		public override object Clone()
		{
			return new CameraWalk();
		}

		public override void Update()
		{
			var forward = -Vector3.UnitZ;
			var right = Vector3.UnitX;

			Vector3 mov = Vector3.Zero;
			if ( Input.GetKey( KeyCode.RightArrow ) )
			{
				mov += right * Time.DeltaTime * Speed;
			}

			if ( Input.GetKey( KeyCode.LeftArrow ) )
			{
				mov -= right * Time.DeltaTime * Speed;
			}

			if ( Input.GetKey( KeyCode.UpArrow ) )
			{
				mov += forward * Time.DeltaTime * Speed;
			}

			if ( Input.GetKey( KeyCode.DownArrow ) )
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