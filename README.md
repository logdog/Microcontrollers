# Microcontrollers
So I was going to upload all of the cool EE projects that I've created over this past year, but silly me did a rm instead of a mv when initiating this GitHub repository on my most important project. I made a Pop-A-Shot clone using a miniature basketball hoop, an _Arduino Nano_ from China, three _74HC595 shift registers_, two _3-digit 7-segment displays_, a _Piezo buzzer_ (stolen originally from a Hallmark birthday card, but replaced with a speaker from a cheap radio), some mechanical springs to detect scores, an unhealthy amount of 60/40 lead solder, and a few pounds of wood glue. I had written an entire bit-banging setup for my shift registers, along with some heavily debugged code to account for game play, all while avoiding multi-threading (as the nano is has a single processing core), and a solid 30 seconds of hard-coded music that played asynchronously (well kinda, I used the timer1 class to interupt the normal operation of the arduino every 781 clock cycles, but you couldn't notice any hesitation in the sound quality), and some bitwise magic for writing 4-byte integers into an 8-bit EEPROM (I know, fancy). 

But now this file is __long gone__. I planned on making a few more of these things, so I'd like to rewrite the software. I'll be getting my wisdom teeth out in two weeks, but I won't have time to work on it until after the surgery. I think that I'm going to try to write some quality C++ libraries when I'm feeling good on those surgeon-grade pain killers designed for playing music, bit-banging to shift registers, and rending text on 7-segment displays. I mean I've done it before; how hard could it be?

I'll be updating this repository starting in August 2017, with hopes I can create a working version in the short time I have before college. I will also upload pictures of my schematics (I drew them in a book, smart me) when I get the chance. Until then, I'm going to be taking really good care of my Pop-A-Shot.

Also, I recommend doing the following to your terminal:
1. type ```touch ~/.bashrc```
2. type ```vi ~/.bashrc```, press ```I```, and then paste the following:
```
alias rm='ls'
alias REMOVE='\rm'
```
3. Press ```ESC```, and then ```:wq```
4. type ```source ~/.bashrc```

Congradulations! You have made it 10 times harder to accidentally screw up your life. To remove a file you must type REMOVE in all caps, and rm just does an ls. Thanks Easton.

I would also like to take the time to just go over how dumb I had to be to lose this file. I had just spend two weeks teaching new interns the ins and outs of bash--giving them fair warning over the power of rm. I told them to cat a file before removing it to double check that it is the file you want to remove, and so if you screw up you can copy paste it back into a text-editor and recover your file if you act quickly. I followed my instructions to create a cat of my file, but then forgot about it by the time I hit rm and went into panic mode. It also didn't help that I immediately started ranting about it instead of searching my terminal window for the files I had lost. By the time I had realized I could have saved the files, it was 4:30am the next day and I had already closed all of my sessions out of spite. So now I can see 
```
cat bit_shifter.ino
rm bit_shifter.ino Pop-A-Shot.ino (I meant mv)
```
in my .bash_history file, but, since I closed my sessions and forgot to implement any sort of backups, I will never find the output of these commands. In hindsite, if any of you ever do a rm, just freeze and scroll up a little in your terminal and recover the file. On the bright side, all of y'all are gonna get some sweet libraries to play around with when this is all said and done, and I'll get some experience writing libraries specifically for microcontroller-based interaction.
