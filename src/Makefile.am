## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = smart

smart_SOURCES = \
	main.c \
	support.c support.h \
	interface.c interface.h \
	callbacks.c callbacks.h \
	capteur.c capteur.h \
	clientInd.c clientInd.h \
	clientPro.c clientPro.h \
	ouvrierAouady.c ouvrierAouady.h \
	Bestouv.c Bestouv.h \
	animal.c animal.h 

smart_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)

