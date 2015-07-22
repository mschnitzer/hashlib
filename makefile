.PHONY: all clean hashlib

GPP = g++
OUTDIR = ./Release
OUTFILE = $(OUTDIR)/hashlib.so

COMPILE_FLAGS = -c -fPIC -m32 -O3 -w -D LINUX -I ./amx/

all: hashlib

clean:
	-rm *.o
	-rm -r $(OUTDIR)

$(OUTDIR):
	mkdir -p $(OUTDIR)

hashlib: clean $(OUTDIR)
	$(GPP) $(COMPILE_FLAGS) *.cpp
	$(GPP) -O2 -fPIC -m32 -fshort-wchar -shared -o $(OUTFILE) *.o
	-rm *.o
