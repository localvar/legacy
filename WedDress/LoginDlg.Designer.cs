namespace WedDress
{
    partial class LoginDlg
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
            System.Windows.Forms.Label label1;
            System.Windows.Forms.Label label2;
            System.Windows.Forms.Button btnOk;
            System.Windows.Forms.Button btnCancel;
            this.cbUser = new System.Windows.Forms.ComboBox();
            this.txtPassword = new System.Windows.Forms.TextBox();
            label1 = new System.Windows.Forms.Label();
            label2 = new System.Windows.Forms.Label();
            btnOk = new System.Windows.Forms.Button();
            btnCancel = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new System.Drawing.Point( 11, 17 );
            label1.Name = "label1";
            label1.Size = new System.Drawing.Size( 65, 12 );
            label1.TabIndex = 0;
            label1.Text = "用户名(&U):";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new System.Drawing.Point( 23, 53 );
            label2.Name = "label2";
            label2.Size = new System.Drawing.Size( 53, 12 );
            label2.TabIndex = 2;
            label2.Text = "密码(&P):";
            // 
            // btnOk
            // 
            btnOk.FlatStyle = System.Windows.Forms.FlatStyle.System;
            btnOk.Location = new System.Drawing.Point( 81, 83 );
            btnOk.Name = "btnOk";
            btnOk.Size = new System.Drawing.Size( 75, 23 );
            btnOk.TabIndex = 4;
            btnOk.Text = "确定";
            btnOk.UseVisualStyleBackColor = true;
            btnOk.Click += new System.EventHandler( this.btnOk_Click );
            // 
            // btnCancel
            // 
            btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            btnCancel.FlatStyle = System.Windows.Forms.FlatStyle.System;
            btnCancel.Location = new System.Drawing.Point( 185, 83 );
            btnCancel.Name = "btnCancel";
            btnCancel.Size = new System.Drawing.Size( 75, 23 );
            btnCancel.TabIndex = 5;
            btnCancel.Text = "退出";
            btnCancel.UseVisualStyleBackColor = true;
            // 
            // cbUser
            // 
            this.cbUser.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.SuggestAppend;
            this.cbUser.AutoCompleteSource = System.Windows.Forms.AutoCompleteSource.ListItems;
            this.cbUser.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.cbUser.FormattingEnabled = true;
            this.cbUser.Location = new System.Drawing.Point( 81, 14 );
            this.cbUser.MaxLength = 10;
            this.cbUser.Name = "cbUser";
            this.cbUser.Size = new System.Drawing.Size( 176, 20 );
            this.cbUser.TabIndex = 1;
            // 
            // txtPassword
            // 
            this.txtPassword.Location = new System.Drawing.Point( 81, 48 );
            this.txtPassword.MaxLength = 20;
            this.txtPassword.Name = "txtPassword";
            this.txtPassword.Size = new System.Drawing.Size( 175, 21 );
            this.txtPassword.TabIndex = 3;
            this.txtPassword.UseSystemPasswordChar = true;
            // 
            // LoginDlg
            // 
            this.AcceptButton = btnOk;
            this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 12F );
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = btnCancel;
            this.ClientSize = new System.Drawing.Size( 268, 119 );
            this.Controls.Add( btnCancel );
            this.Controls.Add( btnOk );
            this.Controls.Add( this.txtPassword );
            this.Controls.Add( label2 );
            this.Controls.Add( this.cbUser );
            this.Controls.Add( label1 );
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "LoginDlg";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "用户登录";
            this.Load += new System.EventHandler( this.LoginDlg_Load );
            this.ResumeLayout( false );
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox cbUser;
        private System.Windows.Forms.TextBox txtPassword;

    }
}