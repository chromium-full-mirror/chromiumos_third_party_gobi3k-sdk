SHAREDSRCS := $(shell echo ../Shared/*.cpp)
SHAREDOBJS := $(patsubst %.cpp,%.o,$(SHAREDOBJS))

../Shared/%.o : ../Shared/%.cpp
	@echo "  CXX $@"
	@$(CXX) $(CXXFLAGS) $(QMICOREFLAGS) -I ../Core -I ../Shared -c -o $@ $^
