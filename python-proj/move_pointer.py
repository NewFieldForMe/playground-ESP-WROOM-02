import pyautogui
import serial
import time

pyautogui.moveRel(100, 100, 0.1)
con = serial.Serial('/dev/cu.usbserial-DN02BC35', 115200)
count = 0
X = 0.0
Y = 0.0
while(count < 20):
    str = con.readline()
    strcon = str.split(":")
    print strcon
    X = X + float(strcon[1])
    Y = Y + float(strcon[2])
    count = count + 1

X = X / 20.0
Y = Y / 20.0

while(True):
    str = con.readline()
    strcon = str.split(":")
    print strcon
    pyautogui.moveRel((float(strcon[1]) - X) * 24, (float(strcon[2]) - Y) * 24, 0.00)
    # time.sleep(0.001)
