
DIRS=src
RECURSIVE_TARGETS=debug release install install-debug install-release clean

default : $(DIRS)
	@for f in $(DIRS); do cd $$f; $(MAKE) $@ || exit 1; cd ..; done

$(RECURSIVE_TARGETS) :  $(DIRS)
	@for f in $(DIRS); do cd $$f; $(MAKE) $@ || exit 1; cd ..; done

