using System;
using System.Collections.Generic;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows.Forms;
using System.Windows.Media;
using System.Linq;

namespace subfont
{

	public partial class MainForm : Form
	{
		public MainForm()
		{
			InitializeComponent();

			var encodings = from ei in Encoding.GetEncodings()
							orderby ei.DisplayName
							select new
							{
								Name = string.Format("{0} [{1}]", ei.DisplayName, ei.CodePage),
								CodePage = ei.CodePage
							};

			var ie = encodings.ToList();
			ie.Insert(0, new { Name = "系统默认 [0]", CodePage = 0 });
			comboInputEncode.DataSource = ie;
			comboInputEncode.DisplayMember = "Name";
			comboInputEncode.ValueMember = "CodePage";
			comboInputEncode.SelectedValue = 65001;

			ie = encodings.ToList();
			ie.Insert(0, new { Name = "不排除任何字符", CodePage = 0 });
			comboExclude.DataSource = ie;
			comboExclude.DisplayMember = "Name";
			comboExclude.ValueMember = "CodePage";
			comboExclude.SelectedValue = 936;
		}

		private void btnBrowseOrigin_Click(object sender, EventArgs e)
		{
			if (originFontDialog.ShowDialog() != DialogResult.OK)
				return;
			txtOriginFont.Text = originFontDialog.FileName;
		}

		private void btnBrowseText_Click(object sender, EventArgs e)
		{
			if (inputTextDialog.ShowDialog() != System.Windows.Forms.DialogResult.OK)
				return;
			txtInputFile.Text = string.Join("; ", inputTextDialog.FileNames);
		}

		private void btnBrowseOutput_Click(object sender, EventArgs e)
		{
			if (outputFontDialog.ShowDialog() != DialogResult.OK)
				return;
			txtOutputFont.Text = outputFontDialog.FileName;
		}

		private void btnExtract_Click(object sender, EventArgs e)
		{
			if (txtOriginFont.Text.Length == 0)
			{
				MessageBox.Show("请选择原始字体文件。", this.Text, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
				return;
			}

			if (txtOutputFont.Text.Length == 0)
			{
				MessageBox.Show("请选择输出字体文件。", this.Text, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
				return;
			}

			if (txtInputFile.Text.Length == 0)
			{
				MessageBox.Show("请至少选择一个输入文字文件。", this.Text, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
				return;
			}

			int codepage = (int)comboInputEncode.SelectedValue;
			KeepList kl = new KeepList();
			foreach (var path in inputTextDialog.FileNames)
				kl.AppendFromFile(path, codepage);

			codepage = (int)comboExclude.SelectedValue;
			if (codepage != 0)
				kl.ExcludeEncoding(codepage);

			var sb = new StringBuilder();
			var list = kl.ToArray();
			for (int i = 0; i < list.Length; ++i)
			{
				var c = Char.ConvertFromUtf32(list[i]);
				sb.AppendFormat("{0:X06}({1})", list[i], c);
				if ((i + 1) % 7 == 0)
					sb.AppendLine();
				else
					sb.Append('\t');
			}

			if (list.Length % 7 != 0)
				sb.AppendLine();
			sb.AppendFormat("\r\n共{0}个需要提取的字符", list.Length);
			txtLog.Text = sb.ToString();

			ExtractFont(originFontDialog.FileName, list, outputFontDialog.FileName);
		}

		private void ExtractFont(string origin, int[] keeplist, string output)
		{
			GlyphTypeface gt = new GlyphTypeface(new Uri(origin));
			List<ushort> indexes = new List<ushort>();
			List<int> notexists = new List<int>();
			foreach (int c in keeplist)
			{
				if (gt.CharacterToGlyphMap.ContainsKey(c))
					indexes.Add(gt.CharacterToGlyphMap[c]);
				else
					notexists.Add(c);
			}
			if (notexists.Count > 0)
			{
				var sb = new StringBuilder();
				sb.AppendFormat("，但下列{0}个字符在原始字体文件中不存在：\r\n\r\n", notexists.Count);
				for (int i = 0; i < notexists.Count; ++i)
				{
					var c = Char.ConvertFromUtf32(notexists[i]);
					sb.AppendFormat("{0:X06}({1})", notexists[i], c);
					if ((i + 1) % 7 == 0)
						sb.AppendLine();
					else
						sb.Append('\t');
				}
				txtLog.AppendText(sb.ToString());
			}
			using (var stream = new System.IO.FileStream(output, System.IO.FileMode.Create))
			{
				var data = gt.ComputeSubset(indexes);
				stream.Write(data, 0, data.Length);
			}
			txtLog.AppendText(string.Format("\r\n\r\n共提取{0}个字符", indexes.Count));
		}
	}
}
