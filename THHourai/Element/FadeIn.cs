using System;
using System.Drawing;

using SC.Game;
using SC.Game.UI;
using SC.Game.UI.Shapes;

using Rectangle = SC.Game.UI.Shapes.Rectangle;

namespace THHourai
{
	class FadeIn : Panel
	{
		Rectangle rectangle;
		float opacity = 1.0f;

		public FadeIn( string xName ) : base( xName )
		{
			InitializeComponents();
		}

		public override void Update( RectangleF clientRect )
		{
			if ( !Ended )
			{
				opacity -= Time.DeltaTime / Duration;

				if ( opacity <= 0 )
				{
					Ended = true;
					opacity = 0.0f;
				}

				rectangle.Fill.Opacity = opacity;
			}

			base.Update( clientRect );
		}

		void InitializeComponents()
		{
			rectangle = new Rectangle( "rectangle" );
			rectangle.Width = 0;
			rectangle.Height = 0;
			rectangle.Fill = new SolidColorBrush( Color.Black );
			Add( rectangle );
		}

		public float Duration
		{
			get;
			set;
		} = 2.0f;

		public bool Ended
		{
			get;
			private set;
		} = false;
	}
}