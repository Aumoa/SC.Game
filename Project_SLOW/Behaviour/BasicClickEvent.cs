using System;
using System.Collections.Generic;
using System.Text;
using SC.Game;

namespace Project_SLOW
{
	class BasicClickEvent : Behaviour
	{
		bool lbuttonDown = false;

		public BasicClickEvent() : base()
		{

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
			if ( Camera != null && lbuttonDown )
			{
				var ray = Camera.ScreenPointToRay( Input.MousePosition );
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

		public Camera Camera
		{
			get;
			set;
		}
	}
}
