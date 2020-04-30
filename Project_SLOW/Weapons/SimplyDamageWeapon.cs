using System;
using System.Collections.Generic;
using System.Text;
using SC.Game;

namespace Project_SLOW
{
	class SimplyDamageWeapon : TargetBasedWeapon
	{
		List<TargetBasedEffect> effects;

		protected SimplyDamageWeapon( string weaponName ) : base( weaponName )
		{
			effects = new List<TargetBasedEffect>();
		}

		public override void ApplyEffect( GameObject target )
		{
			foreach ( var effect in effects )
			{
				effect.ApplyEffect( target );
			}
		}

		protected void AddEffect( TargetBasedEffect effect )
		{
			effects.Add( effect );
		}
	}
}
