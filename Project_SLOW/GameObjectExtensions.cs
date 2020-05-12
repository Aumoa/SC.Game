using SC.Game;

namespace Project_SLOW
{
	static class GameObjectExtensions
	{
		public static GameObject GetChild( this GameObject gameObject, string name )
		{
			int index = gameObject.FindChild( name );
			if ( index == -1 ) return null;
			return gameObject.GetChild( index );
		}

		public static GameObject GetChildRecursive( this GameObject gameObject, string name )
		{
			int index = gameObject.FindChild( name );
			if ( index == -1 )
			{
				for ( int i = 0; i < gameObject.NumChilds; ++i )
				{
					var child = gameObject.GetChild( i );
					var find = child.GetChildRecursive( name );
					if ( find != null ) return find;
				}

				return null;
			}
			else
			{
				return gameObject.GetChild( index );
			}
		}
	}
}
