using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Data.OleDb;

namespace WedDress
{
	public partial class LoginDlg : Form
	{
		public LoginDlg()
		{
			InitializeComponent();
		}

		private void LoginDlg_Load( object sender, EventArgs e )
		{
			OleDbCommand cmd = new OleDbCommand();
			cmd.CommandText = "select [Name] from [user]";
			cmd.CommandType = CommandType.Text;
			cmd.Connection = Program.Database;
			OleDbDataReader reader = cmd.ExecuteReader();
			while( reader.Read() )
				cbUser.Items.Add( reader.GetString( 0 ) );
			reader.Close();
			cmd.Dispose();
			cbUser.SelectedIndex = 0;
		}

		private void btnOk_Click( object sender, EventArgs e )
		{
			bool succeed = false;

			OleDbCommand cmd = new OleDbCommand();
			cmd.CommandText = "select [password], [type] from [user] where [name] ='" + cbUser.Text + "'";
			cmd.CommandType = CommandType.Text;
			cmd.Connection = Program.Database;
			OleDbDataReader reader = cmd.ExecuteReader();

			if( reader.HasRows && reader.Read() )
			{
				string pwd = reader.GetString( 0 );
				int type = reader.GetInt16( 1 );
				if( pwd == txtPassword.Text )
				{
					succeed = true;
					if( type == 1 )
						Program.UserType = UserType.Manager;
					else if( type == 2 )
						Program.UserType = UserType.Admin;
					else
						Program.UserType = UserType.Customer;
				}
			}

			reader.Close();
			cmd.Dispose();

			if( !succeed )
			{
				MessageBox.Show( this, "√‹¬Î¥ÌŒÛ, «Î÷ÿ–¬ ‰»Î!", "µ«¬Ω ß∞‹", MessageBoxButtons.OK, MessageBoxIcon.Error );
			}
			else
			{
				this.DialogResult = DialogResult.OK;
				this.Close();
			}
		}
	}
}