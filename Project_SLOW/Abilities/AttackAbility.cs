using System;
using System.Collections.Generic;
using System.Numerics;
using System.Text;
using SC.Game;

namespace Project_SLOW
{
	class AttackAbility : TargetBasedAbility
	{
		public AttackAbility() : base( "Attack" )
		{

		}

		public override void ApplyEffect( GameObject target )
		{
			var weapon = GetComponent<TargetBasedWeapon>();
			var range = weapon.Range + ( target as Unit ).Radius;

			var left = Transform.Position;
			var right = target.Transform.Position;

			left.Y = 0.0f;
			right.Y = 0.0f;

			var distance = Vector3.Distance( left, right );
			if ( distance > range )
			{
				var move = GetComponent<MoveAbility>();

				var direction = right - left;
				direction = Vector3.Normalize( direction );

				var moveDistance = distance - range;
				var movePoint = direction * moveDistance;

				move.ApplyEffect( left + movePoint );
			}
			else
			{
				weapon.ApplyEffect( target );
			}
		}
	}
}
