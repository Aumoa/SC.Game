using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;

namespace SC.Game.Assets.MDL
{
	partial class Parser
	{
		void ForEachTokensInBracket( Action<string> action )
		{
			int bracketStack = 1;

			string token;

			while ( bracketStack != 0 )  // 닫힘 중괄호가 발견될 때까지
			{
				token = ReadString();

				if ( token[0] == '}' )
				{
					bracketStack -= 1;
				}
				else if ( token[0] == '{' )
				{
					bracketStack += 1;
				}
				else
				{
					action( token );
				}
			}
		}

		Quaternion ReadKeyframe4( string method )
		{
			var ret = ReadQuaternion();

			if ( method == "Hermite" )
			{
				ReadString();  // InTan
				ReadQuaternion();
				ReadString();  // OutTan
				ReadQuaternion();
			}

			return ret;
		}

		Quaternion ReadQuaternion()
		{
			ReadChar();

			var x = ReadSingle();
			var y = ReadSingle();
			var z = ReadSingle();
			var w = ReadSingle();

			ReadChar();

			return new Quaternion( x, y, z, w );
		}

		Vector3 ReadKeyframe3( string method )
		{
			var ret = ReadVector3();

			if ( method == "Hermite" )
			{
				ReadString();  // InTan
				ReadVector3();
				ReadString();  // OutTan
				ReadVector3();
			}

			return ret;
		}

		Vector2 ReadVector2()
		{
			ReadChar();

			var x = ReadSingle();
			var y = ReadSingle();

			ReadChar();

			return new Vector2( x, y );
		}

		Vector3 ReadVector3()
		{
			ReadChar();

			var x = ReadSingle();
			var y = ReadSingle();
			var z = ReadSingle();

			ReadChar();

			return new Vector3( x, y, z );
		}

		Interval ReadInterval()
		{
			ReadChar();

			var x = ReadInt();
			var y = ReadInt();

			ReadChar();

			return new Interval( x, y );
		}

		Vector3 RecomposeVector( Vector3 value )
		{
			return new Vector3( -value.Y, value.Z, value.X );
		}

		Quaternion RecomposeQuaternion( Quaternion value )
		{
			return new Quaternion( -value.Y, value.Z, value.X, -value.W );
		}
	}
}
