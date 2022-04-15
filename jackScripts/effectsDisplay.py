#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Copyright (c) 2014-2020 Richard Hull and contributors
# See LICENSE.rst for details.
# PYTHON_ARGCOMPLETE_OK

"""
Display basic system information.

Needs psutil (+ dependencies) installed::

  $ sudo apt-get install python-dev
  $ sudo -H pip install psutil
"""

import os
import sys
import time
from pathlib import Path
from datetime import datetime
import socket
import json
import requests
from urllib.request import urlopen

if os.name != 'posix':
    sys.exit('{} platform not supported'.format(os.name))

from demo_opts import get_device
from luma.core.render import canvas
from PIL import ImageFont

        


try:
    import psutil
except ImportError:
    print("The psutil library was not found. Run 'sudo -H pip install psutil' to install it.")
    sys.exit()


# TODO: custom font bitmaps for up/down arrows
# TODO: Load histogram


def bytes2human(n):
    """
    >>> bytes2human(10000)
    '9K'
    >>> bytes2human(100001221)
    '95M'
    """
    symbols = ('K', 'M', 'G', 'T', 'P', 'E', 'Z', 'Y')
    prefix = {}
    for i, s in enumerate(symbols):
        prefix[s] = 1 << (i + 1) * 10
    for s in reversed(symbols):
        if n >= prefix[s]:
            value = int(float(n) / prefix[s])
            return '%s%s' % (value, s)
    return "%sB" % n


def cpu_usage():
    # load average, uptime
    uptime = datetime.now() - datetime.fromtimestamp(psutil.boot_time())
    av1, av2, av3 = os.getloadavg()
    return "Ld:%.1f %.1f %.1f Up: %s" \
        % (av1, av2, av3, str(uptime).split('.')[0])


def mem_usage():
    usage = psutil.virtual_memory()
    return "Mem: %s %.0f%%" \
        % (bytes2human(usage.used), 100 - usage.percent)


def disk_usage(dir):
    usage = psutil.disk_usage(dir)
    return "SD:  %s %.0f%%" \
        % (bytes2human(usage.used), usage.percent)


def network(iface):
    stat = psutil.net_io_counters(pernic=True)[iface]
    return "%s: Tx%s, Rx%s" % \
           (iface, bytes2human(stat.bytes_sent), bytes2human(stat.bytes_recv))


def retrieveConfig(device):
    font_path = str(Path(__file__).resolve().parent.joinpath('fonts', 'ProggyTiny.ttf'))
    font2 = ImageFont.truetype(font_path, 16)

def internet_on():
   try:
        response = urlopen('https://www.google.com/', timeout=10)
        return True
   except: 
        return False
        
#TODO: Add Overdrive parameters, add setting if effect is enabled or disabled, eventually add reverb configs when provided
def updateDisplay(device, inputMessage,byPassStatus,internetVar):
    font_path = str(Path(__file__).resolve().parent.joinpath('fonts', 'ProggyTiny.ttf'))
    font2 = ImageFont.truetype(font_path, 20)
    #y = json.loads(inputMessage)
    y = inputMessage
    z = byPassStatus
    internetVar = internet_on()
    #add order number and enabled
    zeroLine= str(y["author"]) 
    firstLine = "TRM F:" + str(y["tremoloFreq"]) + " D:" + str(y["tremoloDepth"]) + " NUM: " + str(y["tremoloOrderNumber"]) + " EN:" + str(y["tremoloEnabled"])
    secondLine = "DST TRSH:" + str(y["distortThresh"]) + "  NUM: " + str(y["distortOrderNumber"]) + " EN:" + str(y["distortEnabled"]) 
    #create your lines here
    thirdLine = "OVD TRSH:" + str(y["overDriveThresh"]) + "  NUM: "+str(y["overDriveOrderNumber"]) + " EN:" + str(y["overDriveEnabled"])
    fourthLine = "PRE AMP: "+ str(y["preAmpGain"]) + "          EN:" +str(y["preAmpEnabled"])
    fifthLine = "RVRBDMPLVL:" + str(y["reverbDampLevel"]) + " NUM:" + str(y["reverbOrderNumber"])+ " EN:" + str(y["reverbEnabled"]) 
    sixthLine = "MOD: " + str(y["reverbMode"]) + " DRYLVL: " + str(y["reverbDryLevel"])+ " SIZE: " + str(y["reverbRoomSize"]) 
    seventhLine ="WETLVL: " + str(y["reverbWetLevel"])+ " WD: " + str(y["reverbWidth"])
    eighthLine = str(y["title"]) 
    bypassLine = "Bypass Status:" + str(z["bypassEnabled"])
    internetLine = "Internet Connection Status:" + str(internetVar)
    
    
    
   
    print(y["author"])
    with canvas(device) as draw:
        draw.text((0, 0), zeroLine, font=font2, fill="white")
        if device.height >= 32:
            draw.text((0, 20),  firstLine, font=font2, fill="white")
            draw.text((0, 40), secondLine, font=font2, fill="white")
            draw.text((0, 60), thirdLine, font=font2, fill="white")
            draw.text((0, 80), fourthLine, font=font2, fill="white")
            draw.text((0, 100), fifthLine, font=font2, fill="white")
            draw.text((0, 120), sixthLine, font=font2, fill="white")
            draw.text((0, 140), seventhLine, font=font2, fill="white")
            draw.text((0, 160), eighthLine, font=font2, fill="white")
            draw.text((0, 180), bypassLine, font=font2, fill="white")
            draw.text((0, 200), internetLine, font=font2, fill="white")
          
            
           
           
            

        if device.height >= 64:
            pass
            #draw.text((0, 26), disk_usage('/'), font=font2, fill="white")
            #try:
                #draw.text((0, 38), network('wlan0'), font=font2, fill="white")
            #except KeyError:
                # no wifi enabled/available
                #pass    

def main():

        while True:
                x = requests.get('http://192.168.86.31:4996/effectsProfile/selectedProfile/')
                z = requests.get('http://192.168.86.31:4996/byPass/')
                internetVar = requests.get('https://www.google.com/')
                print(x.status_code)
                if(x.status_code == 200 and z.status_code == 200):
                    updateDisplay(device, x.json(),z.json(),internetVar)
                time.sleep(2)
       
#python3 effectsDisplay.py --display pygame --width 320 --height 240

if __name__ == "__main__":
    try:
        device = get_device()
        main()
    except KeyboardInterrupt:
        pass