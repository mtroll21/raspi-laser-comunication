in terminal:
sudo apt-get install rpi.gpio

TRANSMISSION
	
	//imports
	inport RPi.GPIO as io
	import time
	import letters.py //import letter map
	
	io.setmode(io.BCM)
	
	//define
	laser = 27
	io.setup(laser, io.OUT)
	
	
	input = raw_input("") //usr input
	letters[] = input.split("") //split text to letters
	loopIf = letter.lenght
	while(loopIf >= 1): //loop
		io.output(laser, True //convert letters to binaray and send data
		time.sleep(<time delay>)




RECEPTION //idk

mesure laser on fotoresistor
convert patern to letters
conect letters
output to terminal





