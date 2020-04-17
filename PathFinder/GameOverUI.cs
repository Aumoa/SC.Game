using System;
using System.Numerics;
using System.Drawing;
using SC.Game;
using SC.Game.UI;

namespace PathFinder
{
	class GameOverUI : RelativePanel
	{
		public GameOverUI( string xName ) : base( xName )
		{
			Initialize();
		}

		void Initialize()
		{
			var textBlock = new TextBlock( "textBlock" );
			textBlock.Content = "Game over!";
			textBlock.Anchor = Anchor.Center;
			Add( textBlock );
		}
	}
}