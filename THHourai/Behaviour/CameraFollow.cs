using System;
using System.Numerics;
using SC.Game;

namespace THHourai
{
	class CameraFollow : Behaviour
	{
		CameraRotate cameraRotate;
		float minDistance = 1.0f;
		float distance = 3.0f;
		float maxDistance = 5.0f;
		Vector3 direction;

		public CameraFollow()
		{

		}

		public override void Start()
		{
			cameraRotate = Object.GetChild( 0 ).GetComponent<CameraRotate>();

			base.Start();
		}

		public void DirectionUpdate()
		{
			// 스크롤에 따라 카메라의 거리를 조절합니다.
			distance = Math.Clamp( distance + Input.MouseScrollDelta.Y * -0.1f, minDistance, maxDistance );

			// 카메라가 바라보는 방향을 가져옵니다.
			var forward = cameraRotate.Transform.Forward;

			Ray ray;
			// 광선의 시작 위치는 카메라의 대상 위치입니다.
			ray.Origin = target.Position + new Vector3( 0.0f, 1.0f, 0.0f );
			// 광선의 방향은 대상 위치에서 카메라의 위치를 뺀 값입니다.
			ray.Direction = -forward;
			// 광선의 길이는 카메라의 최대 거리입니다.
			ray.MaxDepth = distance;

			// 광선 추적을 통해 CameraBlocker 태그를 가진 오브젝트와 충돌을 검사합니다.
			var hit = Physics.RayCast( ray, ( Tag )CustomTag.CameraBlocker, false );

			// 카메라의 실제 거리를 계산합니다.
			float actualDistance = distance;
			if ( hit.Hit )
			{
				// 카메라의 경로에서 충돌이 발생하였을 경우 충돌이 발생한 거리만큼 축소합니다.
				actualDistance = Math.Min( hit.Distance - 0.1f, actualDistance );
			}

			direction = forward;
			direction.Y = 0.0f;
			direction = Vector3.Normalize( direction );

			forward *= actualDistance;
			Transform.Position = target.Position - forward + new Vector3( 0.0f, 1.0f, 0.0f );
		}

		public Transform target;

		public Vector3 Direction
		{
			get
			{
				return direction;
			}
		}
	}
}