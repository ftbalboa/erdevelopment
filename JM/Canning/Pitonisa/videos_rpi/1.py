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

GPIO.setup(16, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(21, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(20, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(26, GPIO.IN, pull_up_down=GPIO.PUD_UP)

movie1 = ("/home/pi/Videos/LADY ACTIS SECUENCIA 1.mp4")
movie2 = ("/home/pi/Videos/LADY ACTIS SECUENCIA 2.mp4")
movie3 = ("/home/pi/Videos/LADY ACTIS SECUENCIA 3.mp4")
movie4 = ("/home/pi/Videos/LADY ACTIS SECUENCIA 4.mp4")

last_state1 = True
last_state2 = True
last_state3 = True
last_state4 = True

input_state1 = True
input_state2 = True
input_state3 = True
input_state4 = True


quit_video = True

player = False

contador = 0

screen_off()

while True:
    #Read states of inputs
    input_state1 = GPIO.input(21)
    input_state2 = GPIO.input(20)
    input_state3 = GPIO.input(16)
    input_state4 = GPIO.input(26)
            
    #If GPIO(21) is shorted to Ground
    if input_state1 != last_state1:
        if (player and not input_state1):
            os.system('killall omxplayer.bin')
            omxc = Popen(['omxplayer', '-b', movie1])
            screen_on()
            player = True
            time.sleep(78)
            screen_off()
        elif not input_state1:
            omxc = Popen(['omxplayer', '-b', movie1])
            screen_on()
            player = True
            time.sleep(78)
            screen_off()

    #If GPIO(20) is shorted to Ground
    if input_state2 != last_state2:
        if (player and not input_state2):
            os.system('killall omxplayer.bin')
            omxc = Popen(['omxplayer', '-b', movie2])
            screen_on()
            player = True
            time.sleep(50)
            screen_off()
        elif not input_state2:
            omxc = Popen(['omxplayer', '-b', movie2])
            screen_on()
            player = True
            time.sleep(50)
            screen_off()

    #If GPIO(16) is shorted to Ground
    if input_state3 != last_state3:
        if (player and not input_state3):
            os.system('killall omxplayer.bin')
            omxc = Popen(['omxplayer', '-b', movie3])
            screen_on()
            player = True
            time.sleep(72)
            screen_off()
        elif not input_state3:
            omxc = Popen(['omxplayer', '-b', movie3])
            screen_on()
            player = True
            time.sleep(72)
            screen_off()

    #If GPIO(26) is shorted to Ground
    if input_state4 != last_state4:
        if (player and not input_state4):
            os.system('killall omxplayer.bin')
            omxc = Popen(['omxplayer', '-b', movie4])
            screen_on()
            player = True
            time.sleep(58)
            screen_off()
        elif not input_state4:
            omxc = Popen(['omxplayer', '-b', movie4])
            screen_on()
            player = True
            time.sleep(58)
            screen_off()


    #If omxplayer is running and GIOP(17) and GPIO(18) and GIOP(27) and GPIO(22) and GIOP(05) and GPIO(06) and GIOP(13) and GPIO(19) and GIOP(26) and GPIO(12) are not shorted to Ground
   # elif (player and input_state1 and input_state2):
    #    os.system('killall omxplayer.bin')
     #   player = False


    #Set last_input states
    last_state1 = input_state1
    last_state2 = input_state2
    last_state3 = input_state3
    last_state4 = input_state4
