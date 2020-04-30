using System;
using System.Collections.Generic;
using System.Text;
using SC.Game;

namespace Shinsekai
{
	class EventHandlerComponent : Behaviour
	{
		EventHandler eventHandler;

		public override void Start()
		{
			eventHandler = Object as EventHandler;
		}

		public override void Update()
		{
			
		}
	}
}
