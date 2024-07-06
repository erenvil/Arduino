import serial
import time
import keyboard
import os
import pyautogui as pu

ser = serial.Serial('COM11', 9600)

obs_path = r"C:\ProgramData\Microsoft\Windows\Start Menu\Programs\OBS Studio\OBS Studio (64bit).lnk"

try:
    while True:
        if ser.in_waiting > 0:
            data = ser.readline().decode('utf-8').strip()
            print(f"Received data: {data}")
            
            if data == "+":
                keyboard.press('volume_up')
            elif data == "-":
                keyboard.press('volume_down')
            elif data == "obs":
                os.startfile(obs_path)
            elif data in ["W", "S", "A", "D"]:
                keyboard.press(data.lower())
                time.sleep(0.1)
                keyboard.release(data.lower())
            elif data == "obs1":
                keyboard.send('ctrl+shift+alt+1')
            elif data == "obs2":
                keyboard.send('ctrl+shift+alt+2')
            elif data == "obs3":
                keyboard.send('ctrl+shift+alt+3')
            elif data == "obs4":
                keyboard.send('ctrl+shift+alt+4')
            elif data == "back":
                pu.press('prevtrack')
            elif data == "next":
                pu.press('nexttrack')
            elif data == "play/pause":
                pu.press("playpause")
except KeyboardInterrupt:
    ser.close()