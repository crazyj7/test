# Mobile Native Code sample
## How to make native library for all platforms.  
## support ; linux, android, ios  
## cross compile 

## Build
makejni.sh  
make linux  
make androidtotal  
make iostotal   (copy to macbook and build)  

## Sample Test
```
$ ./apptest
testAuth: landmark size=10
testAuth: landmark2 size=10
testAuth return=0

$ ./apptestjava.sh
JAVA:call native
testNative:Hello
JAVA:call native
JAVA:result from C:hello cj

```


## Requirements  
```
+ 빌드 환경
1. OS: Centos 7 (x86_64)
2. NDK 다운로드 및 설치
ndk$ wget http://dl.google.com/android/ndk/android-ndk-r10e-linux-x86_64.bin
ndk$ chmod a+x android-ndk-r10e-linux-x86_64.bin
ndk$ ./android-ndk-r10e-linux-x86_64.bin


3. 32비트 arm용 toolchain 패키지 추출
ndk$ cd android-ndk-r10e/build/tools
ndk$ ./make-standalone-toolchain.sh --arch=arm --ndk-dir=../../ --system=linux-x86_64
...
Creating package file: /tmp/ndk-root/arm-linux-androideabi-4.8.tar.bz2


*생성한 툴을 상위 디렉터리로 복사
ndk$ cd ../../.. && cp -rf [생성된패키지경로명] .
ndk$ tar xvfj arm-linux-androideabi-4.8.tar.bz2 


3. 64비트 arm64용 toolchain 패키지 추출
root@crazyj tools]# ./make-standalone-toolchain.sh --arch=arm64 --ndk-dir=../../ --system=linux-x86_64
Auto-config: --toolchain=aarch64-linux-android-4.9
Copying prebuilt binaries...
Copying sysroot headers and libraries...
creating package file : /tmp/ndk-root/aarch64-linux-android-4.9.tar.bz2


# cd ../../.. && cp -rf [생성된패키지경로명] .
# tar xvfj aarch64-linux-android-4.9.tar.bz2


4. 환경변수 설정


#set
ANDROID_HOME_NDK=/home/crazyj/arm-linux-androideabi-4.8
ANDROID_NDK_ROOT=/home/crazyj/android-ndk-r10e
ANDROID_NDK_TOOLCHAIN=/home/crazyj/arm-linux-androideabi-4.8
ANDROID_NDK_TOOLCHAIN64=/home/crazyj/aarch64-linux-android-4.9

PATH=/home/crazyj/arm-linux-androideabi-4.8/bin:/home/crazyj/aarch64-linux-android-4.9/bin


5. gcc 테스트
$ arm-linux-androideabi-gcc -v
$ aarch64-linux-android-gcc -v

```
