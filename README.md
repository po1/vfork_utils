popen_vfork
===========

A teeny-tiny library that is intended to replace the system `popen()` with one that uses `vfork()`


The intended use for this is as follows:

```shell
 LD_PRELOAD=libpopen_vfork.so ./my_prog
```

It will replace the system's `popen()` with one that uses `vfork()` instad
of `fork()`, which is very handy for Xenomai-enabled  programs, or in any
environment where Linux's copy-on-write feature is undesirable.
