namespace subfont
{
	partial class MainForm
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			System.Windows.Forms.Label labelOriginFont;
			System.Windows.Forms.Button btnBrowseOrigin;
			System.Windows.Forms.Button btnBrowseText;
			System.Windows.Forms.Button btnBrowseOutput;
			System.Windows.Forms.Label lblOutputFont;
			System.Windows.Forms.Label lblExclude;
			System.Windows.Forms.Button btnExtract;
			System.Windows.Forms.Label lblInputEncode;
			this.lblInputFile = new System.Windows.Forms.Label();
			this.txtOriginFont = new System.Windows.Forms.TextBox();
			this.txtInputFile = new System.Windows.Forms.TextBox();
			this.txtOutputFont = new System.Windows.Forms.TextBox();
			this.comboExclude = new System.Windows.Forms.ComboBox();
			this.txtLog = new System.Windows.Forms.TextBox();
			this.comboInputEncode = new System.Windows.Forms.ComboBox();
			this.originFontDialog = new System.Windows.Forms.OpenFileDialog();
			this.outputFontDialog = new System.Windows.Forms.SaveFileDialog();
			this.inputTextDialog = new System.Windows.Forms.OpenFileDialog();
			this.txtInputText = new System.Windows.Forms.TextBox();
			this.lblInputText = new System.Windows.Forms.Label();
			labelOriginFont = new System.Windows.Forms.Label();
			btnBrowseOrigin = new System.Windows.Forms.Button();
			btnBrowseText = new System.Windows.Forms.Button();
			btnBrowseOutput = new System.Windows.Forms.Button();
			lblOutputFont = new System.Windows.Forms.Label();
			lblExclude = new System.Windows.Forms.Label();
			btnExtract = new System.Windows.Forms.Button();
			lblInputEncode = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// labelOriginFont
			// 
			labelOriginFont.AutoSize = true;
			labelOriginFont.Location = new System.Drawing.Point(3, 13);
			labelOriginFont.Name = "labelOriginFont";
			labelOriginFont.Size = new System.Drawing.Size(96, 13);
			labelOriginFont.TabIndex = 0;
			labelOriginFont.Text = "原始字体文件(&O):";
			// 
			// btnBrowseOrigin
			// 
			btnBrowseOrigin.Location = new System.Drawing.Point(868, 8);
			btnBrowseOrigin.Name = "btnBrowseOrigin";
			btnBrowseOrigin.Size = new System.Drawing.Size(25, 23);
			btnBrowseOrigin.TabIndex = 2;
			btnBrowseOrigin.Text = "...";
			btnBrowseOrigin.UseVisualStyleBackColor = true;
			btnBrowseOrigin.Click += new System.EventHandler(this.btnBrowseOrigin_Click);
			// 
			// btnBrowseText
			// 
			btnBrowseText.Location = new System.Drawing.Point(868, 90);
			btnBrowseText.Name = "btnBrowseText";
			btnBrowseText.Size = new System.Drawing.Size(25, 23);
			btnBrowseText.TabIndex = 11;
			btnBrowseText.Text = "...";
			btnBrowseText.UseVisualStyleBackColor = true;
			btnBrowseText.Click += new System.EventHandler(this.btnBrowseText_Click);
			// 
			// btnBrowseOutput
			// 
			btnBrowseOutput.Location = new System.Drawing.Point(868, 35);
			btnBrowseOutput.Name = "btnBrowseOutput";
			btnBrowseOutput.Size = new System.Drawing.Size(25, 23);
			btnBrowseOutput.TabIndex = 6;
			btnBrowseOutput.Text = "...";
			btnBrowseOutput.UseVisualStyleBackColor = true;
			btnBrowseOutput.Click += new System.EventHandler(this.btnBrowseOutput_Click);
			// 
			// lblOutputFont
			// 
			lblOutputFont.AutoSize = true;
			lblOutputFont.Location = new System.Drawing.Point(3, 40);
			lblOutputFont.Name = "lblOutputFont";
			lblOutputFont.Size = new System.Drawing.Size(96, 13);
			lblOutputFont.TabIndex = 4;
			lblOutputFont.Text = "输出字体文件(&U):";
			lblOutputFont.Click += new System.EventHandler(this.lblOutputFont_Click);
			// 
			// lblExclude
			// 
			lblExclude.AutoSize = true;
			lblExclude.Location = new System.Drawing.Point(371, 122);
			lblExclude.Name = "lblExclude";
			lblExclude.Size = new System.Drawing.Size(155, 13);
			lblExclude.TabIndex = 14;
			lblExclude.Text = "排除的此字符集中的字符(&X):";
			// 
			// btnExtract
			// 
			btnExtract.Location = new System.Drawing.Point(793, 118);
			btnExtract.Name = "btnExtract";
			btnExtract.Size = new System.Drawing.Size(100, 23);
			btnExtract.TabIndex = 16;
			btnExtract.Text = "提取(&R)";
			btnExtract.UseVisualStyleBackColor = true;
			btnExtract.Click += new System.EventHandler(this.btnExtract_Click);
			// 
			// lblInputEncode
			// 
			lblInputEncode.AutoSize = true;
			lblInputEncode.Location = new System.Drawing.Point(4, 122);
			lblInputEncode.Name = "lblInputEncode";
			lblInputEncode.Size = new System.Drawing.Size(95, 13);
			lblInputEncode.TabIndex = 12;
			lblInputEncode.Text = "输入文件编码(&E):";
			// 
			// lblInputFile
			// 
			this.lblInputFile.AutoSize = true;
			this.lblInputFile.Location = new System.Drawing.Point(4, 95);
			this.lblInputFile.Name = "lblInputFile";
			this.lblInputFile.Size = new System.Drawing.Size(94, 13);
			this.lblInputFile.TabIndex = 9;
			this.lblInputFile.Text = "输入字符文件(&F):";
			// 
			// txtOriginFont
			// 
			this.txtOriginFont.BackColor = System.Drawing.SystemColors.Window;
			this.txtOriginFont.HideSelection = false;
			this.txtOriginFont.Location = new System.Drawing.Point(103, 10);
			this.txtOriginFont.Name = "txtOriginFont";
			this.txtOriginFont.ReadOnly = true;
			this.txtOriginFont.Size = new System.Drawing.Size(763, 20);
			this.txtOriginFont.TabIndex = 1;
			this.txtOriginFont.WordWrap = false;
			// 
			// txtInputFile
			// 
			this.txtInputFile.BackColor = System.Drawing.SystemColors.Window;
			this.txtInputFile.HideSelection = false;
			this.txtInputFile.Location = new System.Drawing.Point(103, 92);
			this.txtInputFile.Name = "txtInputFile";
			this.txtInputFile.ReadOnly = true;
			this.txtInputFile.Size = new System.Drawing.Size(763, 20);
			this.txtInputFile.TabIndex = 10;
			this.txtInputFile.WordWrap = false;
			// 
			// txtOutputFont
			// 
			this.txtOutputFont.BackColor = System.Drawing.SystemColors.Window;
			this.txtOutputFont.HideSelection = false;
			this.txtOutputFont.Location = new System.Drawing.Point(103, 37);
			this.txtOutputFont.Name = "txtOutputFont";
			this.txtOutputFont.ReadOnly = true;
			this.txtOutputFont.Size = new System.Drawing.Size(763, 20);
			this.txtOutputFont.TabIndex = 5;
			this.txtOutputFont.WordWrap = false;
			// 
			// comboExclude
			// 
			this.comboExclude.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.comboExclude.Items.AddRange(new object[] {
            "所有用到的字符",
            "非ASCII字符 [0]",
            "非GBK字符 [936]",
            "非GB18030字符 [54936]",
            "非BIG5字符 [950]"});
			this.comboExclude.Location = new System.Drawing.Point(524, 119);
			this.comboExclude.Name = "comboExclude";
			this.comboExclude.Size = new System.Drawing.Size(267, 21);
			this.comboExclude.TabIndex = 15;
			// 
			// txtLog
			// 
			this.txtLog.BackColor = System.Drawing.SystemColors.Window;
			this.txtLog.Dock = System.Windows.Forms.DockStyle.Bottom;
			this.txtLog.Font = new System.Drawing.Font("SimSun", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.txtLog.HideSelection = false;
			this.txtLog.Location = new System.Drawing.Point(0, 147);
			this.txtLog.MaxLength = 65535;
			this.txtLog.Multiline = true;
			this.txtLog.Name = "txtLog";
			this.txtLog.ReadOnly = true;
			this.txtLog.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
			this.txtLog.Size = new System.Drawing.Size(896, 425);
			this.txtLog.TabIndex = 17;
			// 
			// comboInputEncode
			// 
			this.comboInputEncode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.comboInputEncode.Location = new System.Drawing.Point(103, 119);
			this.comboInputEncode.Name = "comboInputEncode";
			this.comboInputEncode.Size = new System.Drawing.Size(267, 21);
			this.comboInputEncode.TabIndex = 13;
			// 
			// originFontDialog
			// 
			this.originFontDialog.AddExtension = false;
			this.originFontDialog.Filter = "字体文件(*.ttf; *.ttc)|*.ttf;*.ttc|所有文件(*.*)|*.*";
			this.originFontDialog.Title = "选择原始字体文件";
			// 
			// outputFontDialog
			// 
			this.outputFontDialog.DefaultExt = "ttf";
			this.outputFontDialog.Filter = "字体文件(*.ttf)|*.ttf";
			this.outputFontDialog.Title = "选择输出字体文件";
			// 
			// inputTextDialog
			// 
			this.inputTextDialog.AddExtension = false;
			this.inputTextDialog.Filter = "网页文件(*.htm; *.html; *.xhtml)|*.htm; *.html; *.xhtml)|文本文件(*.txt)|*.txt|所有文件(*.*)|" +
    "*.*";
			this.inputTextDialog.Multiselect = true;
			this.inputTextDialog.Title = "选择输入文字文件";
			// 
			// txtInputText
			// 
			this.txtInputText.BackColor = System.Drawing.SystemColors.Window;
			this.txtInputText.HideSelection = false;
			this.txtInputText.Location = new System.Drawing.Point(103, 64);
			this.txtInputText.Name = "txtInputText";
			this.txtInputText.Size = new System.Drawing.Size(763, 20);
			this.txtInputText.TabIndex = 8;
			this.txtInputText.WordWrap = false;
			// 
			// lblInputText
			// 
			this.lblInputText.AutoSize = true;
			this.lblInputText.Location = new System.Drawing.Point(4, 67);
			this.lblInputText.Name = "lblInputText";
			this.lblInputText.Size = new System.Drawing.Size(95, 13);
			this.lblInputText.TabIndex = 7;
			this.lblInputText.Text = "要提取的字符(&T):";
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(896, 572);
			this.Controls.Add(this.txtInputText);
			this.Controls.Add(this.lblInputText);
			this.Controls.Add(this.comboInputEncode);
			this.Controls.Add(lblInputEncode);
			this.Controls.Add(btnExtract);
			this.Controls.Add(this.comboExclude);
			this.Controls.Add(lblExclude);
			this.Controls.Add(btnBrowseOutput);
			this.Controls.Add(this.txtOutputFont);
			this.Controls.Add(lblOutputFont);
			this.Controls.Add(btnBrowseText);
			this.Controls.Add(this.txtInputFile);
			this.Controls.Add(this.lblInputFile);
			this.Controls.Add(btnBrowseOrigin);
			this.Controls.Add(this.txtOriginFont);
			this.Controls.Add(labelOriginFont);
			this.Controls.Add(this.txtLog);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.MaximizeBox = false;
			this.Name = "MainForm";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "字体子集提取器";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.TextBox txtOriginFont;
		private System.Windows.Forms.TextBox txtInputFile;
		private System.Windows.Forms.TextBox txtOutputFont;
		private System.Windows.Forms.ComboBox comboExclude;
		private System.Windows.Forms.TextBox txtLog;
		private System.Windows.Forms.ComboBox comboInputEncode;
		private System.Windows.Forms.OpenFileDialog originFontDialog;
		private System.Windows.Forms.SaveFileDialog outputFontDialog;
		private System.Windows.Forms.OpenFileDialog inputTextDialog;
		private System.Windows.Forms.Label lblInputFile;
		private System.Windows.Forms.TextBox txtInputText;
		private System.Windows.Forms.Label lblInputText;
	}
}

