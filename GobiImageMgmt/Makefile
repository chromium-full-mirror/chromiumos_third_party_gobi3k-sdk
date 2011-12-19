INCLUDES := -I ../Core -I ../Shared -lrt
QMICOREFLAGS := -D IMG_SUPPORT
SOURCES := GobiImageMgmtExports.cpp \
        GobiImageMgmt.cpp \
        ../Shared/GobiQMICore.o \
        ../Shared/GobiQMICoreImg.o \
        ../Shared/GobiQDLCore.o \
        ../Shared/GobiMBNMgmt.o
OUTPUT := libGobiImageMgmt.so

all: $(OUTPUT)

include ../Core/core.mk
include ../Database/db.mk
include ../Shared/shared.mk

$(OUTPUT): $(SOURCES) $(LIBCORE) QMIDB.o
	@echo "  CXX $@"
	@$(CXX) $(CXXFLAGS) $(QMICOREFLAGS) $(INCLUDES) -shared -o $@ $^

# Must set ANDROID_PATH variable
Android:
	$(MAKE) $(MFLAGS) \
      PATH=$(PATH):$(ANDROID_PATH) \
      CXX=arm-linux-androideabi-g++ \
      LD=arm-linux-androideabi-ld \
      AR=arm-linux-androideabi-ar \
      CXXFLAGS=-Wunused-variable \
      LDFLAGS=-marmelf_linux_eabi \
      INCLUDES="-I ../Core -I ../Shared -L. -lCore" \
      all

install: $(OUTPUT) GobiImageMgmtAPI.h
	install -d $(PREFIX)/usr/lib
	install -t $(PREFIX)/usr/lib $(OUTPUT)
	install -d $(PREFIX)/usr/include/gobi
	install -t $(PREFIX)/usr/include/gobi $(filter %.h,$^)

clean:
	rm -f $(OUTPUT)
