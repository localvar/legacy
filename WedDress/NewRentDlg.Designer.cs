namespace WedDress
{
	partial class NewRentDlg
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
			System.Windows.Forms.Label lblStartDate;
			System.Windows.Forms.Label lblEndDate;
			System.Windows.Forms.Label lblCustomer;
			System.Windows.Forms.Button btnOk;
			System.Windows.Forms.Button btnCancel;
			this.dtStartDate = new System.Windows.Forms.DateTimePicker();
			this.dtEndDate = new System.Windows.Forms.DateTimePicker();
			this.txtCustomer = new System.Windows.Forms.TextBox();
			lblStartDate = new System.Windows.Forms.Label();
			lblEndDate = new System.Windows.Forms.Label();
			lblCustomer = new System.Windows.Forms.Label();
			btnOk = new System.Windows.Forms.Button();
			btnCancel = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// lblStartDate
			// 
			lblStartDate.AutoSize = true;
			lblStartDate.FlatStyle = System.Windows.Forms.FlatStyle.System;
			lblStartDate.Location = new System.Drawing.Point( 9, 16 );
			lblStartDate.Name = "lblStartDate";
			lblStartDate.Size = new System.Drawing.Size( 77, 12 );
			lblStartDate.TabIndex = 0;
			lblStartDate.Text = "开始日期(&S):";
			// 
			// lblEndDate
			// 
			lblEndDate.AutoSize = true;
			lblEndDate.FlatStyle = System.Windows.Forms.FlatStyle.System;
			lblEndDate.Location = new System.Drawing.Point( 207, 17 );
			lblEndDate.Name = "lblEndDate";
			lblEndDate.Size = new System.Drawing.Size( 77, 12 );
			lblEndDate.TabIndex = 2;
			lblEndDate.Text = "结束日期(&E):";
			// 
			// lblCustomer
			// 
			lblCustomer.AutoSize = true;
			lblCustomer.FlatStyle = System.Windows.Forms.FlatStyle.System;
			lblCustomer.Location = new System.Drawing.Point( 33, 43 );
			lblCustomer.Name = "lblCustomer";
			lblCustomer.Size = new System.Drawing.Size( 53, 12 );
			lblCustomer.TabIndex = 4;
			lblCustomer.Text = "客户(&C):";
			// 
			// btnOk
			// 
			btnOk.FlatStyle = System.Windows.Forms.FlatStyle.System;
			btnOk.Location = new System.Drawing.Point( 208, 67 );
			btnOk.Name = "btnOk";
			btnOk.Size = new System.Drawing.Size( 91, 22 );
			btnOk.TabIndex = 6;
			btnOk.Text = "确定";
			btnOk.UseVisualStyleBackColor = true;
			btnOk.Click += new System.EventHandler( this.btnOk_Click );
			// 
			// btnCancel
			// 
			btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			btnCancel.FlatStyle = System.Windows.Forms.FlatStyle.System;
			btnCancel.Location = new System.Drawing.Point( 305, 67 );
			btnCancel.Name = "btnCancel";
			btnCancel.Size = new System.Drawing.Size( 91, 22 );
			btnCancel.TabIndex = 7;
			btnCancel.Text = "取消";
			btnCancel.UseVisualStyleBackColor = true;
			// 
			// dtStartDate
			// 
			this.dtStartDate.Location = new System.Drawing.Point( 83, 12 );
			this.dtStartDate.Name = "dtStartDate";
			this.dtStartDate.Size = new System.Drawing.Size( 115, 21 );
			this.dtStartDate.TabIndex = 1;
			// 
			// dtEndDate
			// 
			this.dtEndDate.Location = new System.Drawing.Point( 281, 12 );
			this.dtEndDate.Name = "dtEndDate";
			this.dtEndDate.Size = new System.Drawing.Size( 115, 21 );
			this.dtEndDate.TabIndex = 3;
			// 
			// txtCustomer
			// 
			this.txtCustomer.Location = new System.Drawing.Point( 83, 39 );
			this.txtCustomer.MaxLength = 50;
			this.txtCustomer.Name = "txtCustomer";
			this.txtCustomer.Size = new System.Drawing.Size( 313, 21 );
			this.txtCustomer.TabIndex = 5;
			// 
			// NewRentDlg
			// 
			this.AcceptButton = btnOk;
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 12F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = btnCancel;
			this.ClientSize = new System.Drawing.Size( 404, 92 );
			this.Controls.Add( btnCancel );
			this.Controls.Add( btnOk );
			this.Controls.Add( this.txtCustomer );
			this.Controls.Add( lblCustomer );
			this.Controls.Add( this.dtEndDate );
			this.Controls.Add( lblEndDate );
			this.Controls.Add( this.dtStartDate );
			this.Controls.Add( lblStartDate );
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "NewRentDlg";
			this.ShowIcon = false;
			this.ShowInTaskbar = false;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "填写出件信息";
			this.ResumeLayout( false );
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.DateTimePicker dtStartDate;
		private System.Windows.Forms.DateTimePicker dtEndDate;
		private System.Windows.Forms.TextBox txtCustomer;
	}
}