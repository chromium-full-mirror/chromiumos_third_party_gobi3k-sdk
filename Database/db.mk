QMIDBSRCS := $(shell echo ../Database/QMI/*.txt)

QMIDB.o: $(QMIDBSRCS)
	@cp ../Database/QMI ./ -rf
	@echo "  LD $@"
	@$(LD) $(LDFLAGS) -r -b binary -o $@ $(patsubst ../Database/%,%,$^)
	@rm QMI -rf

