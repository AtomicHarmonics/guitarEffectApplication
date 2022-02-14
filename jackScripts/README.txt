ajConnections: This is a program that will automatically make jack connections for you based on the config file
given, in this case 'fullConnConfig'
gstreamer-script: This program will recieve an audio stream from jack and stream it to a set ip address
effects-script: will start the guitar effects application
jackServer-script: This will start the jack server assuming the usb audio interface is connected.

CHANGE THE PATHS IN THE SCRIPTS TO MATCH YOUR SETUP!!!!!!!!!

After running 'source setupServices.sh' , ajConnections,gstreamer-script, and effects-script will start automatically whenever the
jackServer service is ran 'systemctl --user start jackServer.service'.
To disable this functionality, run the disableServices script 'source disableServices.sh'.

To stop the applications, simply enter 'systemctl --user stop jackServer.service', and wait a bit. If you enabled the services via the script, it will automatically
close other services.

You can also just run each service manually by entering 'systemctl --user start <SERVICENAME>', I would reccomend you first run the disableServices script since otherwise other services would start automatically.