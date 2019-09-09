## clScanner ##

Simple program that scans and lists all OpenCL devices on a host computer, useful for debugging. Build and run like this:

```
g++ scan.cpp -o scan -lOpenCL
./scan
```

An additional program to print more info provided at https://trac.macports.org/ticket/43710.

```
gcc clInfo.c -o info -lOpenCL
./info
```
