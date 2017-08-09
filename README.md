# playground-ESP-WROOM-02
This repository is a playground of ESP-WROOM-02.

## Make Environment(MEMO)
```
pip install -U pip setuptools
pip install -U pip platformio
platformio boards | grep ESP8266
yes y | platformio init -b esp_wroom_02
```

```
pip install pyobjc-core  
pip install pyobjc  
pip install pyautogui  
```

firm update command.
```
sudo platformio run -t upload --upload-port /dev/cu.usbserial-DN02BC35
```
pip install pyserial