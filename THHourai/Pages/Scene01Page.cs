using System;
using System.Drawing;
using SC.Game;
using SC.Game.UI;
using SC.Diagnostics;

namespace THHourai.Scene01
{
	class Page : BasePage
	{
		public Page() : base( "Scene01.Page" )
		{
			InitializeComponents();
		}

		public override void Update( RectangleF clientRect )
		{
			base.Update( clientRect );
		}

		void InitializeComponents()
		{
			var relativePanel = Content as RelativePanel;
			{
				var fader = new FadeIn( "fader" );
				relativePanel.Add( fader );
			}
		}
	}
}