using System;
using System.Collections.Generic;
using System.Text;
using SC.Game;

namespace THHourai
{
	class SingletonGameObject<T> : GameObject where T : class, new()
	{
		public SingletonGameObject( string xName ) : base( xName )
		{

		}

		static T instance;

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
