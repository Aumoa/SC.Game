using System;
using System.Numerics;
using SC.Game;

namespace THHourai
{
	class ShadowFollow : Behaviour
	{
		public ShadowFollow() : base()
		{

		}

		public override object Clone()
		{
			return new ShadowFollow();
		}

		public override void Update()
		{
			Transform.Position = Target.Position - Transform.Forward * 10.0f;

			base.Update();
		}

		public Transform Target
		{
			get;
			set;
		}
	}
}