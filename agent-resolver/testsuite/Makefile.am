# Makefile.am for core/agent-resolver/testsuite

SUBDIRS = config lib ag_resolver.test tests

AM_CXXFLAGS = -DY2LOG=\"agent-resolver\"

PACKAGE = ag_resolver
AUTOMAKE_OPTIONS = dejagnu
export Y2DISABLELANGUAGEPLUGINS = 1
export top_srcdir

AM_CPPFLAGS = ${AGENT_INCLUDES}

noinst_PROGRAMS = runresolver

runresolver_SOURCES = runresolver.cc
runresolver_LDADD = ${AGENT_LIBADD}
runresolver_LDFLAGS = 					\
	-Xlinker --whole-archive			\
	../src/libpy2ag_resolver.la		\
	-Xlinker --no-whole-archive

clean-local:
	rm -f tmp.err.* tmp.out.* site.exp *.log *.sum *.bak

