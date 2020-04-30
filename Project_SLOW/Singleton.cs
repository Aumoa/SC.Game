﻿using System;

namespace Project_SLOW
{
	class Singleton<T> where T : class, new()
	{
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