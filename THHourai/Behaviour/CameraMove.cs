using System;
using System.Collections.Generic;
using System.Numerics;
using System.Text;
using SC.Game;

namespace THHourai
{
	class CameraMove : Behaviour
	{
		public CameraMove() : base()
		{
			
		}

		public override void Update()
		{
			if ( Input.GetKeyDown( KeyCode.Escape ) )
			{
				Cursor.LockState = CursorLockMode.None;
			}
		}

		public override void LateUpdate()
		{
			bool leftKey = Input.GetKey( KeyCode.LeftArrow );
			bool rightKey = Input.GetKey( KeyCode.RightArrow );
			bool upKey = Input.GetKey( KeyCode.UpArrow );
			bool downKey = Input.GetKey( KeyCode.DownArrow );

			ScreenPadding( ref leftKey, ref rightKey, ref upKey, ref downKey );
			MovePosition( leftKey, rightKey, upKey, downKey );
		}

		void ScreenPadding( ref bool leftKey, ref bool rightKey, ref bool upKey, ref bool downKey )
		{
			var mousePosition = Input.MousePosition;
			if ( mousePosition.X < 10 )
			{
				leftKey = true;
			}

			else if ( mousePosition.X > App.Width - 10 )
			{
				rightKey = true;
			}

			if ( mousePosition.Y < 10 )
			{
				upKey = true;
			}

			else if ( mousePosition.Y > App.Height - 10 )
			{
				downKey = true;
			}
		}

		void MovePosition( bool leftKey, bool rightKey, bool upKey, bool downKey )
		{
			var delta = Time.FixedDeltaTime;
			bool updated = false;

			var right = Vector3.UnitX * delta;
			var forward = Vector3.UnitZ * delta;

			var move = Vector3.Zero;

			if ( leftKey )
			{
				move -= right;
				updated = true;
			}

			if ( rightKey )
			{
				move += right;
				updated = true;
			}

			if ( downKey )
			{
				move -= forward;
				updated = true;
			}

			if ( upKey )
			{
				move += forward;
				updated = true;
			}

			if ( updated )
			{
				Transform.Position += move;
			}
		}
	}
}