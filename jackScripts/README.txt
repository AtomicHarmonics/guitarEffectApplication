ajConnections-script: This is a program that will automatically make jack connections for you based on the config file
given, in this case 'fullConnConfig'
gstreamer-script: This program will recieve an audio stream from jack and stream it to a set ip address
effects-script: will start the guitar effects application
jackServer-script: This will start the jack server assuming the usb audio interface is connected.

MAKE SURE TO BUILD THE APPLICATION BEFORE RUNNING 'source setupServices.sh'
Anytime you make a change to the application and build again, run source setupServices.sh again. I would recommend to also stop the jackServer.service before running the setupServices again (run systemctl --user stop jackServer.service)
You shouldn't need to change the paths in the scripts anymore, since now all assets will be copied to a static path (/var/lib/jackAssets/).


After running 'source setupServices.sh' , ajConnections,gstreamer-script, and effects-script will start automatically whenever the
jackServer service is ran 'systemctl --user start jackServer.service'.
To disable this functionality, run the disableServices script 'source disableServices.sh'.

NOTE: verify the jackServer starts succesfully by running 'systemctl --user status jackServer.service', if it doesn't say active in green, run the start command again.

To stop the applications, simply enter 'systemctl --user stop jackServer.service', and wait a bit. If you enabled the services via the script, it will automatically
close other services.

You can also just run each service manually by entering 'systemctl --user start <SERVICENAME>', I would reccomend you first run the disableServices script since otherwise other services would start automatically.

You can view the status of each service by 'systemctl --user status <SERVICENAME>' and exit the status menu via 'q'.

List of services:
ajSnapshotService.service
effectsService.service
gstreamerService.service
jackServer.service
