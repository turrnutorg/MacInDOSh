MacInDOSh (Macintosh Inside DOS) is an open source recreation of the Macintosh System Software 1.0 - System 6 intended for x86 based machines. 

In its current state, it CAN boot to desktop, though not much else, as currently we have yet to reimplement KB/m controls. 

boots on any x86 cpu, needs 1mb of ram, a fdd, and any competent VGA card (qemu reccomended)

does work on qemu

to build run ```bash install-packages.sh``` (because dependencies, yay), then run ```make run```.

written and maintained by tuvalutorture

licensed under gpl v3, contributions welcome

### Not affiliated with Apple, Inc.

Macintosh, Finder, Mac OS, are all trademarks of Apple Incorporated.

### Screenshots
![Starting screen](images/happymac.png)
![Welcome screen](images/welcome.png)
![Desktop!](images/desktop.png)