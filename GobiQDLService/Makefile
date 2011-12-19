INCLUDES := -I ../Shared -I ../Core -lrt
SOURCES := Main.cpp ../Shared/GobiQDLCore.cpp ../Shared/GobiMBNMgmt.cpp
OUTPUT := GobiQDLService

all: $(OUTPUT)

include ../Core/core.mk

$(OUTPUT): $(SOURCES) $(LIBCORE)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ -lpthread

# Must set ANROID_PATH variable
Android: 
	$(MAKE) $(MFLAGS) \
      PATH=$(PATH):$(ANDROID_PATH) \
      CXX=arm-linux-androideabi-g++ \
      AR=arm-linux-androideabi-ar \
      CXXFLAGS=-Wunused-variable \
      INCLUDES="-I ../Core -I ../Shared -L. -lCore" \
      all

debug: 
	$(MAKE) $(MFLAGS) CXXFLAGS="$(CXXFLAGS) $(DEBUGFLAGS)" all

install: $(OUTPUT)
	mkdir -p $(ROOT)/Gobi/GobiQDLService
	cp -f $(OUTPUT) $(ROOT)/Gobi/GobiQDLService

clean:
	rm -f $(OUTPUT)
