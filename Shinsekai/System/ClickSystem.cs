using System;
using System.Collections.Generic;
using System.Text;
using SC.Game;

namespace Shinsekai
{
	static class ClickSystem
	{
		static IList<Trigger> triggers;

		static ClickSystem()
		{
			EventHandler.KeyDown += EventHandler_KeyDown;
		}

		private static void EventHandler_KeyDown( KeyCode keyCode )
		{

		}

		public static void AddTrigger( Trigger trigger )
		{
			triggers.Add( trigger );
		}
	}
}
