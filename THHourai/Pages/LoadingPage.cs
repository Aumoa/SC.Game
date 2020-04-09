using System;
using System.Drawing;

using SC.Game;
using SC.Game.UI;

namespace THHourai
{
	class LoadingPage : BasePage
	{
		TextBlock textBlock;

		public LoadingPage( string xName ) : base( xName )
		{
			InitializeComponents();
		}

		void InitializeComponents()
		{
			var relativePanel = Content as RelativePanel;
			{
				textBlock = new TextBlock( "textBlock" );
				textBlock.Content = "<b>장면을 불러오는 중...</b>";
				textBlock.Alignment = TextAlignment.Center;
				textBlock.AutoSizing = false;
				textBlock.Height = 40.0f;
				textBlock.Format = new TextFormat( "", 30.0f );
				textBlock.Anchor = Anchor.Bottom;
				textBlock.AddDependencyProperty( "RelativePanel.AlignBottomWithPanel=true" );
				textBlock.Fill = new SolidColorBrush( Color.White );
				textBlock.Margin = new Thickness( 10.0f );
				relativePanel.Add( textBlock );
			}
		}
	}
}
