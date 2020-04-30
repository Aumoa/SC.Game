using System;
using System.Collections.Generic;
using System.Text;
using SC.Game;

namespace Project_SLOW
{
	abstract class TargetBasedWeapon : Weapon
	{
		protected TargetBasedWeapon( string weaponName ) : base( weaponName )
		{

		}

		public abstract void ApplyEffect( GameObject target );
	}
}
