using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Cache;
using System.Text.RegularExpressions;
using System.Web;
using HtmlAgilityPack;

namespace Html2Book
{
	public class QuanXueRobot
	{
		public delegate void Logger(string msg);
		public Logger LogEvent { get; set; }
		private HtmlClient _hc;
		private BookBase _book;
		private Stack<TextStyle> _styles;
		private Stack<TextAlign> _aligns;
		private bool _premode = false;
		private Dictionary<string, Action<HtmlNode>> _nodeActions;
		private Dictionary<string, string> _baguaMap;
		private string _currenturl;
 
		public QuanXueRobot(BookBase book)
		{
			_book = book;
			_styles = new Stack<TextStyle>();
			_aligns = new Stack<TextAlign>();

			_nodeActions = new Dictionary<string, Action<HtmlNode>>
			              	{
			              		{"p", ProcessParagraph},
								{"div",ProcessDiv},
								{"center",ProcessCenter},
								{"pre",ProcessPre},
								{"br",ProcessBr},
								{"i",ProcessItalic},
								{"big",ProcessBold},
								{"b",ProcessBold},
								{"u",ProcessUnderLine},
								{"span",ProcessSpan},
								{"acronym",ProcessAcronym},
								{"hr",ProcessSkippedNode},
								{"script",ProcessSkippedNode},
								{"img", ProcessImage},
			              	};

			_baguaMap = new Dictionary<string, string>();
			_baguaMap.Add("━　━━━━━━━━━━━━━━　━", ",");
			_baguaMap.Add("━　━━━━━━━━━━━　━━　━", ".");
			_baguaMap.Add("━　━━　━━━━━━━━━━━　━", "/");
			_baguaMap.Add("━　━", "0");
			_baguaMap.Add("　　　━　━", "0");
			_baguaMap.Add("━━━━━━━━━", "1");
			_baguaMap.Add("━　━━━━━━━", "2");
			_baguaMap.Add("━━━━　━━━━", "3");
			_baguaMap.Add("━　━━　━━━━", "4");
			_baguaMap.Add("━━━━━━━　━", "5");
			_baguaMap.Add("━　━━━━━　━", "6");
			_baguaMap.Add("━━━━　━━　━", "7");
			_baguaMap.Add("━　━━　━━　━", "8");
			_baguaMap.Add("━━━", "9");
			_baguaMap.Add("　　　━━━", "9");
			_baguaMap.Add("━━━━　━━　━━━━━　━━　━", ":");
			_baguaMap.Add("━━━━　━━　━━━━━━━━━━", ";");
			_baguaMap.Add("━　━━　━━━━━━━━　━━　━", "<");
			_baguaMap.Add("━　━━━━━　━━━━━　━━━━", ">");
			_baguaMap.Add("━━━━　━━━━━　━━━━━　━", "?");
			_baguaMap.Add("━━━━　━━　━━　━━━━━━━", "A");
			_baguaMap.Add("━━━━━━━　━━　━━━━━　━", "B");
			_baguaMap.Add("━━━━━━━　━━━━━━━━　━", "C");
			_baguaMap.Add("━　━━━━━━━━　━━　━━　━", "D");
			_baguaMap.Add("━━━━━━━━━━━━━　━━　━", "E");
			_baguaMap.Add("━　━━　━━　━━━━━━━━　━", "F");
			_baguaMap.Add("━　━━━━━━━━　━━━━━　━", "G");
			_baguaMap.Add("━　━━━━━　━━━━━━━━　━", "H");
			_baguaMap.Add("━　━━　━━　━━━━━　━━━━", "I");
			_baguaMap.Add("━　━━━━━━━━━━━　━━━━", "J");
			_baguaMap.Add("━━━━　━━━━━━━━━━━　━", "K");
			_baguaMap.Add("━　━━　━━━━━　━━　━━━━", "L");
			_baguaMap.Add("━━━━━━━　━━　━━━━━━━", "M");
			_baguaMap.Add("━　━━━━━　━━　━━━━━━━", "N");
			_baguaMap.Add("━━━━━━━　━━━━━　━━━━", "O");
			_baguaMap.Add("━━━━　━━━━━　━━━━━━━", "P");
			_baguaMap.Add("━　━━━━━　━━　━━━━━　━", "Q");
			_baguaMap.Add("━　━━　━━━━━━━━━━━━━", "R");
			_baguaMap.Add("━━━━━━━　━━　━━　━━━━", "S");
			_baguaMap.Add("━━━━━━━　━━━━━　━━　━", "T");
			_baguaMap.Add("━━━━　━━━━━　━━　━━　━", "U");
			_baguaMap.Add("━　━━━━━━━━　━━━━━━━", "V");
			_baguaMap.Add("━━━━　━━━━━━━━　━━━━", "W");
			_baguaMap.Add("━━━━　━━━━━━━━　━━　━", "X");
			_baguaMap.Add("━　━━　━━━━━　━━━━━━━", "Y");
			_baguaMap.Add("━　━━　━━━━━━━━　━━━━", "Z");
			_baguaMap.Add("━　━━　━━　━━━━━━━━━━", "[");
			_baguaMap.Add("━━━━━━━━━━　━━　━━　━", "]");
			_baguaMap.Add("━━━━━━━━━━━━━　━━━━", "a");
			_baguaMap.Add("━　━━━━━━━━━━━━━━━━", "b");
			_baguaMap.Add("━━━━　━━　━━　━━　━━　━", "c");
			_baguaMap.Add("━　━━　━━　━━━━━　━━　━", "d");
			_baguaMap.Add("━　━━━━━　━━　━━　━━━━", "e");
			_baguaMap.Add("━　━━　━━━━━　━━　━━　━", "f");
			_baguaMap.Add("━　━━━━━━━━　━━　━━━━", "g");
			_baguaMap.Add("━━━━　━━　━━━━━━━━　━", "h");
			_baguaMap.Add("━　━━━━━　━━　━━　━━　━", "i");
			_baguaMap.Add("━　━━　━━　━━　━━━━━━━", "j");
			_baguaMap.Add("━━━━━━━　━━　━━　━━　━", "k");
			_baguaMap.Add("━━━━━━━━━━　━━　━━━━", "l");
			_baguaMap.Add("━━━━　━━　━━　━━　━━━━", "m");
			_baguaMap.Add("━━━━━━━━━━━━━━━━　━", "n");
			_baguaMap.Add("━━━━━━━　━━━━━━━━━━", "o");
			_baguaMap.Add("━━━━━━━━━━　━━━━━━━", "p");
			_baguaMap.Add("━━━━━━━━━━━━━━━━━━", "q");
			_baguaMap.Add("━━━━　━━　━━　━━━━━　━", "r");
			_baguaMap.Add("━━━━　━━━━━━━━━━━━━", "s");
			_baguaMap.Add("━　━━━━━　━━━━━━━━━━", "t");
			_baguaMap.Add("━　━━　━━　━━　━━━━━　━", "u");
			_baguaMap.Add("━　━━　━━　━━　━━　━━━━", "v");
			_baguaMap.Add("━　━━　━━　━━　━━　━━　━", "w");
			_baguaMap.Add("━━━━　━━　━━━━━　━━━━", "x");
			_baguaMap.Add("━━━━━━━━━━　━━━━━　━", "y");
			_baguaMap.Add("━━━━　━━━━━　━━　━━━━", "z");
			_baguaMap.Add("━　━━━━━　━━━━━　━━　━", "{");
			_baguaMap.Add("━　━━　━━━━━　━━━━━　━", "}");
		}

		public void ProcessBook(string bookurl)
		{
			if(_hc !=null)
				_hc.Dispose();

			_hc = new HtmlClient {CachePolicy = new RequestCachePolicy(RequestCacheLevel.CacheIfAvailable)};

			var urls = GetAllChapterUrl(bookurl);
			foreach(var url in urls)
				ProcessChapter(url);
		}

		private IEnumerable<string> GetAllChapterUrl(string url)
		{
			var html = _hc.DownloadString(url);
			var doc = new HtmlDocument();
			doc.LoadHtml(html);

			var archors = doc.DocumentNode.SelectNodes("//table[@class='indextable']//a[@href]");
			var baseurl = url.Substring(0, url.LastIndexOf('/') + 1);
			return (from a in archors select baseurl + a.Attributes["href"].Value).ToList();

			/*
			List<string> urls = new List<string>();
			for(int i = 1; i<13;++i)
				urls.Add(string.Format("http://quanxue.cn/CT_RuJia/ChunQiu/ChunQiu{0:d2}.html", i));
			return urls;
			*/
		}


		private void ProcessChapter(string url)
		{
			LogEvent("processing: " + url);

			_currenturl = url;
			var html = _hc.DownloadString(url);
			html = Regex.Replace(html, "<([^a-zA-Z<>]*)>", "&lt;$1&gt;");
			html = Regex.Replace(html, "<([^a-zA-Z<]*)<", "&lt;$1<");

			var doc = new HtmlDocument();
			doc.LoadHtml(html);
			var node = doc.DocumentNode.SelectSingleNode("//div[@class='title']");

			for (; node != null; node = node.NextSibling)
			{
				if (node.Name.ToLower() == "span"
					&& node.Attributes["class"].Value.ToLower() == "foot_key")
					break;
				ProcessNode(node);
			}
		}

		private string GetNodeAttribute(HtmlNode node, string attr)
		{
			var a = node.Attributes[attr];
			return a == null ? string.Empty : a.Value;
		}

		private TextStyle GetNodeStyle(HtmlNode node)
		{
			var clsstr = GetNodeAttribute(node, "class").ToLower().Trim();
			if (clsstr.Length == 0)
				return TextStyle.Content;

			var classes = clsstr.Split(' ');
			foreach(var cls in classes)
			{
				switch (cls)
				{
					case "shici":
						return TextStyle.Poem;
					case "jingwen":
						return TextStyle.Lection;
					case "yinyong":
						return TextStyle.Quotation;
					case "jiedu":
						return TextStyle.Explain;
					case "pingxi":
						return TextStyle.Comment;
				}
			}

			if(node.Name.ToLower() == "div")
			{
				if(clsstr == "button width4em")
					return TextStyle.Skip;
				foreach (var cls in classes)
				{
					switch (cls)
					{
						case "title":
							return TextStyle.Heading1;
						case "item":
							return TextStyle.Heading2;
					}
				}
			}

			if(node.Name.ToLower() == "span")
			{
				if (clsstr == "button width6em")
					return TextStyle.Heading2;
				if(clsstr == "button width4em")
					return TextStyle.Skip;
				foreach (var cls in classes)
				{
					switch (cls)
					{
						case "bagua3":
						case "bagua6":
							return TextStyle.Bagua;
					}
				}
				return TextStyle.Content;
			}

			LogEvent(string.Format("unknow class '{0}' in html tag '{1}'.", clsstr, node.Name));
			return TextStyle.Content;
		}


		private void ProcessTextNode(HtmlNode node)
		{
			var text = HttpUtility.HtmlDecode(node.InnerText);

			if(_premode)
			{
				var nl = new[] {'\r', '\n'};
				foreach (var line in text.Split(nl))
				{
					_book.TypeText(line);
					_book.TypeLineBreak();
				}
			}
			else
			{
				var ws = new[] { '\t', ' ', '　' };
				text = text.Replace("\r", "").Replace("\n", "").Trim(ws);
				if (text.Length > 0)
					_book.TypeText(text);
			}
		}


		private void ProcessNode(HtmlNode node)
		{
			if(node.NodeType == HtmlNodeType.Text)
			{
				ProcessTextNode(node);
				return;
			}

			var name = node.Name.ToLower();
			if (_nodeActions.ContainsKey(name))
				_nodeActions[name](node);
			else
				LogEvent("unsupported html tag: " + node.Name);
		}

		private void ProcessSkippedNode(HtmlNode node)
		{
		}

		private void ProcessAcronym(HtmlNode node)
		{
			foreach (var child in node.ChildNodes)
				ProcessNode(child);
			var title = GetNodeAttribute(node, "title").Trim();
			if(title.Length >0)
				_book.TypeText("(" + title + ")");
		}

		private void ProcessBr(HtmlNode node)
		{
			_book.TypeLineBreak();
		}

		private void ProcessPre(HtmlNode node)
		{
			var style = GetNodeStyle(node);
			if (style == TextStyle.Content)
			{
				style = TextStyle.Preformatted;
				LogEvent("Encounter no class 'pre' tag, the program may not handle it properly, please check manually");
			}

			_premode = true;
			foreach (var child in node.ChildNodes)
				ProcessNode(child);
			_book.TypeParagraph();
			_premode = false;
		}

		private void ProcessCenter(HtmlNode node)
		{
			var style = GetNodeStyle(node);
			if (style == TextStyle.Content)
				style = _styles.DefaultIfEmpty(TextStyle.Content).LastOrDefault();

			var align = TextAlign.Center;

			_styles.Push(style);
			_aligns.Push(align);

			_book.SetParagraphStyle(style, align);
			foreach (var child in node.ChildNodes)
				ProcessNode(child);
			_book.TypeParagraph();

			_aligns.Pop();
			_styles.Pop();
		}

		private void ProcessDiv(HtmlNode node)
		{
			var style = GetNodeStyle(node);
			if (style == TextStyle.Skip)
				return;

			if (style == TextStyle.Content)
				style = _styles.DefaultIfEmpty(TextStyle.Content).LastOrDefault();

			var align = _aligns.DefaultIfEmpty(TextAlign.Left).LastOrDefault();

			_styles.Push(style);
			_aligns.Push(align);

			_book.SetParagraphStyle(style, align);
			foreach (var child in node.ChildNodes)
				ProcessNode(child);
			// only end a paragraph if does not contains child element: p, pre, center
			if (node.SelectSingleNode("p|pre|center") == null)
				_book.TypeParagraph();

			_aligns.Pop();
			_styles.Pop();
		}

		private void ProcessSpan(HtmlNode node)
		{
			var style = GetNodeStyle(node);
			if (style == TextStyle.Skip)
				return;

			if (style == TextStyle.Heading2)
			{
				_styles.Push(style);
				_book.SetParagraphStyle(style, TextAlign.Left);
				var text = HttpUtility.HtmlDecode(node.InnerText).Remove(0, 2);
				_book.TypeText(text);
				_book.TypeParagraph();
				_styles.Pop();
			}
			else if(style == TextStyle.Bagua)
			{
				_book.TypeBagua(_baguaMap[node.InnerText]);
			}
			else
			{
				foreach (var child in node.ChildNodes)
					ProcessNode(child);
			}
		}

		private void ProcessBold(HtmlNode node)
		{
			_book.StartBold();
			foreach (var child in node.ChildNodes)
				ProcessNode(child);
			_book.EndBold();
		}

		private void ProcessUnderLine(HtmlNode node)
		{
			_book.StartUnderline();
			foreach (var child in node.ChildNodes)
				ProcessNode(child);
			_book.EndUnderline();
		}

		private void ProcessItalic(HtmlNode node)
		{
			_book.StartItalic();
			foreach (var child in node.ChildNodes)
				ProcessNode(child);
			_book.EndItalic();
		}

		private void ProcessParagraph(HtmlNode node)
		{
			var style = GetNodeStyle(node);
			if (style == TextStyle.Content && GetNodeAttribute(node, "style").Trim().Length > 0)
			{
				LogEvent("paragraph with 'style' attribute is handled as quotation, please check manually.");
				style = TextStyle.Quotation;
			}

			if (style == TextStyle.Content)
				style = _styles.DefaultIfEmpty(TextStyle.Content).LastOrDefault();

			var align = _aligns.DefaultIfEmpty(TextAlign.Left).LastOrDefault();
			var alignattr = GetNodeAttribute(node, "align").Trim().ToLower();
			if (alignattr == "right")
				align = TextAlign.Right;
			else if (alignattr == "center")
				align = TextAlign.Center;

			_styles.Push(style);
			_aligns.Push(align);

			_book.SetParagraphStyle(style, align);
			foreach (var child in node.ChildNodes)
				ProcessNode(child);
			_book.TypeParagraph();

			_aligns.Pop();
			_styles.Pop();
		}

		private void ProcessImage(HtmlNode node)
		{
			LogEvent("unknown html tag: img");
			var url = GetNodeAttribute(node, "src");
			var name = url;
			if(name.LastIndexOf('/') >=0)
				name = name.Substring(name.LastIndexOf('/') + 1);
			name = AppDomain.CurrentDomain.BaseDirectory + name;
			if(!url.StartsWith("http", StringComparison.OrdinalIgnoreCase))
				url = _currenturl.Substring(0, _currenturl.LastIndexOf('/') + 1) + url;
			_hc.DownloadFile(url, name);

			if(node.ParentNode.Name.ToLower() == "p")
				_book.TypeLineBreak();
			_book.AddImage(name);
			if(node.ParentNode.Name.ToLower() == "p")
				_book.TypeLineBreak();

			System.IO.File.Delete(name);
		}

	}
}
