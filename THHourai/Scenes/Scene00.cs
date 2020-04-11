using System;
using System.Numerics;
using System.Threading.Tasks;

using SC.Game;
using SC.Game.UI;

namespace THHourai.Scene00
{
	class Scene : SC.Game.Scene
	{
		readonly int numScripts = 3;

		bool start = false;

		OnlyScriptPage[] pages;

		OnlyScriptPage currentPage;
		int currentScript = 0;

		Task<Scene01.Scene> nextScene;
		bool toNextScene = false;

		public Scene()
		{
			pages = new OnlyScriptPage[numScripts];
		}

		public override void Update()
		{
			if ( !toNextScene )
			{
				if ( !start )
				{
					App.Navigate( currentPage );

					start = true;
				}
			}
			else
			{
				if ( nextScene.IsCompleted )
				{
					SceneManager.Start( nextScene.Result );
				}
			}

			base.Update();
		}

		public override void Load( object arg )
		{
			LoadPages();

			nextScene = SceneManager.LoadSceneAsync<Scene01.Scene>();
		}

		public override void Unload()
		{

		}

		void LoadPages()
		{
			pages[0] = new OnlyScriptPage( "pages[0]", 2 );
			pages[0][0] = "이 게임의 스토리는 <color=Orange><u>워크래프트3</u></color> 맵인 <color=Lime><u>\"동방봉래이야기\"</u></color>에서 가져왔습니다. 스토리에 약간의 변경이 있습니다.";
			pages[0][1] = "캐릭터 <color=DeepPink>\"모코우\"</color>, <color=DeepPink>\"카구야\"</color>의 시점으로 진행됩니다.";
			pages[0].ScriptEnded += OnScriptEnded;

			pages[1] = new OnlyScriptPage( "pages[1]", 6 );
			pages[1][0] = ".......";
			pages[1][1] = "환상향, 기묘한 능력을 지닌 소녀들이 거주하는 땅. 때때로 짖궂은 이변을 일으키기도 하지만, 그럼에도 <color=Orange>평화</color>는 언제나 환상향의 주된 관심사입니다.";
			pages[1][2] = "어느날, 그 일이 발생하기 전까지는.......";
			pages[1][3] = "<color=Red>용신의 힘</color>. 마치 환상향 자체가 파멸을 갈망하듯, 오랜 시간 낙원의 생활을 지내던 소녀들은 대부분 파멸에 대한 두려움을 잊고 있었습니다.";
			pages[1][4] = "재앙 속에서 수많은 생명이 죽고, 오직 불로불사였던 두 명 ――<color=Red>호라이산 카구야</color>와 나, <color=Red>후지와라노 모코우</color>――만이 살아남았습니다.";
			pages[1][5] = "\"살아남아라, 그리고 전생한 소녀들을 찾아내서 이 곳――환상향으로 돌아오게 만들자!\", 그것이 나의 <color=Red>사명</color>입니다.";
			pages[1].ScriptEnded += OnScriptEnded;

			pages[2] = new OnlyScriptPage( "pages[2]", 2 );
			pages[2][0] = ".......";
			pages[2][1] = "여기는.......";
			pages[2].ScriptEnded += OnScriptEnded;

			currentPage = pages[0];
		}

		void OnScriptEnded()
		{
			if ( currentScript == numScripts - 1 )
			{
				if ( nextScene.IsCompleted )
				{
					SceneManager.Start( nextScene.Result );
				}
				else
				{
					toNextScene = true;
				}
			}
			else
			{
				currentPage = pages[++currentScript];
				App.Navigate( currentPage );
			}
		}
	}
}
