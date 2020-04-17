using System;
using System.Numerics;
using SC.Game;

namespace PathFinder
{
	class WASDWalk : Behaviour
	{
		Rigidbody rigidbody;

		public WASDWalk() : base()
		{

		}

		public override void Start()
		{
			rigidbody = GetComponent<Rigidbody>();

			base.Start();
		}

		public override void FixedUpdate()
		{
			var forward = Vector3.UnitZ;
			var right = Vector3.UnitX;

			var mov = new Vector3( 0.0f, 0.0f, 1.0f );
			if ( Input.GetKey( KeyCode.D ) )
			{
				mov += right * Speed;
			}

			if ( Input.GetKey( KeyCode.A ) )
			{
				mov -= right * Speed;
			}

			if ( Input.GetKey( KeyCode.W ) )
			{
				mov += forward * Speed * 0.5f;
			}

			if ( Input.GetKey( KeyCode.S ) )
			{
				mov -= forward * Speed * 0.5f;
			}

			mov *= Speed;

			var pos = Transform.Position;
			pos += mov * Time.FixedDeltaTime;
			rigidbody.MovePosition( pos );

			base.Update();
		}

		public override void OnCollisionEnter( Collision collision )
		{
			if ( typeof( Obstacle ).IsAssignableFrom( collision.Target.GetType() ) )
			{
				var obstacle = collision.Target as Obstacle;
				if ( obstacle.Type == ObstacleType.Killer )
				{
					( Scene01.Page.Instance.Content as SC.Game.UI.RelativePanel ).Add( new GameOverUI( "gameOverUI" ) );
				}
			}

			base.OnCollisionEnter( collision );
		}

		public override void OnTriggerEnter( Collider collider )
		{
			throw new Exception( "Completed!" );

			base.OnTriggerEnter( collider );
		}

		public float Speed
		{
			get;
			set;
		} = 1.0f;

		public float BaseHeight
		{
			get;
			set;
		}
	}
}