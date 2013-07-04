namespace WedDress
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
			System.Windows.Forms.SplitContainer splitContainer1;
			System.Windows.Forms.SplitContainer splitContainer2;
			System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle7 = new System.Windows.Forms.DataGridViewCellStyle();
			System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle8 = new System.Windows.Forms.DataGridViewCellStyle();
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager( typeof( MainForm ) );
			this.lblNumDress = new System.Windows.Forms.Label();
			this.cbAreaNo = new System.Windows.Forms.ComboBox();
			this.label12 = new System.Windows.Forms.Label();
			this.btnDel = new System.Windows.Forms.Button();
			this.btnModify = new System.Windows.Forms.Button();
			this.btnNew = new System.Windows.Forms.Button();
			this.cbProducer = new System.Windows.Forms.ComboBox();
			this.lblProducer = new System.Windows.Forms.Label();
			this.cbColor = new System.Windows.Forms.ComboBox();
			this.label3 = new System.Windows.Forms.Label();
			this.cbCategory = new System.Windows.Forms.ComboBox();
			this.label4 = new System.Windows.Forms.Label();
			this.cbArea = new System.Windows.Forms.ComboBox();
			this.label2 = new System.Windows.Forms.Label();
			this.cbDept = new System.Windows.Forms.ComboBox();
			this.label1 = new System.Windows.Forms.Label();
			this.btnQuery = new System.Windows.Forms.Button();
			this.dataGridView = new System.Windows.Forms.DataGridView();
			this.clmnID = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDept = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnArea = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnAreaNo = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnCate = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnColor = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnPrice = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnAccsry = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.dsDress = new System.Data.DataSet();
			this.WedDress = new System.Data.DataTable();
			this.btnRent = new System.Windows.Forms.Button();
			this.txtBuyer = new System.Windows.Forms.TextBox();
			this.labelBuyer = new System.Windows.Forms.Label();
			this.txtBuyPrice = new System.Windows.Forms.TextBox();
			this.labelBuyPrice = new System.Windows.Forms.Label();
			this.txtBuyDate = new System.Windows.Forms.TextBox();
			this.labelBuyDate = new System.Windows.Forms.Label();
			this.txtReqDate3 = new System.Windows.Forms.TextBox();
			this.labelReqDate3 = new System.Windows.Forms.Label();
			this.txtReq3 = new System.Windows.Forms.TextBox();
			this.labelReq3 = new System.Windows.Forms.Label();
			this.txtReqDate2 = new System.Windows.Forms.TextBox();
			this.labelReqDate2 = new System.Windows.Forms.Label();
			this.txtReq2 = new System.Windows.Forms.TextBox();
			this.labelReq2 = new System.Windows.Forms.Label();
			this.txtReqDate1 = new System.Windows.Forms.TextBox();
			this.labelReqDate1 = new System.Windows.Forms.Label();
			this.txtReq1 = new System.Windows.Forms.TextBox();
			this.labelReq1 = new System.Windows.Forms.Label();
			this.txtArchiveNo = new System.Windows.Forms.TextBox();
			this.labelArchiveNo = new System.Windows.Forms.Label();
			this.txtArchive = new System.Windows.Forms.TextBox();
			this.labelArchive = new System.Windows.Forms.Label();
			this.txtProducerNo = new System.Windows.Forms.TextBox();
			this.labelProducerNo = new System.Windows.Forms.Label();
			this.txtProducer = new System.Windows.Forms.TextBox();
			this.labelProducer = new System.Windows.Forms.Label();
			this.txtAsessory = new System.Windows.Forms.TextBox();
			this.label11 = new System.Windows.Forms.Label();
			this.txtPrice = new System.Windows.Forms.TextBox();
			this.label9 = new System.Windows.Forms.Label();
			this.txtColor = new System.Windows.Forms.TextBox();
			this.label10 = new System.Windows.Forms.Label();
			this.txtAreaNo = new System.Windows.Forms.TextBox();
			this.label7 = new System.Windows.Forms.Label();
			this.txtCategory = new System.Windows.Forms.TextBox();
			this.label8 = new System.Windows.Forms.Label();
			this.txtArea = new System.Windows.Forms.TextBox();
			this.label6 = new System.Windows.Forms.Label();
			this.txtDept = new System.Windows.Forms.TextBox();
			this.label5 = new System.Windows.Forms.Label();
			this.pbPhoto = new System.Windows.Forms.PictureBox();
			this.lblRent = new System.Windows.Forms.Label();
			this.dtRent = new System.Windows.Forms.DateTimePicker();
			this.btnQueryByRent = new System.Windows.Forms.Button();
			splitContainer1 = new System.Windows.Forms.SplitContainer();
			splitContainer2 = new System.Windows.Forms.SplitContainer();
			splitContainer1.Panel1.SuspendLayout();
			splitContainer1.Panel2.SuspendLayout();
			splitContainer1.SuspendLayout();
			splitContainer2.Panel1.SuspendLayout();
			splitContainer2.Panel2.SuspendLayout();
			splitContainer2.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.dataGridView)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.dsDress)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.WedDress)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.pbPhoto)).BeginInit();
			this.SuspendLayout();
			// 
			// splitContainer1
			// 
			splitContainer1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
			splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
			splitContainer1.IsSplitterFixed = true;
			splitContainer1.Location = new System.Drawing.Point( 0, 0 );
			splitContainer1.Name = "splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			splitContainer1.Panel1.Controls.Add( this.btnQueryByRent );
			splitContainer1.Panel1.Controls.Add( this.dtRent );
			splitContainer1.Panel1.Controls.Add( this.lblRent );
			splitContainer1.Panel1.Controls.Add( this.lblNumDress );
			splitContainer1.Panel1.Controls.Add( this.cbAreaNo );
			splitContainer1.Panel1.Controls.Add( this.label12 );
			splitContainer1.Panel1.Controls.Add( this.btnDel );
			splitContainer1.Panel1.Controls.Add( this.btnModify );
			splitContainer1.Panel1.Controls.Add( this.btnNew );
			splitContainer1.Panel1.Controls.Add( this.cbProducer );
			splitContainer1.Panel1.Controls.Add( this.lblProducer );
			splitContainer1.Panel1.Controls.Add( this.cbColor );
			splitContainer1.Panel1.Controls.Add( this.label3 );
			splitContainer1.Panel1.Controls.Add( this.cbCategory );
			splitContainer1.Panel1.Controls.Add( this.label4 );
			splitContainer1.Panel1.Controls.Add( this.cbArea );
			splitContainer1.Panel1.Controls.Add( this.label2 );
			splitContainer1.Panel1.Controls.Add( this.cbDept );
			splitContainer1.Panel1.Controls.Add( this.label1 );
			splitContainer1.Panel1.Controls.Add( this.btnQuery );
			// 
			// splitContainer1.Panel2
			// 
			splitContainer1.Panel2.Controls.Add( splitContainer2 );
			splitContainer1.Size = new System.Drawing.Size( 1014, 709 );
			splitContainer1.SplitterDistance = 206;
			splitContainer1.TabIndex = 0;
			// 
			// lblNumDress
			// 
			this.lblNumDress.AutoSize = true;
			this.lblNumDress.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.lblNumDress.Location = new System.Drawing.Point( 9, 295 );
			this.lblNumDress.Name = "lblNumDress";
			this.lblNumDress.Size = new System.Drawing.Size( 167, 12 );
			this.lblNumDress.TabIndex = 17;
			this.lblNumDress.Text = "共有 0 件符合查询条件的服装";
			this.lblNumDress.Visible = false;
			// 
			// cbAreaNo
			// 
			this.cbAreaNo.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.cbAreaNo.FormattingEnabled = true;
			this.cbAreaNo.Items.AddRange( new object[] {
            ""} );
			this.cbAreaNo.Location = new System.Drawing.Point( 67, 56 );
			this.cbAreaNo.Name = "cbAreaNo";
			this.cbAreaNo.Size = new System.Drawing.Size( 130, 20 );
			this.cbAreaNo.TabIndex = 5;
			// 
			// label12
			// 
			this.label12.AutoSize = true;
			this.label12.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.label12.Location = new System.Drawing.Point( 12, 60 );
			this.label12.Name = "label12";
			this.label12.Size = new System.Drawing.Size( 47, 12 );
			this.label12.TabIndex = 5;
			this.label12.Text = "区域号:";
			// 
			// btnDel
			// 
			this.btnDel.Enabled = false;
			this.btnDel.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.btnDel.Location = new System.Drawing.Point( 6, 256 );
			this.btnDel.Name = "btnDel";
			this.btnDel.Size = new System.Drawing.Size( 191, 25 );
			this.btnDel.TabIndex = 16;
			this.btnDel.Text = "删除(&E)";
			this.btnDel.UseVisualStyleBackColor = true;
			this.btnDel.Visible = false;
			this.btnDel.Click += new System.EventHandler( this.btnDel_Click );
			// 
			// btnModify
			// 
			this.btnModify.Enabled = false;
			this.btnModify.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.btnModify.Location = new System.Drawing.Point( 6, 225 );
			this.btnModify.Name = "btnModify";
			this.btnModify.Size = new System.Drawing.Size( 191, 25 );
			this.btnModify.TabIndex = 15;
			this.btnModify.Text = "修改(&M)...";
			this.btnModify.UseVisualStyleBackColor = true;
			this.btnModify.Visible = false;
			this.btnModify.Click += new System.EventHandler( this.btnModify_Click );
			// 
			// btnNew
			// 
			this.btnNew.Enabled = false;
			this.btnNew.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.btnNew.Location = new System.Drawing.Point( 6, 194 );
			this.btnNew.Name = "btnNew";
			this.btnNew.Size = new System.Drawing.Size( 191, 25 );
			this.btnNew.TabIndex = 14;
			this.btnNew.Text = "添加(&A)...";
			this.btnNew.UseVisualStyleBackColor = true;
			this.btnNew.Visible = false;
			this.btnNew.Click += new System.EventHandler( this.btnNew_Click );
			// 
			// cbProducer
			// 
			this.cbProducer.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.SuggestAppend;
			this.cbProducer.AutoCompleteSource = System.Windows.Forms.AutoCompleteSource.ListItems;
			this.cbProducer.Enabled = false;
			this.cbProducer.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.cbProducer.FormattingEnabled = true;
			this.cbProducer.Location = new System.Drawing.Point( 67, 134 );
			this.cbProducer.MaxDropDownItems = 20;
			this.cbProducer.Name = "cbProducer";
			this.cbProducer.Size = new System.Drawing.Size( 130, 20 );
			this.cbProducer.TabIndex = 10;
			this.cbProducer.Visible = false;
			// 
			// lblProducer
			// 
			this.lblProducer.AutoSize = true;
			this.lblProducer.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.lblProducer.Location = new System.Drawing.Point( 24, 138 );
			this.lblProducer.Name = "lblProducer";
			this.lblProducer.Size = new System.Drawing.Size( 35, 12 );
			this.lblProducer.TabIndex = 9;
			this.lblProducer.Text = "厂商:";
			this.lblProducer.Visible = false;
			// 
			// cbColor
			// 
			this.cbColor.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.SuggestAppend;
			this.cbColor.AutoCompleteSource = System.Windows.Forms.AutoCompleteSource.ListItems;
			this.cbColor.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.cbColor.FormattingEnabled = true;
			this.cbColor.Location = new System.Drawing.Point( 67, 108 );
			this.cbColor.MaxDropDownItems = 20;
			this.cbColor.Name = "cbColor";
			this.cbColor.Size = new System.Drawing.Size( 130, 20 );
			this.cbColor.TabIndex = 8;
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.label3.Location = new System.Drawing.Point( 24, 112 );
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size( 35, 12 );
			this.label3.TabIndex = 7;
			this.label3.Text = "颜色:";
			// 
			// cbCategory
			// 
			this.cbCategory.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.SuggestAppend;
			this.cbCategory.AutoCompleteSource = System.Windows.Forms.AutoCompleteSource.ListItems;
			this.cbCategory.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.cbCategory.FormattingEnabled = true;
			this.cbCategory.Location = new System.Drawing.Point( 67, 82 );
			this.cbCategory.MaxDropDownItems = 20;
			this.cbCategory.Name = "cbCategory";
			this.cbCategory.Size = new System.Drawing.Size( 130, 20 );
			this.cbCategory.TabIndex = 6;
			// 
			// label4
			// 
			this.label4.AutoSize = true;
			this.label4.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.label4.Location = new System.Drawing.Point( 24, 86 );
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size( 35, 12 );
			this.label4.TabIndex = 5;
			this.label4.Text = "类别:";
			// 
			// cbArea
			// 
			this.cbArea.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.SuggestAppend;
			this.cbArea.AutoCompleteSource = System.Windows.Forms.AutoCompleteSource.ListItems;
			this.cbArea.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.cbArea.FormattingEnabled = true;
			this.cbArea.Location = new System.Drawing.Point( 67, 30 );
			this.cbArea.MaxDropDownItems = 20;
			this.cbArea.Name = "cbArea";
			this.cbArea.Size = new System.Drawing.Size( 130, 20 );
			this.cbArea.TabIndex = 4;
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.label2.Location = new System.Drawing.Point( 24, 34 );
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size( 35, 12 );
			this.label2.TabIndex = 3;
			this.label2.Text = "区域:";
			// 
			// cbDept
			// 
			this.cbDept.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.SuggestAppend;
			this.cbDept.AutoCompleteSource = System.Windows.Forms.AutoCompleteSource.ListItems;
			this.cbDept.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.cbDept.FormattingEnabled = true;
			this.cbDept.Location = new System.Drawing.Point( 67, 4 );
			this.cbDept.MaxDropDownItems = 20;
			this.cbDept.Name = "cbDept";
			this.cbDept.Size = new System.Drawing.Size( 130, 20 );
			this.cbDept.TabIndex = 2;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.label1.Location = new System.Drawing.Point( 24, 8 );
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size( 35, 12 );
			this.label1.TabIndex = 1;
			this.label1.Text = "部门:";
			// 
			// btnQuery
			// 
			this.btnQuery.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.btnQuery.Location = new System.Drawing.Point( 6, 163 );
			this.btnQuery.Name = "btnQuery";
			this.btnQuery.Size = new System.Drawing.Size( 191, 25 );
			this.btnQuery.TabIndex = 13;
			this.btnQuery.Text = "查询(&Q)";
			this.btnQuery.UseVisualStyleBackColor = true;
			this.btnQuery.Click += new System.EventHandler( this.btnQuery_Click );
			// 
			// splitContainer2
			// 
			splitContainer2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			splitContainer2.Dock = System.Windows.Forms.DockStyle.Fill;
			splitContainer2.Location = new System.Drawing.Point( 0, 0 );
			splitContainer2.Name = "splitContainer2";
			splitContainer2.Orientation = System.Windows.Forms.Orientation.Horizontal;
			// 
			// splitContainer2.Panel1
			// 
			splitContainer2.Panel1.Controls.Add( this.dataGridView );
			// 
			// splitContainer2.Panel2
			// 
			splitContainer2.Panel2.AutoScroll = true;
			splitContainer2.Panel2.Controls.Add( this.btnRent );
			splitContainer2.Panel2.Controls.Add( this.txtBuyer );
			splitContainer2.Panel2.Controls.Add( this.labelBuyer );
			splitContainer2.Panel2.Controls.Add( this.txtBuyPrice );
			splitContainer2.Panel2.Controls.Add( this.labelBuyPrice );
			splitContainer2.Panel2.Controls.Add( this.txtBuyDate );
			splitContainer2.Panel2.Controls.Add( this.labelBuyDate );
			splitContainer2.Panel2.Controls.Add( this.txtReqDate3 );
			splitContainer2.Panel2.Controls.Add( this.labelReqDate3 );
			splitContainer2.Panel2.Controls.Add( this.txtReq3 );
			splitContainer2.Panel2.Controls.Add( this.labelReq3 );
			splitContainer2.Panel2.Controls.Add( this.txtReqDate2 );
			splitContainer2.Panel2.Controls.Add( this.labelReqDate2 );
			splitContainer2.Panel2.Controls.Add( this.txtReq2 );
			splitContainer2.Panel2.Controls.Add( this.labelReq2 );
			splitContainer2.Panel2.Controls.Add( this.txtReqDate1 );
			splitContainer2.Panel2.Controls.Add( this.labelReqDate1 );
			splitContainer2.Panel2.Controls.Add( this.txtReq1 );
			splitContainer2.Panel2.Controls.Add( this.labelReq1 );
			splitContainer2.Panel2.Controls.Add( this.txtArchiveNo );
			splitContainer2.Panel2.Controls.Add( this.labelArchiveNo );
			splitContainer2.Panel2.Controls.Add( this.txtArchive );
			splitContainer2.Panel2.Controls.Add( this.labelArchive );
			splitContainer2.Panel2.Controls.Add( this.txtProducerNo );
			splitContainer2.Panel2.Controls.Add( this.labelProducerNo );
			splitContainer2.Panel2.Controls.Add( this.txtProducer );
			splitContainer2.Panel2.Controls.Add( this.labelProducer );
			splitContainer2.Panel2.Controls.Add( this.txtAsessory );
			splitContainer2.Panel2.Controls.Add( this.label11 );
			splitContainer2.Panel2.Controls.Add( this.txtPrice );
			splitContainer2.Panel2.Controls.Add( this.label9 );
			splitContainer2.Panel2.Controls.Add( this.txtColor );
			splitContainer2.Panel2.Controls.Add( this.label10 );
			splitContainer2.Panel2.Controls.Add( this.txtAreaNo );
			splitContainer2.Panel2.Controls.Add( this.label7 );
			splitContainer2.Panel2.Controls.Add( this.txtCategory );
			splitContainer2.Panel2.Controls.Add( this.label8 );
			splitContainer2.Panel2.Controls.Add( this.txtArea );
			splitContainer2.Panel2.Controls.Add( this.label6 );
			splitContainer2.Panel2.Controls.Add( this.txtDept );
			splitContainer2.Panel2.Controls.Add( this.label5 );
			splitContainer2.Panel2.Controls.Add( this.pbPhoto );
			splitContainer2.Size = new System.Drawing.Size( 804, 709 );
			splitContainer2.SplitterDistance = 292;
			splitContainer2.TabIndex = 0;
			// 
			// dataGridView
			// 
			this.dataGridView.AllowUserToAddRows = false;
			this.dataGridView.AllowUserToDeleteRows = false;
			this.dataGridView.AllowUserToOrderColumns = true;
			this.dataGridView.AllowUserToResizeRows = false;
			dataGridViewCellStyle7.BackColor = System.Drawing.Color.FromArgb( ((int)(((byte)(192)))), ((int)(((byte)(192)))), ((int)(((byte)(255)))) );
			this.dataGridView.AlternatingRowsDefaultCellStyle = dataGridViewCellStyle7;
			this.dataGridView.AutoGenerateColumns = false;
			this.dataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			this.dataGridView.Columns.AddRange( new System.Windows.Forms.DataGridViewColumn[] {
            this.clmnID,
            this.clmnDept,
            this.clmnArea,
            this.clmnAreaNo,
            this.clmnCate,
            this.clmnColor,
            this.clmnPrice,
            this.clmnAccsry} );
			this.dataGridView.DataMember = "WedDress";
			this.dataGridView.DataSource = this.dsDress;
			this.dataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
			this.dataGridView.Location = new System.Drawing.Point( 0, 0 );
			this.dataGridView.MultiSelect = false;
			this.dataGridView.Name = "dataGridView";
			this.dataGridView.ReadOnly = true;
			this.dataGridView.RowHeadersVisible = false;
			dataGridViewCellStyle8.BackColor = System.Drawing.Color.FromArgb( ((int)(((byte)(192)))), ((int)(((byte)(255)))), ((int)(((byte)(255)))) );
			this.dataGridView.RowsDefaultCellStyle = dataGridViewCellStyle8;
			this.dataGridView.RowTemplate.Height = 23;
			this.dataGridView.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
			this.dataGridView.Size = new System.Drawing.Size( 802, 290 );
			this.dataGridView.StandardTab = true;
			this.dataGridView.TabIndex = 0;
			this.dataGridView.CellMouseDoubleClick += new System.Windows.Forms.DataGridViewCellMouseEventHandler( this.dataGridView_CellMouseDoubleClick );
			this.dataGridView.SelectionChanged += new System.EventHandler( this.dataGridView_SelectionChanged );
			// 
			// clmnID
			// 
			this.clmnID.DataPropertyName = "ID";
			this.clmnID.HeaderText = "ID";
			this.clmnID.Name = "clmnID";
			this.clmnID.ReadOnly = true;
			this.clmnID.Visible = false;
			// 
			// clmnDept
			// 
			this.clmnDept.DataPropertyName = "部门";
			this.clmnDept.HeaderText = "部门";
			this.clmnDept.Name = "clmnDept";
			this.clmnDept.ReadOnly = true;
			this.clmnDept.Width = 90;
			// 
			// clmnArea
			// 
			this.clmnArea.DataPropertyName = "区域";
			this.clmnArea.HeaderText = "区域";
			this.clmnArea.Name = "clmnArea";
			this.clmnArea.ReadOnly = true;
			this.clmnArea.Width = 90;
			// 
			// clmnAreaNo
			// 
			this.clmnAreaNo.DataPropertyName = "区域号";
			this.clmnAreaNo.HeaderText = "区域号";
			this.clmnAreaNo.Name = "clmnAreaNo";
			this.clmnAreaNo.ReadOnly = true;
			this.clmnAreaNo.Width = 90;
			// 
			// clmnCate
			// 
			this.clmnCate.DataPropertyName = "类别";
			this.clmnCate.HeaderText = "类别";
			this.clmnCate.Name = "clmnCate";
			this.clmnCate.ReadOnly = true;
			this.clmnCate.Width = 90;
			// 
			// clmnColor
			// 
			this.clmnColor.DataPropertyName = "颜色";
			this.clmnColor.HeaderText = "颜色";
			this.clmnColor.Name = "clmnColor";
			this.clmnColor.ReadOnly = true;
			this.clmnColor.Width = 90;
			// 
			// clmnPrice
			// 
			this.clmnPrice.DataPropertyName = "售价";
			this.clmnPrice.HeaderText = "售价";
			this.clmnPrice.Name = "clmnPrice";
			this.clmnPrice.ReadOnly = true;
			this.clmnPrice.Width = 90;
			// 
			// clmnAccsry
			// 
			this.clmnAccsry.DataPropertyName = "配件";
			this.clmnAccsry.HeaderText = "配件";
			this.clmnAccsry.Name = "clmnAccsry";
			this.clmnAccsry.ReadOnly = true;
			this.clmnAccsry.Width = 230;
			// 
			// dsDress
			// 
			this.dsDress.DataSetName = "dsDress";
			this.dsDress.Tables.AddRange( new System.Data.DataTable[] {
            this.WedDress} );
			// 
			// WedDress
			// 
			this.WedDress.TableName = "WedDress";
			// 
			// btnRent
			// 
			this.btnRent.Location = new System.Drawing.Point( 615, 385 );
			this.btnRent.Name = "btnRent";
			this.btnRent.Size = new System.Drawing.Size( 171, 23 );
			this.btnRent.TabIndex = 41;
			this.btnRent.Text = "出件(&T)...";
			this.btnRent.UseVisualStyleBackColor = true;
			this.btnRent.Click += new System.EventHandler( this.btnRent_Click );
			// 
			// txtBuyer
			// 
			this.txtBuyer.BackColor = System.Drawing.Color.White;
			this.txtBuyer.ForeColor = System.Drawing.SystemColors.WindowText;
			this.txtBuyer.Location = new System.Drawing.Point( 370, 385 );
			this.txtBuyer.Name = "txtBuyer";
			this.txtBuyer.ReadOnly = true;
			this.txtBuyer.Size = new System.Drawing.Size( 172, 21 );
			this.txtBuyer.TabIndex = 40;
			this.txtBuyer.Visible = false;
			// 
			// labelBuyer
			// 
			this.labelBuyer.AutoSize = true;
			this.labelBuyer.ForeColor = System.Drawing.Color.Red;
			this.labelBuyer.Location = new System.Drawing.Point( 320, 390 );
			this.labelBuyer.Name = "labelBuyer";
			this.labelBuyer.Size = new System.Drawing.Size( 47, 12 );
			this.labelBuyer.TabIndex = 39;
			this.labelBuyer.Text = "订货人:";
			this.labelBuyer.Visible = false;
			// 
			// txtBuyPrice
			// 
			this.txtBuyPrice.BackColor = System.Drawing.Color.White;
			this.txtBuyPrice.ForeColor = System.Drawing.SystemColors.WindowText;
			this.txtBuyPrice.Location = new System.Drawing.Point( 614, 351 );
			this.txtBuyPrice.Name = "txtBuyPrice";
			this.txtBuyPrice.ReadOnly = true;
			this.txtBuyPrice.Size = new System.Drawing.Size( 172, 21 );
			this.txtBuyPrice.TabIndex = 38;
			this.txtBuyPrice.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
			this.txtBuyPrice.Visible = false;
			// 
			// labelBuyPrice
			// 
			this.labelBuyPrice.AutoSize = true;
			this.labelBuyPrice.ForeColor = System.Drawing.Color.Red;
			this.labelBuyPrice.Location = new System.Drawing.Point( 576, 356 );
			this.labelBuyPrice.Name = "labelBuyPrice";
			this.labelBuyPrice.Size = new System.Drawing.Size( 35, 12 );
			this.labelBuyPrice.TabIndex = 37;
			this.labelBuyPrice.Text = "进价:";
			this.labelBuyPrice.Visible = false;
			// 
			// txtBuyDate
			// 
			this.txtBuyDate.BackColor = System.Drawing.Color.White;
			this.txtBuyDate.ForeColor = System.Drawing.SystemColors.WindowText;
			this.txtBuyDate.Location = new System.Drawing.Point( 370, 351 );
			this.txtBuyDate.Name = "txtBuyDate";
			this.txtBuyDate.ReadOnly = true;
			this.txtBuyDate.Size = new System.Drawing.Size( 172, 21 );
			this.txtBuyDate.TabIndex = 36;
			this.txtBuyDate.Visible = false;
			// 
			// labelBuyDate
			// 
			this.labelBuyDate.AutoSize = true;
			this.labelBuyDate.ForeColor = System.Drawing.Color.Red;
			this.labelBuyDate.Location = new System.Drawing.Point( 308, 356 );
			this.labelBuyDate.Name = "labelBuyDate";
			this.labelBuyDate.Size = new System.Drawing.Size( 59, 12 );
			this.labelBuyDate.TabIndex = 35;
			this.labelBuyDate.Text = "进货日期:";
			this.labelBuyDate.Visible = false;
			// 
			// txtReqDate3
			// 
			this.txtReqDate3.BackColor = System.Drawing.Color.White;
			this.txtReqDate3.ForeColor = System.Drawing.SystemColors.WindowText;
			this.txtReqDate3.Location = new System.Drawing.Point( 614, 316 );
			this.txtReqDate3.Name = "txtReqDate3";
			this.txtReqDate3.ReadOnly = true;
			this.txtReqDate3.Size = new System.Drawing.Size( 172, 21 );
			this.txtReqDate3.TabIndex = 34;
			this.txtReqDate3.Visible = false;
			// 
			// labelReqDate3
			// 
			this.labelReqDate3.AutoSize = true;
			this.labelReqDate3.ForeColor = System.Drawing.Color.Blue;
			this.labelReqDate3.Location = new System.Drawing.Point( 570, 321 );
			this.labelReqDate3.Name = "labelReqDate3";
			this.labelReqDate3.Size = new System.Drawing.Size( 41, 12 );
			this.labelReqDate3.TabIndex = 33;
			this.labelReqDate3.Text = "日期3:";
			this.labelReqDate3.Visible = false;
			// 
			// txtReq3
			// 
			this.txtReq3.BackColor = System.Drawing.Color.White;
			this.txtReq3.ForeColor = System.Drawing.SystemColors.WindowText;
			this.txtReq3.Location = new System.Drawing.Point( 370, 316 );
			this.txtReq3.Name = "txtReq3";
			this.txtReq3.ReadOnly = true;
			this.txtReq3.Size = new System.Drawing.Size( 172, 21 );
			this.txtReq3.TabIndex = 32;
			this.txtReq3.Visible = false;
			// 
			// labelReq3
			// 
			this.labelReq3.AutoSize = true;
			this.labelReq3.ForeColor = System.Drawing.Color.Blue;
			this.labelReq3.Location = new System.Drawing.Point( 314, 321 );
			this.labelReq3.Name = "labelReq3";
			this.labelReq3.Size = new System.Drawing.Size( 53, 12 );
			this.labelReq3.TabIndex = 31;
			this.labelReq3.Text = "调拨单3:";
			this.labelReq3.Visible = false;
			// 
			// txtReqDate2
			// 
			this.txtReqDate2.BackColor = System.Drawing.Color.White;
			this.txtReqDate2.ForeColor = System.Drawing.SystemColors.WindowText;
			this.txtReqDate2.Location = new System.Drawing.Point( 614, 282 );
			this.txtReqDate2.Name = "txtReqDate2";
			this.txtReqDate2.ReadOnly = true;
			this.txtReqDate2.Size = new System.Drawing.Size( 172, 21 );
			this.txtReqDate2.TabIndex = 30;
			this.txtReqDate2.Visible = false;
			// 
			// labelReqDate2
			// 
			this.labelReqDate2.AutoSize = true;
			this.labelReqDate2.ForeColor = System.Drawing.Color.Blue;
			this.labelReqDate2.Location = new System.Drawing.Point( 570, 287 );
			this.labelReqDate2.Name = "labelReqDate2";
			this.labelReqDate2.Size = new System.Drawing.Size( 41, 12 );
			this.labelReqDate2.TabIndex = 29;
			this.labelReqDate2.Text = "日期2:";
			this.labelReqDate2.Visible = false;
			// 
			// txtReq2
			// 
			this.txtReq2.BackColor = System.Drawing.Color.White;
			this.txtReq2.ForeColor = System.Drawing.SystemColors.WindowText;
			this.txtReq2.Location = new System.Drawing.Point( 370, 282 );
			this.txtReq2.Name = "txtReq2";
			this.txtReq2.ReadOnly = true;
			this.txtReq2.Size = new System.Drawing.Size( 172, 21 );
			this.txtReq2.TabIndex = 28;
			this.txtReq2.Visible = false;
			// 
			// labelReq2
			// 
			this.labelReq2.AutoSize = true;
			this.labelReq2.ForeColor = System.Drawing.Color.Blue;
			this.labelReq2.Location = new System.Drawing.Point( 314, 287 );
			this.labelReq2.Name = "labelReq2";
			this.labelReq2.Size = new System.Drawing.Size( 53, 12 );
			this.labelReq2.TabIndex = 27;
			this.labelReq2.Text = "调拨单2:";
			this.labelReq2.Visible = false;
			// 
			// txtReqDate1
			// 
			this.txtReqDate1.BackColor = System.Drawing.Color.White;
			this.txtReqDate1.ForeColor = System.Drawing.SystemColors.WindowText;
			this.txtReqDate1.Location = new System.Drawing.Point( 614, 247 );
			this.txtReqDate1.Name = "txtReqDate1";
			this.txtReqDate1.ReadOnly = true;
			this.txtReqDate1.Size = new System.Drawing.Size( 172, 21 );
			this.txtReqDate1.TabIndex = 26;
			this.txtReqDate1.Visible = false;
			// 
			// labelReqDate1
			// 
			this.labelReqDate1.AutoSize = true;
			this.labelReqDate1.ForeColor = System.Drawing.Color.Blue;
			this.labelReqDate1.Location = new System.Drawing.Point( 570, 252 );
			this.labelReqDate1.Name = "labelReqDate1";
			this.labelReqDate1.Size = new System.Drawing.Size( 41, 12 );
			this.labelReqDate1.TabIndex = 25;
			this.labelReqDate1.Text = "日期1:";
			this.labelReqDate1.Visible = false;
			// 
			// txtReq1
			// 
			this.txtReq1.BackColor = System.Drawing.Color.White;
			this.txtReq1.ForeColor = System.Drawing.SystemColors.WindowText;
			this.txtReq1.Location = new System.Drawing.Point( 370, 247 );
			this.txtReq1.Name = "txtReq1";
			this.txtReq1.ReadOnly = true;
			this.txtReq1.Size = new System.Drawing.Size( 172, 21 );
			this.txtReq1.TabIndex = 24;
			this.txtReq1.Visible = false;
			// 
			// labelReq1
			// 
			this.labelReq1.AutoSize = true;
			this.labelReq1.ForeColor = System.Drawing.Color.Blue;
			this.labelReq1.Location = new System.Drawing.Point( 314, 252 );
			this.labelReq1.Name = "labelReq1";
			this.labelReq1.Size = new System.Drawing.Size( 53, 12 );
			this.labelReq1.TabIndex = 23;
			this.labelReq1.Text = "调拨单1:";
			this.labelReq1.Visible = false;
			// 
			// txtArchiveNo
			// 
			this.txtArchiveNo.BackColor = System.Drawing.Color.White;
			this.txtArchiveNo.ForeColor = System.Drawing.SystemColors.WindowText;
			this.txtArchiveNo.Location = new System.Drawing.Point( 614, 213 );
			this.txtArchiveNo.Name = "txtArchiveNo";
			this.txtArchiveNo.ReadOnly = true;
			this.txtArchiveNo.Size = new System.Drawing.Size( 172, 21 );
			this.txtArchiveNo.TabIndex = 22;
			this.txtArchiveNo.Visible = false;
			// 
			// labelArchiveNo
			// 
			this.labelArchiveNo.AutoSize = true;
			this.labelArchiveNo.ForeColor = System.Drawing.Color.Blue;
			this.labelArchiveNo.Location = new System.Drawing.Point( 552, 218 );
			this.labelArchiveNo.Name = "labelArchiveNo";
			this.labelArchiveNo.Size = new System.Drawing.Size( 59, 12 );
			this.labelArchiveNo.TabIndex = 21;
			this.labelArchiveNo.Text = "资料卡号:";
			this.labelArchiveNo.Visible = false;
			// 
			// txtArchive
			// 
			this.txtArchive.BackColor = System.Drawing.Color.White;
			this.txtArchive.ForeColor = System.Drawing.SystemColors.WindowText;
			this.txtArchive.Location = new System.Drawing.Point( 370, 213 );
			this.txtArchive.Name = "txtArchive";
			this.txtArchive.ReadOnly = true;
			this.txtArchive.Size = new System.Drawing.Size( 172, 21 );
			this.txtArchive.TabIndex = 20;
			this.txtArchive.Visible = false;
			// 
			// labelArchive
			// 
			this.labelArchive.AutoSize = true;
			this.labelArchive.ForeColor = System.Drawing.Color.Blue;
			this.labelArchive.Location = new System.Drawing.Point( 308, 218 );
			this.labelArchive.Name = "labelArchive";
			this.labelArchive.Size = new System.Drawing.Size( 59, 12 );
			this.labelArchive.TabIndex = 19;
			this.labelArchive.Text = "入档日期:";
			this.labelArchive.Visible = false;
			// 
			// txtProducerNo
			// 
			this.txtProducerNo.BackColor = System.Drawing.Color.White;
			this.txtProducerNo.ForeColor = System.Drawing.SystemColors.WindowText;
			this.txtProducerNo.Location = new System.Drawing.Point( 614, 178 );
			this.txtProducerNo.Name = "txtProducerNo";
			this.txtProducerNo.ReadOnly = true;
			this.txtProducerNo.Size = new System.Drawing.Size( 172, 21 );
			this.txtProducerNo.TabIndex = 18;
			this.txtProducerNo.Visible = false;
			// 
			// labelProducerNo
			// 
			this.labelProducerNo.AutoSize = true;
			this.labelProducerNo.ForeColor = System.Drawing.Color.Blue;
			this.labelProducerNo.Location = new System.Drawing.Point( 564, 183 );
			this.labelProducerNo.Name = "labelProducerNo";
			this.labelProducerNo.Size = new System.Drawing.Size( 47, 12 );
			this.labelProducerNo.TabIndex = 17;
			this.labelProducerNo.Text = "厂商号:";
			this.labelProducerNo.Visible = false;
			// 
			// txtProducer
			// 
			this.txtProducer.BackColor = System.Drawing.Color.White;
			this.txtProducer.ForeColor = System.Drawing.SystemColors.WindowText;
			this.txtProducer.Location = new System.Drawing.Point( 370, 178 );
			this.txtProducer.Name = "txtProducer";
			this.txtProducer.ReadOnly = true;
			this.txtProducer.Size = new System.Drawing.Size( 172, 21 );
			this.txtProducer.TabIndex = 16;
			this.txtProducer.Visible = false;
			// 
			// labelProducer
			// 
			this.labelProducer.AutoSize = true;
			this.labelProducer.ForeColor = System.Drawing.Color.Blue;
			this.labelProducer.Location = new System.Drawing.Point( 332, 183 );
			this.labelProducer.Name = "labelProducer";
			this.labelProducer.Size = new System.Drawing.Size( 35, 12 );
			this.labelProducer.TabIndex = 15;
			this.labelProducer.Text = "厂商:";
			this.labelProducer.Visible = false;
			// 
			// txtAsessory
			// 
			this.txtAsessory.BackColor = System.Drawing.Color.White;
			this.txtAsessory.Location = new System.Drawing.Point( 370, 121 );
			this.txtAsessory.Multiline = true;
			this.txtAsessory.Name = "txtAsessory";
			this.txtAsessory.ReadOnly = true;
			this.txtAsessory.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
			this.txtAsessory.Size = new System.Drawing.Size( 416, 44 );
			this.txtAsessory.TabIndex = 14;
			// 
			// label11
			// 
			this.label11.AutoSize = true;
			this.label11.Location = new System.Drawing.Point( 332, 126 );
			this.label11.Name = "label11";
			this.label11.Size = new System.Drawing.Size( 35, 12 );
			this.label11.TabIndex = 13;
			this.label11.Text = "配件:";
			// 
			// txtPrice
			// 
			this.txtPrice.BackColor = System.Drawing.Color.White;
			this.txtPrice.Location = new System.Drawing.Point( 614, 86 );
			this.txtPrice.Name = "txtPrice";
			this.txtPrice.ReadOnly = true;
			this.txtPrice.Size = new System.Drawing.Size( 172, 21 );
			this.txtPrice.TabIndex = 12;
			this.txtPrice.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
			// 
			// label9
			// 
			this.label9.AutoSize = true;
			this.label9.Location = new System.Drawing.Point( 576, 91 );
			this.label9.Name = "label9";
			this.label9.Size = new System.Drawing.Size( 35, 12 );
			this.label9.TabIndex = 11;
			this.label9.Text = "售价:";
			// 
			// txtColor
			// 
			this.txtColor.BackColor = System.Drawing.Color.White;
			this.txtColor.Location = new System.Drawing.Point( 370, 86 );
			this.txtColor.Name = "txtColor";
			this.txtColor.ReadOnly = true;
			this.txtColor.Size = new System.Drawing.Size( 172, 21 );
			this.txtColor.TabIndex = 10;
			// 
			// label10
			// 
			this.label10.AutoSize = true;
			this.label10.Location = new System.Drawing.Point( 332, 91 );
			this.label10.Name = "label10";
			this.label10.Size = new System.Drawing.Size( 35, 12 );
			this.label10.TabIndex = 9;
			this.label10.Text = "颜色:";
			// 
			// txtAreaNo
			// 
			this.txtAreaNo.BackColor = System.Drawing.Color.White;
			this.txtAreaNo.Location = new System.Drawing.Point( 614, 51 );
			this.txtAreaNo.Name = "txtAreaNo";
			this.txtAreaNo.ReadOnly = true;
			this.txtAreaNo.Size = new System.Drawing.Size( 172, 21 );
			this.txtAreaNo.TabIndex = 8;
			// 
			// label7
			// 
			this.label7.AutoSize = true;
			this.label7.Location = new System.Drawing.Point( 564, 56 );
			this.label7.Name = "label7";
			this.label7.Size = new System.Drawing.Size( 47, 12 );
			this.label7.TabIndex = 7;
			this.label7.Text = "区域号:";
			// 
			// txtCategory
			// 
			this.txtCategory.BackColor = System.Drawing.Color.White;
			this.txtCategory.Location = new System.Drawing.Point( 370, 51 );
			this.txtCategory.Name = "txtCategory";
			this.txtCategory.ReadOnly = true;
			this.txtCategory.Size = new System.Drawing.Size( 172, 21 );
			this.txtCategory.TabIndex = 6;
			// 
			// label8
			// 
			this.label8.AutoSize = true;
			this.label8.Location = new System.Drawing.Point( 332, 56 );
			this.label8.Name = "label8";
			this.label8.Size = new System.Drawing.Size( 35, 12 );
			this.label8.TabIndex = 5;
			this.label8.Text = "类别:";
			// 
			// txtArea
			// 
			this.txtArea.BackColor = System.Drawing.Color.White;
			this.txtArea.Location = new System.Drawing.Point( 614, 16 );
			this.txtArea.Name = "txtArea";
			this.txtArea.ReadOnly = true;
			this.txtArea.Size = new System.Drawing.Size( 172, 21 );
			this.txtArea.TabIndex = 4;
			// 
			// label6
			// 
			this.label6.AutoSize = true;
			this.label6.Location = new System.Drawing.Point( 576, 21 );
			this.label6.Name = "label6";
			this.label6.Size = new System.Drawing.Size( 35, 12 );
			this.label6.TabIndex = 3;
			this.label6.Text = "区域:";
			// 
			// txtDept
			// 
			this.txtDept.BackColor = System.Drawing.Color.White;
			this.txtDept.Location = new System.Drawing.Point( 370, 16 );
			this.txtDept.Name = "txtDept";
			this.txtDept.ReadOnly = true;
			this.txtDept.Size = new System.Drawing.Size( 172, 21 );
			this.txtDept.TabIndex = 2;
			// 
			// label5
			// 
			this.label5.AutoSize = true;
			this.label5.Location = new System.Drawing.Point( 332, 21 );
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size( 35, 12 );
			this.label5.TabIndex = 1;
			this.label5.Text = "部门:";
			// 
			// pbPhoto
			// 
			this.pbPhoto.ErrorImage = ((System.Drawing.Image)(resources.GetObject( "pbPhoto.ErrorImage" )));
			this.pbPhoto.ImageLocation = "";
			this.pbPhoto.InitialImage = ((System.Drawing.Image)(resources.GetObject( "pbPhoto.InitialImage" )));
			this.pbPhoto.Location = new System.Drawing.Point( 3, 3 );
			this.pbPhoto.Name = "pbPhoto";
			this.pbPhoto.Size = new System.Drawing.Size( 300, 400 );
			this.pbPhoto.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
			this.pbPhoto.TabIndex = 0;
			this.pbPhoto.TabStop = false;
			// 
			// lblRent
			// 
			this.lblRent.AutoSize = true;
			this.lblRent.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.lblRent.Location = new System.Drawing.Point( 24, 357 );
			this.lblRent.Name = "lblRent";
			this.lblRent.Size = new System.Drawing.Size( 35, 12 );
			this.lblRent.TabIndex = 18;
			this.lblRent.Text = "日期:";
			this.lblRent.Visible = false;
			// 
			// dtRent
			// 
			this.dtRent.Enabled = false;
			this.dtRent.Location = new System.Drawing.Point( 67, 353 );
			this.dtRent.Name = "dtRent";
			this.dtRent.Size = new System.Drawing.Size( 130, 21 );
			this.dtRent.TabIndex = 19;
			this.dtRent.Visible = false;
			// 
			// btnQueryByRent
			// 
			this.btnQueryByRent.Enabled = false;
			this.btnQueryByRent.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.btnQueryByRent.Location = new System.Drawing.Point( 6, 382 );
			this.btnQueryByRent.Name = "btnQueryByRent";
			this.btnQueryByRent.Size = new System.Drawing.Size( 191, 25 );
			this.btnQueryByRent.TabIndex = 20;
			this.btnQueryByRent.Text = "按出件日期查询(&U)";
			this.btnQueryByRent.UseVisualStyleBackColor = true;
			this.btnQueryByRent.Visible = false;
			this.btnQueryByRent.Click += new System.EventHandler( this.btnQueryByRent_Click );
			// 
			// MainForm
			// 
			this.AcceptButton = this.btnQuery;
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 12F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size( 1014, 709 );
			this.Controls.Add( splitContainer1 );
			this.Icon = ((System.Drawing.Icon)(resources.GetObject( "$this.Icon" )));
			this.Name = "MainForm";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "纽约婚纱";
			this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
			this.Shown += new System.EventHandler( this.MainForm_Shown );
			this.Load += new System.EventHandler( this.MainForm_Load );
			splitContainer1.Panel1.ResumeLayout( false );
			splitContainer1.Panel1.PerformLayout();
			splitContainer1.Panel2.ResumeLayout( false );
			splitContainer1.ResumeLayout( false );
			splitContainer2.Panel1.ResumeLayout( false );
			splitContainer2.Panel2.ResumeLayout( false );
			splitContainer2.Panel2.PerformLayout();
			splitContainer2.ResumeLayout( false );
			((System.ComponentModel.ISupportInitialize)(this.dataGridView)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.dsDress)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.WedDress)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.pbPhoto)).EndInit();
			this.ResumeLayout( false );

        }

        #endregion

		private System.Windows.Forms.DataGridView dataGridView;
		private System.Windows.Forms.Button btnQuery;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.ComboBox cbProducer;
		private System.Windows.Forms.Label lblProducer;
		private System.Windows.Forms.ComboBox cbColor;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.ComboBox cbCategory;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.ComboBox cbArea;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.ComboBox cbDept;
		private System.Windows.Forms.Button btnModify;
		private System.Windows.Forms.Button btnNew;
		private System.Windows.Forms.Button btnDel;
		private System.Windows.Forms.PictureBox pbPhoto;
		private System.Data.DataSet dsDress;
		private System.Data.DataTable WedDress;
		private System.Windows.Forms.TextBox txtDept;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.TextBox txtArea;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.TextBox txtPrice;
		private System.Windows.Forms.Label label9;
		private System.Windows.Forms.TextBox txtColor;
		private System.Windows.Forms.Label label10;
		private System.Windows.Forms.TextBox txtAreaNo;
		private System.Windows.Forms.Label label7;
		private System.Windows.Forms.TextBox txtCategory;
		private System.Windows.Forms.Label label8;
		private System.Windows.Forms.TextBox txtAsessory;
		private System.Windows.Forms.Label label11;
		private System.Windows.Forms.TextBox txtArchiveNo;
		private System.Windows.Forms.Label labelArchiveNo;
		private System.Windows.Forms.TextBox txtArchive;
		private System.Windows.Forms.Label labelArchive;
		private System.Windows.Forms.TextBox txtProducerNo;
		private System.Windows.Forms.Label labelProducerNo;
		private System.Windows.Forms.TextBox txtProducer;
		private System.Windows.Forms.Label labelProducer;
		private System.Windows.Forms.TextBox txtReqDate1;
		private System.Windows.Forms.Label labelReqDate1;
		private System.Windows.Forms.TextBox txtReq1;
		private System.Windows.Forms.Label labelReq1;
		private System.Windows.Forms.TextBox txtReqDate3;
		private System.Windows.Forms.Label labelReqDate3;
		private System.Windows.Forms.TextBox txtReq3;
		private System.Windows.Forms.Label labelReq3;
		private System.Windows.Forms.TextBox txtReqDate2;
		private System.Windows.Forms.Label labelReqDate2;
		private System.Windows.Forms.TextBox txtReq2;
		private System.Windows.Forms.Label labelReq2;
		private System.Windows.Forms.TextBox txtBuyPrice;
		private System.Windows.Forms.Label labelBuyPrice;
		private System.Windows.Forms.TextBox txtBuyDate;
		private System.Windows.Forms.Label labelBuyDate;
		private System.Windows.Forms.TextBox txtBuyer;
		private System.Windows.Forms.Label labelBuyer;
		private System.Windows.Forms.Label label12;
		private System.Windows.Forms.ComboBox cbAreaNo;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnID;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDept;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnArea;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnAreaNo;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnCate;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnColor;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnPrice;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnAccsry;
		private System.Windows.Forms.Label lblNumDress;
		private System.Windows.Forms.Button btnRent;
		private System.Windows.Forms.Button btnQueryByRent;
		private System.Windows.Forms.DateTimePicker dtRent;
		private System.Windows.Forms.Label lblRent;
    }
}

