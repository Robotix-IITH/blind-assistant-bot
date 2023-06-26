from flask import Flask, abort, send_file
import serial
import time
from threading import Thread


ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
ser.reset_input_buffer()
ser.write(b'E')


def print_ser(ser):
    while True:
        while ser.in_waiting:
            print(ser.readline().decode('utf-8'), end='')
        time.sleep(1)


thr = Thread(target=print_ser, args=(ser,))
thr.start()

app = Flask(__name__)


@app.post('/send/<b>')
def send_byte(b):
    if len(b) != 1:
        abort(400)
        return ""
    ser.write(bytes(b, 'utf-8'))
    return ""


@app.get('/')
def home():
    return send_file('index.html')


app.run('0.0.0.0', port=8080)
