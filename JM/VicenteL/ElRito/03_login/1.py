##Raspberry Python GUI Auttentication 
##with image answer
##
##
##

####IMPORT GUI
from guizero import App, Text, TextBox, PushButton, Window, Picture
from PIL import Image, ImageTk
##GLOBALES
PASSWORD = "MCASINTIKO"
PASSWORDD = "mcasintiko"
####FUNCIONES
##Boton
def push_login():
    if caja.value == PASSWORD:
        plano.show()
    if caja.value == PASSWORDD:
        plano.show()
        
def push_logout():
        plano.hide()
        caja.value="******"   
        
###DECLARA GUI
app = App(title="Main", layout="grid", height = 1050 , width = 1680)
plano = Window(app,title="Answer")
plano.hide()
croquis=Picture(plano, image = "/home/pi/Documents/plano.png",grid=[0,0,])
app.tk.attributes("-fullscreen",True)
plano.tk.attributes("-fullscreen",True)
fondo=Picture(app, image = "/home/pi/Documents/fondo.png",grid=[0,0,])
fondo.tk.place(height=1050,width=1680)
caja = TextBox(app, grid = [3,4], width = 20, text = "******")
caja.tk.place(x=765,y=600)
boton_login = PushButton(app,grid=[3,5],text="LOGIN", command = push_login)
source_boton = Image.open("/home/pi/Documents/b_login.png")
boton_login.image=source_boton
boton_login.tk.place(x=720,y=650)
boton_logout = PushButton(plano,grid=[3,5],text="LOGOUT", command = push_logout)
boton_logout.image=source_boton
boton_logout.tk.place(x=720,y=650)


app.display()

