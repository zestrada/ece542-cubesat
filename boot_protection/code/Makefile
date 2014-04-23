UBOOT="./u-boot-2013.10/u-boot.bin"
UBUILDARGS=ARCH=arm CROSS_COMPILE=arm-linux-gnu- #args when building Uboot
SCRIPT="verify_kernel.sh"
BOOTIMAGE="boot.img" #This is the -kernel arg for qemu
NCOPIES="3" #How many copies of the kernel we want to store

all: ${BOOTIMAGE}

${BOOTIMAGE}: ${UBOOT} ${SCRIPT}
	mkimage -A arm -T script -C none -n "Linux Verify" -d ${SCRIPT} ${BOOTIMAGE}

${UBOOT}: 
	make -C `dirname ${UBOOT}` ${UBUILDARGS}
