using System;
using System.Diagnostics;
using System.Drawing;
using SC.Game.UI;

namespace THHourai
{
	class BasePage : Page
	{
		Stopwatch fpsTimer = new Stopwatch();

		double fpsChecker = 0;
		ulong tickCount = 0;

		static TextBlock fpsText;
		static TextBlock debugText;

		protected BasePage( string xName ) : base( xName )
		{
			InitializeComponents();
		}

		protected override RectangleF OnUpdate( RectangleF clientRect )
		{
			// 시간 측정 장치가 시작되지 않았다면 처음 업데이트에서 시작합니다.
			if ( !fpsTimer.IsRunning )
			{
				fpsTimer.Start();
			}

			// 마지막 FPS 측정으로부터 1초 이상 지났을 경우 FPS를 기록합니다.
			double time = fpsTimer.Elapsed.TotalSeconds; 
			if ( fpsChecker + 1.0 <= time )
			{
				var dur = time - fpsChecker;
				var fps = ( double )tickCount;
				var milli = dur * 1000.0 / ( double )tickCount;

				fpsText.Content = string.Format(
					"FPS: {0}\nTime: {1:0.00}ms\n{2}",
					fps,
					milli,
					App.Instance.Configuration.AdapterName
					);

				// 시간 및 틱 횟수를 초기화합니다.
				fpsChecker = time;
				tickCount = 0;
			}

			tickCount += 1;

			return base.OnUpdate( clientRect );
		}

		void InitializeComponents()
		{
			var relativePanel = new RelativePanel( "relativePanel" );
			{
				if ( fpsText == null || debugText == null )
				{
					fpsText = new TextBlock( "fpsText" );
					fpsText.Content = "FPS: 0\nTime: 0ms\n(Null)";
					fpsText.Fill = new SolidColorBrush( Color.White );
					fpsText.Margin = new Thickness( 10 );
					fpsText.Anchor = Anchor.RightTop;
					fpsText.AddDependencyProperty( "Panel.ZOrder=100" );

					debugText = new TextBlock( "debugText" );
					debugText.Margin = new Thickness( 10 );
					debugText.Fill = new SolidColorBrush( Color.White );
					debugText.AddDependencyProperty( "Panel.ZOrder=100" );

					App.Disposing += () =>
					{
						// 전역 개체는 명시적으로 참조를 제거합니다.
						// 이후 App의 OnExit 단계에서 GC.Collect를 통해 수집됩니다.
						fpsText = null;
						debugText = null;
					};
				}

				relativePanel.Add( fpsText );
				relativePanel.Add( debugText );
			}

			Content = relativePanel;
		}
	}
}