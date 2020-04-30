using System;
using System.Collections.Generic;
using System.Text;
using SC.Game;

namespace Project_SLOW
{
	abstract class TargetBasedAbility : Ability
	{
		GameObject target;

		protected TargetBasedAbility( string abilityName ) : base( abilityName )
		{

		}

		public GameObject Target
		{
			get
			{
				return target;
			}
			set
			{
				target = value;
			}
		}

		public abstract void ApplyEffect( GameObject target );
	}
}
