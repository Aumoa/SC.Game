using System;
using System.Drawing;
using SC.Game;
using SC.Game.UI;

namespace Project_SLOW
{
	delegate void ClickedDelegate();

	class SimpleButton : Panel
	{
		TextFormat textFormat;
		TextBlock textBlock;
		RevealBrush borderBrush;
		SolidColorBrush textColor;
		float fontSize = 30.0f;

		bool hover = false;
		bool clickDown = false;

		public SimpleButton( string xName ) : base( xName )
		{
			InitializeAssets();
			InitializeComponents();
		}

		protected override RectangleF OnUpdate( RectangleF clientRect )
		{
			var mousePosition = Input.MousePosition;

			if ( ActualRenderingRect.Contains( ( float )mousePosition.X, ( float )mousePosition.Y ) )
			{
				hover = true;
			}
			else
			{
				hover = false;
			}

			if ( Input.GetKeyDown( KeyCode.Mouse0 ) && hover )
			{
				clickDown = true;
			}
			else if ( Input.GetKeyUp( KeyCode.Mouse0 ) )
			{
				if ( clickDown )
				{
					clickDown = false;

					if ( hover )
					{
						Clicked?.Invoke();
					}
				}
			}

			float minOpacity = 0.35f;
			if ( hover ) minOpacity += 0.15f;
			if ( clickDown ) minOpacity -= 0.3f;
			borderBrush.MinOpacity = minOpacity;

			return base.OnUpdate( clientRect );
		}

		void InitializeAssets()
		{
			textFormat = new TextFormat( "", fontSize );
			textColor = new SolidColorBrush( Color.White );
			borderBrush = new RevealBrush( Color.White );
			borderBrush.MinOpacity = 0.35f;
		}

		void InitializeComponents()
		{
			var border = new Border( "border" );
			border.Fill = borderBrush;

			textBlock = new TextBlock( "textBlock" );
			textBlock.Content = "버튼";
			textBlock.Fill = textColor;
			textBlock.Format = textFormat;
			textBlock.Alignment = TextAlignment.Center;
			textBlock.VerticalAlignment = TextVerticalAlignment.Center;
			textBlock.Width = 0;
			textBlock.Height = 0;
			textBlock.AutoSizing = false;

			border.Content = textBlock;
			Add( border );
		}

		public string ButtonText
		{
			get
			{
				if ( textBlock.Content is string str )
				{
					return str;
				}
				else
				{
					return textBlock.Content.ToString();
				}
			}
			set
			{
				textBlock.Content = value;
			}
		}

		public Color TextColor
		{
			get
			{
				return textColor.Color;
			}
			set
			{
				textColor.Color = value;
			}
		}

		public float FontSize
		{
			get
			{
				return fontSize;
			}
			set
			{
				fontSize = value;
				textFormat = new TextFormat( "", fontSize );
				textBlock.Format = textFormat;
			}
		}

		public event ClickedDelegate Clicked;
	}
}
