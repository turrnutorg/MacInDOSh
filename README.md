# MacInDOSh Operating System.

### What is MacInDOSh?

MacInDOSh (Macintosh Inside DOS) is an open source recreation of the Macintosh System Softwares 1-6 intended for x86 based machines. 

In its current state, it can boot to desktop, though not much else, as currently we have yet to reimplement KB/m controls. 

> [!NOTE]
> Colour is officially supported, but is currently commented out in code to allow for more performance and authenticity (it can be re-enabled, however, and works out of the box, as the video mode is VGA 12h 640x480x4).

# System Requirements

boots on any x86 cpu, needs 1mb of ram, a fdd, and any competent VGA card 

QEMU is recommended to run it, as it is currently the only confirmed emulator able to run it. QEMU is included in the dependencies, and ```make run``` automatically launches it through qemu-system-i386.

> [!NOTE]
> If you do not have a VGA card, but do own an EGA adapter, you can also change it to ```mov ax, 0x000f``` (EGA mode 640x350x1) for a similar resolution. You would also need to modify the ```HEIGHT``` and ```WIDTH``` defines in ```video.c```

# Building

To build, run ```bash install-packages.sh``` (if you do not already have the existing dependencies), then run ```make run```.

# Licensing & Credits

written and maintained by tuvalutorture

licensed under gpl v3, contributions welcome :D

### This project is NOT affiliated or endorsed by Apple, Inc.

Macintosh, Finder, Mac OS, the "Happy Mac" icon, Apple Logo, Chicago typeface, Geneva typeface, are all trademarks/properties of Apple Incorporated.

also apple i swear to fucking god if you DMCA this repo i will personally resurrect steve jobs and personally smash a NeXT cube in front of his eyes just to spite you

### Screenshots
![Starting screen](images/happymac.png)
![Welcome screen](images/welcome.png)
![Desktop!](images/desktop.png)
