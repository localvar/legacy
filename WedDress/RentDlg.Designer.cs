namespace WedDress
{
	partial class RentDlg
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
			System.Windows.Forms.Button btnRent;
			System.Windows.Forms.Button btnClose;
			System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle9 = new System.Windows.Forms.DataGridViewCellStyle();
			System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle11 = new System.Windows.Forms.DataGridViewCellStyle();
			System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle12 = new System.Windows.Forms.DataGridViewCellStyle();
			System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle10 = new System.Windows.Forms.DataGridViewCellStyle();
			this.btnDelRent = new System.Windows.Forms.Button();
			this.btnModify = new System.Windows.Forms.Button();
			this.dgvRent = new System.Windows.Forms.DataGridView();
			this.clmnYearMonth = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDay01 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDay02 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDay03 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDay04 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDay05 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDay06 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDay07 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDay08 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDay09 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDay10 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDay11 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDay12 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDay13 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDay14 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDay15 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDay16 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDay17 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDay18 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDay19 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDay20 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDay21 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDay22 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDay23 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDay24 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDay25 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDay26 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDay27 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDay28 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDay29 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDay30 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.clmnDay31 = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.lblRentTime = new System.Windows.Forms.Label();
			this.txtCustomer = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.txtDate = new System.Windows.Forms.TextBox();
			btnRent = new System.Windows.Forms.Button();
			btnClose = new System.Windows.Forms.Button();
			((System.ComponentModel.ISupportInitialize)(this.dgvRent)).BeginInit();
			this.SuspendLayout();
			// 
			// btnRent
			// 
			btnRent.FlatStyle = System.Windows.Forms.FlatStyle.System;
			btnRent.Location = new System.Drawing.Point( 590, 512 );
			btnRent.Name = "btnRent";
			btnRent.Size = new System.Drawing.Size( 84, 23 );
			btnRent.TabIndex = 6;
			btnRent.Text = "出件(&R)...";
			btnRent.UseVisualStyleBackColor = true;
			btnRent.Click += new System.EventHandler( this.btnRent_Click );
			// 
			// btnClose
			// 
			btnClose.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			btnClose.FlatStyle = System.Windows.Forms.FlatStyle.System;
			btnClose.Location = new System.Drawing.Point( 851, 512 );
			btnClose.Name = "btnClose";
			btnClose.Size = new System.Drawing.Size( 84, 23 );
			btnClose.TabIndex = 9;
			btnClose.Text = "关闭(&C)";
			btnClose.UseVisualStyleBackColor = true;
			// 
			// btnDelRent
			// 
			this.btnDelRent.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.btnDelRent.Location = new System.Drawing.Point( 764, 512 );
			this.btnDelRent.Name = "btnDelRent";
			this.btnDelRent.Size = new System.Drawing.Size( 84, 23 );
			this.btnDelRent.TabIndex = 8;
			this.btnDelRent.Text = "删除(&D)";
			this.btnDelRent.UseVisualStyleBackColor = true;
			this.btnDelRent.Visible = false;
			this.btnDelRent.Click += new System.EventHandler( this.btnDelRent_Click );
			// 
			// btnModify
			// 
			this.btnModify.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.btnModify.Location = new System.Drawing.Point( 677, 512 );
			this.btnModify.Name = "btnModify";
			this.btnModify.Size = new System.Drawing.Size( 84, 23 );
			this.btnModify.TabIndex = 7;
			this.btnModify.Text = "修改(&M)...";
			this.btnModify.UseVisualStyleBackColor = true;
			this.btnModify.Visible = false;
			this.btnModify.Click += new System.EventHandler( this.btnModify_Click );
			// 
			// dgvRent
			// 
			this.dgvRent.AllowUserToAddRows = false;
			this.dgvRent.AllowUserToDeleteRows = false;
			this.dgvRent.AllowUserToResizeColumns = false;
			this.dgvRent.AllowUserToResizeRows = false;
			dataGridViewCellStyle9.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
			dataGridViewCellStyle9.BackColor = System.Drawing.SystemColors.Control;
			dataGridViewCellStyle9.Font = new System.Drawing.Font( "SimSun", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)) );
			dataGridViewCellStyle9.ForeColor = System.Drawing.SystemColors.WindowText;
			dataGridViewCellStyle9.SelectionBackColor = System.Drawing.SystemColors.Highlight;
			dataGridViewCellStyle9.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
			dataGridViewCellStyle9.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
			this.dgvRent.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle9;
			this.dgvRent.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			this.dgvRent.Columns.AddRange( new System.Windows.Forms.DataGridViewColumn[] {
            this.clmnYearMonth,
            this.clmnDay01,
            this.clmnDay02,
            this.clmnDay03,
            this.clmnDay04,
            this.clmnDay05,
            this.clmnDay06,
            this.clmnDay07,
            this.clmnDay08,
            this.clmnDay09,
            this.clmnDay10,
            this.clmnDay11,
            this.clmnDay12,
            this.clmnDay13,
            this.clmnDay14,
            this.clmnDay15,
            this.clmnDay16,
            this.clmnDay17,
            this.clmnDay18,
            this.clmnDay19,
            this.clmnDay20,
            this.clmnDay21,
            this.clmnDay22,
            this.clmnDay23,
            this.clmnDay24,
            this.clmnDay25,
            this.clmnDay26,
            this.clmnDay27,
            this.clmnDay28,
            this.clmnDay29,
            this.clmnDay30,
            this.clmnDay31} );
			this.dgvRent.DataMember = "RentDetail";
			dataGridViewCellStyle11.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
			dataGridViewCellStyle11.BackColor = System.Drawing.SystemColors.Window;
			dataGridViewCellStyle11.Font = new System.Drawing.Font( "SimSun", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)) );
			dataGridViewCellStyle11.ForeColor = System.Drawing.Color.Red;
			dataGridViewCellStyle11.SelectionBackColor = System.Drawing.SystemColors.Highlight;
			dataGridViewCellStyle11.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
			dataGridViewCellStyle11.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
			this.dgvRent.DefaultCellStyle = dataGridViewCellStyle11;
			this.dgvRent.Location = new System.Drawing.Point( 1, 2 );
			this.dgvRent.MultiSelect = false;
			this.dgvRent.Name = "dgvRent";
			this.dgvRent.ReadOnly = true;
			dataGridViewCellStyle12.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
			dataGridViewCellStyle12.BackColor = System.Drawing.SystemColors.Control;
			dataGridViewCellStyle12.Font = new System.Drawing.Font( "SimSun", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)) );
			dataGridViewCellStyle12.ForeColor = System.Drawing.SystemColors.WindowText;
			dataGridViewCellStyle12.SelectionBackColor = System.Drawing.SystemColors.Highlight;
			dataGridViewCellStyle12.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
			dataGridViewCellStyle12.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
			this.dgvRent.RowHeadersDefaultCellStyle = dataGridViewCellStyle12;
			this.dgvRent.RowHeadersVisible = false;
			this.dgvRent.RowTemplate.Height = 23;
			this.dgvRent.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.CellSelect;
			this.dgvRent.Size = new System.Drawing.Size( 934, 504 );
			this.dgvRent.TabIndex = 0;
			this.dgvRent.CellDoubleClick += new System.Windows.Forms.DataGridViewCellEventHandler( this.dgvRent_CellDoubleClick );
			this.dgvRent.CurrentCellChanged += new System.EventHandler( this.dgvRent_CurrentCellChanged );
			// 
			// clmnYearMonth
			// 
			this.clmnYearMonth.DataPropertyName = "YearMonth";
			dataGridViewCellStyle10.BackColor = System.Drawing.Color.FromArgb( ((int)(((byte)(192)))), ((int)(((byte)(192)))), ((int)(((byte)(255)))) );
			dataGridViewCellStyle10.ForeColor = System.Drawing.Color.Black;
			dataGridViewCellStyle10.Format = "y";
			dataGridViewCellStyle10.NullValue = null;
			this.clmnYearMonth.DefaultCellStyle = dataGridViewCellStyle10;
			this.clmnYearMonth.Frozen = true;
			this.clmnYearMonth.HeaderText = "年月";
			this.clmnYearMonth.Name = "clmnYearMonth";
			this.clmnYearMonth.ReadOnly = true;
			this.clmnYearMonth.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnYearMonth.Width = 70;
			// 
			// clmnDay01
			// 
			this.clmnDay01.DataPropertyName = "d01";
			this.clmnDay01.HeaderText = "01";
			this.clmnDay01.Name = "clmnDay01";
			this.clmnDay01.ReadOnly = true;
			this.clmnDay01.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnDay01.Width = 27;
			// 
			// clmnDay02
			// 
			this.clmnDay02.DataPropertyName = "d02";
			this.clmnDay02.HeaderText = "02";
			this.clmnDay02.Name = "clmnDay02";
			this.clmnDay02.ReadOnly = true;
			this.clmnDay02.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnDay02.Width = 27;
			// 
			// clmnDay03
			// 
			this.clmnDay03.DataPropertyName = "d03";
			this.clmnDay03.HeaderText = "03";
			this.clmnDay03.Name = "clmnDay03";
			this.clmnDay03.ReadOnly = true;
			this.clmnDay03.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnDay03.Width = 27;
			// 
			// clmnDay04
			// 
			this.clmnDay04.DataPropertyName = "d04";
			this.clmnDay04.HeaderText = "04";
			this.clmnDay04.Name = "clmnDay04";
			this.clmnDay04.ReadOnly = true;
			this.clmnDay04.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnDay04.Width = 27;
			// 
			// clmnDay05
			// 
			this.clmnDay05.DataPropertyName = "d05";
			this.clmnDay05.HeaderText = "05";
			this.clmnDay05.Name = "clmnDay05";
			this.clmnDay05.ReadOnly = true;
			this.clmnDay05.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnDay05.Width = 27;
			// 
			// clmnDay06
			// 
			this.clmnDay06.DataPropertyName = "d06";
			this.clmnDay06.HeaderText = "06";
			this.clmnDay06.Name = "clmnDay06";
			this.clmnDay06.ReadOnly = true;
			this.clmnDay06.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnDay06.Width = 27;
			// 
			// clmnDay07
			// 
			this.clmnDay07.DataPropertyName = "d07";
			this.clmnDay07.HeaderText = "07";
			this.clmnDay07.Name = "clmnDay07";
			this.clmnDay07.ReadOnly = true;
			this.clmnDay07.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnDay07.Width = 27;
			// 
			// clmnDay08
			// 
			this.clmnDay08.DataPropertyName = "d08";
			this.clmnDay08.HeaderText = "08";
			this.clmnDay08.Name = "clmnDay08";
			this.clmnDay08.ReadOnly = true;
			this.clmnDay08.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnDay08.Width = 27;
			// 
			// clmnDay09
			// 
			this.clmnDay09.DataPropertyName = "d09";
			this.clmnDay09.HeaderText = "09";
			this.clmnDay09.Name = "clmnDay09";
			this.clmnDay09.ReadOnly = true;
			this.clmnDay09.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnDay09.Width = 27;
			// 
			// clmnDay10
			// 
			this.clmnDay10.DataPropertyName = "d10";
			this.clmnDay10.HeaderText = "10";
			this.clmnDay10.Name = "clmnDay10";
			this.clmnDay10.ReadOnly = true;
			this.clmnDay10.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnDay10.Width = 27;
			// 
			// clmnDay11
			// 
			this.clmnDay11.DataPropertyName = "d11";
			this.clmnDay11.HeaderText = "11";
			this.clmnDay11.Name = "clmnDay11";
			this.clmnDay11.ReadOnly = true;
			this.clmnDay11.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnDay11.Width = 27;
			// 
			// clmnDay12
			// 
			this.clmnDay12.DataPropertyName = "d12";
			this.clmnDay12.HeaderText = "12";
			this.clmnDay12.Name = "clmnDay12";
			this.clmnDay12.ReadOnly = true;
			this.clmnDay12.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnDay12.Width = 27;
			// 
			// clmnDay13
			// 
			this.clmnDay13.DataPropertyName = "d13";
			this.clmnDay13.HeaderText = "13";
			this.clmnDay13.Name = "clmnDay13";
			this.clmnDay13.ReadOnly = true;
			this.clmnDay13.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnDay13.Width = 27;
			// 
			// clmnDay14
			// 
			this.clmnDay14.DataPropertyName = "d14";
			this.clmnDay14.HeaderText = "14";
			this.clmnDay14.Name = "clmnDay14";
			this.clmnDay14.ReadOnly = true;
			this.clmnDay14.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnDay14.Width = 27;
			// 
			// clmnDay15
			// 
			this.clmnDay15.DataPropertyName = "d15";
			this.clmnDay15.HeaderText = "15";
			this.clmnDay15.Name = "clmnDay15";
			this.clmnDay15.ReadOnly = true;
			this.clmnDay15.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnDay15.Width = 27;
			// 
			// clmnDay16
			// 
			this.clmnDay16.DataPropertyName = "d16";
			this.clmnDay16.HeaderText = "16";
			this.clmnDay16.Name = "clmnDay16";
			this.clmnDay16.ReadOnly = true;
			this.clmnDay16.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnDay16.Width = 27;
			// 
			// clmnDay17
			// 
			this.clmnDay17.DataPropertyName = "d17";
			this.clmnDay17.HeaderText = "17";
			this.clmnDay17.Name = "clmnDay17";
			this.clmnDay17.ReadOnly = true;
			this.clmnDay17.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnDay17.Width = 27;
			// 
			// clmnDay18
			// 
			this.clmnDay18.DataPropertyName = "d18";
			this.clmnDay18.HeaderText = "18";
			this.clmnDay18.Name = "clmnDay18";
			this.clmnDay18.ReadOnly = true;
			this.clmnDay18.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnDay18.Width = 27;
			// 
			// clmnDay19
			// 
			this.clmnDay19.DataPropertyName = "d19";
			this.clmnDay19.HeaderText = "19";
			this.clmnDay19.Name = "clmnDay19";
			this.clmnDay19.ReadOnly = true;
			this.clmnDay19.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnDay19.Width = 27;
			// 
			// clmnDay20
			// 
			this.clmnDay20.DataPropertyName = "d20";
			this.clmnDay20.HeaderText = "20";
			this.clmnDay20.Name = "clmnDay20";
			this.clmnDay20.ReadOnly = true;
			this.clmnDay20.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnDay20.Width = 27;
			// 
			// clmnDay21
			// 
			this.clmnDay21.DataPropertyName = "d21";
			this.clmnDay21.HeaderText = "21";
			this.clmnDay21.Name = "clmnDay21";
			this.clmnDay21.ReadOnly = true;
			this.clmnDay21.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnDay21.Width = 27;
			// 
			// clmnDay22
			// 
			this.clmnDay22.DataPropertyName = "d22";
			this.clmnDay22.HeaderText = "22";
			this.clmnDay22.Name = "clmnDay22";
			this.clmnDay22.ReadOnly = true;
			this.clmnDay22.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnDay22.Width = 27;
			// 
			// clmnDay23
			// 
			this.clmnDay23.DataPropertyName = "d23";
			this.clmnDay23.HeaderText = "23";
			this.clmnDay23.Name = "clmnDay23";
			this.clmnDay23.ReadOnly = true;
			this.clmnDay23.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnDay23.Width = 27;
			// 
			// clmnDay24
			// 
			this.clmnDay24.DataPropertyName = "d24";
			this.clmnDay24.HeaderText = "24";
			this.clmnDay24.Name = "clmnDay24";
			this.clmnDay24.ReadOnly = true;
			this.clmnDay24.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnDay24.Width = 27;
			// 
			// clmnDay25
			// 
			this.clmnDay25.DataPropertyName = "d25";
			this.clmnDay25.HeaderText = "25";
			this.clmnDay25.Name = "clmnDay25";
			this.clmnDay25.ReadOnly = true;
			this.clmnDay25.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnDay25.Width = 27;
			// 
			// clmnDay26
			// 
			this.clmnDay26.DataPropertyName = "d26";
			this.clmnDay26.HeaderText = "26";
			this.clmnDay26.Name = "clmnDay26";
			this.clmnDay26.ReadOnly = true;
			this.clmnDay26.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnDay26.Width = 27;
			// 
			// clmnDay27
			// 
			this.clmnDay27.DataPropertyName = "d27";
			this.clmnDay27.HeaderText = "27";
			this.clmnDay27.Name = "clmnDay27";
			this.clmnDay27.ReadOnly = true;
			this.clmnDay27.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnDay27.Width = 27;
			// 
			// clmnDay28
			// 
			this.clmnDay28.DataPropertyName = "d28";
			this.clmnDay28.HeaderText = "28";
			this.clmnDay28.Name = "clmnDay28";
			this.clmnDay28.ReadOnly = true;
			this.clmnDay28.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnDay28.Width = 27;
			// 
			// clmnDay29
			// 
			this.clmnDay29.DataPropertyName = "d29";
			this.clmnDay29.HeaderText = "29";
			this.clmnDay29.Name = "clmnDay29";
			this.clmnDay29.ReadOnly = true;
			this.clmnDay29.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnDay29.Width = 27;
			// 
			// clmnDay30
			// 
			this.clmnDay30.DataPropertyName = "d30";
			this.clmnDay30.HeaderText = "30";
			this.clmnDay30.Name = "clmnDay30";
			this.clmnDay30.ReadOnly = true;
			this.clmnDay30.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnDay30.Width = 27;
			// 
			// clmnDay31
			// 
			this.clmnDay31.DataPropertyName = "d31";
			this.clmnDay31.HeaderText = "31";
			this.clmnDay31.Name = "clmnDay31";
			this.clmnDay31.ReadOnly = true;
			this.clmnDay31.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
			this.clmnDay31.Width = 27;
			// 
			// lblRentTime
			// 
			this.lblRentTime.AutoSize = true;
			this.lblRentTime.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this.lblRentTime.Location = new System.Drawing.Point( 473, 518 );
			this.lblRentTime.Name = "lblRentTime";
			this.lblRentTime.Size = new System.Drawing.Size( 107, 12 );
			this.lblRentTime.TabIndex = 5;
			this.lblRentTime.Text = "出件次数:        ";
			this.lblRentTime.Visible = false;
			// 
			// txtCustomer
			// 
			this.txtCustomer.BackColor = System.Drawing.Color.White;
			this.txtCustomer.Location = new System.Drawing.Point( 176, 513 );
			this.txtCustomer.Name = "txtCustomer";
			this.txtCustomer.ReadOnly = true;
			this.txtCustomer.Size = new System.Drawing.Size( 291, 21 );
			this.txtCustomer.TabIndex = 4;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point( 139, 518 );
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size( 35, 12 );
			this.label1.TabIndex = 3;
			this.label1.Text = "客户:";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point( 1, 518 );
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size( 35, 12 );
			this.label2.TabIndex = 1;
			this.label2.Text = "日期:";
			// 
			// txtDate
			// 
			this.txtDate.BackColor = System.Drawing.Color.White;
			this.txtDate.Location = new System.Drawing.Point( 39, 513 );
			this.txtDate.Name = "txtDate";
			this.txtDate.ReadOnly = true;
			this.txtDate.Size = new System.Drawing.Size( 95, 21 );
			this.txtDate.TabIndex = 2;
			// 
			// RentDlg
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 12F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = btnClose;
			this.ClientSize = new System.Drawing.Size( 937, 537 );
			this.Controls.Add( this.btnModify );
			this.Controls.Add( this.txtDate );
			this.Controls.Add( this.label2 );
			this.Controls.Add( this.btnDelRent );
			this.Controls.Add( this.label1 );
			this.Controls.Add( btnClose );
			this.Controls.Add( btnRent );
			this.Controls.Add( this.txtCustomer );
			this.Controls.Add( this.lblRentTime );
			this.Controls.Add( this.dgvRent );
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "RentDlg";
			this.ShowIcon = false;
			this.ShowInTaskbar = false;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "出件";
			this.Load += new System.EventHandler( this.RentDlg_Load );
			((System.ComponentModel.ISupportInitialize)(this.dgvRent)).EndInit();
			this.ResumeLayout( false );
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.DataGridView dgvRent;
		private System.Windows.Forms.Label lblRentTime;
		private System.Windows.Forms.TextBox txtCustomer;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnYearMonth;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDay01;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDay02;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDay03;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDay04;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDay05;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDay06;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDay07;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDay08;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDay09;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDay10;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDay11;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDay12;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDay13;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDay14;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDay15;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDay16;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDay17;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDay18;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDay19;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDay20;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDay21;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDay22;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDay23;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDay24;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDay25;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDay26;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDay27;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDay28;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDay29;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDay30;
		private System.Windows.Forms.DataGridViewTextBoxColumn clmnDay31;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.TextBox txtDate;
		private System.Windows.Forms.Button btnDelRent;
		private System.Windows.Forms.Button btnModify;


	}
}