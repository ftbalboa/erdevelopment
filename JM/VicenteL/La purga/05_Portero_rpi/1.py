##05_Portero_Purga
##1234567890
##0142466397
##30/06/18
##78902411
##IMPORTS VIDEO
import os
import sys
from subprocess import Popen
import subprocess
import time
##IMPORTS INTERNET
from socket import *
import select
##FUNCIONES VIDEO
def screen_off():
    os.system("xscreensaver-command -activate")
    time.sleep(1)
    print("OFF PANTALLA")
def screen_on():
    time.sleep(1)
    os.system("xscreensaver-command -deactivate")
    print("ON PANTALLA")
##DECLARACIONES VIDEO
movie1 = ("/home/pi/Videos/1.mp4")
movie2 = ("/home/pi/Videos/2.mp4")
last_state1 = True
input_state1 = True
player = False
screen_off()
##DECLARA INTERNET
data = None
timeout = 3 # timeout in seconds
host = "192.168.0.110"
print ("Connecting to " + host)
port = 24
s = socket(AF_INET, SOCK_STREAM)
print ("Socket made")
ready = select.select([s],[],[],timeout)
s.connect((host,port))
print("ARRANQUE OK")
resuelto = False
first_activo = False
activo = False
first_reset = False
##LOOP
while True:
    #First activo
    if (first_activo and activo):
        print("paso1 OK")
        first_activo = False
        first_reset = True
        omxc = Popen(['omxplayer', '-b', movie1])
        screen_on()
        player = True
        time.sleep(6)
    if (activo and not resuelto and not first_activo):
        resuelto = True
        print("paso2 OK")
        screen_off()
        time.sleep(2)
        os.system('killall omxplayer.bin')
        omxc = Popen(['omxplayer', '-b', movie2])
        screen_on()
        player = True
        time.sleep(33)
        screen_off()
        time.sleep(2)
        os.system('killall omxplayer.bin')        

    if ready[0]:        #if data is actually available for you
        print("[INFO] Sending message...")
        print("[INFO] Message sent.")
        data = s.recv(4096)
        print("[INFO] Data received")
        print (data)
        ##RESET
        if (data == b'R' and first_reset):
            resuelto = False
            first_reset = False
            first_activo = True
            player = False
            screen_off()
            first_activo = True
        if (data == b'7' and not activo) :
            activo = True
            print("ENTRE EN 7")
        if (data == b'7' and resuelto == True):
            s.sendall(data)
        if (data == b'8' and resuelto == False):
            activo = True
