using System;
using System.Drawing;
using SC.Game;
using SC.Game.UI;

namespace Project_SLOW.Title
{
	partial class Mypage
	{
		void InitializeComponents()
		{
			var titleLogoTextFormat = new TextFormat( "", 50.0f );
			var buttonTextFormat = new TextFormat( "", 25.0f );
			var solidWhite = new SolidColorBrush( Color.White );

			var relativePanel = Content as RelativePanel;
			{
				var titleLogo = new TextBlock( "titleLogo" );
				titleLogo.Content = "타이틀 로고";
				titleLogo.Alignment = TextAlignment.Center;
				titleLogo.Anchor = Anchor.Top;
				titleLogo.Format = titleLogoTextFormat;
				titleLogo.Fill = solidWhite;
				titleLogo.Margin = new Thickness( 0, 40.0f );
				relativePanel.Add( titleLogo );

				var exit = new SimpleButton( "exit" );
				exit.ButtonText = "종료";
				exit.Margin = new Thickness( 40.0f, 40.0f );
				exit.Anchor = Anchor.LeftBottom;
				exit.Width = 200.0f;
				exit.Height = 60.0f;
				exit.Clicked += OnClicked_Exit;
				relativePanel.Add( exit );

				var options = new SimpleButton( "options" );
				options.ButtonText = "설정";
				options.Margin = new Thickness( 40.0f, 20.0f );
				options.Anchor = Anchor.LeftBottom;
				options.Width = 200.0f;
				options.Height = 60.0f;
				options.AddDependencyProperty( "RelativePanel.Above=exit" );
				relativePanel.Add( options );

				var create_new = new SimpleButton( "create_new" );
				create_new.ButtonText = "새로운 여정";
				create_new.Margin = new Thickness( 40.0f, 20.0f );
				create_new.Anchor = Anchor.LeftBottom;
				create_new.Width = 200.0f;
				create_new.Height = 60.0f;
				create_new.Clicked += OnClicked_CreateNew;
				create_new.AddDependencyProperty( "RelativePanel.Above=options" );
				relativePanel.Add( create_new );

				var @continue = new SimpleButton( "continue" );
				@continue.ButtonText = "지난 여정";
				@continue.Margin = new Thickness( 40.0f, 20.0f );
				@continue.Anchor = Anchor.LeftBottom;
				@continue.Width = 200.0f;
				@continue.Height = 60.0f;
				@continue.AddDependencyProperty( "RelativePanel.Above=create_new" );
				relativePanel.Add( @continue );

				var fadeIn = new FadeIn( "fadeIn" );
				relativePanel.Add( fadeIn );
			}
		}
	}
}
