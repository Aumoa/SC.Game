using System;
using System.Collections.Generic;
using System.Text;

namespace Project_SLOW.Stage1
{
	class BasicProperties : Properties
	{
		public BasicProperties() : base()
		{
			SetMinValue( "Health", 0.0f );
			SetMaxValue( "Health", 200.0f );
			SetCurrentValue( "Health", 200.0f );
		}

		public float Health
		{
			get
			{
				return GetCurrentValue( "Health" );
			}
			set
			{
				SetCurrentValue( "Health", value );
			}
		}

		public float MaxHealth
		{
			get
			{
				return GetMaxValue( "Health" );
			}
			set
			{
				SetMaxValue( "Health", value );
			}
		}

		public float MinHealth
		{
			get
			{
				return GetMinValue( "Health" );
			}
			set
			{
				SetMinValue( "Health", value );
			}
		}
	}
}
