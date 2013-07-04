using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Data.OleDb;
using System.Data;


namespace WedDress
{
	enum UserType
	{
		Customer = 0,
		Manager = 1,
		Admin = 2,
	}
	//
	static class Program
	{
		static OleDbConnection m_database;
		static UserType m_userType;


		public static string AppTitle
		{
			get { return "婚纱礼服管理系统"; }
		}

		public static UserType UserType
		{
			get { return m_userType; }
			set { m_userType = value; }
		}

		public static OleDbConnection Database
		{
			get { return m_database; }
		}

		static void OpenDatabase()
		{
			m_database = new OleDbConnection();
			m_database.ConnectionString = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=|DataDirectory|\\WedDress.mdb;Persist Security Info=True;Jet OLEDB:Database Password=localvar";
			m_database.Open();
		}


		public static void FillComboBox( string field, ComboBox cb )
		{
			OleDbCommand cmd = new OleDbCommand();
			cmd.CommandText = "select distinct [" + field + "] from [WedDress]";
			cmd.CommandType = CommandType.Text;
			cmd.Connection = Program.Database;
			OleDbDataReader reader = cmd.ExecuteReader();
			while( reader.Read() )
			{
				if( !reader.IsDBNull( 0 ) )
				{
					string s = reader.GetString( 0 );
					if( s.Length > 0 )
						cb.Items.Add( s );
				}
			}
			reader.Close();
			cmd.Dispose();
		}


		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main()
		{
			AppDomain.CurrentDomain.SetData( "DataDirectory", Application.StartupPath );
			Application.EnableVisualStyles();
			Application.SetCompatibleTextRenderingDefault( false );
			OpenDatabase();
			Application.Run( new MainForm() );
			m_database.Close();
		}
	}
}