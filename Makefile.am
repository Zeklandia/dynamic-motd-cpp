## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src po doc

dynamic_motd_cppdocdir = ${prefix}/doc/dynamic_motd_cpp


INTLTOOL_FILES = intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

EXTRA_DIST = $(dynamic_motd_cppdoc_DATA) \
	$(INTLTOOL_FILES)

DISTCLEANFILES = intltool-extract \
	intltool-merge \
	intltool-update \
	po/.intltool-merge-cache


# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(dynamic_motd_cppdocdir)
