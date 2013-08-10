## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src po

dynmotd_cppdocdir = ${prefix}/doc/dynmotd_cpp
dynmotd_cppdoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS


INTLTOOL_FILES = intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

EXTRA_DIST = $(dynmotd_cppdoc_DATA) \
	$(INTLTOOL_FILES)

DISTCLEANFILES = intltool-extract \
	intltool-merge \
	intltool-update \
	po/.intltool-merge-cache


# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(dynmotd_cppdocdir)
