using System;
using System.Diagnostics;
using System.Drawing;
using SC.Game;
using SC.Game.UI;
using SC.Drawing;

namespace THHourai
{
	class DemoPage : BasePage
	{
		double totalSeconds = 0;
		SolidColorBrush gameTextBrush = new SolidColorBrush( Color.White );
		EaseFunction myEase = new EaseInOut( 1.0 );

		TextBlock smartComponent;
		TextBlock gameEngine;

		public DemoPage() : base( "DemoPage" )
		{
			InitializeComponents();

			myEase.Start();
		}

		protected override RectangleF OnUpdate( RectangleF clientRect )
		{
			totalSeconds += Time.DeltaTime;

			if ( totalSeconds >= 5.0 )
			{
				DemoEnd = true;
			}

			else if ( totalSeconds >= 3.0 )
			{
				float t = ( float )( ( totalSeconds - 3.0 ) * 0.5 );
				gameTextBrush.Opacity = 1.0f - t;
			}

			else if ( totalSeconds >= 2.0 )
			{
				float t = 1.0f;
				myEase.FixedUpdate( t );

				float height = smartComponent.ActualRenderingRect.Height;

				smartComponent.Margin = new Thickness( 0, ( float )-myEase.CurrentValue * height, 0, 0 );
				gameEngine.Margin = new Thickness( 0, ( float )myEase.CurrentValue * height, 0, 0 );

				smartComponent.Fill = gameTextBrush;
				gameTextBrush.Opacity = ( float )( myEase.CurrentValue - 0.5 ) * 2.0f;
			}

			else if ( totalSeconds >= 1.0 )
			{
				float t = ( float )totalSeconds - 1.0f;
				myEase.FixedUpdate( t );

				float height = smartComponent.ActualRenderingRect.Height;

				smartComponent.Margin = new Thickness( 0, ( float )-myEase.CurrentValue * height, 0, 0 );
				gameEngine.Margin = new Thickness( 0, ( float )myEase.CurrentValue * height, 0, 0 );

				gameTextBrush.Opacity = ( float )( myEase.CurrentValue - 0.5 ) * 2.0f;
			}

			return base.OnUpdate( clientRect );
		}

		public bool DemoEnd
		{
			get;
			private set;
		}

		public string HelpText
		{
			get;
			set;
		}

		void InitializeComponents()
		{
			var relativePanel = Content as RelativePanel;
			{
				smartComponent = new TextBlock( "smartComponent" );
				smartComponent.Content = "Smart Component";
				smartComponent.Anchor = Anchor.Center;
				smartComponent.Fill = new SolidColorBrush( Color.White );
				smartComponent.Format = new TextFormat( "", 50.0f );
				relativePanel.Add( smartComponent );

				gameEngine = new TextBlock( "gameEngine" );
				gameEngine.Content = "<b>GAME ENGINE</b>";
				gameEngine.AutoSizing = false;
				gameEngine.AddDependencyProperty( "RelativePanel.AlignTopWith=smartComponent" );
				gameEngine.Height = 100;
				gameEngine.Format = new TextFormat( "", 60.0f );
				gameEngine.Fill = gameTextBrush;
				gameEngine.Alignment = TextAlignment.Center;
				relativePanel.Add( gameEngine );

				gameTextBrush.Opacity = 0;
			}
		}
	}
}