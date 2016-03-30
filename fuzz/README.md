# I Can Haz Fuzz?

Or, how to fuzz OpenSSL with libfuzzer.

Starting from a vanilla+OpenSSH server Ubuntu install.

## New Way

Use Chrome's handy recent build of clang.

    $ sudo apt-get install git
    $ mkdir git-work
    $ git clone https://chromium.googlesource.com/chromium/src/tools/clang
    $ clang/scripts/update.py

You may want to git pull and re-run the update from time to time.

Update your path:

    $ PATH=$PATH:~/third_party/llvm-build/Release+Asserts/bin/

Get and build libFuzzer:

    $ cd
    $ sudo apt-get install subversion
    $ mkdir svn-work
    $ cd svn-work
    $ svn co http://llvm.org/svn/llvm-project/llvm/trunk/lib/Fuzzer
    $ cd Fuzzer
    $ clang++ -c -g -O2 -std=c++11 *.cpp
    $ ar r libFuzzer.a *.o
    $ ranlib libFuzzer.a

Install a modified version of OpenSSL.

    $ cd
    $ cd git-work
    $ git clone https://github.com/benlaurie/openssl.git
    $ cd openssl
    $ git checkout fuzz

Configure for fuzzing:

    $ CC=clang ./config enable-fuzz
    $ sudo apt-get install make
    $ LDCMD=clang++ make -j
    $ fuzz/server

If you are working on developing new fuzzing targets (which is much easier
than all this palaver), you might want to also use ccache:

    $ sudo apt-get install ccache
    $ CC="ccache clang" ./config enable-fuzz
    $ LDCMD="ccache clang++" make -j

Look at [the
diff](https://github.com/openssl/openssl/compare/master...benlaurie:fuzz) for
more info.

## Old Way

Install an appropriate version of clang (>= 3.7). Up-to-date
instructions may be here: http://llvm.org/apt/. At the time of
writing, the 3.8 version allegedly available for Ubuntu is not
actually there, so edit `/etc/apt/sources.list` and add:

    deb http://llvm.org/apt/trusty/ llvm-toolchain-trusty-3.7 main
    deb-src http://llvm.org/apt/trusty/ llvm-toolchain-trusty-3.7 main

Add the LLVM PGP key:

    $ wget -O - http://llvm.org/apt/llvm-snapshot.gpg.key|sudo apt-key add -

Install clang 3.7 (or later if available):

    $ sudo apt-get update
    $ sudo apt-get install clang-3.7

Clang packaging is incorrect, fix up:

    $ cd /tmp
    $ wget http://llvm.org/releases/3.7.1/clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-14.04.tar.xz
    $ tar xf clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-14.04.tar.xz
    $ cd clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-14.04/lib/clang/3.7.1/lib/linux/
    $ sudo cp -n *.a /usr/lib/llvm-3.7/lib/clang/3.7.1/lib/linux/

Get and build libFuzzer:

    $ cd
    $ sudo apt-get install subversion
    $ mkdir svn-work
    $ cd svn-work
    $ svn co http://llvm.org/svn/llvm-project/llvm/trunk/lib/Fuzzer
    $ cd Fuzzer
    $ clang++-3.7 -c -g -O2 -std=c++11 *.cpp
    $ ar r libFuzzer.a *.o
    $ ranlib libFuzzer.a

Install a modified version of OpenSSL.

    $ cd
    $ sudo apt-get install git
    $ mkdir git-work
    $ cd git-work
    $ git clone https://github.com/benlaurie/openssl.git
    $ cd openssl
    $ git checkout fuzz

Configure for fuzzing:

    $ CC=clang-3.7 ./config enable-fuzz
    $ sudo apt-get install make
    $ LDCMD=clang++-3.7 make -j
    $ fuzz/server

If you are working on developing new fuzzing targets (which is much easier
than all this palaver), you might want to also use ccache:

    $ sudo apt-get install ccache
    $ CC="ccache clang-3.7" ./config enable-fuzz
    $ LDCMD="ccache clang++-3.7" make -j

Look at [the
diff](https://github.com/openssl/openssl/compare/master...benlaurie:fuzz) for
more info.
