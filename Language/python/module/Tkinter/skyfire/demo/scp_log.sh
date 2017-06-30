#!/bin/bash

cd ~/temp; \
tar zcvf log_classified.tgz ./log_classified
scp ~/temp/log_classified.tgz lj@192.168.128.88:~

