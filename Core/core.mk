CORESRCS := $(shell echo ../Core/*.cpp)
COREOBJS := $(patsubst %.cpp,%.o,$(CORESRCS))
LIBCORE := ../Core/libCore.a

../Core/%.o : ../Core/%.cpp
	@echo "  CXX $@"
	@$(CXX) $(CXXFLAGS) -c -o $@ $^

$(LIBCORE) : $(COREOBJS)
	@echo "  AR $@"
	@$(AR) rcs $@ $^
