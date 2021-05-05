#Ejemplo de cliente TCP para rpi
#
#

from socket import *
import select 

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


if ready[0]:        #if data is actually available for you
    print("[INFO] Sending message...")

    print("[INFO] Message sent.")

    data = s.recv(4096)
    print("[INFO] Data received")
    print (data)
	s.sendall(bytes((48,)))
