using System;
using System.Collections.Generic;
using System.Text;
using SC.Game;

namespace Shinsekai
{
	abstract class TargetBasedEffect : Effect
	{
		protected TargetBasedEffect()
		{

		}

		public abstract void ApplyEffect( GameObject target );
	}
}
