{
  "targets": [
    {
      "target_name": "addon",
      "sources": [ "addon.cc", "./src/answer.cc"],
      "include_dirs" : 
	["../stemmer", 
	 "../textpreprocessor", 
	 "../../third-party/libstemmer/include",
	 "../../include"
	], 

      "libraries" : 
	["-laskme", "-L../../lib", 
	 "-lstemmer", "-L../../../third-party/libstemmer/lib"]
    }
  ]
}
