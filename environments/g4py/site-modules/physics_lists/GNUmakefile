# $Id$
# $Name$
# ===========================================================
#   Makefile for building Geant4Py site-modules
# ===========================================================

SUBDIR := ExN01pl ExN03pl EMSTDpl

.PHONY: all install clean

all:
	@for dir in $(SUBDIR); do (cd $$dir && $(MAKE)); done;:

install:
	@for dir in $(SUBDIR); do (cd $$dir && $(MAKE) install); done;:

clean:
	@for dir in $(SUBDIR); do (cd $$dir && $(MAKE) clean); done;:

