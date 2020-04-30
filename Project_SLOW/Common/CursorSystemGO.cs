using System;
using System.Collections.Generic;
using System.Text;

namespace Project_SLOW
{
	class CursorSystemGO : SingletonGameObject<CursorSystemGO>
	{
		public CursorSystemGO() : base( "CursorSystemGO" )
		{
			AddComponent<CursorSystem>();
		}
	}
}
