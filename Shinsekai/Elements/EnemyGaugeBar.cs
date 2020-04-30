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
	class EnemyGaugeBar : RelativePanel
	{
		static EnemyGaugeBar instance;

		BaseBar hpGauge;
		BaseBar mpGauge;

		public EnemyGaugeBar() : base( "BasicGauge" )
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
			hpGauge.Width = 300.0f;
			hpGauge.Height = 20.0f;
			hpGauge.Fill = new SolidColorBrush( Color.Red );

			mpGauge = new BaseBar( "mpGauge" );
			mpGauge.Width = 300.0f;
			mpGauge.Height = 20.0f;
			mpGauge.Fill = new SolidColorBrush( Color.Blue );
			mpGauge.AddDependencyProperty( "RelativePanel.Below=hpGauge" );
			mpGauge.AddDependencyProperty( "RelativePanel.AlignLeftWith=hpGauge" );
			mpGauge.Margin = new Thickness( 0.0f, 5.0f, 0.0f, 0.0f );

			hpGauge.Anchor = Anchor.LeftTop;
			hpGauge.Margin = new Thickness( 10.0f, 10.0f, 0.0f, 0.0f );

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

		public static EnemyGaugeBar Instance
		{
			get
			{
				return instance;
			}
		}
	}
}
