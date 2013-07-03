using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;

namespace Html2Book
{
	class HtmlClient : WebClient
	{
		protected override WebRequest GetWebRequest(Uri address)
		{
			var request = (HttpWebRequest)base.GetWebRequest(address);
			/*
			if (request != null)
			{
				request.Timeout = 1000 * 100;
				request.ReadWriteTimeout = 1000 * 100;
			}
			*/
			return request;
		}
	}
}
