using System;
using System.Collections.Generic;
using System.Numerics;
using System.Text;

namespace Project_SLOW
{
	class MoveAbility : PositionBasedAbility
	{
		public MoveAbility() : base( "Move" )
		{

		}

		public override void ApplyEffect( Vector3 target )
		{
			var tpm = GetComponent<TargetPositionMove>();
			tpm.Target = target;
		}
	}
}
