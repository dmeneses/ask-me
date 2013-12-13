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
	 "../../third-party/curl-7.33.0/include"
	], 

      "libraries" : 
	["-laskme", "-L../../lib", 
	 "-lstemmer", "-L../../../third-party/libstemmer/lib",
	 "-lTwitterCrawler", "-L../../crawlers/Twitter-lib/lib",
	 "-lcurl", "-L../../../third-party/curl-7.33.0/lib"
	]
    }
  ]
}
