####### Compiler, tools and options

CC            = arm-linux-gnueabihf-gcc
CXX           = arm-none-linux-gnueabi-g++
VERSION       = 0.2.6
DEFINES       = -DUSE_SDL -O3 -DLINUX -DVERSION=\"$(VERSION)\" -march=armv7-a -mcpu=cortex-a9 -mfloat-abi=softfp -mfpu=neon -mthumb-interwork
CFLAGS        = $(DEFINES)
INCPATH       =
LINK          = arm-none-linux-gnueabi-gcc
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS) -lm -static
AR            = arm-none-linux-gnueabi-ar cqs
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -sf
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

OBJECTS       = luvcview.o color.o utils.o gui.o avilib.o v4l2uvc.o osd.o ge2d.o colorkey.o key.o ge2d_multi_process.o
TARGET        = luvcview

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

clean:
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) $(TARGET)

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

