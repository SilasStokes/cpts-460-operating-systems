


# Mar 29: he said was going to be a review


init.c sets it up and calls sh.c 

files are in eos.6.load, init.c then login.c and sh.c


// inside QEMU
Login:root
PW:12345

// Inside shell
login:kcw
pw: abcde

So in our shell there's multiple processes running.
So when we access INODES we should use P() to lock
it with a semaphore and then V() to unlock it





