#!/bin/bash
./reset_testfs.sh
sudo chown zak /mnt/inotify
mkdir /mnt/inotify/cubesat/
for f in /home/zak/cubesat/data/*; do
  cp ${f} /mnt/inotify/cubesat/
  sleep 0.05
done
sudo ./clear_cache.sh  
sudo ./github/ece542/flash_patrol/flip /dev/sdb1 2000000
sudo ./clear_cache.sh  
