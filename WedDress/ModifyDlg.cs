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
	public partial class ModifyDlg : Form
	{
		private DataRow m_row;


		public ModifyDlg()
		{
			InitializeComponent();
		}


		public void SetRow( DataRow row )
		{
			m_row = row;

			try
			{
				string path = (string)row["照片"];
				txtPath.Text = path;
				if( path.Length > 0 )
					pbPhoto.Load( path );
				else
					pbPhoto.Image = pbPhoto.InitialImage;
			}
			catch( Exception )
			{
				pbPhoto.Image = pbPhoto.ErrorImage;
			}

			cbDept.Text = (string)row["部门"];
			cbArea.Text = (string)row["区域"];
			cbCategory.Text = (string)row["类别"];
			txtAreaNo.Text = (string)row["区域号"];
			cbColor.Text = (string)row["颜色"];
			txtPrice.Text = row["售价"].ToString();
			txtAsessory.Text = (string)row["配件"];

			cbProducer.Text = (string)row["厂商"];
			txtProducerNo.Text = (string)row["厂商号"];
			dtArchive.Value = (DateTime)row["入档日期"];
			txtArchiveNo.Text = (string)row["资料卡号"];

			txtReq1.Text = (string)row["调拨单号1"];
			dtReq1.Value = (DateTime)row["调拨日期1"];
			txtReq2.Text = (string)row["调拨单号2"];
			dtReq2.Value = (DateTime)row["调拨日期2"];
			txtReq3.Text = (string)row["调拨单号3"];
			dtReq3.Value = (DateTime)row["调拨日期3"];

			dtBuy.Value = (DateTime)row["进货日期"];
			txtBuyPrice.Text = row["进价"].ToString();
			cbBuyer.Text = row["订货人"].ToString();

		}


		private void btnModify_Click( object sender, EventArgs e )
		{
			float price = 0, buyprice = 0;
			if( (txtPrice.Text.Length > 0 && !float.TryParse( txtPrice.Text, out price )) ||
				(txtBuyPrice.Text.Length > 0 && !float.TryParse( txtBuyPrice.Text, out buyprice )) )
			{
				MessageBox.Show( "价格输入错误, 请更正", Program.AppTitle, MessageBoxButtons.OK, MessageBoxIcon.Hand );
				return;
			}

			OleDbCommand cmd = new OleDbCommand();
			cmd.CommandText =
				"update [WedDress] set 照片=?,部门=?,区域=?,类别=?,区域号=?,颜色=?,售价=?,配件=?,厂商=?,厂商号=?,入档日期=?,资料卡号=?,调拨单号1=?,调拨日期1=?,调拨单号2=?,调拨日期2=?,调拨单号3=?,调拨日期3=?,进货日期=?,进价=?,订货人=?"
			+ " where [id]=?";
			cmd.CommandType = CommandType.Text;
			cmd.Connection = Program.Database;
			cmd.Parameters.Add( "", OleDbType.VarChar ).Value = txtPath.Text;
			cmd.Parameters.Add( "", OleDbType.VarChar ).Value = cbDept.Text;
			cmd.Parameters.Add( "", OleDbType.VarChar ).Value = cbArea.Text;
			cmd.Parameters.Add( "", OleDbType.VarChar ).Value = cbCategory.Text;
			cmd.Parameters.Add( "", OleDbType.VarChar ).Value = txtAreaNo.Text;
			cmd.Parameters.Add( "", OleDbType.VarChar ).Value = cbColor.Text;
			cmd.Parameters.Add( "", OleDbType.Currency ).Value = price;
			cmd.Parameters.Add( "", OleDbType.VarChar ).Value = txtAsessory.Text;
			cmd.Parameters.Add( "", OleDbType.VarChar ).Value = cbProducer.Text;
			cmd.Parameters.Add( "", OleDbType.VarChar ).Value = txtProducerNo.Text;
			cmd.Parameters.Add( "", OleDbType.Date ).Value = dtArchive.Value;
			cmd.Parameters.Add( "", OleDbType.VarChar ).Value = txtArchiveNo.Text;
			cmd.Parameters.Add( "", OleDbType.VarChar ).Value = txtReq1.Text;
			cmd.Parameters.Add( "", OleDbType.Date ).Value = dtReq1.Value;
			cmd.Parameters.Add( "", OleDbType.VarChar ).Value = txtReq2.Text;
			cmd.Parameters.Add( "", OleDbType.Date ).Value = dtReq2.Value;
			cmd.Parameters.Add( "", OleDbType.VarChar ).Value = txtReq3.Text;
			cmd.Parameters.Add( "", OleDbType.Date ).Value = dtReq3.Value;
			cmd.Parameters.Add( "", OleDbType.Date ).Value = dtBuy.Value;
			cmd.Parameters.Add( "", OleDbType.Currency ).Value = buyprice;
			cmd.Parameters.Add( "", OleDbType.VarChar ).Value = cbBuyer.Text;
			cmd.Parameters.Add( "", OleDbType.Integer ).Value = (int)m_row["ID"];
			cmd.ExecuteNonQuery();
			cmd.Dispose();



			m_row["照片"] = txtPath.Text;
			m_row["部门"] =cbDept.Text;
			m_row["区域"] = cbArea.Text;
			m_row["类别"]=cbCategory.Text;
			m_row["区域号"]=txtAreaNo.Text;
			m_row["颜色"]=cbColor.Text;
			m_row["售价"] = price;
			m_row["配件"]=txtAsessory.Text;

			m_row["厂商"]=cbProducer.Text;
			m_row["厂商号"]=txtProducerNo.Text;
			m_row["入档日期"] = dtArchive.Value;
			m_row["资料卡号"]=txtArchiveNo.Text;

			m_row["调拨单号1"]=txtReq1.Text;
			m_row["调拨日期1"]=dtReq1.Value;
			m_row["调拨单号2"]=txtReq2.Text;
			m_row["调拨日期2"] = dtReq2.Value;
			m_row["调拨单号3"]=txtReq3.Text;
			m_row["调拨日期3"] = dtReq3.Value;

			m_row["进货日期"] = dtBuy.Value;
			m_row["进价"] = buyprice;
			m_row["订货人"] = cbBuyer.Text;


			this.DialogResult = DialogResult.OK;
			this.Close();
		}


		private void btnSelect_Click( object sender, EventArgs e )
		{
			if( dlgSelImg.ShowDialog() == DialogResult.OK )
			{
				try
				{
					pbPhoto.Load( dlgSelImg.FileName );
				}
				catch( Exception )
				{
					pbPhoto.Image = pbPhoto.ErrorImage;
				}
				txtPath.Text = dlgSelImg.FileName;
			}
		}

		private void ModifyDlg_Load( object sender, EventArgs e )
		{
			if( Program.UserType == UserType.Admin )
			{
				labelBuyDate.Visible = dtBuy.Visible = true;
				labelBuyPrice.Visible = txtBuyPrice.Visible = true;
				labelBuyer.Visible = cbBuyer.Visible = true;
			}
			Program.FillComboBox( "部门", cbDept );
			Program.FillComboBox( "区域", cbArea );
			Program.FillComboBox( "类别", cbCategory );
			Program.FillComboBox( "颜色", cbColor );
			Program.FillComboBox( "厂商", cbProducer );
			Program.FillComboBox( "订货人", cbBuyer );
		}

	}
}