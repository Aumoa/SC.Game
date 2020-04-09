using System;

using SC.Game;
using SC.Game.UI;

namespace THHourai
{
	class Scene00 : Scene
	{
		bool start = false;

		OnlyScriptPage page0;

		OnlyScriptPage currentPage;

		public Scene00()
		{

		}

		public override void Update()
		{
			if ( !start )
			{
				App.Navigate( currentPage );

				start = true;
			}

			base.Update();
		}

		public override void Load( object arg )
		{
			LoadPages();
		}

		public override void Unload()
		{

		}

		void LoadPages()
		{
			page0 = new OnlyScriptPage( "page0", 2 );
			page0[0] = "이 게임의 스토리는 <color=Orange><u>워크래프트3</u></color> 맵인 <color=Lime><u>\"동방봉래이야기\"</u></color>에서 가져왔습니다. 스토리에 약간의 변경이 있습니다.";
			page0[1] = "캐릭터 <color=DeepPink>\"모코우\"</color>, <color=DeepPink>\"카구야\"</color>의 시점으로 진행됩니다.";

			currentPage = page0;
		}
	}
}
