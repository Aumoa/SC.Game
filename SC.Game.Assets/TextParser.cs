using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SC.Game.Assets
{
	abstract class TextParser : IParser
	{
		char[] separates;

		List<string> splits;
		int seekpos = 0;
		int splitpos = 0;

		public TextParser( string separates = @" ,{}[]()+-/*\n" )
		{
			this.separates = new char[separates.Length];

			for ( int i = 0; i < separates.Length; ++i )
			{
				this.separates[i] = separates[i];
			}
		}

		public abstract void TryParse();
		public abstract LoadedInfo Compose();

		public string TextBuffer
		{
			set
			{
				var splits = value.Split( separates, StringSplitOptions.RemoveEmptyEntries );
				this.splits = new List<string>();

				string textSequence = null;
				for ( int i = 0; i < splits.Length; ++i )
				{
					// 문자열 시퀸스
					if ( splits[i][0] == '\"' )
					{
						if ( splits[i][splits[i].Length - 1] == '\"' )
						{
							textSequence = splits[i].Substring( 1, splits[i].Length - 2 );

							this.splits.Add( textSequence );
							textSequence = null;
						}
						else
						{
							textSequence = splits[i].Substring( 1 );
						}
					}
					else if ( splits[i][splits[i].Length - 1] == '\"' )
					{
						textSequence += " " + splits[i].Substring( 0, splits[i].Length - 1 );
						this.splits.Add( textSequence );
						textSequence = null;
					}
					else if ( textSequence != null )
					{
						textSequence += " " + splits[i];
					}
					else
					{
						this.splits.Add( splits[i] );
					}
				}
			}
		}

		public bool EOF
		{
			get
			{
				return seekpos >= splits.Count;
			}
		}

		public char PeekChar()
		{
			return splits[seekpos][splitpos];
		}

		public char ReadChar()
		{
			char v = splits[seekpos][splitpos];

			if ( splitpos + 1 < splits[seekpos].Length )
			{
				splitpos += 1;
			}
			else
			{
				seekpos += 1;
				splitpos = 0;
			}

			return v;
		}

		public string ReadString()
		{
			if ( seekpos < splits.Count )
			{
				var s = splits[seekpos++];
				splitpos = 0;
				return s;
			}
			else
			{
				return null;
			}
		}

		public int ReadInt()
		{
			return int.Parse( ReadString() );
		}

		public long ReadInt64()
		{
			return long.Parse( ReadString() );
		}

		public float ReadSingle()
		{
			return float.Parse( ReadString() );
		}

		public double ReadDouble()
		{
			return double.Parse( ReadString() );
		}
	}
}
