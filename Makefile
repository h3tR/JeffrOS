## Compiler
CC=/usr/local/i386elfgcc/bin/i386-elf-gcc
## Linker
LD=/usr/local/i386elfgcc/bin/i386-elf-ld


SRC=./src
## Directory to write binaries to
BUILD=./build
## Compiler Flags
FLAGS=-ffreestanding -m32 -g

## C++ source files
CPPSRC := $(shell find ./ -name "*.cpp")
## C++ target files
CPPTAR := $(patsubst %.cpp,%.o,$(CPPSRC))

## Assembly source files that must be compiled to ELF
ASMSRC:= $(SRC)/asmlibs/ISR_asm.asm 
## Assembly target files
ASMTAR := $(subst $(SRC), $(BUILD)/src,$(patsubst %.asm, %.o, $(ASMSRC)))

## Files which must be linked first, if things break just bodge it together
LDPRIORITY := $(BUILD)/src/kernel/kernel.o

all: prebuild build run

prebuild:	## Prebuild instructions
	clear
	rm -rf $(BUILD)
	mkdir $(BUILD)

build: boot $(ASMTAR) $(CPPTAR)
	$(LD) -o $(BUILD)/kernel.bin -Ttext 0x1000 $(LDPRIORITY) --start-group $(filter-out $(LDPRIORITY),$(shell find ./ -name "*.o" | xargs)) --end-group --oformat binary --entry main
	cat $(BUILD)/boot.bin $(BUILD)/kernel.bin $(BUILD)/padding.bin> ./bin/JeffrOS.bin

boot:
	nasm $(SRC)/boot/boot.asm -f bin -o $(BUILD)/boot.bin -i $(SRC)
	nasm $(SRC)/boot/padding.asm -f bin -o $(BUILD)/padding.bin

%.o: %.cpp
	mkdir -p $(BUILD)/$(shell dirname $<)
	$(CC) $(FLAGS) -c $< -o $(BUILD)/$(subst .cpp,.o,$<) $(addprefix -I ,$(shell dirname $(shell echo $(CPPSRC) | tr ' ' '\n' | sort -u | xargs)))

$(ASMTAR): $(ASMSRC)
	mkdir -p $(BUILD)/$(shell dirname $<)
	nasm $< -f elf -o $(BUILD)/$(subst .asm,.o,$<)

run:
	qemu-system-x86_64 -drive format=raw,file=./bin/JeffrOS.bin,index=0,if=floppy,  -m 128M