# Microcontrollers
So I was going to upload all of the cool EE projects that I've created over this past year, but silly me did a rm instead of a mv when initiating this GitHub repository on my most important project. I made a Pop-A-Shot clone using a miniature basketball hoop, an _Arduino Nano_ from China, three _74HC595 shift registers_, two _3-digit 7-segment displays_, a _Piezo buzzer_ (stolen originally from a Hallmark birthday card, but replaced with a speaker from a cheap radio), some mechanical springs to detect scores, an unhealthy amount of 60/40 lead solder, and a few pounds of wood glue. I had written an entire bit-banging setup for my shift registers, along with some heavily debugged code to account for game play, all while avoiding multi-threading (as the nano is has a single processing core), and a solid 30 seconds of hard-coded music that played asynchronously (well kinda, I used the timer1 class to interupt the normal operation of the arduino every 781 clock cycles, but you couldn't notice any hesitation in the sound quality), and some bitwise magic for writing 4-byte integers into an 8-bit EEPROM (I know, fancy). 

But now this file is __long gone__. I planned on making a few more of these things, so I'd like to rewrite the software. I'll be getting my wisdom teeth out in two weeks, and I'm going to try to write some quality C++ libraries designed for playing music, bit-banging to shift registers, and rending text on 7-segment displays.

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
