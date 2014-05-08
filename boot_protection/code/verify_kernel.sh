#U-boot script to verify copies of the kernel
#On the versatilePB, flash starts at 0x34000000

#Global Variables
FLASH_ADDR=0x34000000
BOOT_ARGS="console=ttyAMA0"
#Obtained from printf "0x%X\n" `stat -c%s ./script.img`
KERNEL_OFFSET=0x000003D5
#Easier than forcing u-boot to parse iminfo
KERNEL_SIZE=0x1a8300
NUM_IMAGES=3

#Now we'll try booting it from the beginning of flash
setenv bootargs $BOOT_ARGS
setexpr kernadd ${FLASH_ADDR} + ${KERNEL_OFFSET}
while test $NUM_IMAGES -gt "0"; do
  if imi ${kernadd} ; then
    echo "${kernadd} verified"
    setenv bootcmd bootm ${kernadd}
    run bootcmd
    exit #EXITS SCRIPT, SHOULD NEVER GET HERE
  fi
  setexpr kernadd ${kernadd} + ${KERNEL_SIZE} ;
  setexpr NUM_IMAGES ${NUM_IMAGES} - 1 ;
done

echo "NO CRC CHECKS PASSED! Booting the first and hoping for the best!"
setexpr kernadd ${FLASH_ADDR} + ${KERNEL_OFFSET}
setenv bootcmd bootm ${kernadd}
run bootcmd
