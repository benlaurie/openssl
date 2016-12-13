all: aes128enc.proof aes128dec.proof aes256enc.proof aes256dec.proof

clean:
	rm -f *.bc *.aig *.proof

aes.proof: aes.cry aes.saw
	PATH=$(PATH):$(Z3) $(SAW)/saw aes.saw
	touch aes.proof

aes128enc-wrap.bc: aes128enc-wrap.c
	$(LLVM)/clang -c -emit-llvm -I../include -o $@ $^

aes256enc-wrap.bc: aes256enc-wrap.c
	$(LLVM)/clang -c -emit-llvm -I../include -o $@ $^

aes128dec-wrap.bc: aes128dec-wrap.c
	$(LLVM)/clang -c -emit-llvm -I../include -o $@ $^

aes256dec-wrap.bc: aes256dec-wrap.c
	$(LLVM)/clang -c -emit-llvm -I../include -o $@ $^

# note that the .o file is really a .bc if OpenSSL has been built correctly.
aes128enc.bc: aes128enc-wrap.bc ../crypto/aes/aes_core.o
	$(LINK) -o aes128enc.bc aes128enc-wrap.bc ../crypto/aes/aes_core.o

aes256enc.bc: aes256enc-wrap.bc ../crypto/aes/aes_core.o
	$(LINK) -o aes256enc.bc aes256enc-wrap.bc ../crypto/aes/aes_core.o

aes128dec.bc: aes128dec-wrap.bc ../crypto/aes/aes_core.o
	$(LINK) -o aes128dec.bc aes128dec-wrap.bc ../crypto/aes/aes_core.o

aes256dec.bc: aes256dec-wrap.bc ../crypto/aes/aes_core.o
	$(LINK) -o aes256dec.bc aes256dec-wrap.bc ../crypto/aes/aes_core.o

aes128enc.aig: aes128enc.bc
	time $(SAW)/lss aes128enc.bc

aes256enc.aig: aes256enc.bc
	time $(SAW)/lss aes256enc.bc

aes128dec.aig: aes128dec.bc
	time $(SAW)/lss --satbranches aes128dec.bc

aes256dec.aig: aes256dec.bc
	time $(SAW)/lss aes256dec.bc

aes128enc.proof: aes128enc.aig aes128enc.saw aes.cry
	PATH=$(PATH):$(Z3) $(SAW)/saw aes128enc.saw
	touch aes128enc.proof

aes256enc.proof: aes256enc.aig aes256enc.saw
	PATH=$(PATH):$(Z3) $(SAW)/saw aes256enc.saw
	touch aes256enc.proof

aes128dec.proof: aes128dec.aig aes128dec.saw aes.cry
	PATH=$(PATH):$(Z3) $(SAW)/saw aes128dec.saw
	touch aes128dec.proof

aes256dec.proof: aes256dec.aig aes256dec.saw
	PATH=$(PATH):$(Z3) $(SAW)/saw aes256dec.saw
	touch aes256dec.proof
