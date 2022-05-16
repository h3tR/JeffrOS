export PATH=$PATH:/usr/local/i386elfgcc/bin
export BUILD="../build/"

touch "../logs/compile.log"
chmod +rwx "../logs/compile.log"
exec > "../logs/compile.log" 2>&1

echo "Assembling bootsector..."
touch $BUILD"boot.bin"
chmod +rwx $BUILD"boot.bin"
nasm -f bin "../project/boot/boot.asm" -i "../project" -o $BUILD"boot.bin"

# assemble padding
touch $BUILD"padding.bin"
chmod +rwx $BUILD"padding.bin"
nasm "../project/boot/padding.asm" -f bin -o $BUILD"padding.bin"

# compile cpp code
echo "Compiling kernel..."
touch $BUILD"kernel.o"
chmod +rwx $BUILD"kernel.o"
i386-elf-gcc -ffreestanding -m32 -g -c "../project/kernel/kernel.cpp" -o $BUILD"kernel.o"

echo "Compiling Drivers..."
    echo "  -portIO"
    touch $BUILD"portIO.o"
    chmod +rwx $BUILD"portIO.o"
    i386-elf-gcc -ffreestanding -m32 -g -c "../project/drivers/portIO.cpp" -o $BUILD"portIO.o"

    echo "  -VGA"
    touch "$BUILDVGA.o"
    chmod +rwx $BUILD"VGA.o"
    i386-elf-gcc -ffreestanding -m32 -g -c "../project/drivers/VGA.cpp" -o $BUILD"VGA.o"


echo "Linking Kernel..."
touch $BUILD"kernel.bin"
chmod +rwx $BUILD"kernel.bin"
i386-elf-ld -o $BUILD"kernel.bin" -Ttext 0x1000 $BUILD"kernel.o" $BUILD"portIO.o" $BUILD"VGA.o" --oformat binary --entry main

echo "Concatenating binaries..."
cat $BUILD"boot.bin" $BUILD"kernel.bin" $BUILD"padding.bin" > "../bin/JeffrOS.bin"
echo "Build complete!"

