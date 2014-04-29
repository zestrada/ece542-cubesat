UBOOT="./u-boot-2013.10/u-boot.bin"
UBUILDARGS=ARCH=arm CROSS_COMPILE=arm-linux-gnu- #args when building Uboot
SCRIPT="verify_kernel.sh"
BOOTIMAGE="boot.img" #This is the -kernel arg for qemu
SCRIPTIMAGE="script.img" #This is the -kernel arg for qemu
NCOPIES="3" #How many copies of the kernel we want to store
QEMUARGS=-m 128M -M versatilepb -nographic #for 'make run'
FLASHIMG="flash.img" #The flash disk image

all: ${BOOTIMAGE}

${BOOTIMAGE}: ${UBOOT}
	mkimage -A arm -T script -C none -n "Linux Verify" -d ${SCRIPT} ${SCRIPTIMAGE}
	cat ${UBOOT} ${SCRIPTIMAGE} > ${BOOTIMAGE}

${UBOOT}: 
	make -C `dirname ${UBOOT}` ${UBUILDARGS} 1>/dev/null

run: ${BOOTIMAGE}
	echo 'Script stored at: '
	printf "0x%X\n" `expr $$(stat -c%s ${UBOOT}) + 65536`
	qemu-system-arm ${QEMUARGS} -kernel ${BOOTIMAGE} -pflash ${FLASHIMG}
