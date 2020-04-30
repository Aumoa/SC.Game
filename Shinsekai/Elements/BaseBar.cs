using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using SC.Game.UI;

using Rectangle = SC.Game.UI.Shapes.Rectangle;
using Shinsekai.BasicField;

namespace Shinsekai
{
	class BaseBar : RelativePanel
	{
		TextBlock text;
		Rectangle bar;
		Border gauge;

		public BaseBar( string xName ) : base( xName )
		{
			InitializeComponents();
		}

		protected override RectangleF OnUpdate( RectangleF clientRect )
		{
			text.Content = string.Format( "{0}/{1}", Value.Value, Value.MaxValue );
			var width = Width;
			var percent = Value.Value / Value.MaxValue;
			bar.Width = width * percent;

			if ( bar.Width == 0 )
			{
				bar.Fill.Opacity = 0.0f;
			}
			else
			{
				bar.Fill.Opacity = 1.0f;
			}

			return base.OnUpdate( clientRect );
		}

		void InitializeComponents()
		{
			var padding = new Rectangle( "padding" );
			padding.Width = 0.0f;
			padding.Height = 0.0f;
			padding.Fill = null;

			bar = new Rectangle( "bar" );
			bar.Width = 0;
			bar.Height = 0;

			text = new TextBlock( "gaugeText" );
			text.AutoSizing = false;
			text.Alignment = TextAlignment.Center;
			text.VerticalAlignment = TextVerticalAlignment.Center;
			text.Width = 0;
			text.Height = 0;
			text.Content = string.Format( "{0}/{1}", Value.Value, Value.MaxValue );

			gauge = new Border( "gauge" );
			gauge.Content = padding;
			gauge.Padding = new Thickness( 1.0f );
			gauge.StrokeWidth = 1.0f;

			Add( bar );
			Add( gauge );
			Add( text );
		}

		public PropertyPair Value
		{
			get;
			set;
		}

		public Brush Fill
		{
			get
			{
				return bar.Fill;
			}
			set
			{
				bar.Fill = value;
			}
		}
	}
}
