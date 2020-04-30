using System;
using System.Drawing;
using SC.Game;
using SC.Game.UI;

namespace Project_SLOW.Title
{
	partial class Mypage
	{
		void OnClicked_Exit()
		{
			fadeOutTrigger = true;
			buttonType = 1;
		}

		void OnClicked_CreateNew()
		{
			fadeOutTrigger = true;
			buttonType = 2;
		}
	}
}
