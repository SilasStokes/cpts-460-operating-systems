
# notes:
so. mostly used kfork, but used the code from exec to get the kline and filename (use kline for istring) and the file-descriptor copying from fork

kfe just dosn't copy the image

i think kfe should be pulling from kfork and exec - use the kfork method of spawning a process and the exec way of injecting the command-line args

Yeah I think he said basically copy his functions but don't copy the image.

Yeah I put the code from fork and exec together and commented out the parts where I thought fork copied the image....
It works but I am also not sure that I understand fork enough to comment out the right parts lol

so. mostly used kfork, but used the code from exec to get the kline and filename (use kline for istring) and the file-descriptor copying from fork
