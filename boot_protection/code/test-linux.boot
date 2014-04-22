#U-boot script to boot a simple linux image stored in flash
#On the versatilePB, flash starts at 0x34000000

#Global Variables
FLASH_ADDR=0x34000000
BOOT_ARGS="console=ttyAMA0"

#Now we'll try booting it from the beginning of flash
setenv bootcmd bootm $FLASH_ADDR
setenv bootargs $BOOT_ARGS
