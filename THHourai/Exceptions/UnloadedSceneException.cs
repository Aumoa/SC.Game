using System;

using SC.Game;

namespace THHourai
{
	class UnloadedSceneException : Exception
	{
		public UnloadedSceneException( Exception innerException ) : base( "장면을 불러오는 중 예외가 발생하여 장면이 언로드 되었습니다.", innerException )
		{

		}
	}
}