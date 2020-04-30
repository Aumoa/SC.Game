using System;
using System.Drawing;
using SC.Game;
using SC.Game.UI;
using SC.Drawing;

namespace Shinsekai
{
	class BaseCombatPage : BasePage
	{
		public BaseCombatPage() : base( "BaseCombatPage" )
		{
			InitializeComponents();
		}

		protected override RectangleF OnUpdate( RectangleF clientRect )
		{
			return base.OnUpdate( clientRect );
		}

		void InitializeComponents()
		{
			var brush = new RevealBrush( Color.Black );
			brush.MinOpacity = 0.5f;

			var relativePanel = Content as RelativePanel;
			{
				var basicGaugeBar = new BasicGaugeBar();
				var enemyGaugeBar = new EnemyGaugeBar();

				relativePanel.Add( basicGaugeBar );
				//relativePanel.Add( enemyGaugeBar );
			}
		}
	}
}