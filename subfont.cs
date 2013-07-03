using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Media;

namespace subfont
{
	class Program
	{
		static List<int> GetCharacterList(string path)
		{
			List<int> chars = new List<int>();
			using (var sr = new System.IO.StreamReader(path, Encoding.Default, true))
			{
				var line = sr.ReadLine();
				while (line != null)
				{
					int v = 0;
					if (int.TryParse(line, out v))
					{
						chars.Add(v);
					}
					else foreach( var c in line )
					{
						chars.Add(c);
					}
					line = sr.ReadLine();
				}
			}
			return chars;
		}


		static void Main(string[] args)
		{
			if (args.Length < 3)
			{
				Console.WriteLine("Usage:\n\tsubfont.exe SourceFontFile TargetFontFile CharListFile");
				Console.WriteLine("Example:\n\tsubfont.exe c:\\windows\\fonts\\simun.ttc c:\\subset.ttf c:\\list.txt");
			}

			List<int> chars = GetCharacterList(args[2]);

			GlyphTypeface gt = new GlyphTypeface(new Uri(args[0]));
			List<ushort> indexes = new List<ushort>();
			foreach( int c in chars )
				indexes.Add( gt.CharacterToGlyphMap[c] );

			using (var stream = new System.IO.FileStream(args[1], System.IO.FileMode.Create))
			{
				var data = gt.ComputeSubset(indexes);
				stream.Write(data, 0, data.Length);
			}

			Console.WriteLine("Done.");
		}
	}
}
