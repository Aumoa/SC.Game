using System;
using System.Drawing;
using SC.Game;
using SC.Game.UI;

using Rectangle = SC.Game.UI.Shapes.Rectangle;

namespace Project_SLOW
{
	class FadeOut : Panel
	{
		Rectangle rectangle;
		float opacity = 0.0f;

		public FadeOut( string xName ) : base( xName )
		{
			InitializeComponents();
		}

		public override void Update( RectangleF clientRect )
		{
			if ( !Ended )
			{
				opacity += Time.DeltaTime / Duration;

				if ( opacity >= 1 )
				{
					Ended = true;
					opacity = 1.0f;
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
