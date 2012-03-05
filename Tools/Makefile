# Copyright (c) 2010 The Chromium OS Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

BINDIR = $(PREFIX)/opt/Qualcomm/bin

INCLUDES := -I. -I.. -I../Core
LIBS := -L. -lGobiConnectionMgmt

CFLAGS := $(CFLAGS) $(INCLUDES)
CFLAGS := $(CFLAGS) -Wall -Wextra

all : gobi-factory-reset sdk-stress open-deauth powercycle-all-gobis

gobi-factory-reset : gobi-factory-reset.c libGobiConnectionMgmt.so
	$(CC) $(CFLAGS) -o $@ $(filter %.c,$^) $(LIBS)

sdk-stress : sdk-stress.c libGobiConnectionMgmt.so
	$(CC) $(CFLAGS) -o $@ $(filter %.c,$^) $(LIBS)

open-deauth : open-deauth.c libGobiConnectionMgmt.so
	$(CC) $(CFLAGS) -o $@ $(filter %.c,$^) $(LIBS) -lpthread

libGobiConnectionMgmt.so:
	ln -s ../GobiConnectionMgmt/libGobiConnectionMgmt.so $@

install : all
	install -D gobi-factory-reset $(BINDIR)/gobi-factory-reset
	install -D sdk-stress $(BINDIR)/sdk-stress
	install -D open-deauth $(BINDIR)/open-deauth
	install -D powercycle-all-gobis $(BINDIR)/powercycle-all-gobis
