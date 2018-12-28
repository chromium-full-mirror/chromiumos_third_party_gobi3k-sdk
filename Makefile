# Copyright (c) 2011 The Chromium OS Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be found
# in the LICENSE file.

ROOT := $(DESTDIR)/opt/Qualcomm
PREFIX := $(DESTDIR)
LIBSUBDIR ?= lib
CXXFLAGS += -fPIC -Werror
# TODO(benchan): Gobi code has lots of other warnings, which should be cleaned
# up eventually.
CXXFLAGS += -Wno-switch

sdk :
	$(MAKE) -C GobiConnectionMgmt
	$(MAKE) -C GobiImageMgmt

qdl :
	$(MAKE) -C GobiQDLService

install : sdk qdl
	$(MAKE) -C Core install PREFIX=$(PREFIX)
	$(MAKE) -C GobiConnectionMgmt install PREFIX=$(PREFIX)
	$(MAKE) -C GobiImageMgmt install PREFIX=$(PREFIX)
	$(MAKE) -C GobiQDLService install
	$(MAKE) -C Tools install PREFIX=$(PREFIX)
