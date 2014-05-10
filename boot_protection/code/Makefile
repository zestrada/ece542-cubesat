UBOOT="./u-boot-2013.10/u-boot.bin"
UBUILDARGS=ARCH=arm CROSS_COMPILE=arm-linux-gnu- #args when building Uboot
SCRIPT="verify_kernel.sh"
BOOTIMAGE="boot.img" #This is the -kernel arg for qemu
SCRIPTIMAGE="script.img" #This is the -kernel arg for qemu
NCOPIES="3" #How many copies of the kernel we want to store
QEMUARGS=-m 128M -M versatilepb -nographic #for 'make run'
FLASHIMG="flash.img" #The flash disk image
KERNEL=linux-3.2.57/arch/arm/boot/uImage
CORRUPTED_KERNEL=linux-3.2.57/arch/arm/boot/faultyuImage #image w/ flipped bits
INITRD=initrd.img
ROOT_CPIO=hello_root #cpio archive containing root filesystem

all: ${BOOTIMAGE}

${BOOTIMAGE}: ${UBOOT} ${INITRD}
	mkimage -A arm -T script -C none -n "Linux Verify" -d ${SCRIPT} ${SCRIPTIMAGE}
	cat ${UBOOT} ${INITRD} > ${BOOTIMAGE}

${UBOOT}: 
	make -C `dirname ${UBOOT}` ${UBUILDARGS} 1>/dev/null

flash:
	dd if=/dev/zero of=${FLASHIMG} bs=1M count=64
	cat ${SCRIPTIMAGE} ${KERNEL} ${KERNEL} ${KERNEL} > ./tmpKERNEL
	dd if=./tmpKERNEL of=${FLASHIMG} conv=notrunc
	rm -f tmpKERNEL

#A kernel without out U-boot script
noprotect:
	dd if=/dev/zero of=${FLASHIMG} bs=1M count=64
	cat ${KERNEL} ${KERNEL} ${KERNEL} > ./tmpKERNEL
	dd if=./tmpKERNEL of=${FLASHIMG} conv=notrunc
	rm -f tmpKERNEL

run:
	printf "Initrd stored at: 0x%X\n" `expr $$(stat -c%s ${UBOOT}) + 65536`
	printf "kernel size: %x\n" `stat -c\%s ${KERNEL}`
	qemu-system-arm ${QEMUARGS} -kernel ${BOOTIMAGE} -pflash ${FLASHIMG}

#No code reuse here, should fix in a future version. 
#Once u-boot environment invocation of a script is figured out, we can
#automatically test with multiple corrupted images
faulty:
	dd if=/dev/zero of=${FLASHIMG} bs=1M count=64
	cat ${SCRIPTIMAGE} ${CORRUPTED_KERNEL} ${KERNEL} ${KERNEL} > ./tmpKERNEL
	dd if=./tmpKERNEL of=${FLASHIMG} conv=notrunc
	rm -f tmpKERNEL

${INITRD}:
	mkimage -A arm -T ramdisk -C none -n "Hello World" -d ${INITRD_CPIO} ${INITRD}
