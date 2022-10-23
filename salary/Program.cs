using System;
using System.Collections.Generic;
using System.Data.OleDb;
using System.IO;
using System.Linq;
using System.Windows.Forms;

namespace salary
{
	static class Program
	{
		static private void Process(string path)
		{
			var names = new Dictionary<string, bool>();
			var cs = "Provider=Microsoft.ACE.OLEDB.12.0;Extended Properties='Excel 8.0; HDR=No';Data Source=" + path + ";";
			// var cs = "Provider=Microsoft.Jet.OLEDB.4.0;Extended Properties='Excel 8.0; HDR=No';Data Source=" + path + ";";
			using (OleDbConnection conn = new OleDbConnection(cs))
			{
				conn.Open();
				var dtSheet = conn.GetOleDbSchemaTable(OleDbSchemaGuid.Tables, null);
				var table = dtSheet.Rows[0]["TABLE_NAME"].ToString().Trim('\'');

				path = Path.Combine(Path.GetDirectoryName(path), table.Trim('$') + ".xml");
				using (var sw = new StreamWriter(path))
				{
					sw.WriteLine(header);

					var cmd = new OleDbCommand();
					cmd.Connection = conn;
					cmd.CommandText = "SELECT * FROM [" + table + "A4:O];";
					var dr = cmd.ExecuteReader();
					var rows = 0;
					while (dr.Read())
					{
						rows++;
						int ordinal = 0;
						if (!int.TryParse(dr[0].ToString(), out ordinal) || ordinal != rows)
							continue;
						var name = dr[2].ToString();
						if(names.ContainsKey(name))
						{
							Console.WriteLine(string.Format("'{0}'重名了，已被重命名为'{0}{1}'", name, rows));
							name += rows.ToString();
						}
						names[name] = true;

						var s = string.Format(sheet,
							name,              // name
							dr[1].ToString(),  // account
							dr[3].ToString(),  // base salary
							dr[4].ToString(),  // vacation
							dr[5].ToString(),  // bonus
							dr[6].ToString(),  // salary
							dr[7].ToString(),  // house fund
							dr[8].ToString(),  // medical
							dr[9].ToString(), // endorment
							dr[10].ToString(), // unemployment
							dr[11].ToString(), // tax base
							dr[13].ToString(), // tax
							dr[14].ToString()  // actual payed
							);
						sw.WriteLine(s);
					}
					dr.Close();

					sw.WriteLine(footer);
				}
			}

		}

		/// <summary>
		/// 应用程序的主入口点。
		/// </summary>
		[STAThread]
		static void Main()
		{
			var dlgOpenFile = new OpenFileDialog();
			dlgOpenFile.Filter = "Excel文件|*.xlsx|Excel文件|*.xls|所有文件|*.*";
			if (dlgOpenFile.ShowDialog() == DialogResult.OK)
			{
				Process(dlgOpenFile.FileName);
				Console.WriteLine();
				Console.WriteLine("处理完成，按任意键退出");
				Console.ReadKey();
			}
		}

		static string sheet = @" <Worksheet ss:Name='{0}'> <Table ss:ExpandedColumnCount='3' ss:ExpandedRowCount='15' x:FullColumns='1' x:FullRows='1' ss:StyleID='s62' ss:DefaultColumnWidth='54' ss:DefaultRowHeight='13.5'> <Column ss:StyleID='s62' ss:AutoFitWidth='0' ss:Width='36'/> <Column ss:StyleID='s62' ss:AutoFitWidth='0' ss:Width='81.75'/> <Column ss:StyleID='s62' ss:AutoFitWidth='0' ss:Width='126.75'/> <Row ss:AutoFitHeight='0'/> <Row ss:AutoFitHeight='0' ss:Height='16.5'> <Cell ss:Index='2' ss:StyleID='s63'><Data ss:Type='String'>银行卡号（交行）</Data></Cell> <Cell ss:StyleID='s64'><Data ss:Type='String'>{1}</Data></Cell> </Row> <Row ss:AutoFitHeight='0' ss:Height='16.5'> <Cell ss:Index='2' ss:StyleID='s65'><Data ss:Type='String'>姓名</Data></Cell> <Cell ss:StyleID='s66'><Data ss:Type='String'>{0}</Data></Cell> </Row> <Row ss:AutoFitHeight='0' ss:Height='16.5'> <Cell ss:Index='2' ss:StyleID='s65'><Data ss:Type='String'>基本工资</Data></Cell> <Cell ss:StyleID='s68'><Data ss:Type='Number'>{2}</Data></Cell> </Row> <Row ss:AutoFitHeight='0' ss:Height='16.5'> <Cell ss:Index='2' ss:StyleID='s69'><Data ss:Type='String'>请假</Data></Cell> <Cell ss:StyleID='s68'><Data ss:Type='Number'>{3}</Data></Cell> </Row> <Row ss:AutoFitHeight='0' ss:Height='16.5'> <Cell ss:Index='2' ss:StyleID='s69'><Data ss:Type='String'>奖励</Data></Cell> <Cell ss:StyleID='s68'><Data ss:Type='Number'>{4}</Data></Cell> </Row> <Row ss:AutoFitHeight='0' ss:Height='16.5'> <Cell ss:Index='2' ss:StyleID='s69'><Data ss:Type='String'>应发工资</Data></Cell> <Cell ss:StyleID='s69' ss:Formula='=SUM(R[-3]C:R[-1]C)'><Data ss:Type='Number'>{5}</Data></Cell> </Row> <Row ss:AutoFitHeight='0' ss:Height='16.5'> <Cell ss:Index='2' ss:StyleID='s69'><Data ss:Type='String'>住房公积金</Data></Cell> <Cell ss:StyleID='s69'><Data ss:Type='Number'>{6}</Data></Cell> </Row> <Row ss:AutoFitHeight='0' ss:Height='16.5'> <Cell ss:Index='2' ss:StyleID='s69'><Data ss:Type='String'>医保</Data></Cell> <Cell ss:StyleID='s70'><Data ss:Type='Number'>{7}</Data></Cell> </Row> <Row ss:AutoFitHeight='0' ss:Height='16.5'> <Cell ss:Index='2' ss:StyleID='s71'><Data ss:Type='String'>养老</Data></Cell> <Cell ss:StyleID='s70'><Data ss:Type='Number'>{8}</Data></Cell> </Row> <Row ss:AutoFitHeight='0' ss:Height='16.5'> <Cell ss:Index='2' ss:StyleID='s71'><Data ss:Type='String'>失业</Data></Cell> <Cell ss:StyleID='s70'><Data ss:Type='Number'>{9}</Data></Cell> </Row> <Row ss:AutoFitHeight='0' ss:Height='16.5'> <Cell ss:Index='2' ss:StyleID='s71'><Data ss:Type='String'>计税基数</Data></Cell> <Cell ss:StyleID='s69'><Data ss:Type='Number'>{10}</Data></Cell> </Row> <Row ss:AutoFitHeight='0' ss:Height='16.5'> <Cell ss:Index='2' ss:StyleID='s71'><Data ss:Type='String'>税率</Data></Cell> <Cell ss:StyleID='s73' ss:Formula='=IF(R[-1]C&gt;35000,30%,IF(AND(R[-1]C&gt;9000,R[-1]C&lt;35000),25%,IF(AND(R[-1]C&gt;4500,R[-1]C&lt;9000),20%,IF(AND(R[-1]C&gt;1500,R[-1]C&lt;45000),10%,IF(AND(R[-1]C&gt;0,R[-1]C&lt;1500),3%,0)))))'><Data ss:Type='Number'>0.2</Data></Cell> </Row> <Row ss:AutoFitHeight='0' ss:Height='16.5'> <Cell ss:Index='2' ss:StyleID='s71'><Data ss:Type='String'>个税</Data></Cell> <Cell ss:StyleID='s74'><Data ss:Type='Number'>{11}</Data></Cell> </Row> <Row ss:AutoFitHeight='0' ss:Height='16.5'> <Cell ss:Index='2' ss:StyleID='s71'><Data ss:Type='String'>实发工资</Data></Cell> <Cell ss:StyleID='s69'><Data ss:Type='Number'>{12}</Data></Cell> </Row> </Table> <WorksheetOptions xmlns='urn:schemas-microsoft-com:office:excel'> <PageSetup> <Header x:Margin='0.3'/> <Footer x:Margin='0.3'/> <PageMargins x:Bottom='0.75' x:Left='0.7' x:Right='0.7' x:Top='0.75'/> </PageSetup> <Unsynced/> <Print> <ValidPrinterInfo/> <PaperSizeIndex>9</PaperSizeIndex> <HorizontalResolution>600</HorizontalResolution> <VerticalResolution>600</VerticalResolution> </Print> <Selected/> <Panes> <Pane> <Number>3</Number> <ActiveRow>20</ActiveRow> <ActiveCol>7</ActiveCol> </Pane> </Panes> <ProtectObjects>False</ProtectObjects> <ProtectScenarios>False</ProtectScenarios> </WorksheetOptions> </Worksheet>";
		static string header = @"<?xml version='1.0'?><?mso-application progid='Excel.Sheet'?><Workbook xmlns='urn:schemas-microsoft-com:office:spreadsheet' xmlns:o='urn:schemas-microsoft-com:office:office' xmlns:x='urn:schemas-microsoft-com:office:excel' xmlns:ss='urn:schemas-microsoft-com:office:spreadsheet' xmlns:html='http://www.w3.org/TR/REC-html40'> <DocumentProperties xmlns='urn:schemas-microsoft-com:office:office'> <Author>zhangwp</Author> <LastAuthor></LastAuthor> <Created></Created> <LastSaved></LastSaved> <Version>15.00</Version> </DocumentProperties> <OfficeDocumentSettings xmlns='urn:schemas-microsoft-com:office:office'> <AllowPNG/> </OfficeDocumentSettings> <ExcelWorkbook xmlns='urn:schemas-microsoft-com:office:excel'> <WindowHeight>12585</WindowHeight> <WindowWidth>28800</WindowWidth> <WindowTopX>0</WindowTopX> <WindowTopY>0</WindowTopY> <TabRatio>856</TabRatio> <ProtectStructure>False</ProtectStructure> <ProtectWindows>False</ProtectWindows> </ExcelWorkbook> <Styles> <Style ss:ID='Default' ss:Name='Normal'> <Alignment ss:Vertical='Center'/> <Borders/> <Font ss:FontName='宋体' x:CharSet='134' ss:Size='11' ss:Color='#000000'/> <Interior/> <NumberFormat/> <Protection/> </Style> <Style ss:ID='s20' ss:Name='百分比'> <NumberFormat ss:Format='0%'/> </Style> <Style ss:ID='s16' ss:Name='千位分隔'> <NumberFormat ss:Format='_ * #,##0.00_ ;_ * \-#,##0.00_ ;_ * &quot;-&quot;??_ ;_ @_ '/> </Style> <Style ss:ID='s62'> <Interior/> </Style> <Style ss:ID='s63'> <Alignment ss:Horizontal='Center' ss:Vertical='Center'/> <Borders> <Border ss:Position='Bottom' ss:LineStyle='Continuous' ss:Weight='1'/> <Border ss:Position='Left' ss:LineStyle='Continuous' ss:Weight='1'/> <Border ss:Position='Right' ss:LineStyle='Continuous' ss:Weight='1'/> <Border ss:Position='Top' ss:LineStyle='Continuous' ss:Weight='1'/> </Borders> <Font ss:FontName='微软雅黑' x:CharSet='134' x:Family='Swiss'/> <Interior/> <NumberFormat ss:Format='@'/> <Protection x:HideFormula='1'/> </Style> <Style ss:ID='s64'> <Alignment ss:Horizontal='Center' ss:Vertical='Center'/> <Borders> <Border ss:Position='Bottom' ss:LineStyle='Continuous' ss:Weight='1'/> <Border ss:Position='Left' ss:LineStyle='Continuous' ss:Weight='1'/> <Border ss:Position='Right' ss:LineStyle='Continuous' ss:Weight='1'/> <Border ss:Position='Top' ss:LineStyle='Continuous' ss:Weight='1'/> </Borders> <Font ss:FontName='微软雅黑' x:CharSet='134' x:Family='Swiss'/> <Interior ss:Color='#FFFFFF' ss:Pattern='Solid'/> <NumberFormat ss:Format='@'/> <Protection ss:Protected='0'/> </Style> <Style ss:ID='s65'> <Alignment ss:Horizontal='Center' ss:Vertical='Center'/> <Borders> <Border ss:Position='Bottom' ss:LineStyle='Continuous' ss:Weight='1'/> <Border ss:Position='Left' ss:LineStyle='Continuous' ss:Weight='1'/> <Border ss:Position='Right' ss:LineStyle='Continuous' ss:Weight='1'/> <Border ss:Position='Top' ss:LineStyle='Continuous' ss:Weight='1'/> </Borders> <Font ss:FontName='微软雅黑' x:CharSet='134' x:Family='Swiss'/> <Interior/> <Protection x:HideFormula='1'/> </Style> <Style ss:ID='s66'> <Alignment ss:Horizontal='Center' ss:Vertical='Center'/> <Borders> <Border ss:Position='Bottom' ss:LineStyle='Continuous' ss:Weight='1'/> <Border ss:Position='Left' ss:LineStyle='Continuous' ss:Weight='1'/> <Border ss:Position='Right' ss:LineStyle='Continuous' ss:Weight='1'/> <Border ss:Position='Top' ss:LineStyle='Continuous' ss:Weight='1'/> </Borders> <Font ss:FontName='微软雅黑' x:CharSet='134' x:Family='Swiss'/> <Interior ss:Color='#FFFFFF' ss:Pattern='Solid'/> <Protection ss:Protected='0'/> </Style> <Style ss:ID='s68' ss:Parent='s16'> <Alignment ss:Horizontal='Center' ss:Vertical='Center'/> <Borders> <Border ss:Position='Bottom' ss:LineStyle='Continuous' ss:Weight='1'/> <Border ss:Position='Left' ss:LineStyle='Continuous' ss:Weight='1'/> <Border ss:Position='Right' ss:LineStyle='Continuous' ss:Weight='1'/> <Border ss:Position='Top' ss:LineStyle='Continuous' ss:Weight='1'/> </Borders> <Font ss:FontName='微软雅黑' x:CharSet='134' x:Family='Swiss'/> <Interior ss:Color='#FFFFFF' ss:Pattern='Solid'/> <Protection ss:Protected='0'/> </Style> <Style ss:ID='s69' ss:Parent='s16'> <Alignment ss:Horizontal='Center' ss:Vertical='Center'/> <Borders> <Border ss:Position='Bottom' ss:LineStyle='Continuous' ss:Weight='1'/> <Border ss:Position='Left' ss:LineStyle='Continuous' ss:Weight='1'/> <Border ss:Position='Right' ss:LineStyle='Continuous' ss:Weight='1'/> <Border ss:Position='Top' ss:LineStyle='Continuous' ss:Weight='1'/> </Borders> <Font ss:FontName='微软雅黑' x:CharSet='134' x:Family='Swiss'/> <Interior/> <Protection x:HideFormula='1'/> </Style> <Style ss:ID='s70' ss:Parent='s16'> <Alignment ss:Horizontal='Center' ss:Vertical='Center'/> <Borders> <Border ss:Position='Bottom' ss:LineStyle='Continuous' ss:Weight='1'/> <Border ss:Position='Left' ss:LineStyle='Continuous' ss:Weight='1'/> <Border ss:Position='Right' ss:LineStyle='Continuous' ss:Weight='1'/> <Border ss:Position='Top' ss:LineStyle='Continuous' ss:Weight='1'/> </Borders> <Font ss:FontName='微软雅黑' x:CharSet='134' x:Family='Swiss'/> <Interior/> <Protection ss:Protected='0'/> </Style> <Style ss:ID='s71' ss:Parent='s16'> <Alignment ss:Horizontal='Center' ss:Vertical='Center' ss:WrapText='1'/> <Borders> <Border ss:Position='Bottom' ss:LineStyle='Continuous' ss:Weight='1'/> <Border ss:Position='Left' ss:LineStyle='Continuous' ss:Weight='1'/> <Border ss:Position='Right' ss:LineStyle='Continuous' ss:Weight='1'/> <Border ss:Position='Top' ss:LineStyle='Continuous' ss:Weight='1'/> </Borders> <Font ss:FontName='微软雅黑' x:CharSet='134' x:Family='Swiss'/> <Interior/> <Protection x:HideFormula='1'/> </Style> <Style ss:ID='s73' ss:Parent='s20'> <Alignment ss:Horizontal='Center' ss:Vertical='Center'/> <Borders> <Border ss:Position='Bottom' ss:LineStyle='Continuous' ss:Weight='1'/> <Border ss:Position='Left' ss:LineStyle='Continuous' ss:Weight='1'/> <Border ss:Position='Right' ss:LineStyle='Continuous' ss:Weight='1'/> <Border ss:Position='Top' ss:LineStyle='Continuous' ss:Weight='1'/> </Borders> <Font ss:FontName='微软雅黑' x:CharSet='134' x:Family='Swiss'/> <Interior/> <Protection x:HideFormula='1'/> </Style> <Style ss:ID='s74' ss:Parent='s16'> <Borders> <Border ss:Position='Bottom' ss:LineStyle='Continuous' ss:Weight='1'/> <Border ss:Position='Left' ss:LineStyle='Continuous' ss:Weight='1'/> <Border ss:Position='Right' ss:LineStyle='Continuous' ss:Weight='1'/> <Border ss:Position='Top' ss:LineStyle='Continuous' ss:Weight='1'/> </Borders> <Font ss:FontName='微软雅黑' x:CharSet='134' x:Family='Swiss' ss:Color='#333333'/> <Interior/> <Protection x:HideFormula='1'/> </Style> </Styles>";
		static string footer = @"</Workbook>";
	}
}
