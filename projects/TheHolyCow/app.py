from flask import Flask, render_template, Response, request
import serial
import time

#serialcom = serial.Serial('/dev/tyy',9600)
#serialcom.timeout=1

app = Flask(__name__)

@app.route("/mixer/<color>", methods=['GET', 'POST'])
def ledRed(color):
	colors = ['red','blue','green','off']
	if color in colors:
		serialcom.write(str(color).encode())
	elif color == 'disconnect':
		serialcom.disconnect()
	else:
		serialcom.write(str('red').encode())

@app.route("/", methods=['GET', 'POST'])
def index():
	return render_template('index.html')

if __name__ == '__main__':
	app.run(host="0.0.0.0",port=5000,debug=True)


