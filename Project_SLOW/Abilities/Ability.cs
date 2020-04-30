using System;
using System.Collections.Generic;
using System.Text;
using SC.Game;

namespace Project_SLOW
{
	class Ability : Component
	{
		string abilityName;

		protected Ability( string abilityName ) : base()
		{
			this.abilityName = abilityName;
		}

		public string AbilityName
		{
			get
			{
				return abilityName;
			}
		}
	}
}
