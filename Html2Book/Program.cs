using System;

namespace Html2Book
{
	class Program
	{
		static void LogEvent(string msg)
		{
			Console.WriteLine(msg);
		}
		static void Main(string[] args)
		{
			//var book = new WordBook();
			var book = new FakeBook();
			book.Create("abc", "bcd", "f:\\zbmprj\\htmlrobot\\template.dotx");
			var robot = new QuanXueRobot(book);
			robot.LogEvent += LogEvent;
			robot.ProcessBook("http://quanxue.cn/CT_NanHuaiJin/XiChiIndex.html");
		}
	}
}
