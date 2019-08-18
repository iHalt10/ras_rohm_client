# coding: utf-8

import serial
import requests
import json
import time

ser = serial.Serial("/dev/ttyUSB0", 115200)

while True:
  res = requests.get("https://rasrohm.herokuapp.com/fetch")
  status = res.json()
  if status["isupdated"]:
    ser.write(b"\r")
  time.sleep(0.0005)
