using System;
using System.Numerics;
using System.Drawing;
using SC.Game;
using SC.Game.UI;

namespace PathFinder.Scene01
{
	class Page : BasePage
	{
		static Page instance;

		Page( string xName ) : base( xName )
		{
			InitializeComponent();
		}

		void InitializeComponent()
		{
			var relativePanel = Content as RelativePanel;
		}

		public static Page Instance
		{
			get
			{
				if ( instance == null )
				{
					instance = new Page( "page" );
				}

				return instance;
			}
		}
	}
}