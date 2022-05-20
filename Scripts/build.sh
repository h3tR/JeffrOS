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

touch $BUILD"IDT.o"
chmod +rwx $BUILD"IDT.o"
i386-elf-gcc -ffreestanding -m32 -g -c "../project/kernel/interrupts/IDT.cpp" -o $BUILD"IDT.o"

touch $BUILD"ISR.o"
chmod +rwx $BUILD"ISR.o"
i386-elf-gcc -ffreestanding -m32 -g -c "../project/kernel/interrupts/ISR.cpp" -o $BUILD"ISR.o"

touch $BUILD"Heap.o"
chmod +rwx $BUILD"Heap.o"
i386-elf-gcc -ffreestanding -m32 -g -c "../project/kernel/Heap.cpp" -o $BUILD"Heap.o"


touch $BUILD"isr.bin"
chmod +rwx $BUILD"isr.bin"
nasm -felf32 "../project/asmlibs/ISR.asm" -o $BUILD"ISR_asm.o"

echo "Compiling Drivers..."
    echo "  -portIO"
    touch $BUILD"portIO.o"
    chmod +rwx $BUILD"portIO.o"
    i386-elf-gcc -ffreestanding -m32 -g -c "../project/drivers/portIO.cpp" -o $BUILD"portIO.o"

    echo "  -VGA"
    touch $BUILD"VGA.o"
    chmod +rwx $BUILD"VGA.o"
    i386-elf-gcc -ffreestanding -m32 -g -c "../project/drivers/VGA.cpp" -o $BUILD"VGA.o"

echo "Compiling Libraries..."
    echo "  -math"
    touch $BUILD"math.o"
    chmod +rwx $BUILD"math.o"
    i386-elf-gcc -ffreestanding -m32 -g -c "../project/libraries/math.cpp" -o $BUILD"math.o"

    echo "  -string"
    touch $BUILD"string.o"
    chmod +rwx $BUILD"string.o"
    i386-elf-gcc -ffreestanding -m32 -g -c "../project/libraries/string.cpp" -o $BUILD"string.o"

    


echo "Linking Kernel..."
touch $BUILD"kernel.bin"
chmod +rwx $BUILD"kernel.bin"
i386-elf-ld -o $BUILD"kernel.bin" -Ttext 0x1000 $BUILD"kernel.o" $BUILD"Heap.o" $BUILD"portIO.o" $BUILD"VGA.o" $BUILD"IDT.o" $BUILD"ISR.o" $BUILD"ISR_asm.o" $BUILD"math.o" $BUILD"string.o" --oformat binary --entry main

echo "Concatenating binaries..."
cat $BUILD"boot.bin" $BUILD"kernel.bin" $BUILD"padding.bin" > "../bin/JeffrOS.bin"
echo "Build complete!"

