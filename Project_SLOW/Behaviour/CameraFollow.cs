using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;
using SC.Game;

namespace Project_SLOW
{
	class CameraFollow : Behaviour
	{
		public CameraFollow()
		{

		}

		public override void Update()
		{
			if ( player != null )
			{
				Transform.Position = Vector3.Lerp( Transform.Position, player.Transform.Position, Time.DeltaTime * speed );
			}
		}

		public GameObject player;
		public float speed = 3.0f;
	}
}
