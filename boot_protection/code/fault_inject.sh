#!/bin/bash
#Run fault injection campaign for flash image
KERNEL=./linux-2.6.32.61/arch/arm/boot/uImage
SCRIPT=./script.img
FLASH=flash.img
FLASH_GOLD=flash.img_gold

#We only inject into the parts that contain our script and the kernel code
FLASH_SIZE=`expr $(stat -c%s $SCRIPT) + 2 \* $(stat -c%s $KERNEL)`
LOG_FILE=faults.log

for d in {1..100}; do
  RAND=`shuf -i 0-${FLASH_SIZE} -n 1`
  cp $FLASH_GOLD ./tmpflash
  #Flip a random bit
  ./flip ./tmpflash $RAND 
  cp ./tmpflash $FLASH
  sleep 4
done
