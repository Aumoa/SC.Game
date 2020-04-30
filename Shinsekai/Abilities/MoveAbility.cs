using System;
using System.Collections.Generic;
using System.Numerics;
using System.Text;
using Shinsekai.BasicField;

namespace Shinsekai
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
