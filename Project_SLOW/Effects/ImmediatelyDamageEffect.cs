using System;
using System.Collections.Generic;
using System.Text;
using SC.Game;

namespace Project_SLOW
{
	class ImmediatelyDamageEffect : TargetBasedEffect
	{
		float damageValue;

		public ImmediatelyDamageEffect( float value ) : base()
		{
			damageValue = value;
		}

		public float Damage
		{
			get
			{
				return damageValue;
			}
		}

		public override void ApplyEffect( GameObject target )
		{
			var prop = target.GetComponent<Properties>();

			var health = prop.GetCurrentValue( "Health" );
			health -= damageValue;

			var minHealth = prop.GetMinValue( "Health" );
			if ( health < minHealth )
			{
				health = minHealth;
			}

			prop.SetCurrentValue( "Health", health );
		}
	}
}
