import serial, time
import socketio

status = "open"

sio = socketio.Client()
ser = serial.Serial('/dev/cu.usbmodem21401', 9600)

@sio.on('open_arduino')
def open():
    ser.write(b"0")

@sio.on('close_arduino')
def close():
    ser.write(b"1")

sio.connect('http://192.168.1.18:5000/')
sio.wait()
