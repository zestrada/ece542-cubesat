#!/bin/bash
. patrol-cubesat.env
make kill
~/reset_testfs.sh
sudo chown zak /mnt/inotify
NBYTES=`df -B1 /mnt/inotify |grep sdb | awk '{print $2}'`
make run
sleep 1
find /home/zak/cubesat/data/ -type f -exec cp {} /mnt/inotify/ \;
sudo ~/clear_cache.sh  
sleep 2
RAND=`shuf -i 0-${NBYTES} -n 1`
sudo ./flip /dev/sdb1 $RAND
sudo ~/clear_cache.sh  
