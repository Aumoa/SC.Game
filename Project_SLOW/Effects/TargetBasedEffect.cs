using System;
using System.Collections.Generic;
using System.Text;
using SC.Game;

namespace Project_SLOW
{
	abstract class TargetBasedEffect : Effect
	{
		protected TargetBasedEffect()
		{

		}

		public abstract void ApplyEffect( GameObject target );
	}
}
