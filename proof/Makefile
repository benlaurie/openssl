all: aes128enc.proof

aes128enc-wrap.bc: aes128enc-wrap.c
	$(LLVM)/clang -c -emit-llvm -I../include -o $@ $^

# note that the .o file is really a .bc if OpenSSL has been built correctly.
aes128enc.bc: aes128enc-wrap.bc ../crypto/aes/aes_core.o
	$(LLVM)/llvm-link -o aes128enc.bc aes128enc-wrap.bc ../crypto/aes/aes_core.o

aes128enc.aig: aes128enc.bc
	time $(SAW)/lss aes128enc.bc

aes128enc.proof: aes128enc.aig aes128enc.saw
	PATH=$(PATH):$(Z3) ${SAW}/saw aes128enc.saw
	touch aes128enc.proof
