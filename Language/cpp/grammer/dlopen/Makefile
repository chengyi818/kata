CC = arm-linux-androideabi-g++
LD = arm-linux-androideabi-ld
CFLAGS  := -Wall -O3 -std=c++11 -fPIE -fPIC -fvisibility=hidden -Wno-unknown-pragmas \
	-I /home/chengyi/Android/Sdk/ndk-bundle/sources/cxx-stl/gnu-libstdc++/4.9/include \
	-I /home/chengyi/Android/Sdk/ndk-bundle/sources/cxx-stl/gnu-libstdc++/4.9/libs/armeabi-v7a/include \
	-I /home/chengyi/Android/Sdk/ndk-bundle/platforms/android-22/arch-arm/usr/include \

LDFLAGS = -shared \
-L/home/chengyi/Android/Sdk/ndk-bundle/platforms/android-22/arch-arm/usr/lib \
-L/home/chengyi/Android/Sdk/ndk-bundle/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/lib/gcc/arm-linux-androideabi/4.9.x/armv7-a \

OBJS = point.o
LIB = libpoint.so

# main: $(LIB)
# 	$(CC) $(CFLAGS) -g main.cc -o main.o

$(LIB): $(OBJS)
	rm -f $@
	$(LD) $(LDFLAGS) -o $@ $(OBJS)
	rm $(OBJS)

$(OBJS):
	$(CC) $(CFLAGS)  -c point.cc -o $(OBJS)

clean:
	rm *.out *.so *.o
