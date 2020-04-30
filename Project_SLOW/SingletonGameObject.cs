using System;
using SC.Game;

namespace Project_SLOW
{
	class SingletonGameObject<T> : GameObject where T : class, new()
	{
		static T instance;

		protected SingletonGameObject( string xName ) : base( xName )
		{

		}

		public static T Instance
		{
			get
			{
				if ( instance == null )
				{
					instance = new T();
				}

				return instance;
			}
		}
	}
}
