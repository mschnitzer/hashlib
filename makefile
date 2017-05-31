.PHONY: all clean hashlib

GPP = g++
OUTDIR = ./Release
OUTFILE = $(OUTDIR)/hashlib.so

COMPILE_FLAGS = -std=c++11 -c -fPIC -m32 -O3 -w -D LINUX -I ./amx/ -D _strdup=strdup

all: hashlib

clean:
	-rm *.o
	-rm -r $(OUTDIR)

$(OUTDIR):
	mkdir -p $(OUTDIR)

hashlib: clean $(OUTDIR)
	$(GPP) $(COMPILE_FLAGS) -U__i386__ crypt_blowfish/*.cpp
	$(GPP) $(COMPILE_FLAGS) *.c *.cpp
	$(GPP) -O2 -fPIC -m32 -fshort-wchar -shared -o $(OUTFILE) *.o
	-rm -r *.o
