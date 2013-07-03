namespace Html2Book
{
	public enum TextStyle
	{
		Content = 0,
		Explain,
		Comment,
		Quotation,
		Poem,
		Lection,
		Heading,
		Subheading,
		Heading1,
		Heading2,
		Heading3,
		Heading4,
		Heading5,
		Heading6,
		Preformatted,
		Bagua,
		Skip,
	}

	public enum TextAlign
	{
		Left = 0,
		Center,
		Right,
	}

	public abstract class BookBase
	{
		public delegate void Logger(string msg);
		public Logger LogEvent { get; set; }

		protected BookBase()
		{
		}

		public abstract void Create(string book, string author, string template);
		public abstract void TypeText(string text);
		public abstract void TypeLineBreak();
		public abstract void TypeBagua(string text);
		public abstract void AddImage(string path);
		public abstract void SetParagraphStyle(TextStyle style, TextAlign align);
		public abstract void TypeParagraph();
		public abstract void StartBold();
		public abstract void EndBold();
		public abstract void StartItalic();
		public abstract void EndItalic();
		public abstract void StartUnderline();
		public abstract void EndUnderline();
		public abstract void Save(string path);
	}
}