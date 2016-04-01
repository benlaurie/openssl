#!/usr/bin/python

import os
import subprocess
import sys

FUZZER = sys.argv[1]

THIS_DIR = os.path.abspath(os.path.dirname(__file__))
CORPORA_DIR = os.path.abspath(os.path.join(THIS_DIR, "corpora"))

FUZZER_DIR = os.path.abspath(os.path.join(CORPORA_DIR, FUZZER))
if not os.path.isdir(FUZZER_DIR):
    os.mkdir(FUZZER_DIR)

corpora = []

def create(d):
    dd = os.path.abspath(os.path.join(CORPORA_DIR, d))
    if not os.path.isdir(dd):
        os.mkdir(dd)
    corpora.append(dd)

def add(d):
    dd = os.path.abspath(os.path.join(CORPORA_DIR, d))
    if os.path.isdir(dd):
        corpora.append(dd)

create(FUZZER)
create(FUZZER + "-crash")
add(FUZZER + "-seed")

cmd = [os.path.abspath(os.path.join(THIS_DIR, FUZZER)),
       "-artifact_prefix=" + corpora[1] + "/"] + sys.argv[2:] + corpora
print " ".join(cmd)
subprocess.call(cmd)
