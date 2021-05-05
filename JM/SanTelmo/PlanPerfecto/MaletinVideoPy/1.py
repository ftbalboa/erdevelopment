import RPi.GPIO as GPIO
import os
import sys
from subprocess import Popen
import subprocess
import time
  
def screen_off():
        os.system("xscreensaver-command -activate")
	time.sleep(1)
#    command1 = "echo 80"
 #   command2 = "/usr/bin/sudo tee /sys/class/backlight/rpi_backlight/brightness"
  #  process1 = subprocess.Popen(command1.split(), stdout=subprocess.PIPE)
#    process2 = subprocess.Popen(command2.split(), stdin=process1.stdout, stdout=subprocess.PIPE)
#    output = process2.communicate()[0]
#    print(output)

def screen_on():
        time.sleep(1)
        os.system("xscreensaver-command -deactivate")
#    command1 = "echo 255"
#    command2 = "/usr/bin/sudo tee /sys/class/backlight/rpi_backlight/brightness"
#    process1 = subprocess.Popen(command1.split(), stdout=subprocess.PIPE)
##    process2 = subprocess.Popen(command2.split(), stdin=process1.stdout, stdout=subprocess.PIPE)
#    output = process2.communicate()[0]
#    print(output)


GPIO.setmode(GPIO.BCM)

GPIO.setup(17, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(18, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(27, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(22, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(5, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(6, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(13, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(19, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(26, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(12, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(24, GPIO.IN, pull_up_down=GPIO.PUD_UP)


movie1 = ("/home/pi/Videos/1.mp4")
movie2 = ("/home/pi/Videos/2.mp4")
movie3 = ("/home/pi/Videos/3.mp4")
movie4 = ("/home/pi/Videos/4.mp4")
movie5 = ("/home/pi/Videos/5.mp4")
movie6 = ("/home/pi/Videos/6.mp4")
movie7 = ("/home/pi/Videos/7.mp4")
movie8 = ("/home/pi/Videos/8.mp4")
movie9 = ("/home/pi/Videos/9.mp4")
movie10 = ("/home/pi/Videos/10.mp4")

last_state1 = True
last_state2 = True
last_state3 = True
last_state4 = True
last_state5 = True
last_state6 = True
last_state7 = True
last_state8 = True
last_state9 = True
last_state10 = True

input_state1 = True
input_state2 = True
input_state3 = True
input_state4 = True
input_state5 = True
input_state6 = True
input_state7 = True
input_state8 = True
input_state9 = True
input_state10 = True

quit_video = True

player = False

contador = 0

screen_off()

while True:
    #Read states of inputs
    input_state1 = GPIO.input(17)
    input_state2 = GPIO.input(18)
    input_state3 = GPIO.input(27)
    input_state4 = GPIO.input(22)
    input_state5 = GPIO.input(5)
    input_state6 = GPIO.input(6)
    input_state7 = GPIO.input(13)
    input_state8 = GPIO.input(19)
    input_state9 = GPIO.input(26)
    input_state10 = GPIO.input(12)

    quit_video = GPIO.input(24)

    #If GPIO(17) is shorted to Ground
    if input_state1 != last_state1:
        if (player and not input_state1):
            os.system('killall omxplayer.bin')
            omxc = Popen(['omxplayer', '-b', movie1])
	    screen_on()
	    player = True
            time.sleep(5)
            screen_off()
        elif not input_state1:
            omxc = Popen(['omxplayer', '-b', movie1])
	    screen_on()
            player = True
            time.sleep(5)
            screen_off()
    #If GPIO(18) is shorted to Ground
    elif input_state2 != last_state2:
        if (player and not input_state2):
            os.system('killall omxplayer.bin')
            omxc = Popen(['omxplayer', '-b', movie2])
	    screen_on()
            player = True
            time.sleep(56)
            screen_off()
        elif not input_state2:
            omxc = Popen(['omxplayer', '-b', movie2])
	    screen_on()
            player = True
            time.sleep(56)
            screen_off() 
    #If GPIO(27) is shorted to Ground
    elif input_state3 != last_state3:
        if (player and not input_state3):
            os.system('killall omxplayer.bin')
            omxc = Popen(['omxplayer', '-b', movie3])
	    screen_on()
            player = True
            time.sleep(35)
            screen_off()
        elif not input_state3:
            omxc = Popen(['omxplayer', '-b', movie3])
	    screen_on()
            player = True
            time.sleep(35)
            screen_off()

    #If GPIO(22) is shorted to Ground
    elif input_state4 != last_state4:
        if (player and not input_state4):
            os.system('killall omxplayer.bin')
            omxc = Popen(['omxplayer', '-b', movie4])
            screen_on()
            player = True
            time.sleep(21)
            screen_off()
        elif not input_state4:
            omxc = Popen(['omxplayer', '-b', movie4])
            screen_on()
            player = True
            time.sleep(21)
            screen_off()

    #If GPIO(05) is shorted to Ground
    elif input_state5 != last_state5:
        if (player and not input_state5):
            os.system('killall omxplayer.bin')
            omxc = Popen(['omxplayer', '-b', movie5])
            screen_on()
            player = True
            time.sleep(19)
            screen_off()
        elif not input_state5:
            omxc = Popen(['omxplayer', '-b', movie5])
            screen_on()
            player = True
            time.sleep(19)
            screen_off()

    #If GPIO(06) is shorted to Ground
    elif input_state6 != last_state6:
        if (player and not input_state6):
            os.system('killall omxplayer.bin')
            omxc = Popen(['omxplayer', '-b', movie6])
            screen_on()
            player = True
            time.sleep(37)
            screen_off()
        elif not input_state6:
            omxc = Popen(['omxplayer', '-b', movie6])
            screen_on()
            player = True
            time.sleep(37)
            screen_off()

    #If GPIO(13) is shorted to Ground
    elif input_state7 != last_state7:
        if (player and not input_state7):
            os.system('killall omxplayer.bin')
            omxc = Popen(['omxplayer', '-b', movie7])
            screen_on()
            player = True
            time.sleep(23)
            screen_off()
        elif not input_state7:
            omxc = Popen(['omxplayer', '-b', movie7])
            screen_on()
	    player = True
            time.sleep(23)
            screen_off()

    #If GPIO(19) is shorted to Ground
    elif input_state8 != last_state8:
        if (player and not input_state8):
            os.system('killall omxplayer.bin')
            omxc = Popen(['omxplayer', '-b', movie8])
            screen_on()
            player = True
            time.sleep(20)
            screen_off()
        elif not input_state8:
            omxc = Popen(['omxplayer', '-b', movie8])
            screen_on()
            player = True
            time.sleep(20)
            screen_off()

    #If GPIO(26) is shorted to Ground
    elif input_state9 != last_state9:
        if (player and not input_state9):
            os.system('killall omxplayer.bin')
            omxc = Popen(['omxplayer', '-b', movie9])
            screen_on()
            player = True
            time.sleep(15)
            screen_off()
        elif not input_state9:
            omxc = Popen(['omxplayer', '-b', movie9])
            screen_on()
            player = True
            time.sleep(15)
            screen_off()

    #If GPIO(12) is shorted to Ground
    elif input_state10 != last_state10:
        if (player and not input_state10):
            os.system('killall omxplayer.bin')
            omxc = Popen(['omxplayer', '-b', movie10])
            screen_on()
            player = True
            time.sleep(16)
            screen_off()
        elif not input_state10:
            omxc = Popen(['omxplayer', '-b', movie10])
            screen_on()
            player = True
            time.sleep(16)
            screen_off()
            

    #If omxplayer is running and GIOP(17) and GPIO(18) and GIOP(27) and GPIO(22) and GIOP(05) and GPIO(06) and GIOP(13) and GPIO(19) and GIOP(26) and GPIO(12) are not shorted to Ground
   # elif (player and input_state1 and input_state2):
    #    os.system('killall omxplayer.bin')
     #   player = False

    #GPIO(24) to close omxplayer manually - used during debug
    if quit_video == False:
        os.system('sudo shutdown -r now')
        player = False

    #Set last_input states
    last_state1 = input_state1
    last_state2 = input_state2
    last_state3 = input_state3
    last_state4 = input_state4
    last_state5 = input_state5
    last_state6 = input_state6
    last_state7 = input_state7
    last_state8 = input_state8
    last_state9 = input_state9
    last_state10 = input_state10

   	
