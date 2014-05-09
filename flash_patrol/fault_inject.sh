#!/bin/bash
./reset_testfs.sh
md5sum /mnt/inotify/fonz.txt  
sudo ./clear_cache.sh  
sudo ./github/ece542/flash_patrol/flip /dev/sdb1 2000000
sudo ./clear_cache.sh  
md5sum /mnt/inotify/fonz.txt
