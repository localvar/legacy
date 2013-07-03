namespace Html2Book
{
	public class FakeBook : BookBase
	{
		public FakeBook() { }
		public override void Create(string book, string author, string template) { }
		public override void TypeText(string text) { }
		public override void TypeLineBreak() { }
		public override void SetParagraphStyle(TextStyle style, TextAlign align) { }
		public override void TypeParagraph() { }
		public override void StartBold() { }
		public override void EndBold() { }
		public override void StartItalic() { }
		public override void EndItalic() { }
		public override void StartUnderline() { }
		public override void EndUnderline() { }
		public override void Save(string path) { }
		public override void TypeBagua(string text) { }
		public override void AddImage(string path) { }
	}
}
