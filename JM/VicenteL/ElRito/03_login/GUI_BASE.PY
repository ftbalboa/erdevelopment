##Raspberry Python GUI Auttentication 
##with image answer
##
##
##

####IMPORT GUI
from guizero import App, Text, TextBox, PushButton, Window, Picture
from PIL import Image, ImageTk
####IMPORT TCP
from socket import *
import select 
##GLOBALES
PASSWORD = "falopa"
####FUNCIONES
##Boton
def push_login():
    if caja.value == PASSWORD:
        plano.show()
##Loop        
def loopea():
    if ready[0]:        #if data is actually available for you
        print("[INFO] Sending message...")

        print("[INFO] Message sent.")

        data = s.recv(4096)
        print("[INFO] Data received")
        print (data)
        if data == b'R':
            plano.hide()
            caja.value="******"
        if data == b'3' and plano.visible == True:
            s.sendall(data)
###DECLARA GUI
app = App(title="Main", layout="grid", height = 1050 , width = 1680)
plano = Window(app,title="Answer")
plano.hide()
croquis=Picture(plano, image = "plano.gif",grid=[0,0,])
app.tk.attributes("-fullscreen",True)
plano.tk.attributes("-fullscreen",True)
fondo=Picture(app, image = "fondo.png",grid=[0,0,])
fondo.tk.place(height=1050,width=1680)
caja = TextBox(app, grid = [3,4], width = 20, text = "******")
caja.tk.place(x=765,y=600)
boton_login = PushButton(app,grid=[3,5],text="LOGIN", command = push_login)
source_boton = Image.open("b_login.png")
boton_login.image=source_boton
boton_login.tk.place(x=720,y=650)
data = None

timeout = 3 # timeout in seconds
msg = "test"

host = "192.168.1.101"
print ("Connecting to " + host)

port = 23

s = socket(AF_INET, SOCK_STREAM)
print ("Socket made")

ready = select.select([s],[],[],timeout)


s.connect((host,port))
print("Connection made")

app.repeat(500,loopea)
app.display()
####JUEGA TCP

##TODO
##agregar cliente tcp
##bloquear con xmodmap la tecla alt y alguna mas que hinche los huevos
##
