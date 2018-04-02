particledetector
================

In theory this should detect cosmic rays n' stuff.

So far I've not caught any. If you do, let me know!

Building
========

Just clone it,

    git clone https://github.com/ky0ko/particledetector

then change directory and make

    cd particledetector
    make

Using
=====

just run

    ./particledetector

from within the build folder. It has some options, you can pass -h for help

    ./particledetector -h
    Valid options:
      -m [number]       Set size of memory allocation for scanning, in GiB (default 8)
      -n [filename]     Set filename for logging (default ./particles.log)
      -v                Set verbose mode
      -h                Show help
