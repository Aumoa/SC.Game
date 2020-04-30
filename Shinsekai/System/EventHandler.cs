using System;
using System.Collections.Generic;
using System.Text;
using SC.Game;

namespace Shinsekai
{
	class EventHandler : SingletonGO<EventHandler>
	{
		public EventHandler() : base( "EventHandler" )
		{
			LoadComponents();
		}

		void LoadComponents()
		{
			AddComponent<EventHandlerComponent>();
		}

		static public event Event<KeyCode> KeyDown;
		static public event Event<KeyCode> KeyUp;

		static public void InvokeKeyDown( KeyCode keyCode )
		{
			KeyDown( keyCode );
		}

		static public void InvokeKeyUp( KeyCode keyCode )
		{
			KeyUp( keyCode );
		}
	}
}
