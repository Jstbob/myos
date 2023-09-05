# objdump -s --section=.text <input_file> > <output_file>
# readelf --hex-dump=.text boot.o
# objcopy -O binary --only-section=.text /path/firmware.ko /content.bin
dump:
	gcc -nostdlib boot.s -c
	objcopy -O binary --only-section=.text boot.o boot.img

# -drive file=fs.img,index=0,media=disk,format=raw
qemu-debug: dump
	qemu-system-i386 -drive file=boot.img,index=0,media=disk,format=raw -s -S

.PHONY:
clean:
	rm *.o *.img *.img.* -f
