using System;
using System.Collections.Generic;
using System.Text;

namespace Project_SLOW
{
	struct PropertyPair
	{
		float value;

		public float MinValue;
		public float MaxValue;

		public float Value
		{
			get
			{
				return value;
			}

			set
			{
				if ( value < MinValue )
				{
					value = MinValue;
				}
				else if ( value > MaxValue )
				{
					value = MaxValue;
				}

				this.value = value;
			}
		}
	}
}
