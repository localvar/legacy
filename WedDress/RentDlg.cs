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
	public partial class RentDlg : Form
	{
		private int m_nDressId;
		private int m_nRentTime = 0;


		public RentDlg( int DressId )
		{
			m_nDressId = DressId;
			InitializeComponent();
		}


		//private void AddRentDay( RentDetail.RentDetailDataTable dt, DateTime day, string customer )
		//{
		//    RentDetail.RentDetailRow row;
		//    DateTime YearMonth = new DateTime( day.Year, day.Month, 1 );
		//    DataRow[] rows = dt.Select( "YearMonth = '" + YearMonth + "'" );
		//    if( rows.Length == 0 )
		//    {
		//        row = (RentDetail.RentDetailRow)dt.NewRow();
		//        row.YearMonth = YearMonth;
		//        dt.Rows.Add( row );
		//    }
		//    else
		//    {
		//        row = (RentDetail.RentDetailRow)rows[0];
		//    }

		//    row[day.Day] = customer;
		//}


		private void RefreshRentDetail()
		{
			RentDetail ds = new RentDetail();
			RentDetail.RentDetailDataTable dt = ds._RentDetail;

			m_nRentTime = 0;

			// rent, dressid, startdate,enddate,customer
			OleDbCommand oc = new OleDbCommand();
			oc.CommandText = String.Format( "select startdate, enddate, customer from rent where dressid={0} order by startdate", m_nDressId );
			oc.CommandType = CommandType.Text;
			oc.Connection = Program.Database;

			OleDbDataReader reader = oc.ExecuteReader();
			if( reader.HasRows )
			{
				RentDetail.RentDetailRow row = (RentDetail.RentDetailRow)dt.NewRow();
				row.YearMonth = new DateTime( 1900, 1, 1 );

				while( reader.Read() )
				{
					DateTime dtStart = reader.GetDateTime( 0 );
					DateTime dtEnd = reader.GetDateTime( 1 );
					string customer = reader.GetString( 2 );
					for( DateTime day = dtStart; day <= dtEnd; day = day.AddDays( 1 ) )
					{
						DateTime YearMonth = new DateTime( day.Year, day.Month, 1 );
						if( row.YearMonth != YearMonth )
						{
							DataRow[] rows = dt.Select( "YearMonth = '" + YearMonth + "'" );
							if( rows.Length == 0 )
							{
								row = (RentDetail.RentDetailRow)dt.NewRow();
								row.YearMonth = YearMonth;
								dt.Rows.Add( row );
							}
							else
							{
								row = (RentDetail.RentDetailRow)rows[0];
							}
						}

						row[day.Day] = customer;
					//	AddRentDay( dt, day, customer );
					}
					++m_nRentTime;
				}
			}

			reader.Dispose();
			oc.Dispose();

			dgvRent.DataSource = ds;
			lblRentTime.Text = "出件次数:  " + m_nRentTime;
		}



		private void RentDlg_Load( object sender, EventArgs e )
		{
			RefreshRentDetail();
			if( Program.UserType != UserType.Customer )
			{
				btnDelRent.Visible = true;
				btnModify.Visible = true;
				lblRentTime.Visible = true;
			}
		}



		private void dgvRent_CurrentCellChanged( object sender, EventArgs e )
		{
			Point pt = dgvRent.CurrentCellAddress;
			if( pt.X > 0 && pt.Y >= 0 && dgvRent.CurrentCell.Value != DBNull.Value )
				txtCustomer.Text = (string)dgvRent.CurrentCell.Value;
			else
				txtCustomer.Text = string.Empty;

			if( pt.X <= 0 || pt.Y < 0 )
			{
				txtDate.Text = string.Empty;
			}
			else
			{
				DateTime YearMonth = (DateTime)dgvRent.CurrentRow.Cells[0].Value;
				try
				{
					DateTime date = new DateTime( YearMonth.Year, YearMonth.Month, pt.X );
					txtDate.Text = date.ToLongDateString();
				}
				catch( Exception )
				{
					txtDate.Text = string.Empty;
				}
			}
		}



		private void btnRent_Click( object sender, EventArgs e )
		{
			NewRentDlg dlg = new NewRentDlg( m_nDressId );
			if( dlg.ShowDialog() == DialogResult.OK )
				RefreshRentDetail();
		}


		private void btnDelRent_Click( object sender, EventArgs e )
		{
			Point pt = dgvRent.CurrentCellAddress;
			if( pt.X <= 0 || pt.Y < 0 )
				return;

			if( dgvRent.CurrentCell.Value == DBNull.Value )
				return;

			if( Program.UserType == UserType.Customer )
				return;

			if( MessageBox.Show( this, "您确实要删除选定的出件吗?", Program.AppTitle, MessageBoxButtons.YesNo, MessageBoxIcon.Question, MessageBoxDefaultButton.Button2 ) == DialogResult.No )
				return;

			DateTime YearMonth = (DateTime)dgvRent.CurrentRow.Cells[0].Value;
			DateTime date = new DateTime(YearMonth.Year, YearMonth.Month, pt.X, 12, 0, 0);
			OleDbCommand oc = new OleDbCommand();
			oc.CommandText = "delete from rent where dressid = ? and ? between startdate and enddate";
			oc.CommandType = CommandType.Text;
			oc.Connection = Program.Database;

			oc.Parameters.Add( "a", OleDbType.Integer ).Value = m_nDressId;
			oc.Parameters.Add( "b", OleDbType.Date ).Value = date;
			oc.ExecuteNonQuery();

			RefreshRentDetail();
		}


		private void OnModify()
		{
			Point pt = dgvRent.CurrentCellAddress;
			if( pt.X <= 0 || pt.Y < 0 )
				return;

			if( dgvRent.CurrentCell.Value == DBNull.Value )
				return;

			if( Program.UserType == UserType.Customer )
				return;

			DateTime YearMonth = (DateTime)dgvRent.CurrentRow.Cells[0].Value;
			DateTime date = new DateTime( YearMonth.Year, YearMonth.Month, pt.X );

			NewRentDlg dlg = new NewRentDlg( m_nDressId, date );
			if( dlg.ShowDialog() == DialogResult.OK )
				RefreshRentDetail();
		}


		private void dgvRent_CellDoubleClick( object sender, DataGridViewCellEventArgs e )
		{
			OnModify();
		}


		private void btnModify_Click( object sender, EventArgs e )
		{
			OnModify();
		}
	}
}