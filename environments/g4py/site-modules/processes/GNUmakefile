# $Id$
# $Name$
# ===========================================================
#   Makefile for building Geant4Py site-modules
# ===========================================================

SUBDIR := emcalculator

.PHONY: all install clean cleanlib

all:
	@for dir in $(SUBDIR); do (cd $$dir && $(MAKE)); done;:

install:
	@for dir in $(SUBDIR); do (cd $$dir && $(MAKE) install); done;:

clean:
	@for dir in $(SUBDIR); do (cd $$dir && $(MAKE) clean); done;:

