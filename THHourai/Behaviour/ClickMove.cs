using System;
using System.Collections.Generic;
using System.Text;
using SC.Game;

namespace THHourai
{
	class ClickMove : Behaviour
	{
		Camera camera;
		TargetPositionMove player;

		bool lbuttonDown = false;

		public ClickMove() : base()
		{

		}

		public override void Start()
		{
			camera = GameCamera.Instance.GetComponentInChildren<Camera>();
			var player = GamePlayer.Instance;
			this.player = player.GetComponentInChildren<TargetPositionMove>();

			base.Start();
		}

		public override void Update()
		{
			if ( Input.GetKeyDown( KeyCode.Mouse1 ) )
			{
				lbuttonDown = true;
			}

			base.Update();
		}

		public override void FixedUpdate()
		{
			if ( camera != null && lbuttonDown )
			{
				var ray = camera.ScreenPointToRay( Input.MousePosition );
				var hit = Physics.RayCast( ray, ( Tag )CustomTag.Terrain, false );

				if ( hit.Hit )
				{
					player.target = hit.Point;
				}

				lbuttonDown = false;
			}

			base.FixedUpdate();
		}
	}
}
