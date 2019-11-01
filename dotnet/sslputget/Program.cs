using Apache.Geode.Client;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace sslputget
{
    class Program
    {
        static void Main(string[] args)
        {
            CacheFactory cacheFactory = CacheFactory.CreateCacheFactory();
            Cache cache = cacheFactory.Set("cache-xml-file", "client_config.xml")
		    .Set("log-level", "debug")
		    .Set("log-file", "sslputget.log")
		    .Set("ssl-enabled", "true")
		    .Set("ssl-strict-mode", "true")
		    .Set("ssl-keystore", "<path to keystore>")
		    .Set("ssl-keystore-password", "<password>")
		    .Set("ssl-truststore", "<path to truststore>")
		    .Create();

            IRegion<int, string> region = cache.GetRegion<int, string>("testSSLRegion");

            region[0] = "zero";
            Console.WriteLine("Put key/value in region.");

            string result = region[0];

            Console.WriteLine("Retrieved the value \"{0}\" from the region.", result);

            cache.Close();
        }
    }
}
