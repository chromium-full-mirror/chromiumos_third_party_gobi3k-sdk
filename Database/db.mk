QMIDBPATH := ../Database/QMI/

QMIDBSRCS := $(shell echo $(QMIDBPATH)*.txt)

QMIDB.o: $(QMIDBSRCS)
	cp -rf $(QMIDBPATH) .
# Amusingly, the armv7a ld(1) tosses up an internal error when trying to
# link with -b binary; it appears to treat all its commandline arguments
# as arm ELF binaries regardless of whether they are or not.
# You can test for the presence of this bug with:
#  $ echo foo > foo.txt
#  $ armv7a-cros-linux-gnueabi-ld -r -b binary -o foo foo.txt
# If that bug goes away, we can go back to using ld for this instead of
# generating a .S file. Woo!
	rm -f dbfiles.S
	for file in $(QMIDBSRCS) ; do \
		filebase=$${file%.txt} ; \
		name=$${filebase#$(QMIDBPATH)} ; \
		echo ".global _binary_QMI_$${name}_txt_start" >> dbfiles.S ; \
		echo "_binary_QMI_$${name}_txt_start:" >> dbfiles.S ; \
		echo ".incbin \"$${file}\"" >> dbfiles.S ; \
		echo ".global _binary_QMI_$${name}_txt_end" >> dbfiles.S ; \
		echo "_binary_QMI_$${name}_txt_end:" >> dbfiles.S ; \
	done
# There doesn't seem to be a way to get gcc to build us with
# noexecstack, so we'll force it off here by sticking the relevant
# section into the .S file...
	echo '.section .note.GNU-stack,"",%progbits' >> dbfiles.S
	$(CXX) $(CFLAGS) -c -o $@ dbfiles.S

