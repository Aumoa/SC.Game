using System;
using System.Collections.Generic;
using System.Text;
using SC.Game;

namespace Project_SLOW
{
	class Properties : Component
	{
		Dictionary<string, PropertyPair> properties;

		public Properties() : base()
		{
			properties = new Dictionary<string, PropertyPair>();
		}

		public void SetMinValue( string name, float value = 0 )
		{
			if ( properties.ContainsKey( name ) )
			{
				var prop = properties[name];
				prop.MinValue = value;
				properties[name] = prop;
			}
			else
			{
				var prop = new PropertyPair { MinValue = value, MaxValue = value, Value = value };
				properties[name] = prop;
			}
		}

		public void SetMaxValue( string name, float value )
		{
			if ( properties.ContainsKey( name ) )
			{
				var prop = properties[name];
				prop.MaxValue = value;
				properties[name] = prop;
			}
			else
			{
				var prop = new PropertyPair { MinValue = value, MaxValue = value, Value = value };
				properties[name] = prop;
			}
		}

		public void SetCurrentValue( string name, float value )
		{
			if ( properties.ContainsKey( name ) )
			{
				var prop = properties[name];
				prop.Value = value;
				properties[name] = prop;
			}
			else
			{
				var prop = new PropertyPair { MinValue = value, MaxValue = value, Value = value };
				properties[name] = prop;
			}
		}

		public float GetMinValue( string name )
		{
			if ( properties.ContainsKey( name ) )
			{
				return properties[name].MinValue;
			}
			else
			{
				return 0.0f;
			}
		}

		public float GetMaxValue( string name )
		{
			if ( properties.ContainsKey( name ) )
			{
				return properties[name].MaxValue;
			}
			else
			{
				return 0.0f;
			}
		}

		public float GetCurrentValue( string name )
		{
			if ( properties.ContainsKey( name ) )
			{
				return properties[name].Value;
			}
			else
			{
				return 0.0f;
			}
		}
	}
}
