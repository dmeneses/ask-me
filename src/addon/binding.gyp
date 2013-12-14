{
  "targets": [
    {
      "target_name": "addon",
      "sources": [ "addon.cc", "./src/answer.cc"],
      "include_dirs" : 
	["../stemmer", 
	 "../textpreprocessor", 
	 "../../third-party/libstemmer/include",
	 "../../include",
	 "../crawlers/Twitter-lib",
	 "../../third-party/curl-7.33.0/include",
	 "../../third-party/jsoncpp-src-0.5.0/include",
	 "../../third-party/boost_1_54_0"
	], 

      "libraries" : 
	["-laskme", "-L../../lib", 
	 "-lstemmer", "-L../../../third-party/libstemmer/lib",
	 "-lTwitterCrawler", "-L../../crawlers/Twitter-lib/lib",
	 "-lcurl", "-L../../../third-party/curl-7.33.0/lib",
	 "-ljson", "-L../../../third-party/jsoncpp-src-0.5.0/lib",
	 "-lboost_regex-gcc-1_53", "-L../../../third-party/boost_1_54_0/lib/regex"
	]
    }
  ]
}
