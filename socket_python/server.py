import socket
import sys
from thread import *

port = 6060
host = ''
list = []
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
	sock.bind((host, port))
except socket.error as err:
	print((err))

sock.listen(3)
#conn, addr = sock.accept()

def thread_client(me, friend):
	#conn.send(str.endcode('Welcome to our server\n'))

	while True:
		data_recieved = me.recv(1024)
		friend.sendall(data_recieved)


ramesh, addr = sock.accept()
ramesh.sendall('Welcome to our server\n')
ramesh.sendall('Waiting for your friend to join...\n')
suresh, address = sock.accept()
suresh.sendall('Welcome to our server\n')
suresh.sendall('You\'ve joined the chat succesfully \n')

start_new_thread(thread_client, (ramesh,suresh))
start_new_thread(thread_client, (suresh, ramesh))

while True:
	connect, addres = sock.accept()
