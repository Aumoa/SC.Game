using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SC.Game;

namespace Project_SLOW
{
	class TestComponent : Behaviour
	{
		GameObject amature;

		public override void Start()
		{
			amature = Object.GetChild( 0 );
		}

		public override void Update()
		{
			BasePage.Debug = string.Format(
				"Name: {0}\nPos: {1:F3}",
				amature,
				amature.Transform.LocalPosition
				);
		}
	}
}
