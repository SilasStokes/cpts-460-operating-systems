# Compilation of bullet points I either discovered myself doing lab 2 or I saw in the CS discord. 

- Saving this link bc it's not on his website this semester: https://web.archive.org/web/20180521043753/http://www.eecs.wsu.edu/~cs460/serial.html

- for part 2.1:
    KC has the mk script hard coded to link a library
    ```
    LIB=/usr/lib/gcc/arm-none-eabi/9.2.1/
    ```
    however, it's most likely not that library on your machine, just ls the arm-non-eabi dir and see what verion you have in there to change it

- someone on the discord said that they had to use -fno-stack-protector flag to get part 2.1 to work. 
- The actual word to quit is 'end', not quit like the terminal says. 
- KC annoyingly doesn't consistnently type urpu so sometimes you'll need to change rpu to urpu
- in urpu, kc has hardcoded base 10, you'll have to make a variable for it.
- when launching ./mk headless from ssh, add the -nographic flag. Once QEMU starts you can close it with "ctrl+a" and then "x"
