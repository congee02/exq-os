#!bin/bash
. ./os.conf

# 为 grub-rescue 准备文件夹
mkdir -p $ISO_DIR/boot/grub
cp $OS_NAME.bin $ISO_DIR/boot/$OS_NAME.bin
cp grub.cfg $ISO_DIR/boot/grub/grub.cfg

# grub-rescue 输出 iso 文件
grub-mkrescue -o $OS_NAME.iso $ISO_DIR

# 删除临时文件
rm -rf ${ISO_DIR}
rm -rf ${OS_NAME}.bin