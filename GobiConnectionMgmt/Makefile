INCLUDES := -I ../Core -I ../Shared -lrt
QMICOREFLAGS := -D WDS_SUPPORT \
             -D DMS_SUPPORT \
             -D NAS_SUPPORT \
             -D PDS_SUPPORT \
             -D CAT_SUPPORT \
             -D RMS_SUPPORT \
             -D OMA_SUPPORT \
             -D UIM_SUPPORT \
             -D WMS_SUPPORT \
             -D IMG2K_SUPPORT \
             -D VOICE_SUPPORT
all: clean $(OUTPUT)

SOURCES := GobiConnectionMgmtExports.cpp \
        GobiConnectionMgmt.cpp \
        ../Shared/GobiQMICore.o \
        ../Shared/GobiQMICoreWDS.o \
        ../Shared/GobiQMICoreDMS.o \
        ../Shared/GobiQMICoreNAS.o \
        ../Shared/GobiQMICorePDS.o \
        ../Shared/GobiQMICoreCAT.o \
        ../Shared/GobiQMICoreRMS.o \
        ../Shared/GobiQMICoreOMA.o \
        ../Shared/GobiQMICoreImg2k.o \
        ../Shared/GobiQMICoreSMS.o \
        ../Shared/GobiQMICoreUIM.o \
        ../Shared/GobiQMIVoice.o \
        ../Shared/GobiMBNMgmt.o
OUTPUT := libGobiConnectionMgmt.so

all: $(OUTPUT)

include ../Core/core.mk
include ../Database/db.mk
include ../Shared/shared.mk

$(OUTPUT): $(SOURCES) $(LIBCORE) QMIDB.o
	@echo "  CXX $@"
	@$(CXX) $(CXXFLAGS) $(QMICOREFLAGS) $(INCLUDES) -shared -o $@ $^ -lpthread


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

install: $(OUTPUT) GobiConnectionMgmtAPI.h
	install -d $(PREFIX)/usr/lib
	install -t $(PREFIX)/usr/lib $(OUTPUT)
	install -d $(PREFIX)/usr/include/gobi
	install -t $(PREFIX)/usr/include/gobi $(filter %.h,$^)

clean:
	rm -f $(OUTPUT)

