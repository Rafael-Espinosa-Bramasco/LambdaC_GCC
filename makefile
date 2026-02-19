cc = gcc
flags = -Iinclude -Llib
srcs = $(wildcard src/*.c)

ws:
	rm -rf build/ && mkdir build/
	mkdir build/obj/
	mkdir build/lib/
	$(cc) -c $(srcs) $(flags)
	mv *.o build/obj/
	cp -r include/ build/include/
	ar rcs build/lib/liblda.a build/obj/*.o

.PHONY: c
c:
	rm -rf build/
	rm -f *.s