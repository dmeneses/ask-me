#!/bin/sh
sudo apt-get install tcl-dev 
sudo apt-get install tk-dev
./configure
make 
sudo make install


