export PATH=$PATH:/usr/local/i386elfgcc/bin

touch "../logs/compile.log"
chmod +rwx "../logs/compile.log"
exec > "../logs/compile.log" 2>&1

echo "Assembling bootsector..."
touch "../build/boot.bin"
chmod +rwx "../build/boot.bin"
nasm -f bin "../project/boot/boot.asm" -i "../project" -o "../build/boot.bin"

# assemble padding
touch "../build/padding.bin"
chmod +rwx "../build/padding.bin"
nasm "../project/boot/padding.asm" -f bin -o "../build/padding.bin"

echo "Compiling kernel..."
touch "../build/kernel.o"
chmod +rwx "../build/kernel.o"
i386-elf-gcc -ffreestanding -m32 -g -c "../project/kernel/kernel.cpp" -o "../build/kernel.o"

echo "Linking Kernel..."
i386-elf-ld -o "../build/kernel.bin" -Ttext 0x1000 "../build/kernel.o" --oformat binary --entry main

echo "Concatenating binaries..."
cat "../build/boot.bin" "../build/kernel.bin" "../build/padding.bin" > "../bin/JeffrOS.bin"
echo "Build complete!"

