GPP = g++
GCC = gcc
OUTFILE = "../server/plugins/hashlib.so"

COMPILE_FLAGS = -c -fPIC -m32 -O3 -w -D LINUX -I ./amx/

clean:
	-rm *~ *.o *.so

hashlib: clean
	$(GPP) $(COMPILE_FLAGS) ./*.cpp
	$(GPP) $(COMPILE_FLAGS) *.cpp
	$(GPP) -O2 -fPIC -m32 -fshort-wchar -shared -o $(OUTFILE) *.o
