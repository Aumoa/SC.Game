using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;
using SC.Game;

namespace Project_SLOW
{
	class CursorSystem : Behaviour
	{
		public override void Update()
		{
			if ( App.Activated )
			{
				if ( Input.GetKeyDown( KeyCode.Escape ) )
				{
					Cursor.LockState = CursorLockMode.None;
				}

				var rect = new RectangleF( 0.0f, 0.0f, App.Width, App.Height );
				var cursor = Input.MousePosition;

				if ( rect.Contains( ( float )cursor.X, ( float )cursor.Y ) && Input.GetKeyDown( KeyCode.Mouse0 ) )
				{
					Cursor.LockState = CursorLockMode.Confined;
				}
			}
		}
	}
}
