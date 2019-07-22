################################################
# testAuth
################################################
# ** Build
# make linux		; glibc 2.23
# make androidtotal	; android
# make iostotal	; ios
#

CC=g++
IOS_CC=clang
ANDROID_CC=arm-linux-androideabi-g++
ANDROID_CC64=aarch64-linux-android-g++

##################################################
# linux full result! for analyze system!!!!!!
HEADER=-I. -I../cg/include -I/usr/java/latest/include -I/usr/java/latest/include/linux -D_LINUX_ 
LIB=-L. -L/usr/local/lib
LIBA=-L. -llog

# -O2 ; speed
# -g ; debug
# -Os ; size

# LINUX flag
CFLAGS=-w -O2 -fPIC -ffunction-sections -fdata-sections $(HEADER) -g -std=c++11
CFLAGS21=-w -O2 -fPIC -ffunction-sections -fdata-sections $(HEADER) -g


# ANDROID flag
ACFLAGS=-w -Os -fPIC -ffunction-sections -fdata-sections -D_ANDROID_ $(HEADER) -std=c++11
ALDFLAGS=-Wl,--gc-sections

# iOS32 simulator
ICFLAGS32S=-Wall -W -O2 -g $(HEADER) -arch i386 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator.sdk -mios-simulator-version-min=7.0 -fobjc-abi-version=2 
# iOS64 simulator
ICFLAGS64S=-Wall -W -O2 -g $(HEADER) -arch x86_64 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator.sdk -mios-simulator-version-min=7.0 -fobjc-abi-version=2 

# ios32
ICFLAGS32=-Wall -W -O2 $(HEADER) -arch armv7 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS.sdk -mios-version-min=7.0 -fobjc-abi-version=2 
# ios64
ICFLAGS64=-Wall -W -O2 $(HEADER) -arch arm64 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS.sdk -mios-version-min=7.0 -fobjc-abi-version=2 

LD=ld
SO=libtest
SO2=test
MAJORVER=1
MINERVER=0
PATCHVER=0
OUTLIB=$(SO).a
SONAME=$(SO).so
SONAMEVER=$(SO).so.$(MAJORVER).$(MINERVER).$(PATCHVER)
JNISONAME=libtestjni.so

OBJ=test.o 
OBJ_IOS=test.o
JNIOBJ=com_my_app_testNative.o

.SUFFIXES : .c .o
.SUFFIXES : .cpp .o

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<
.cpp.o:
	$(CC) $(CFLAGS) -c -o $@ $<

all: 
	make alll "LIBA=$(LIB)"
	cp $(SONAME) $(SONAME).linux
	cp $(JNISONAME) $(JNISONAME).linux

linux: all

install: /usr/bin
	@echo "copy to lib path(usr/local/lib)"
	cp $(SONAME).linux /usr/local/lib/$(SONAME)
	cp $(JNISONAME).linux /usr/local/lib/$(JNISONAME)


# linux glibc 2.4 over
alll: clean lib jnilib apptest

alla: clean liba jniliba

alli: clean libi 

ios:
	make alli "CC=$(IOS_CC)" "OBJ=$(OBJ_IOS)" "CFLAGS=$(ICFLAGS64) " "LDFLAGS="
	cp $(OUTLIB) $(OUTLIB).ios64

ios32:
	make alli "CC=$(IOS_CC)" "OBJ=$(OBJ_IOS)" "CFLAGS=$(ICFLAGS32) -m32" "LDFLAGS=-m32"
	cp $(OUTLIB) $(OUTLIB).ios32

ioss:
	make alli "CC=$(IOS_CC)" "OBJ=$(OBJ_IOS)" "CFLAGS=$(ICFLAGS64S)" "LDFLAGS="
	cp $(OUTLIB) $(OUTLIB).ios64s

ios32s:
	make alli "CC=$(IOS_CC)" "OBJ=$(OBJ_IOS)" "CFLAGS=$(ICFLAGS32S) -m32" "LDFLAGS=-m32"
	cp $(OUTLIB) $(OUTLIB).ios32s

iostotal:
	make ios
#	make ioss
	make ios32
#	make ios32s
#	libtool $(OUTLIB).ios64 $(OUTLIB).ios32 $(OUTLIB).ios64s $(OUTLIB).ios32s -o $(OUTLIB).iostotal
	libtool $(OUTLIB).ios64 $(OUTLIB).ios32 -o $(OUTLIB).iostotal

android32:
	make alla "CC=$(ANDROID_CC)" "CFLAGS=$(ACFLAGS)" "LDFLAGS=$(ALDFLAGS)"
	cp $(SONAME) $(SONAME).android32
	cp $(JNISONAME) $(JNISONAME).android32

android64:
	make alla "CC=$(ANDROID_CC64)" "CFLAGS=$(ACFLAGS)" "LDFLAGS=$(ALDFLAGS)"
	cp $(SONAME) $(SONAME).android64
	cp $(JNISONAME) $(JNISONAME).android64

androidtotal:
	make android32
	make android64

jnilib: $(JNIOBJ)
	$(CC) -shared -o $(JNISONAME) $(JNIOBJ) -L./ -l$(SO2) $(LIB)

jniliba: $(JNIOBJ)
	$(CC) -shared $(LDFLAGS) -o $(JNISONAME) $(JNIOBJ) -L./ -l$(SO2) $(LIBA)

com_my_app_test.o: com_my_app_testNative.cpp
	$(CC) -c $(CFLAGS) $<

lib: $(OBJ)
	$(CC) -shared -o $(SONAME) $(OBJ) $(LIB)

liba: $(OBJ)
	$(CC) -shared $(LDFLAGS) -o $(SONAME) $(OBJ) $(LIBA)

libi: $(OBJ)
	ar -crs $(OUTLIB) $(OBJ)

object:$(OBJ)
	$(CC) -c $(CFLAGS) $<

apptest:apptest.o $(SONAME)
	-rm -f test.log
	$(CC) -o apptest apptest.o $(SONAME) $(LIB)

clean:
#	ctags -R
	rm -rf *.o
	rm -rf *.so
	rm -rf $(OUTLIB)
	rm -rf $(SONAME)
	rm -rf $(JNISONAME)
	rm -rf apptest
      
