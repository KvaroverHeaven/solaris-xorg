###############################################################################
#
# X Window System standard bitmaps
#
# Copyright (c) 2006, 2015, Oracle and/or its affiliates. All rights reserved.
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice (including the next
# paragraph) shall be included in all copies or substantial portions of the
# Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
#
#

# Package name used in tarballs
MODULE_NAME=xbitmaps

# Package metadata
MODULE_DESC = bitmap images from X.Org
GIT_URL     = $(XORG_GIT_URL)/data/bitmaps
GIT_URL_SET = yes

# Version number (used in path names)
MODULE_VERSION=1.1.1

# Checksums for upstream tarball
TARBALL_MD5  = 7444bbbd999b53bec6a60608a5301f4c
TARBALL_SHA1 = 578afff7e4912192b524c25254cf7f54c16e57d8

# Patches to apply to source after unpacking, in order
SOURCE_PATCHES=	

# bitmap pkg-config files are architecture independent, so install in share
MODULE_PKGCONFIG_DIR=$(PKGCONFIG_DIR_SHARE)
MODULE_PKGCONFIG_DIR_SET=yes

### Include common rulesets
include ../Makefile.inc

