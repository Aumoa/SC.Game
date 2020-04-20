using System;
using System.Collections.Generic;
using System.Numerics;
using SC.Game;

namespace THHourai
{
	class CameraRotate : Behaviour
	{
		float rotX = 0;
		float rotY = 0;

		public CameraRotate() : base()
		{

		}

		public override void Start()
		{
			base.Start();
		}

		public override void Update()
		{
			if ( !Cursor.Visible && Input.GetKeyDown( KeyCode.Escape ) )
			{
				Cursor.LockState = CursorLockMode.None;
				Cursor.Visible = true;
			}

			if ( Cursor.Visible && Input.GetKeyDown( KeyCode.Mouse0 ) )
			{
				Cursor.LockState = CursorLockMode.Locked;
				Cursor.Visible = false;
			}

			base.Update();
		}

		public override void LateUpdate()
		{
			if ( !Cursor.Visible )
			{
				var delta = Input.MousePosition;
				var center = Input.CenterMousePosition;

				delta.X -= center.X;
				delta.Y -= center.Y;

				var rotX = ( float )delta.X / 1000.0f;
				var rotY = ( float )delta.Y / 1000.0f;

				this.rotX += rotX;
				this.rotX = this.rotX % ( 3.141592f * 2.0f );
				this.rotY = Math.Clamp( this.rotY + rotY, -3.141592f * 0.5f, 3.141592f * 0.5f );

				var rot = Quaternion.CreateFromAxisAngle( Vector3.UnitY, this.rotX );
				rot = Quaternion.CreateFromAxisAngle( Vector3.Transform( Vector3.UnitX, rot ), this.rotY ) * rot;
				Transform.Rotation = rot;
			}

			target.DirectionUpdate();

			base.LateUpdate();
		}

		public CameraFollow target;
	}
}