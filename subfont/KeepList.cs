using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Linq;

namespace subfont
{
	class KeepList
	{
		private HashSet<int> m_list = new HashSet<int>();

		public KeepList()
		{
		}

		public void Append( int c )
		{
			m_list.Add(c);
		}

		public void AppendFromString(string str)
		{
			for (int i = 0; i < str.Length; ++i)
			{
				m_list.Add(Char.ConvertToUtf32(str, i));
				if (Char.IsSurrogatePair(str, i))
					++i;
			}
		}

		private void AppendFromStreamReader(StreamReader sr)
		{
			var line = sr.ReadLine();
			while (line != null)
			{
				AppendFromString(line);
				line = sr.ReadLine();
			}
		}

		public void AppendFromStream(Stream stream, Encoding encoding)
		{
			using (var sr = new StreamReader(stream, encoding))
			{
				AppendFromStreamReader(sr);
			}
		}

		public void AppendFromFile(string path, Encoding encoding)
		{
			using (var sr = new StreamReader(path, encoding, true))
			{
				AppendFromStreamReader(sr);
			}
		}

		public void AppendFromFile(string path, int codepage)
		{
			var encoding = Encoding.GetEncoding(codepage);
			AppendFromFile(path, encoding);
		}

		public void Remove(int c)
		{
			m_list.Remove(c);
		}

		private void ExcludeEncoding(Encoding encoding)
		{
			List<int> exclude = new List<int>();

			foreach( var c in m_list)
			{
				var s = Char.ConvertFromUtf32(c);
				var bytes = Encoding.Unicode.GetBytes(s);
				try
				{
					Encoding.Convert(Encoding.Unicode, encoding, bytes);
					exclude.Add(c);
				}
				catch(EncoderFallbackException)
				{
				}
			}

			m_list.ExceptWith(exclude);
		}

		public void ExcludeEncoding(int codepage)
		{
			var encoding = Encoding.GetEncoding(codepage, new EncoderExceptionFallback(), new DecoderReplacementFallback());
			ExcludeEncoding(encoding);
		}

		public void ExcludeEncoding(string name)
		{
			var encoding = Encoding.GetEncoding(name, new EncoderExceptionFallback(), new DecoderReplacementFallback());
			ExcludeEncoding(encoding);
		}

		public int[] ToArray()
		{
			return (from i in m_list orderby i select i).ToArray();
			//return m_list.ToArray();
		}
	}
}
