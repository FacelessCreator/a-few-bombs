# A few bombs
Sometimes programs do terrible things because of bugs. This repository contains examples of such software. Build them and test on your systems to check their resistance.

Every bomb has it's own ```test```. Tests log important information in ```csv``` files in ```logs``` directory. If computer crashes, you can read them after restart. To run ```test```, just type ```make test-BOMBNAME```.

## Forkbomb
This bomb named after the function 'fork' in GNU/Linux. The process clones itself for infinity. Operation systems have limit on process count.

Possible aftermath:
- everything freezes
- no more ssh connections - you wouldn't stop madness remotely
- something else?
