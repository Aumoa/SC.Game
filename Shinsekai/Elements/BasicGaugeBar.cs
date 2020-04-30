using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;
using SC.Game.UI;
using SC.Game.UI.Shapes;
using Shinsekai.BasicField;

using Rectangle = SC.Game.UI.Shapes.Rectangle;

namespace Shinsekai
{
	class BasicGaugeBar : RelativePanel
	{
		static BasicGaugeBar instance;

		BaseBar hpGauge;
		BaseBar mpGauge;

		public BasicGaugeBar() : base( "BasicGauge" )
		{
			instance = this;

			InitializeComponents();
		}

		protected override RectangleF OnUpdate( RectangleF clientRect )
		{
			return base.OnUpdate( clientRect );
		}

		void InitializeComponents()
		{
			hpGauge = new BaseBar( "hpGauge" );
			hpGauge.Width = 600.0f;
			hpGauge.Height = 40.0f;
			hpGauge.Fill = new SolidColorBrush( Color.Red );

			mpGauge = new BaseBar( "mpGauge" );
			mpGauge.Width = 600.0f;
			mpGauge.Height = 40.0f;
			mpGauge.Fill = new SolidColorBrush( Color.Blue );
			mpGauge.AddDependencyProperty( "RelativePanel.Below=hpGauge" );
			mpGauge.AddDependencyProperty( "RelativePanel.AlignLeftWith=hpGauge" );
			mpGauge.Margin = new Thickness( 0.0f, 5.0f, 0.0f, 0.0f );

			hpGauge.Anchor = Anchor.Bottom;
			hpGauge.Margin = new Thickness( 0.0f, 0.0f, 0.0f, 60.0f );

			Add( hpGauge );
			Add( mpGauge );
		}

		public PropertyPair HPValue
		{
			get
			{
				return hpGauge.Value;
			}
			set
			{
				hpGauge.Value = value;
			}
		}

		public PropertyPair MPValue
		{
			get
			{
				return hpGauge.Value;
			}
			set
			{
				hpGauge.Value = value;
			}
		}

		public static BasicGaugeBar Instance
		{
			get
			{
				return instance;
			}
		}
	}
}
