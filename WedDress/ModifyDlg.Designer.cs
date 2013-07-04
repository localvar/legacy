namespace WedDress
{
	partial class ModifyDlg
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose( bool disposing )
		{
			if( disposing && (components != null) )
			{
				components.Dispose();
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			System.Windows.Forms.Button btnClose;
			System.Windows.Forms.Button btnModify;
			System.Windows.Forms.Label labelReqDate3;
			System.Windows.Forms.Label labelReq3;
			System.Windows.Forms.Label labelReqDate2;
			System.Windows.Forms.Label labelReq2;
			System.Windows.Forms.Label labelReqDate1;
			System.Windows.Forms.Label labelReq1;
			System.Windows.Forms.Label labelArchiveNo;
			System.Windows.Forms.Label labelArchive;
			System.Windows.Forms.Label labelProducerNo;
			System.Windows.Forms.Label labelProducer;
			System.Windows.Forms.Button btnSelect;
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager( typeof( ModifyDlg ) );
			this.dlgSelImg = new System.Windows.Forms.OpenFileDialog();
			this.txtPrice = new System.Windows.Forms.TextBox();
			this.cbBuyer = new System.Windows.Forms.ComboBox();
			this.cbProducer = new System.Windows.Forms.ComboBox();
			this.cbColor = new System.Windows.Forms.ComboBox();
			this.cbCategory = new System.Windows.Forms.ComboBox();
			this.cbArea = new System.Windows.Forms.ComboBox();
			this.cbDept = new System.Windows.Forms.ComboBox();
			this.dtBuy = new System.Windows.Forms.DateTimePicker();
			this.dtReq3 = new System.Windows.Forms.DateTimePicker();
			this.dtReq2 = new System.Windows.Forms.DateTimePicker();
			this.dtReq1 = new System.Windows.Forms.DateTimePicker();
			this.dtArchive = new System.Windows.Forms.DateTimePicker();
			this.labelBuyer = new System.Windows.Forms.Label();
			this.txtBuyPrice = new System.Windows.Forms.TextBox();
			this.labelBuyPrice = new System.Windows.Forms.Label();
			this.labelBuyDate = new System.Windows.Forms.Label();
			this.txtReq3 = new System.Windows.Forms.TextBox();
			this.txtReq2 = new System.Windows.Forms.TextBox();
			this.txtReq1 = new System.Windows.Forms.TextBox();
			this.txtArchiveNo = new System.Windows.Forms.TextBox();
			this.txtProducerNo = new System.Windows.Forms.TextBox();
			this.txtAsessory = new System.Windows.Forms.TextBox();
			this.label11 = new System.Windows.Forms.Label();
			this.label9 = new System.Windows.Forms.Label();
			this.label10 = new System.Windows.Forms.Label();
			this.txtAreaNo = new System.Windows.Forms.TextBox();
			this.label7 = new System.Windows.Forms.Label();
			this.label8 = new System.Windows.Forms.Label();
			this.label6 = new System.Windows.Forms.Label();
			this.label5 = new System.Windows.Forms.Label();
			this.txtPath = new System.Windows.Forms.TextBox();
			this.pbPhoto = new System.Windows.Forms.PictureBox();
			btnClose = new System.Windows.Forms.Button();
			btnModify = new System.Windows.Forms.Button();
			labelReqDate3 = new System.Windows.Forms.Label();
			labelReq3 = new System.Windows.Forms.Label();
			labelReqDate2 = new System.Windows.Forms.Label();
			labelReq2 = new System.Windows.Forms.Label();
			labelReqDate1 = new System.Windows.Forms.Label();
			labelReq1 = new System.Windows.Forms.Label();
			labelArchiveNo = new System.Windows.Forms.Label();
			labelArchive = new System.Windows.Forms.Label();
			labelProducerNo = new System.Windows.Forms.Label();
			labelProducer = new System.Windows.Forms.Label();
			btnSelect = new System.Windows.Forms.Button();
			((System.ComponentModel.ISupportInitialize)(this.pbPhoto)).BeginInit();
			this.SuspendLayout();
			// 
			// btnClose
			// 
			btnClose.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			btnClose.Location = new System.Drawing.Point( 704, 410 );
			btnClose.Name = "btnClose";
			btnClose.Size = new System.Drawing.Size( 93, 23 );
			btnClose.TabIndex = 89;
			btnClose.Text = "取消";
			btnClose.UseVisualStyleBackColor = true;
			// 
			// btnModify
			// 
			btnModify.Location = new System.Drawing.Point( 589, 410 );
			btnModify.Name = "btnModify";
			btnModify.Size = new System.Drawing.Size( 93, 23 );
			btnModify.TabIndex = 88;
			btnModify.Text = "确定";
			btnModify.UseVisualStyleBackColor = true;
			btnModify.Click += new System.EventHandler( this.btnModify_Click );
			// 
			// labelReqDate3
			// 
			labelReqDate3.AutoSize = true;
			labelReqDate3.ForeColor = System.Drawing.Color.Blue;
			labelReqDate3.Location = new System.Drawing.Point( 582, 314 );
			labelReqDate3.Name = "labelReqDate3";
			labelReqDate3.Size = new System.Drawing.Size( 41, 12 );
			labelReqDate3.TabIndex = 80;
			labelReqDate3.Text = "日期3:";
			// 
			// labelReq3
			// 
			labelReq3.AutoSize = true;
			labelReq3.ForeColor = System.Drawing.Color.Blue;
			labelReq3.Location = new System.Drawing.Point( 326, 314 );
			labelReq3.Name = "labelReq3";
			labelReq3.Size = new System.Drawing.Size( 53, 12 );
			labelReq3.TabIndex = 78;
			labelReq3.Text = "调拨单3:";
			// 
			// labelReqDate2
			// 
			labelReqDate2.AutoSize = true;
			labelReqDate2.ForeColor = System.Drawing.Color.Blue;
			labelReqDate2.Location = new System.Drawing.Point( 582, 279 );
			labelReqDate2.Name = "labelReqDate2";
			labelReqDate2.Size = new System.Drawing.Size( 41, 12 );
			labelReqDate2.TabIndex = 76;
			labelReqDate2.Text = "日期2:";
			// 
			// labelReq2
			// 
			labelReq2.AutoSize = true;
			labelReq2.ForeColor = System.Drawing.Color.Blue;
			labelReq2.Location = new System.Drawing.Point( 326, 279 );
			labelReq2.Name = "labelReq2";
			labelReq2.Size = new System.Drawing.Size( 53, 12 );
			labelReq2.TabIndex = 74;
			labelReq2.Text = "调拨单2:";
			// 
			// labelReqDate1
			// 
			labelReqDate1.AutoSize = true;
			labelReqDate1.ForeColor = System.Drawing.Color.Blue;
			labelReqDate1.Location = new System.Drawing.Point( 582, 244 );
			labelReqDate1.Name = "labelReqDate1";
			labelReqDate1.Size = new System.Drawing.Size( 41, 12 );
			labelReqDate1.TabIndex = 72;
			labelReqDate1.Text = "日期1:";
			// 
			// labelReq1
			// 
			labelReq1.AutoSize = true;
			labelReq1.ForeColor = System.Drawing.Color.Blue;
			labelReq1.Location = new System.Drawing.Point( 326, 244 );
			labelReq1.Name = "labelReq1";
			labelReq1.Size = new System.Drawing.Size( 53, 12 );
			labelReq1.TabIndex = 70;
			labelReq1.Text = "调拨单1:";
			// 
			// labelArchiveNo
			// 
			labelArchiveNo.AutoSize = true;
			labelArchiveNo.ForeColor = System.Drawing.Color.Blue;
			labelArchiveNo.Location = new System.Drawing.Point( 564, 208 );
			labelArchiveNo.Name = "labelArchiveNo";
			labelArchiveNo.Size = new System.Drawing.Size( 59, 12 );
			labelArchiveNo.TabIndex = 68;
			labelArchiveNo.Text = "资料卡号:";
			// 
			// labelArchive
			// 
			labelArchive.AutoSize = true;
			labelArchive.ForeColor = System.Drawing.Color.Blue;
			labelArchive.Location = new System.Drawing.Point( 320, 209 );
			labelArchive.Name = "labelArchive";
			labelArchive.Size = new System.Drawing.Size( 59, 12 );
			labelArchive.TabIndex = 66;
			labelArchive.Text = "入档日期:";
			// 
			// labelProducerNo
			// 
			labelProducerNo.AutoSize = true;
			labelProducerNo.ForeColor = System.Drawing.Color.Blue;
			labelProducerNo.Location = new System.Drawing.Point( 576, 173 );
			labelProducerNo.Name = "labelProducerNo";
			labelProducerNo.Size = new System.Drawing.Size( 47, 12 );
			labelProducerNo.TabIndex = 64;
			labelProducerNo.Text = "厂商号:";
			// 
			// labelProducer
			// 
			labelProducer.AutoSize = true;
			labelProducer.ForeColor = System.Drawing.Color.Blue;
			labelProducer.Location = new System.Drawing.Point( 344, 174 );
			labelProducer.Name = "labelProducer";
			labelProducer.Size = new System.Drawing.Size( 35, 12 );
			labelProducer.TabIndex = 62;
			labelProducer.Text = "厂商:";
			// 
			// btnSelect
			// 
			btnSelect.FlatStyle = System.Windows.Forms.FlatStyle.System;
			btnSelect.Location = new System.Drawing.Point( 278, 410 );
			btnSelect.Name = "btnSelect";
			btnSelect.Size = new System.Drawing.Size( 31, 21 );
			btnSelect.TabIndex = 47;
			btnSelect.Text = "...";
			btnSelect.UseVisualStyleBackColor = true;
			btnSelect.Click += new System.EventHandler( this.btnSelect_Click );
			// 
			// dlgSelImg
			// 
			this.dlgSelImg.DefaultExt = "jpg";
			this.dlgSelImg.Filter = "图片文件(*.jpg;*.bmp;*.gif;*.png)|*.jpg;*.gif;*.bmp;*.png|所有文件(*.*)|*.*";
			this.dlgSelImg.Title = "选择照片";
			// 
			// txtPrice
			// 
			this.txtPrice.BackColor = System.Drawing.Color.White;
			this.txtPrice.Location = new System.Drawing.Point( 625, 78 );
			this.txtPrice.MaxLength = 12;
			this.txtPrice.Name = "txtPrice";
			this.txtPrice.Size = new System.Drawing.Size( 172, 21 );
			this.txtPrice.TabIndex = 59;
			this.txtPrice.Text = "0.00";
			this.txtPrice.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
			// 
			// cbBuyer
			// 
			this.cbBuyer.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.SuggestAppend;
			this.cbBuyer.AutoCompleteSource = System.Windows.Forms.AutoCompleteSource.ListItems;
			this.cbBuyer.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.cbBuyer.FormattingEnabled = true;
			this.cbBuyer.Location = new System.Drawing.Point( 382, 380 );
			this.cbBuyer.MaxDropDownItems = 20;
			this.cbBuyer.MaxLength = 50;
			this.cbBuyer.Name = "cbBuyer";
			this.cbBuyer.Size = new System.Drawing.Size( 172, 20 );
			this.cbBuyer.TabIndex = 87;
			this.cbBuyer.Visible = false;
			// 
			// cbProducer
			// 
			this.cbProducer.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.SuggestAppend;
			this.cbProducer.AutoCompleteSource = System.Windows.Forms.AutoCompleteSource.ListItems;
			this.cbProducer.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.cbProducer.FormattingEnabled = true;
			this.cbProducer.Location = new System.Drawing.Point( 382, 171 );
			this.cbProducer.MaxDropDownItems = 20;
			this.cbProducer.MaxLength = 50;
			this.cbProducer.Name = "cbProducer";
			this.cbProducer.Size = new System.Drawing.Size( 172, 20 );
			this.cbProducer.TabIndex = 63;
			// 
			// cbColor
			// 
			this.cbColor.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.SuggestAppend;
			this.cbColor.AutoCompleteSource = System.Windows.Forms.AutoCompleteSource.ListItems;
			this.cbColor.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.cbColor.FormattingEnabled = true;
			this.cbColor.Location = new System.Drawing.Point( 382, 79 );
			this.cbColor.MaxDropDownItems = 20;
			this.cbColor.MaxLength = 50;
			this.cbColor.Name = "cbColor";
			this.cbColor.Size = new System.Drawing.Size( 172, 20 );
			this.cbColor.TabIndex = 57;
			// 
			// cbCategory
			// 
			this.cbCategory.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.SuggestAppend;
			this.cbCategory.AutoCompleteSource = System.Windows.Forms.AutoCompleteSource.ListItems;
			this.cbCategory.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.cbCategory.FormattingEnabled = true;
			this.cbCategory.Location = new System.Drawing.Point( 382, 45 );
			this.cbCategory.MaxDropDownItems = 20;
			this.cbCategory.MaxLength = 50;
			this.cbCategory.Name = "cbCategory";
			this.cbCategory.Size = new System.Drawing.Size( 172, 20 );
			this.cbCategory.TabIndex = 53;
			// 
			// cbArea
			// 
			this.cbArea.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.SuggestAppend;
			this.cbArea.AutoCompleteSource = System.Windows.Forms.AutoCompleteSource.ListItems;
			this.cbArea.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.cbArea.FormattingEnabled = true;
			this.cbArea.Location = new System.Drawing.Point( 625, 11 );
			this.cbArea.MaxDropDownItems = 20;
			this.cbArea.MaxLength = 50;
			this.cbArea.Name = "cbArea";
			this.cbArea.Size = new System.Drawing.Size( 172, 20 );
			this.cbArea.TabIndex = 51;
			// 
			// cbDept
			// 
			this.cbDept.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.SuggestAppend;
			this.cbDept.AutoCompleteSource = System.Windows.Forms.AutoCompleteSource.ListItems;
			this.cbDept.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.cbDept.FormattingEnabled = true;
			this.cbDept.Location = new System.Drawing.Point( 382, 11 );
			this.cbDept.MaxDropDownItems = 20;
			this.cbDept.MaxLength = 50;
			this.cbDept.Name = "cbDept";
			this.cbDept.Size = new System.Drawing.Size( 172, 20 );
			this.cbDept.TabIndex = 49;
			// 
			// dtBuy
			// 
			this.dtBuy.Location = new System.Drawing.Point( 382, 345 );
			this.dtBuy.MaxDate = new System.DateTime( 2100, 12, 31, 0, 0, 0, 0 );
			this.dtBuy.MinDate = new System.DateTime( 1900, 1, 1, 0, 0, 0, 0 );
			this.dtBuy.Name = "dtBuy";
			this.dtBuy.Size = new System.Drawing.Size( 172, 21 );
			this.dtBuy.TabIndex = 83;
			this.dtBuy.Value = new System.DateTime( 1900, 1, 1, 0, 0, 0, 0 );
			this.dtBuy.Visible = false;
			// 
			// dtReq3
			// 
			this.dtReq3.Location = new System.Drawing.Point( 625, 310 );
			this.dtReq3.MaxDate = new System.DateTime( 2100, 12, 31, 0, 0, 0, 0 );
			this.dtReq3.MinDate = new System.DateTime( 1900, 1, 1, 0, 0, 0, 0 );
			this.dtReq3.Name = "dtReq3";
			this.dtReq3.Size = new System.Drawing.Size( 172, 21 );
			this.dtReq3.TabIndex = 81;
			this.dtReq3.Value = new System.DateTime( 1900, 1, 1, 0, 0, 0, 0 );
			// 
			// dtReq2
			// 
			this.dtReq2.Location = new System.Drawing.Point( 625, 275 );
			this.dtReq2.MaxDate = new System.DateTime( 2100, 12, 31, 0, 0, 0, 0 );
			this.dtReq2.MinDate = new System.DateTime( 1900, 1, 1, 0, 0, 0, 0 );
			this.dtReq2.Name = "dtReq2";
			this.dtReq2.Size = new System.Drawing.Size( 172, 21 );
			this.dtReq2.TabIndex = 77;
			this.dtReq2.Value = new System.DateTime( 1900, 1, 1, 0, 0, 0, 0 );
			// 
			// dtReq1
			// 
			this.dtReq1.Location = new System.Drawing.Point( 625, 240 );
			this.dtReq1.MaxDate = new System.DateTime( 2100, 12, 31, 0, 0, 0, 0 );
			this.dtReq1.MinDate = new System.DateTime( 1900, 1, 1, 0, 0, 0, 0 );
			this.dtReq1.Name = "dtReq1";
			this.dtReq1.Size = new System.Drawing.Size( 172, 21 );
			this.dtReq1.TabIndex = 73;
			this.dtReq1.Value = new System.DateTime( 1900, 1, 1, 0, 0, 0, 0 );
			// 
			// dtArchive
			// 
			this.dtArchive.Location = new System.Drawing.Point( 382, 205 );
			this.dtArchive.MaxDate = new System.DateTime( 2100, 12, 31, 0, 0, 0, 0 );
			this.dtArchive.MinDate = new System.DateTime( 1900, 1, 1, 0, 0, 0, 0 );
			this.dtArchive.Name = "dtArchive";
			this.dtArchive.Size = new System.Drawing.Size( 172, 21 );
			this.dtArchive.TabIndex = 67;
			this.dtArchive.Value = new System.DateTime( 1900, 1, 1, 0, 0, 0, 0 );
			// 
			// labelBuyer
			// 
			this.labelBuyer.AutoSize = true;
			this.labelBuyer.ForeColor = System.Drawing.Color.Red;
			this.labelBuyer.Location = new System.Drawing.Point( 332, 384 );
			this.labelBuyer.Name = "labelBuyer";
			this.labelBuyer.Size = new System.Drawing.Size( 47, 12 );
			this.labelBuyer.TabIndex = 86;
			this.labelBuyer.Text = "订货人:";
			this.labelBuyer.Visible = false;
			// 
			// txtBuyPrice
			// 
			this.txtBuyPrice.BackColor = System.Drawing.Color.White;
			this.txtBuyPrice.Location = new System.Drawing.Point( 626, 345 );
			this.txtBuyPrice.MaxLength = 12;
			this.txtBuyPrice.Name = "txtBuyPrice";
			this.txtBuyPrice.Size = new System.Drawing.Size( 172, 21 );
			this.txtBuyPrice.TabIndex = 85;
			this.txtBuyPrice.Text = "0.00";
			this.txtBuyPrice.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
			this.txtBuyPrice.Visible = false;
			// 
			// labelBuyPrice
			// 
			this.labelBuyPrice.AutoSize = true;
			this.labelBuyPrice.ForeColor = System.Drawing.Color.Red;
			this.labelBuyPrice.Location = new System.Drawing.Point( 588, 349 );
			this.labelBuyPrice.Name = "labelBuyPrice";
			this.labelBuyPrice.Size = new System.Drawing.Size( 35, 12 );
			this.labelBuyPrice.TabIndex = 84;
			this.labelBuyPrice.Text = "进价:";
			this.labelBuyPrice.Visible = false;
			// 
			// labelBuyDate
			// 
			this.labelBuyDate.AutoSize = true;
			this.labelBuyDate.ForeColor = System.Drawing.Color.Red;
			this.labelBuyDate.Location = new System.Drawing.Point( 320, 349 );
			this.labelBuyDate.Name = "labelBuyDate";
			this.labelBuyDate.Size = new System.Drawing.Size( 59, 12 );
			this.labelBuyDate.TabIndex = 82;
			this.labelBuyDate.Text = "进货日期:";
			this.labelBuyDate.Visible = false;
			// 
			// txtReq3
			// 
			this.txtReq3.BackColor = System.Drawing.Color.White;
			this.txtReq3.Location = new System.Drawing.Point( 382, 310 );
			this.txtReq3.MaxLength = 50;
			this.txtReq3.Name = "txtReq3";
			this.txtReq3.Size = new System.Drawing.Size( 172, 21 );
			this.txtReq3.TabIndex = 79;
			// 
			// txtReq2
			// 
			this.txtReq2.BackColor = System.Drawing.Color.White;
			this.txtReq2.Location = new System.Drawing.Point( 382, 275 );
			this.txtReq2.MaxLength = 50;
			this.txtReq2.Name = "txtReq2";
			this.txtReq2.Size = new System.Drawing.Size( 172, 21 );
			this.txtReq2.TabIndex = 75;
			// 
			// txtReq1
			// 
			this.txtReq1.BackColor = System.Drawing.Color.White;
			this.txtReq1.Location = new System.Drawing.Point( 382, 240 );
			this.txtReq1.MaxLength = 50;
			this.txtReq1.Name = "txtReq1";
			this.txtReq1.Size = new System.Drawing.Size( 172, 21 );
			this.txtReq1.TabIndex = 71;
			// 
			// txtArchiveNo
			// 
			this.txtArchiveNo.BackColor = System.Drawing.Color.White;
			this.txtArchiveNo.Location = new System.Drawing.Point( 626, 205 );
			this.txtArchiveNo.MaxLength = 50;
			this.txtArchiveNo.Name = "txtArchiveNo";
			this.txtArchiveNo.Size = new System.Drawing.Size( 172, 21 );
			this.txtArchiveNo.TabIndex = 69;
			// 
			// txtProducerNo
			// 
			this.txtProducerNo.BackColor = System.Drawing.Color.White;
			this.txtProducerNo.Location = new System.Drawing.Point( 626, 170 );
			this.txtProducerNo.MaxLength = 50;
			this.txtProducerNo.Name = "txtProducerNo";
			this.txtProducerNo.Size = new System.Drawing.Size( 172, 21 );
			this.txtProducerNo.TabIndex = 65;
			// 
			// txtAsessory
			// 
			this.txtAsessory.BackColor = System.Drawing.Color.White;
			this.txtAsessory.Location = new System.Drawing.Point( 382, 113 );
			this.txtAsessory.MaxLength = 255;
			this.txtAsessory.Multiline = true;
			this.txtAsessory.Name = "txtAsessory";
			this.txtAsessory.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
			this.txtAsessory.Size = new System.Drawing.Size( 416, 44 );
			this.txtAsessory.TabIndex = 61;
			// 
			// label11
			// 
			this.label11.AutoSize = true;
			this.label11.Location = new System.Drawing.Point( 344, 117 );
			this.label11.Name = "label11";
			this.label11.Size = new System.Drawing.Size( 35, 12 );
			this.label11.TabIndex = 60;
			this.label11.Text = "配件:";
			// 
			// label9
			// 
			this.label9.AutoSize = true;
			this.label9.Location = new System.Drawing.Point( 588, 82 );
			this.label9.Name = "label9";
			this.label9.Size = new System.Drawing.Size( 35, 12 );
			this.label9.TabIndex = 58;
			this.label9.Text = "售价:";
			// 
			// label10
			// 
			this.label10.AutoSize = true;
			this.label10.Location = new System.Drawing.Point( 344, 83 );
			this.label10.Name = "label10";
			this.label10.Size = new System.Drawing.Size( 35, 12 );
			this.label10.TabIndex = 56;
			this.label10.Text = "颜色:";
			// 
			// txtAreaNo
			// 
			this.txtAreaNo.BackColor = System.Drawing.Color.White;
			this.txtAreaNo.Location = new System.Drawing.Point( 626, 44 );
			this.txtAreaNo.MaxLength = 50;
			this.txtAreaNo.Name = "txtAreaNo";
			this.txtAreaNo.Size = new System.Drawing.Size( 172, 21 );
			this.txtAreaNo.TabIndex = 55;
			// 
			// label7
			// 
			this.label7.AutoSize = true;
			this.label7.Location = new System.Drawing.Point( 576, 48 );
			this.label7.Name = "label7";
			this.label7.Size = new System.Drawing.Size( 47, 12 );
			this.label7.TabIndex = 54;
			this.label7.Text = "区域号:";
			// 
			// label8
			// 
			this.label8.AutoSize = true;
			this.label8.Location = new System.Drawing.Point( 344, 49 );
			this.label8.Name = "label8";
			this.label8.Size = new System.Drawing.Size( 35, 12 );
			this.label8.TabIndex = 52;
			this.label8.Text = "类别:";
			// 
			// label6
			// 
			this.label6.AutoSize = true;
			this.label6.Location = new System.Drawing.Point( 588, 15 );
			this.label6.Name = "label6";
			this.label6.Size = new System.Drawing.Size( 35, 12 );
			this.label6.TabIndex = 50;
			this.label6.Text = "区域:";
			// 
			// label5
			// 
			this.label5.AutoSize = true;
			this.label5.Location = new System.Drawing.Point( 344, 15 );
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size( 35, 12 );
			this.label5.TabIndex = 48;
			this.label5.Text = "部门:";
			// 
			// txtPath
			// 
			this.txtPath.BackColor = System.Drawing.Color.White;
			this.txtPath.Location = new System.Drawing.Point( 9, 410 );
			this.txtPath.Name = "txtPath";
			this.txtPath.ReadOnly = true;
			this.txtPath.Size = new System.Drawing.Size( 267, 21 );
			this.txtPath.TabIndex = 46;
			// 
			// pbPhoto
			// 
			this.pbPhoto.ErrorImage = ((System.Drawing.Image)(resources.GetObject( "pbPhoto.ErrorImage" )));
			this.pbPhoto.InitialImage = ((System.Drawing.Image)(resources.GetObject( "pbPhoto.InitialImage" )));
			this.pbPhoto.Location = new System.Drawing.Point( 9, 4 );
			this.pbPhoto.Name = "pbPhoto";
			this.pbPhoto.Size = new System.Drawing.Size( 300, 400 );
			this.pbPhoto.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
			this.pbPhoto.TabIndex = 45;
			this.pbPhoto.TabStop = false;
			// 
			// ModifyDlg
			// 
			this.AcceptButton = btnModify;
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 12F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = btnClose;
			this.ClientSize = new System.Drawing.Size( 806, 437 );
			this.Controls.Add( this.txtPrice );
			this.Controls.Add( this.cbBuyer );
			this.Controls.Add( this.cbProducer );
			this.Controls.Add( this.cbColor );
			this.Controls.Add( this.cbCategory );
			this.Controls.Add( this.cbArea );
			this.Controls.Add( this.cbDept );
			this.Controls.Add( btnClose );
			this.Controls.Add( btnModify );
			this.Controls.Add( this.dtBuy );
			this.Controls.Add( this.dtReq3 );
			this.Controls.Add( this.dtReq2 );
			this.Controls.Add( this.dtReq1 );
			this.Controls.Add( this.dtArchive );
			this.Controls.Add( this.labelBuyer );
			this.Controls.Add( this.txtBuyPrice );
			this.Controls.Add( this.labelBuyPrice );
			this.Controls.Add( this.labelBuyDate );
			this.Controls.Add( labelReqDate3 );
			this.Controls.Add( this.txtReq3 );
			this.Controls.Add( labelReq3 );
			this.Controls.Add( labelReqDate2 );
			this.Controls.Add( this.txtReq2 );
			this.Controls.Add( labelReq2 );
			this.Controls.Add( labelReqDate1 );
			this.Controls.Add( this.txtReq1 );
			this.Controls.Add( labelReq1 );
			this.Controls.Add( this.txtArchiveNo );
			this.Controls.Add( labelArchiveNo );
			this.Controls.Add( labelArchive );
			this.Controls.Add( this.txtProducerNo );
			this.Controls.Add( labelProducerNo );
			this.Controls.Add( labelProducer );
			this.Controls.Add( this.txtAsessory );
			this.Controls.Add( this.label11 );
			this.Controls.Add( this.label9 );
			this.Controls.Add( this.label10 );
			this.Controls.Add( this.txtAreaNo );
			this.Controls.Add( this.label7 );
			this.Controls.Add( this.label8 );
			this.Controls.Add( this.label6 );
			this.Controls.Add( this.label5 );
			this.Controls.Add( btnSelect );
			this.Controls.Add( this.txtPath );
			this.Controls.Add( this.pbPhoto );
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "ModifyDlg";
			this.ShowInTaskbar = false;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "修改";
			this.Load += new System.EventHandler( this.ModifyDlg_Load );
			((System.ComponentModel.ISupportInitialize)(this.pbPhoto)).EndInit();
			this.ResumeLayout( false );
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.OpenFileDialog dlgSelImg;
		private System.Windows.Forms.TextBox txtPrice;
		private System.Windows.Forms.ComboBox cbBuyer;
		private System.Windows.Forms.ComboBox cbProducer;
		private System.Windows.Forms.ComboBox cbColor;
		private System.Windows.Forms.ComboBox cbCategory;
		private System.Windows.Forms.ComboBox cbArea;
		private System.Windows.Forms.ComboBox cbDept;
		private System.Windows.Forms.DateTimePicker dtBuy;
		private System.Windows.Forms.DateTimePicker dtReq3;
		private System.Windows.Forms.DateTimePicker dtReq2;
		private System.Windows.Forms.DateTimePicker dtReq1;
		private System.Windows.Forms.DateTimePicker dtArchive;
		private System.Windows.Forms.Label labelBuyer;
		private System.Windows.Forms.TextBox txtBuyPrice;
		private System.Windows.Forms.Label labelBuyPrice;
		private System.Windows.Forms.Label labelBuyDate;
		private System.Windows.Forms.TextBox txtReq3;
		private System.Windows.Forms.TextBox txtReq2;
		private System.Windows.Forms.TextBox txtReq1;
		private System.Windows.Forms.TextBox txtArchiveNo;
		private System.Windows.Forms.TextBox txtProducerNo;
		private System.Windows.Forms.TextBox txtAsessory;
		private System.Windows.Forms.Label label11;
		private System.Windows.Forms.Label label9;
		private System.Windows.Forms.Label label10;
		private System.Windows.Forms.TextBox txtAreaNo;
		private System.Windows.Forms.Label label7;
		private System.Windows.Forms.Label label8;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.TextBox txtPath;
		private System.Windows.Forms.PictureBox pbPhoto;
	}
}