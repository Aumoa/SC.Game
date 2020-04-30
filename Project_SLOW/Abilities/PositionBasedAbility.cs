using System;
using System.Collections.Generic;
using System.Numerics;
using System.Text;

namespace Project_SLOW
{
	abstract class PositionBasedAbility : Ability
	{
		Vector3 position;

		protected PositionBasedAbility( string abilityName ) : base( abilityName )
		{

		}

		public Vector3 Target
		{
			get
			{
				return position;
			}
			set
			{
				position = value;
			}
		}

		public abstract void ApplyEffect( Vector3 target );
	}
}
