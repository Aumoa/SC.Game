using System;
using System.Collections.Generic;
using System.Text;
using SC.Game;

namespace Shinsekai
{
	class Weapon : Component
	{
		string weaponName;

		protected Weapon( string weaponName )
		{
			this.weaponName = weaponName;
		}

		public float Range
		{
			get;
			set;
		} = 0.1f;

		public string WeaponName
		{
			get
			{
				return weaponName;
			}
		}
	}
}
