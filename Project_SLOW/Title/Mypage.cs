using System;
using System.Drawing;
using System.Threading.Tasks;
using SC.Game;
using SC.Game.UI;

namespace Project_SLOW.Title
{
	partial class Mypage : BasePage
	{
		bool fadeOutTrigger = false;
		FadeOut fadeOut;
		int buttonType = 0;

		Task<Stage1.Myscene> nextScene;

		public Mypage() : base( "TitlePage" )
		{
			InitializeComponents();
		}

		protected override RectangleF OnUpdate( RectangleF clientRect )
		{
			if ( fadeOutTrigger )
			{
				fadeOut = new FadeOut( "fadeOut" );

				var relativePanel = Content as RelativePanel;
				relativePanel.Add( fadeOut );

				fadeOutTrigger = false;

				if ( buttonType == 2 )
				{
					nextScene = SceneManager.LoadSceneAsync<Stage1.Myscene>();
				}
			}

			if ( fadeOut != null && fadeOut.Ended )
			{
				if ( buttonType == 1 )
				{
					App.Quit( 0 );
				}
				else if ( buttonType == 2 )
				{
					SceneManager.Start( nextScene.Result );
				}
			}

			return base.OnUpdate( clientRect );
		}
	}
}
