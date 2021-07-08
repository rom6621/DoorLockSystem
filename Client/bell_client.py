import serial, time
import socketio


sio = socketio.Client()
ser = serial.Serial('/dev/cu.usbmodem21401', 9600)


sio.connect('http://192.168.1.18:5000/')

while(True):
    line = ser.readline()
    print(line)
    if line == b'bell\r\n':
        sio.emit('bell')
        