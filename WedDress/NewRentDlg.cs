using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.OleDb;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace WedDress
{
	public partial class NewRentDlg : Form
	{
		private bool m_bModify;
		private int m_nDressId;
		private string m_strCustomer;
		private DateTime m_dtStart;
		private DateTime m_dtEnd;
		private DateTime m_date;


		public NewRentDlg( int nDressId )
		{
			m_nDressId = nDressId;
			m_bModify = false;

			InitializeComponent();
		}


		public NewRentDlg( int nDressId, DateTime date )
		{
			m_nDressId = nDressId;
			m_date = date;
			m_bModify = true;

			InitializeComponent();

			OleDbCommand oc = new OleDbCommand();
			oc.CommandText = "select startdate, enddate, customer from rent where dressid=? and ? between startdate and enddate"; 
			oc.CommandType = CommandType.Text;
			oc.Connection = Program.Database;
			oc.Parameters.Add( "a", OleDbType.Integer ).Value = m_nDressId;
			oc.Parameters.Add( "b", OleDbType.Date ).Value = date;

			OleDbDataReader reader = oc.ExecuteReader();
			reader.Read();
			dtStartDate.Value = reader.GetDateTime( 0 );
			dtEndDate.Value = reader.GetDateTime( 1 );
			txtCustomer.Text = reader.GetString( 2 );
			reader.Dispose();
			oc.Dispose();

			this.Text = "修改出件信息";
		}



		private bool DoRent()
		{
			// rent, dressid, startdate,enddate,customer
			OleDbCommand oc = new OleDbCommand();
			oc.CommandText = "select dressid from rent where dressid=? and ? <= enddate and ? >= startdate";
			oc.CommandType = CommandType.Text;
			oc.Connection = Program.Database;
			oc.Parameters.Add( "a", OleDbType.Integer ).Value = m_nDressId;
			oc.Parameters.Add( "b", OleDbType.Date ).Value = m_dtStart;
			oc.Parameters.Add( "c", OleDbType.Date ).Value = m_dtEnd;

			OleDbDataReader reader = oc.ExecuteReader();
			if( reader.HasRows )
			{
				reader.Dispose();
				oc.Dispose();
				MessageBox.Show( this, "出件时间冲突, 请查正后重新输入", Program.AppTitle, MessageBoxButtons.OK, MessageBoxIcon.Hand );
				return false;
			}

			reader.Dispose();
			oc.Dispose();

			oc = new OleDbCommand();
			oc.CommandText = "insert into rent(dressid, startdate, enddate, customer) values(?,?,?,?)";
			oc.CommandType = CommandType.Text;
			oc.Connection = Program.Database;
			oc.Parameters.Add( "a", OleDbType.Integer ).Value = m_nDressId;
			oc.Parameters.Add( "b", OleDbType.Date ).Value = m_dtStart;
			oc.Parameters.Add( "c", OleDbType.Date ).Value = m_dtEnd;
			oc.Parameters.Add( "d", OleDbType.VarWChar ).Value = m_strCustomer;
			oc.ExecuteNonQuery();
			oc.Dispose();

			return true;
		}


		private bool DoModify()
		{
			OleDbCommand oc = new OleDbCommand();
			oc.CommandText = "select dressid from rent where dressid=? and ? <= enddate and ? >= startdate and (not ? between startdate and enddate)";
			oc.CommandType = CommandType.Text;
			oc.Connection = Program.Database;
			oc.Parameters.Add( "a", OleDbType.Integer ).Value = m_nDressId;
			oc.Parameters.Add( "b", OleDbType.Date ).Value = m_dtStart;
			oc.Parameters.Add( "c", OleDbType.Date ).Value = m_dtEnd;
			oc.Parameters.Add( "d", OleDbType.Date ).Value = m_date;

			OleDbDataReader reader = oc.ExecuteReader();
			if( reader.HasRows )
			{
				reader.Dispose();
				oc.Dispose();
				MessageBox.Show( this, "出件时间冲突, 请查正后重新输入", Program.AppTitle, MessageBoxButtons.OK, MessageBoxIcon.Hand );
				return false;
			}

			reader.Dispose();
			oc.Dispose();

			oc = new OleDbCommand();
			oc.CommandText = "update rent set startdate=?, enddate=?, customer=? where dressid=? and ? between startdate and enddate";
			oc.CommandType = CommandType.Text;
			oc.Connection = Program.Database;
			oc.Parameters.Add( "a", OleDbType.Date ).Value = m_dtStart;
			oc.Parameters.Add( "b", OleDbType.Date ).Value = m_dtEnd;
			oc.Parameters.Add( "c", OleDbType.VarWChar ).Value = m_strCustomer;
			oc.Parameters.Add( "d", OleDbType.Integer ).Value = m_nDressId;
			oc.Parameters.Add( "e", OleDbType.Date ).Value = m_date;
			oc.ExecuteNonQuery();
			oc.Dispose();

			return true;
		}


		private void btnOk_Click( object sender, EventArgs e )
		{
			m_dtStart = new DateTime( dtStartDate.Value.Year, dtStartDate.Value.Month, dtStartDate.Value.Day );
			m_dtEnd = new DateTime( dtEndDate.Value.Year, dtEndDate.Value.Month, dtEndDate.Value.Day, 23, 59, 59 );

			if( m_dtEnd < m_dtStart )
			{
				MessageBox.Show( this, "结束日期不能小于开始日期", Program.AppTitle, MessageBoxButtons.OK, MessageBoxIcon.Hand );
				return;
			}

			m_strCustomer = txtCustomer.Text.Trim();
			if( m_strCustomer.Length == 0 )
			{
				MessageBox.Show( this, "必须输入客户名称", Program.AppTitle, MessageBoxButtons.OK, MessageBoxIcon.Hand );
				return;
			}

			if( m_bModify ? DoModify() : DoRent() )
			{
				this.DialogResult = DialogResult.OK;
				this.Close();
			}
		}
	}
}