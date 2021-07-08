from os import sendfile
from flask import Flask, render_template, request
from flask_socketio import SocketIO
from werkzeug.utils import send_file, send_from_directory

app = Flask(__name__)
socketio = SocketIO(app)

status = "open"

@app.route('/')
def index():
    return render_template('index.html')

@app.route("/music/<path:filename>")
def play(filename):
    return send_from_directory("music", filename, environ=request.environ)

@socketio.on('open')
def open():
    print('解錠します')
    global status
    status = "open"
    socketio.emit('open_arduino')
    socketio.emit('response_status', {"status": status})

@socketio.on('close')
def close():
    print('施錠します')
    global status
    status = "close"
    socketio.emit('close_arduino')
    socketio.emit('response_status', {"status": status})

@socketio.on('request_status')
def status():
    print('ステータスを送信します')
    global status
    socketio.emit('response_status', {"status": status})

@socketio.on('bell')
def bell():
    print('ベルを鳴らします')
    socketio.emit('ring_bell')

if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0', port=5000)