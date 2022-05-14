exec > "../logs/run.log" 2>&1

qemu-system-x86_64 -drive format=raw,file="../bin/JeffrOS.bin",index=0,if=floppy, -m 128M