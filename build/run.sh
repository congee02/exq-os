#!bin/bash
. ./os.conf

# 在虚拟机QEMU以cdrom的形式启动
qemu-system-i386 -cdrom $OS_NAME.iso

# 删除 iso 文件
rm $OS_NAME.iso