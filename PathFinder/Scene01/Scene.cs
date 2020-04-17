using System;
using System.Numerics;
using SC.Game;

namespace PathFinder.Scene01
{
	class Scene : SC.Game.Scene
	{
		Page page;
		bool start = false;

		public Scene() : base()
		{

		}

		void Start()
		{
			App.Navigate( page );
		}

		public override void Update()
		{
			if ( !start )
			{
				Start();
				start = true;
			}

			base.Update();
		}

		public override void Load( object arg )
		{
			page = Page.Instance;

			Add( MainCamera.Instance );
			Add( Terrain.Instance );
			Add( PlayerSphere.Instance );
			Add( Sunlight.Instance );

			float range = 0.075f * 13.0f;
			for ( int i = 0; i < 3; ++i )
			{
				var obstacle = new Obstacle( ObstacleShape.Cube, ObstacleType.None, new Vector3( range, 0.2f, 0.075f ) );
				obstacle.Transform.Position = new Vector3( -3.5f + range + ( range * 2.5f ) * ( float )i, obstacle.Transform.Scale.Y, 4.75f );
				Add( obstacle );
				
				var rigidbody = obstacle.GetComponent<Rigidbody>();
				rigidbody.Mass = 15.0f;
			}

			for ( int j = 0; j < 5; ++j )
			{
				for ( int i = 0; i < 39; ++i )
				{
					var type = ObstacleType.None;

					if ( j == 1 )
					{
						type = ObstacleType.Killer;
					}

					Obstacle obstacle = new Obstacle( ObstacleShape.Cube, type, 0.075f, 0.2f );
					obstacle.Transform.Position = new Vector3( -3.8f + ( float )i * 0.2f, obstacle.Transform.Scale.Y, 5.0f + j * 0.5f );
					Add( obstacle );

					obstacle.AddComponent<ThreadDispatcher>().ID = j;
				}
			}

			MainCamera.Instance.GetComponent<CamChaser>().Target = PlayerSphere.Instance;
		}

		public override void Unload()
		{

		}
	}
}