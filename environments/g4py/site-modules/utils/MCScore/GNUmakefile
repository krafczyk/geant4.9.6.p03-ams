# $Id$
# $Name$
# ===========================================================
#   Makefile for building Geant4Py modules
# ===========================================================
include ../../../config/config.gmk

ifeq ($(Q_WITH_PYTHON3), 0)
  install_dir := $(Q_LIBDIR)/g4py

  include $(G4PY_INSTALL)/config/g4py.gmk
  include $(G4PY_INSTALL)/config/sys/$(Q_SYSTEM).gmk
  include $(G4PY_INSTALL)/config/script-install.gmk

else

.PHONY: all install clean 

all:
	@cd python3 && $(MAKE)

install:
	@cd python3 && $(MAKE) install

clean:
	@cd python3 && $(MAKE) clean

endif
