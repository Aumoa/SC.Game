using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SC.Game.Assets
{
	interface IParser
	{
		void TryParse();
		LoadedInfo Compose();
	}
}
