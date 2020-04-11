using System;
using System.Threading.Tasks;

using SC.Game;

namespace THHourai
{
	class DemoScene : Scene
	{
		DemoPage demoPage;
		LoadingPage loadingPage;
		bool isFirst = false;

		Task<Scene00.Scene> nextScene;

		public DemoScene() : base()
		{

		}

		public override void Update()
		{
			if ( isFirst )
			{
				App.Navigate( demoPage );
				demoPage.HelpText = "장면을 불러오는 중...";

				nextScene = SceneManager.LoadSceneAsync<Scene00.Scene>();
				isFirst = false;
			}

			if ( nextScene.Status == TaskStatus.Faulted )
			{
				var exception = new UnloadedSceneException( nextScene.Exception );
				demoPage.HelpText = string.Format( "게임 엔진에서 장면을 불러오는 중 오류가 발생하였습니다. 예외 메시지:\n{0}", exception );
			}
			else
			{
				if ( demoPage.DemoEnd )
				{
					if ( nextScene.Status == TaskStatus.RanToCompletion )
					{
						SceneManager.Start( nextScene.Result );
					}
					else
					{
						App.Navigate( loadingPage );
					}
				}
			}

			base.Update();
		}

		public override void Load( object arg )
		{
			isFirst = true;

			demoPage = new DemoPage();
			loadingPage = new LoadingPage( "loadingPage" );
		}

		public override void Unload()
		{
			demoPage = null;

			// 장면이 언로드될 때 명시적으로 자원을 해제할 수 있도록 지원하는 샘플 코드입니다.
			GC.Collect();
		}
	}
}
