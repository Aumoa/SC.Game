using System;
using System.Collections.Generic;
using System.Text;
using SC.Game;
using Shinsekai.BasicField;

namespace Shinsekai
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
			var prop = target.GetComponent<BasicProperties>();

			var health = prop.Health;
			health -= damageValue;

			if ( health < prop.MinHealth )
			{
				health = prop.MinHealth;
			}

			prop.Health = health;
		}
	}
}
