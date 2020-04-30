using System;
using System.Collections.Generic;
using System.Text;
using SC.Game;

namespace Shinsekai
{
	class SingletonGO<T> : GameObject where T : class, new()
	{
		static T instance;

		public SingletonGO( string xName ) : base( xName )
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
