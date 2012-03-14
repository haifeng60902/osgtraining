TOPDIR=.

CFLAGS=-nologo -Gm -EHsc -W3
DEFS=-DWINDOWS -D_WIN32 -D_CONSOLE -D_MBCS
SHARED=-DLL
PRGFLAGS=-SUBSYSTEM:CONSOLE -OPT:REF -OPT:ICF
LDFLAGS=-nologo
CC=cl
LD=link
INSTALL=install

DEST=$(TOPDIR)/../../sdk
DESTBIN=$(DEST)/bin
DESTBINDBG=$(DESTBIN)/debug
DESTBINREL=$(DESTBIN)/release
DESTLIB=$(DEST)/lib
DESTLIBDBG=$(DESTLIB)/debug
DESTLIBREL=$(DESTLIB)/release
DESTINC=$(DEST)/inc

LUA_A=	lua51.lib
LUA_D=	lua51.dll
LUA_E=	lua51.exp
LUA_P=	lua51.pdb
CORE_O=	lapi.obj lcode.obj ldebug.obj ldo.obj ldump.obj lfunc.obj lgc.obj \
	llex.obj lmem.obj lobject.obj lopcodes.obj lparser.obj lstate.obj \
	lstring.obj ltable.obj ltm.obj lundump.obj lvm.obj lzio.obj print.obj
LIB_O=	lauxlib.obj lbaselib.obj ldblib.obj liolib.obj lmathlib.obj \
	loslib.obj ltablib.obj lstrlib.obj loadlib.obj linit.obj

HEADERS=lua.h lua.hpp luaconf.h lualib.h lauxlib.h

LUA_T=	lua.exe
LUA_O=	lua.obj

LUAC_T=	luac.exe
LUAC_O=	luac.obj

ALL_O= $(CORE_O) $(LIB_O) $(LUA_O) $(LUAC_O)
ALL_T= $(LUA_A) $(LUA_T) $(LUAC_T)
ALL_A= $(LUA_A)


default: debug release

ifeq ($(MODE),debug)
CFLAGS += -MDd -Od -RTC1 -ZI
DEFS += -D_DEBUG
LDFLAGS += -DEBUG
else
CFLAGS += -O2 -MD -Zi
DEFS += -DNDEBUG
endif


%.obj: ../%.c
	$(CC) $(CFLAGS) $(DEFS) -c $<

debug: debug-$(LUA_A) debug-$(LUAC_T) debug-$(LUA_T)

release: release-$(LUA_A) release-$(LUAC_T) release-$(LUA_T)

release-$(LUA_A):
	@[ -d release ] || mkdir release
	@cd release ; $(MAKE) -f ../GNUmakefile TOPDIR=../$(TOPDIR) MODE=release $(LUA_A)

debug-$(LUA_A):
	@[ -d debug ] || mkdir debug
	@cd debug ; $(MAKE) -f ../GNUmakefile TOPDIR=../$(TOPDIR) MODE=debug $(LUA_A)

$(LUA_A): 
$(LUA_A): $(CORE_O) $(LIB_O)
	$(LD) $(SHARED) $(LDFLAGS) $(LIBS) $(CORE_O) $(LIB_O) -IMPLIB:$(LUA_A) -OUT:$(LUA_D)

release-$(LUA_T):
	@[ -d release ] || mkdir release
	@cd release ; $(MAKE) -f ../GNUmakefile TOPDIR=../$(TOPDIR) MODE=release $(LUA_T)

debug-$(LUA_T):
	@[ -d debug ] || mkdir debug
	@cd debug ; $(MAKE) -f ../GNUmakefile TOPDIR=../$(TOPDIR) MODE=debug $(LUA_T)

$(LUA_T): $(LUA_O) $(LUA_A)
	$(LD) $(LDFLAGS) $(PRGFLAGS) $(LIBS) $(LUA_O) $(LUA_A) -OUT:$(LUA_T)

release-$(LUAC_T):
	@[ -d release ] || mkdir release
	@cd release ; $(MAKE) -f ../GNUmakefile TOPDIR=../$(TOPDIR) MODE=release $(LUAC_T)

debug-$(LUAC_T):
	@[ -d debug ] || mkdir debug
	@cd debug ; $(MAKE) -f ../GNUmakefile TOPDIR=../$(TOPDIR) MODE=debug $(LUAC_T)

$(LUAC_T): $(LUAC_O) $(LUA_A)
	$(LD) $(LDFLAGS) $(PRGFLAGS) $(LIBS) $(LUAC_O) $(LUA_A) -OUT:$(LUAC_T)

install: install-debug install-release

install-debug: debug
	$(INSTALL) debug/$(LUA_D) $(DESTBINDBG)
	$(INSTALL) debug/$(LUA_P) $(DESTBINDBG)
	$(INSTALL) debug/$(LUA_A) $(DESTLIBDBG)
	$(INSTALL) debug/$(LUA_E) $(DESTLIBDBG)
	$(INSTALL) debug/$(LUA_T) $(DESTBINDBG)
	$(INSTALL) debug/$(LUAC_T) $(DESTBINDBG)
	$(INSTALL) $(HEADERS) $(DESTINC)

install-release: release
	$(INSTALL) release/$(LUA_D) $(DESTBINDBG)
	$(INSTALL) release/$(LUA_A) $(DESTLIBDBG)
	$(INSTALL) release/$(LUA_E) $(DESTLIBDBG)
	$(INSTALL) release/$(LUA_T) $(DESTBINDBG)
	$(INSTALL) release/$(LUAC_T) $(DESTBINDBG)
	$(INSTALL) $(HEADERS) $(DESTINC)

clean:
	rm -rf debug release

