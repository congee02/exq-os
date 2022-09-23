#!bin/bash
. ./os.conf

# 找到所有汇编、C源文件，和C头文件
C=$(find ../ -name "*.c")
S=$(find ../ -name "*.S")
H=$(find ../ -name "*.h")

echo ${C}
echo ${S}
echo ${H}

mkdir -p $SRC_DIR
mkdir -p $OBJC_DIR
mkdir -p $OBJS_DIR

# 将所有源文件复制入 SRC_DIR
\cp -f ${C} $SRC_DIR
\cp -f ${S} $SRC_DIR
\cp -f ${H} $SRC_DIR

SRCS=$(ls $SRC_DIR)

# 编译所有源文件为对象文件
for file in ${SRCS}  
do
    if [ "${file##*.}" = "S" ]; then
        i686-elf-gcc -c -I../includes ${SRC_DIR}/${file} -o $OBJS_DIR/$(basename ${file} .S).o -std=gnu99 -ffreestanding -O0 -Wall -Wextra
    fi

    if [ "${file##*.}" = "c" ]; then
        i686-elf-gcc -c -I../includes ${SRC_DIR}/${file} -o $OBJC_DIR/$(basename ${file} .c).o -std=gnu99 -ffreestanding -O0 -Wall -Wextra
    fi
done

# 连接所有对象为 bin 文件
i686-elf-gcc -T linker.ld -o $OS_NAME.bin -ffreestanding -O0 -nostdlib $OBJC_DIR/*.o $OBJS_DIR/*.o -lgcc

# 删除临时文件
rm -rf $OBJC_DIR
rm -rf $OBJS_DIR
rm -rf $SRC_DIR
