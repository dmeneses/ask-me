{
  "targets": [
    {
      "target_name": "addon",
      "sources": [ "addon.cc", "./src/answer.cc"],
      "include_dirs" : 
	["../stemmer", 
	 "../textpreprocessor", 
	 "../../third-party/libstemmer/include",
	 "../../third-party/curl-7.33.0/include",
	 "../../third-party/jsoncpp-src-0.5.0/include",
	 "../../third-party/boost_1_54_0",
	 "../../third-party/FANN-2.2.0/include",
         "../../third-party/wnb-0.6/include"
	], 

      "libraries" : 
	["-laskme", "-L../../lib", 
	 "-lstemmer", "-L../../../third-party/libstemmer/lib64",
	 "-lcurl", "-L../../../third-party/curl-7.33.0/lib64",
	 "-ljson", "-L../../../third-party/jsoncpp-src-0.5.0/lib64",
	 "-lboost_regex", "-L../../../third-party/boost_1_54_0/lib64/regex",
	 "-lfann", "-L../../../third-party/FANN-2.2.0/lib64",
         "-lwnb", "-L../../../third-party/wnb-0.6/lib64"
	]
    }
  ]
}
