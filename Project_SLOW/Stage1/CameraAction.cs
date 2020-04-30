using System;
using System.Numerics;
using SC.Game;

namespace Project_SLOW.Stage1
{
	class CameraAction : Behaviour
	{
		readonly Vector3 initialPos = new Vector3( 0.0f, 10.0f, -3.0f );

		float range = 1.0f;
		float distance = 1.0f;

		float prange = 1.0f;

		Quaternion pquat;
		Vector3 target;
		Vector3 ptarget;

		public CameraAction()
		{

		}

		public override void Start()
		{
			Transform.LocalPosition = initialPos;
			Transform.LocalLookAt( Vector3.Zero );

			ptarget = Vector3.Zero;
		}

		public override void Update()
		{
			Quaternion quat = Quaternion.Identity;
			if ( Input.GetKey( KeyCode.End ) )
			{
				// 180 * 0.15의 회전 각도로 회전합니다.
				quat = Quaternion.CreateFromAxisAngle( Vector3.UnitX, -3.14f * 0.15f );

				// 거리를 0.5배로 낮춥니다.
				range = 0.5f;

				// 타겟의 위치를 조정합니다.
				target = new Vector3( 0, 1.0f, 0 );
			}
			else
			{
				range = 1.0f;
				target = Vector3.Zero;
			}

			if ( Input.GetKey( KeyCode.Delete ) )
			{
				// 180 * 0.15의 회전 각도로 회전합니다.
				quat = Quaternion.CreateFromAxisAngle( Vector3.UnitY, 3.14f * 0.35f ) * quat;
			}

			if ( Input.GetKey( KeyCode.PageDown ) )
			{
				// 180 * 0.15의 회전 각도로 회전합니다.
				quat = Quaternion.CreateFromAxisAngle( Vector3.UnitY, -3.14f * 0.35f ) * quat;
			}

			distance = Math.Clamp( distance + -Input.MouseScrollDelta.Y * 0.1f, 0.5f, 10.0f );

			var t = Time.DeltaTime * RotateSpeed;

			quat = Quaternion.Slerp( pquat, quat, t );
			pquat = quat;
			ptarget = Vector3.Lerp( ptarget, target, t );

			prange = prange * ( 1.0f - t ) + range * distance * t;

			var newpos = Vector3.Transform( initialPos, quat ) * prange;

			if ( !Transform.LocalPosition.Equals( newpos ) )
			{
				Transform.LocalPosition = newpos;
				Transform.LocalLookAt( ptarget );
			}
		}

		public float RotateSpeed
		{
			get;
			set;
		} = 5.0f;
	}
}