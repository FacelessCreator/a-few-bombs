# A few bombs
Sometimes programs do terrible things because of bugs. This repository contains examples of such software. Build them and test on your systems to check their resistance.

Every bomb has it's own ```test```. Tests log important information in ```csv``` files in ```logs``` directory. If computer crashes, you can read them after restart. To run ```test```, just type ```make test-BOMBNAME```.

See my experience running these tests in ```docs```.

## Forkbomb (```make test-forkbomb```)
This bomb named after the function 'fork' in GNU/Linux. The process clones itself for infinity. Operation systems have limit on process count.

Possible aftermath:
- everything freezes (windows 10)
- no more ssh connections - you wouldn't stop madness remotely (archlinux on raspberry PI)
- impossible to reboot carefully (MIUI 10 - Android 8)
- something else?

## Membomb (```make test-membomb```)
Eats all of your memory. Save your SSD and do ```swapoff -a```. Usually when system is out of memory, this bomb is being killed. But we still has some special effects.

Possible aftermath:
- other processes die (MIUI 10 - Android 8)
- music stumbles (archlinux)
- something else?
