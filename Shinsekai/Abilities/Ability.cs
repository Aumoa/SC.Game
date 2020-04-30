using System;
using System.Collections.Generic;
using System.Text;
using SC.Game;

namespace Shinsekai
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
