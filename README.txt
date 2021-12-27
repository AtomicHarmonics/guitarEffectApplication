Dependencies:
Install required packages before running build steps (if jackd2 asks to enable realtime, select yes):
sudo apt install jackd2
sudo apt install libjack-jackd2-dev
sudo apt install cmake

Figure out what version of python is installed on your PC by running 'python' or 'python3' in a terminal. For example mine is '3.9.7'. Use that number to determine which packages to install:
sudo apt-get install python3-matplotlib python3-numpy python3.9-dev

Also change the audioEffectsLib/graphTests/CMakeLists.txt for your version of python (just the first two numbers) 

To clone this project:
1.) git clone https://github.com/raoufahmed248/guitarEffectApplication.git
2.) cd guitarEffectApplication





To build:
1.) mkdir build
2.) cd build
3.) cmake ..
4.) make





To run the effects application:
1.) Make sure JACK is running (I recommend using QJackCtl)
1. a.) IF USING RPI INTEGRATED AUDIO, YOU HAVE TO RUN A SPECIAL COMMAND TO START JACK:
JACK_NO_AUDIO_RESERVATION=1 jackd -R -P40 -d alsa -d hw:0 -P -S -p 1024 -n 2 -r 44100 -i 0 -o 2
Then in another terminal run qjackctl to make connections (DO NOT CLICK START IN QJACKCTL!!)
1. b.) IF USING A USB AUDIO INTERFACE THEN YOU CAN USE QJACKCTL TO BOTH START AND MAKE CONNECTIONS, JUST MAKE SURE YOU SELECT RIGHT DEVICES IN SETUP
2.) build/bin/myApp

You should now be able to hear a tremolo effect onto the incomming audio.
You may have to 'wire' up the input audio device to the application and 
from the application to the output audio device via QJackCtl.


To run the benchmark application:
1.) build/bin/audioEffectsLibBenchmark

To run the graph test:
1.) build/bin/audioEffectsLibGraphTests


Tips/General Knowledge:
The way this repo is setup, the Makefile that the cmake generated will build all 
components in this library. In laymans terms, if you make any changes to the code in this repo,
run the make command inside the build directory to build it. The resulting binaries are stored in build/bin . You won't need to run the cmake command anymore unless you change a CMakeLists.txt file anywhere in the repo.





