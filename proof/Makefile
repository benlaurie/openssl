all: aes128enc.proof aes128dec.proof

aes.proof: aes.cry aes.saw
	PATH=$(PATH):$(Z3) $(SAW)/saw aes.saw
	touch aes.proof

aes128enc-wrap.bc: aes128enc-wrap.c
	$(LLVM)/clang -c -emit-llvm -I../include -o $@ $^

aes128dec-wrap.bc: aes128dec-wrap.c
	$(LLVM)/clang -c -emit-llvm -I../include -o $@ $^

# note that the .o file is really a .bc if OpenSSL has been built correctly.
aes128enc.bc: aes128enc-wrap.bc ../crypto/aes/aes_core.o
	$(LLVM)/llvm-link -o aes128enc.bc aes128enc-wrap.bc ../crypto/aes/aes_core.o

aes128dec.bc: aes128dec-wrap.bc ../crypto/aes/aes_core.o
	$(LLVM)/llvm-link -o aes128dec.bc aes128dec-wrap.bc ../crypto/aes/aes_core.o

aes128enc.aig: aes128enc.bc
	time $(SAW)/lss aes128enc.bc

aes128dec.aig: aes128dec.bc
	time $(SAW)/lss aes128dec.bc

aes128enc.proof: aes128enc.aig aes128enc.saw
	PATH=$(PATH):$(Z3) ${SAW}/saw aes128enc.saw
	touch aes128enc.proof

aes128dec.proof: aes128dec.aig aes128dec.saw
	PATH=$(PATH):$(Z3) ${SAW}/saw aes128dec.saw
	touch aes128dec.proof
