using System;
using System.Collections.Generic;
using System.Text;
using SC.Game;

namespace Project_SLOW
{
	class MokouAttackWeapon : SimplyDamageWeapon
	{
		ImmediatelyDamageEffect damage;

		public MokouAttackWeapon() : base( "MokouAttackWeapon" )
		{
			damage = new ImmediatelyDamageEffect( 10.0f );

			AddEffect( damage );
		}
	}
}
