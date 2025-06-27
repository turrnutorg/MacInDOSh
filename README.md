MacInDOSh (Macintosh Inside DOS) is an open source recreation of the Macintosh System Software 1.0 intended for x86 based machines. 

In its current state, it CAN boot to desktop, though not much else, as currently we have yet to reimplement KB/m controls. 
(is pain :c )
(i should really make loading 2-stage)

also
colours
so more like 
system 6

boots on any x86 cpu
needs 1mb of ram
and a fdd
and also any competent VGA card
does not work on VirtualBox
not tested on real hw
does work on qemu
don't expect much success elsewhere ngl

to build
bash install-packages.sh (because dependencies, yay)
make run (clean is redundant, this already rm -rf's the stuff)

written by tuvalutorture
maintained by... also tuvalutorture
as part of the turrnut open source org

licensed under gpl v3
in other words
pls dont steal :P

contributions welcome