using System;
using System.Collections.Generic;
using System.Numerics;
using System.Text;

namespace Project_SLOW
{
	abstract class PositionBasedWeapon : Weapon
	{
		protected PositionBasedWeapon( string weaponName ) : base( weaponName )
		{

		}

		public abstract void ApplyEffect( Vector3 target );
	}
}
