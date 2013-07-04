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
	public partial class MainForm : Form
	{
		public MainForm()
		{
			InitializeComponent();
			this.Text = Program.AppTitle;
		}

		private void MainForm_Shown( object sender, EventArgs e )
		{
			LoginDlg dlg = new LoginDlg();
			if( dlg.ShowDialog( this ) != DialogResult.OK )
			{
				this.Close();
			}
			else
			{
				if( Program.UserType != UserType.Customer )
				{
					lblProducer.Visible = cbProducer.Visible = cbProducer.Enabled = true;
					btnNew.Visible = btnNew.Enabled = true;
					btnModify.Visible = btnModify.Enabled = true;
					btnQueryByRent.Enabled = dtRent.Enabled = true;

					labelProducer.Visible = txtProducer.Visible = true;
					labelProducerNo.Visible = txtProducerNo.Visible = true;
					labelArchive.Visible = txtArchive.Visible = true;
					labelArchiveNo.Visible = txtArchiveNo.Visible = true;
					labelReq1.Visible = txtReq1.Visible = true;
					labelReqDate1.Visible = txtReqDate1.Visible = true;
					labelReq2.Visible = txtReq2.Visible = true;
					labelReqDate2.Visible = txtReqDate2.Visible = true;
					labelReq3.Visible = txtReq3.Visible = true;
					labelReqDate3.Visible = txtReqDate3.Visible = true;
					lblNumDress.Visible = true;
					btnQueryByRent.Visible = dtRent.Visible = lblRent.Visible = true;
				}
				if( Program.UserType == UserType.Admin )
				{
					btnDel.Visible = btnDel.Enabled = true;
					labelBuyDate.Visible = txtBuyDate.Visible = true;
					labelBuyPrice.Visible = txtBuyPrice.Visible = true;
					labelBuyer.Visible = txtBuyer.Visible = true;
				}
			}
		}


		private void MainForm_Load( object sender, EventArgs e )
		{
			pbPhoto.Image = pbPhoto.InitialImage;
			RefillComboBoxes();
		}


		void RefillComboBoxes()
		{
			string str = cbDept.Text;
			cbDept.Items.Clear();
			cbDept.Items.Add( "" );
			Program.FillComboBox( "部门", cbDept );
			cbDept.Text = str;

			str = cbColor.Text;
			cbColor.Items.Clear();
			cbColor.Items.Add( "" );
			Program.FillComboBox( "颜色", cbColor );
			cbColor.Text = str;

			str = cbArea.Text;
			cbArea.Items.Clear();
			cbArea.Items.Add( "" );
			Program.FillComboBox( "区域", cbArea );
			cbArea.Text = str;

			str = cbCategory.Text;
			cbCategory.Items.Clear();
			cbCategory.Items.Add( "" );
			Program.FillComboBox( "类别", cbCategory );
			cbCategory.Text = str;

			str = cbProducer.Text;
			cbProducer.Items.Clear();
			cbProducer.Items.Add( "" );
			Program.FillComboBox( "厂商", cbProducer );
			cbProducer.Text = str;
		}


		private void DoQuery( OleDbCommand cmd )
		{
			OleDbDataAdapter oda = new OleDbDataAdapter( cmd );
			dsDress.Tables["WedDress"].Clear();
			int count = oda.Fill( dsDress, "WedDress" );
			oda.Dispose();
			cmd.Dispose();

			lblNumDress.Text = "共有 " + count + " 件符合查询条件的服装";
		}


		#region 查询
		private void btnQuery_Click( object sender, EventArgs e )
		{
			OleDbCommand oc = new OleDbCommand();
			oc.CommandType = CommandType.Text;
			oc.Connection = Program.Database;
			string prefix = " where ";
			string and = " and ";

			StringBuilder sb = new StringBuilder();
			if( cbDept.Text.Length > 0 )
			{
				sb.AppendFormat( "{0}[部门]=?", prefix );
				oc.Parameters.Add( "a", OleDbType.VarWChar ).Value = cbDept.Text;
				prefix = and;
			}

			if( cbColor.Text.Length > 0 )
			{
				sb.AppendFormat( "{0}[颜色]=?", prefix );
				oc.Parameters.Add( "b", OleDbType.VarWChar ).Value = cbColor.Text;
				prefix = and;
			}

			if( cbArea.Text.Length > 0 )
			{
				sb.AppendFormat( "{0}[区域]=?", prefix );
				oc.Parameters.Add( "c", OleDbType.VarWChar ).Value = cbArea.Text;
				prefix = and;
			}

			if( cbCategory.Text.Length > 0 )
			{
				sb.AppendFormat( "{0}[类别]=?", prefix );
				oc.Parameters.Add( "d", OleDbType.VarWChar ).Value = cbCategory.Text;
				prefix = and;
			}

			if( cbProducer.Text.Length > 0 )
			{
				sb.AppendFormat( "{0}[厂商]=?", prefix );
				oc.Parameters.Add( "e", OleDbType.VarWChar ).Value = cbProducer.Text;
				prefix = and;
			}

			if( cbAreaNo.Text.Length > 0 )
			{
				sb.AppendFormat( "{0}[区域号]=?", prefix );
				oc.Parameters.Add( "f", OleDbType.VarWChar ).Value = cbAreaNo.Text;
				prefix = and;
			}

			sb.Insert( 0, "select * from WedDress" );
			oc.CommandText = sb.ToString();
			DoQuery( oc );
		}
		#endregion


		DataRow GetCurrentRow()
		{
			if( dataGridView.CurrentRow != null )
			{
				int id = (int)dataGridView.CurrentRow.Cells[0].Value;
				DataTable dt = dsDress.Tables["WedDress"];
				DataRow[] rows = dt.Select( "[ID]=" + id );
				if( rows.GetLength(0) > 0 )
					return rows[0];
			}
			return null;
		}


		#region 选择的行改变
		private void OnSelectionChange()
		{
			DataRow row = GetCurrentRow();
			if( row != null )
			{
				try
				{
					pbPhoto.Load( (string)row["照片"] );
				}
				catch( Exception )
				{
					pbPhoto.Image = pbPhoto.ErrorImage;
				}

				txtDept.Text = (string)row["部门"];
				txtArea.Text = (string)row["区域"];
				txtCategory.Text = (string)row["类别"];
				txtAreaNo.Text = (string)row["区域号"];
				txtColor.Text = (string)row["颜色"];
				txtPrice.Text = row["售价"].ToString();
				txtAsessory.Text = (string)row["配件"];

				txtProducer.Text = (string)row["厂商"];
				txtProducerNo.Text = (string)row["厂商号"];
				txtArchive.Text = ((DateTime)row["入档日期"]).ToLongDateString();
				txtArchiveNo.Text = (string)row["资料卡号"];

				txtReq1.Text = (string)row["调拨单号1"];
				txtReqDate1.Text = ((DateTime)row["调拨日期1"]).ToLongDateString();
				txtReq2.Text = (string)row["调拨单号2"];
				txtReqDate2.Text = ((DateTime)row["调拨日期2"]).ToLongDateString();
				txtReq3.Text = (string)row["调拨单号3"];
				txtReqDate3.Text = ((DateTime)row["调拨日期3"]).ToLongDateString();

				txtBuyDate.Text = ((DateTime)row["进货日期"]).ToLongDateString();
				txtBuyPrice.Text = row["进价"].ToString();
				txtBuyer.Text = row["订货人"].ToString();
			}
			else
			{
				pbPhoto.Image = pbPhoto.InitialImage;
				txtDept.Text = "";
				txtArea.Text = "";
				txtCategory.Text = "";
				txtAreaNo.Text = "";
				txtColor.Text = "";
				txtPrice.Text = "";
				txtAsessory.Text = "";

				txtProducer.Text = "";
				txtProducerNo.Text = "";
				txtArchive.Text = "";
				txtArchiveNo.Text = "";

				txtReq1.Text = "";
				txtReqDate1.Text = "";
				txtReq2.Text = "";
				txtReqDate2.Text = "";
				txtReq3.Text = "";
				txtReqDate3.Text = "";

				txtBuyDate.Text = "";
				txtBuyPrice.Text = "";
				txtBuyer.Text = "";
			}
		}
		#endregion

		private void dataGridView_SelectionChanged( object sender, EventArgs e )
		{
			OnSelectionChange();
		}


		private void btnNew_Click( object sender, EventArgs e )
		{
			if( Program.UserType == UserType.Customer )
				return;

			AddDlg dlg = new AddDlg();
			if( dlg.ShowDialog( this ) != DialogResult.OK )
				return;

			RefillComboBoxes();

			OleDbCommand cmd = new OleDbCommand();
			cmd.CommandText = "select top 1 * from WedDress order by [ID] desc";
			cmd.Connection = Program.Database;
			cmd.CommandType = CommandType.Text;

			OleDbDataAdapter oda = new OleDbDataAdapter( cmd);
			DataTable dt = new DataTable();
			oda.Fill( dt );

			dsDress.Tables["WedDress"].Merge( dt );
			dt.Dispose();
			oda.Dispose();
			cmd.Dispose();
		}


		private void DoModify()
		{
			if( Program.UserType == UserType.Customer )
				return;

			DataRow row = GetCurrentRow();
			if( row == null )
				return;

			ModifyDlg dlg = new ModifyDlg();
			dlg.SetRow( row );
			if( dlg.ShowDialog( this ) == DialogResult.OK )
			{
				RefillComboBoxes();
				OnSelectionChange();
			}
		}



		private void btnModify_Click( object sender, EventArgs e )
		{
			DoModify();
		}



		private void btnDel_Click( object sender, EventArgs e )
		{
			if( Program.UserType != UserType.Admin )
				return;

			if( dataGridView.CurrentRow == null )
				return;

			int id = (int)dataGridView.CurrentRow.Cells[0].Value;
			DataTable dt = dsDress.Tables["WedDress"];
			DataRow[] rows = dt.Select( "[ID]=" + id );
			if( rows.GetLength( 0 ) <= 0 )
				return;

			if( MessageBox.Show( this, "您确实要删除选定的服装吗?", Program.AppTitle,
				MessageBoxButtons.YesNo, MessageBoxIcon.Question, MessageBoxDefaultButton.Button2 )
				== DialogResult.No )
				return;

			OleDbCommand cmd = new OleDbCommand();
			cmd.CommandText = "delete from [WedDress] where [ID]=" + id.ToString();
			cmd.CommandType = CommandType.Text;
			cmd.Connection = Program.Database;
			cmd.ExecuteNonQuery();
			cmd.Dispose();

			dt.Rows.Remove( rows[0] );
		}



		private void DoRent()
		{
			if( dataGridView.CurrentRow == null )
				return;
			int id = (int)dataGridView.CurrentRow.Cells[0].Value;
			RentDlg dlg = new RentDlg( id );
			dlg.ShowDialog();
		}



		private void dataGridView_CellMouseDoubleClick( object sender, DataGridViewCellMouseEventArgs e )
		{
			DoRent();
		}



		private void btnRent_Click( object sender, EventArgs e )
		{
			DoRent();
		}

		private void btnQueryByRent_Click( object sender, EventArgs e )
		{
			DateTime date = dtRent.Value;
			OleDbCommand cmd = new OleDbCommand();
			cmd.CommandText = "select * from WedDress where [id] in (select dressid from rent where ? between startdate and enddate)";
			cmd.CommandType = CommandType.Text;
			cmd.Connection = Program.Database;
			cmd.Parameters.Add( "a", OleDbType.Date ).Value = new DateTime( date.Year, date.Month, date.Day, 12, 0, 0 );
			DoQuery( cmd );
		}

	}
}