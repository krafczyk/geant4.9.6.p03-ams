# $Id$
# $Name$
# ===========================================================
#   Makefile for building Geant4Py site-modules
# ===========================================================
include  ../config/config.gmk

SUBDIR := geometries materials processes physics_lists primaries
SUBDIR += utils python

.PHONY: all install clean

all:
	@for dir in $(SUBDIR); do (cd $$dir && $(MAKE)); done;:

install:
	@for dir in $(SUBDIR); do (cd $$dir && $(MAKE) install); done;:

clean:
	@for dir in $(SUBDIR); do (cd $$dir && $(MAKE) clean); done;:

