using System;
using Word = Microsoft.Office.Interop.Word;

namespace Html2Book
{
	class WordBook : BookBase
	{
		private Word.Application _wordapp;

		private int _boldstart = 0;
		private int _italicstart = 0;
		private int _underlinestart = 0;

		public override void Create(string book, string author, string template)
		{
			_wordapp = new Word.Application {Visible = true};
			_wordapp.Documents.Add(template);

			// clear the content of this document
			_wordapp.Selection.WholeStory();
			_wordapp.Selection.TypeBackspace();

			CreatePreface();
			CreateTableOfContent();
		}

		private void CreatePreface()
		{
		}

		private void CreateTableOfContent()
		{
			Object oUpperHeadingLevel = "1";
			Object oLowerHeadingLevel = "3";
			Object oTOCTableID = "TableOfContents";
			_wordapp.ActiveDocument.TablesOfContents.Add(_wordapp.Selection.Range);
			_wordapp.Selection.InsertBreak(Word.WdBreakType.wdSectionBreakNextPage);
		}

		public override void TypeText(string text)
		{
			_wordapp.Selection.TypeText(text);
		}

		public override void TypeLineBreak()
		{
			_wordapp.Selection.InsertBreak(Word.WdBreakType.wdLineBreak);
		}


		public override void TypeBagua(string text)
		{
			var old = _wordapp.Selection.Font.Name;
			_wordapp.Selection.Font.Name = "YiJing Symbols";
			_wordapp.Selection.TypeText(text);
			_wordapp.Selection.Font.Name = old;
		}

		public override void SetParagraphStyle(TextStyle style, TextAlign align)
		{
			_wordapp.Selection.set_Style(style.ToString());
			if (align == TextAlign.Right)
				_wordapp.Selection.ParagraphFormat.Alignment = Word.WdParagraphAlignment.wdAlignParagraphRight;
			else if (align == TextAlign.Center)
				_wordapp.Selection.ParagraphFormat.Alignment = Word.WdParagraphAlignment.wdAlignParagraphCenter;
		}

		public override void TypeParagraph()
		{
			_wordapp.Selection.TypeParagraph();
		}

		public override void StartBold()
		{
			_boldstart = _wordapp.Selection.Range.Start;
		}
		public override void EndBold()
		{
			int end = _wordapp.Selection.Range.Start;
			_wordapp.ActiveDocument.Range(_boldstart, end).Bold = 1;
		}

		public override void StartItalic()
		{
			_italicstart = _wordapp.Selection.Range.Start;
		}
		public override void EndItalic()
		{
			int end = _wordapp.Selection.Range.Start;
			_wordapp.ActiveDocument.Range(_italicstart, end).Italic = 1;
		}

		public override void StartUnderline()
		{
			_underlinestart = _wordapp.Selection.Range.Start;
		}
		public override void EndUnderline()
		{
			int end = _wordapp.Selection.Range.Start;
			_wordapp.ActiveDocument.Range(_underlinestart, end).Underline = Word.WdUnderline.wdUnderlineSingle;
		}

		public override void AddImage(string path)
		{
			_wordapp.Selection.InlineShapes.AddPicture(path);
		}

		private void UpdateTableOfContent()
		{
			_wordapp.ActiveDocument.TablesOfContents[1].Update();
			_wordapp.ActiveDocument.TablesOfContents[1].UpdatePageNumbers();
		}

		public override void Save(string path)
		{
			UpdateTableOfContent();
			_wordapp.ActiveDocument.SaveAs2(path);
			_wordapp.Quit(Word.WdSaveOptions.wdDoNotSaveChanges);
		}
	}
}
