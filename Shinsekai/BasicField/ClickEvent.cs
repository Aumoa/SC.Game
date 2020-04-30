using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using SC.Game;
using Shinsekai.Weapons;

namespace Shinsekai.BasicField
{
	class ClickEvent : Behaviour
	{
		Camera camera;

		bool lbuttonDown = false;

		public ClickEvent() : base()
		{

		}

		public override void Start()
		{
			camera = GameCamera.Instance.GetComponentInChildren<Camera>();

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
				var hit = Physics.RayCast( ray );

				if ( hit.Hit )
				{
					var tag = hit.Collider.Object.Tag;
					if ( ( tag & ( Tag )CustomTag.Terrain ) == ( Tag )CustomTag.Terrain )
					{
						var moveAbility = GetComponent<MoveAbility>();
						moveAbility.ApplyEffect( hit.Point );
					}
					else if ( ( tag & ( Tag )CustomTag.AbilityTarget ) == ( Tag )CustomTag.AbilityTarget )
					{
						var attackAbility = GetComponent<AttackAbility>();
						if ( attackAbility == null )
						{
							var moveAbility = GetComponent<MoveAbility>();
							moveAbility.ApplyEffect( hit.Collider.Object.Transform.Position );
						}
						else
						{
							attackAbility.ApplyEffect( hit.Collider.Object );
						}
					}
				}

				lbuttonDown = false;
			}

			base.FixedUpdate();
		}
	}
}
