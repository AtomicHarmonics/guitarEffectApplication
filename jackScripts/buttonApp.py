import RPi.GPIO as GPIO
import time
# Import Raspberry Pi GPIO library
import requests

testVarz = 0
def bypassfunc():
	x = requests.get('http://192.168.86.31:4996/byPass/')
	print(x.status_code)
	jsonResponse = x.json()
	print(jsonResponse["bypassEnabled"])
	tempVar = not jsonResponse["bypassEnabled"]
	print(tempVar)
	r = requests.post('http://192.168.86.31:4996/byPass/', json={"bypassEnabled": tempVar})
	return

def byPass():
    print("called bypass function")
    bypassfunc()

def switchProfile():
    # Making a get request
    response = requests.get('http://192.168.86.31:4996/effectsProfiles')
    if(len(response.json()) == 0):
        return
    tempIndex = 0
    for idx, obj in enumerate(response.json()):
        if(obj["isSelected"] == True):
            tempIndex = (idx + 1) % len(response.json())
            newProfile = response.json()[tempIndex]
            r = requests.post('http://192.168.86.31:4996/effectsProfile/selectedProfile/', json={"title": newProfile["title"], "password": "defaultPass"})
            return
    newProfile = response.json()[tempIndex]
    r = requests.post('http://192.168.86.31:4996/effectsProfile/selectedProfile/', json={"title": newProfile["title"], "password": "defaultPass"})
    return

def switchSelected():
    print("called switchSelected")
    switchProfile()

def button_callback2(channel):
    #if GPIO.input(29) == GPIO.LOW:
    global testVarz
    testVarz = testVarz + 1
    print(testVarz)
    print("Button2 was pushed!")
    byPass()

def button_callback3(channel):
    #if GPIO.input(31) == GPIO.LOW:
    global testVarz
    testVarz = testVarz + 1
    print(testVarz)
    print("Button2 was pushed!")
    switchSelected()


def button_callback(channel):
    if GPIO.input(31) == GPIO.HIGH:
        print("Button1 was pushed!")
        switchSelected()

GPIO.setwarnings(False) # Ignore warning for now
GPIO.setmode(GPIO.BOARD) # Use physical pin numbering
GPIO.setup(29, GPIO.IN, pull_up_down=GPIO.PUD_UP)# Set pin 10 to be an input pin and set initial value to be pulled low (off)
GPIO.add_event_detect(29,GPIO.FALLING,callback=button_callback2, bouncetime=1000)# Setup event on pin 10 rising edge
GPIO.setup(31, GPIO.IN, pull_up_down=GPIO.PUD_UP)# Set pin 10 to be an input pin and set initial value to be pulled low (off)
GPIO.add_event_detect(31,GPIO.FALLING,callback=button_callback3, bouncetime=1000)# Setup event on pin 10 rising edge


# Setup event on pin 10 rising edge


# Setup event on pin 10 rising edge

while(1):
    time.sleep(1)
GPIO.cleanup() # Clean up