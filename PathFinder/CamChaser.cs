using System;
using System.Numerics;
using SC.Game;

namespace PathFinder
{
	class CamChaser : Behaviour
	{
		public GameObject Target
		{
			get;
			set;
		}

		public override void LateUpdate()
		{
			if ( Target != null )
			{
				var position = Transform.Position;
				var target = Target.Transform.Position;
				position.X = target.X;
				position.Z = target.Z;
				Transform.Position = position;
			}

			base.Update();
		}
	}
}