# Copyright (c) 2011 The Chromium OS Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be found
# in the LICENSE file.

ROOT := $(DESTDIR)/opt/Qualcomm
LIBDIR := $(DESTDIR)/usr/lib

sdk :
	$(MAKE) -C GobiConnectionMgmt
	$(MAKE) -C GobiImageMgmt

qdl :
	$(MAKE) -C GobiQDLService

install : sdk qdl
	$(MAKE) -C GobiConnectionMgmt install LIBDIR=$(LIBDIR)
	$(MAKE) -C GobiImageMgmt install LIBDIR=$(LIBDIR)
	$(MAKE) -C GobiQDLService install
