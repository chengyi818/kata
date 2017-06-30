#!/bin/bash

/bin/rm -rf ~/temp/release
scp -r chengyi@192.168.128.73:~/code/wheeljack3/release ~/temp
rm ~/temp/release/database/wheeljack_dynamic_info.db

sudo rm /usr/local/bin/mario
sudo rm -rf /usr/local/lib/python3.4/dist-packages/Mario*
sudo pip3 install ~/temp/release/software/Mario*.whl

