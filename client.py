# coding: utf-8

import serial
import requests
import json

ser = serial.Serial("/dev/ttyUSB0", 115200)

while True:
  status = json.loads(requests.get("https://rasrohm.herokuapp.com/fetch"))
  if status["isupdated"]:
    ser.write(b"\r")
  sleep(0.0005)