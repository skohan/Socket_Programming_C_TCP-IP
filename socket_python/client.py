import socket
import sys
from thread import *

def Send(sock):
    file_data = ''
    print('File transfer has been initiated....')
    file_name = raw_input('Enter the d=file name with extension: ')
    list = file_name.split('.')
    sock.send(list[0])
    sock.send(list[1])
    file = open(file_name, 'rb')
    with open("rb") as f:
        byte = f.read(1)
        
        while byte != "":
            file_data = file_data + byte
            byte = f.read(1)
    f.close()


server_ip = raw_input('Enter server IP address: ')
port = 6060

sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

sock.connect((server_ip, port))

data_recieved = sock.recv(10240)
print(data_recieved)

data_recieved = sock.recv(10240)
print(data_recieved)

def thread_recv(sock):
    while True:
        data_recieved = sock.recv(10240)
        if data_recieved == 'Send()':Receive(sock)
        elif  data_recieved == 'Receive()':Send(sock)
        elif:  print('Friend: ' + data_recieved)


start_new_thread(thread_recv, (sock, ))

while True:
    data_to_send = raw_input()
    if data_recieved == 'Send()':Send(sock)
    elif  data_recieved == 'Receive()':Receive(sock)
    sock.sendall(data_to_send)
