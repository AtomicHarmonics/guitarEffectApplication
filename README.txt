Dependencies: TODO

To clone this project:
1.) git clone https://github.com/raoufahmed248/guitarEffectApplication.git
2.) cd guitarEffectApplication

To build:
1.) mkdir build
2.) cmake ..
3.) make


To run:
1.) Make sure JACK is running (I recommend using QJackCtl)
2.) build/app/myApp

You should now be able to hear a tremolo effect onto the incomming audio.
You may have to 'wire' up the input audio device to the application and 
from the application to the output audio device via QJackCtl.
