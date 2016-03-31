BeatStrip - Controlling a digital LED strip through an Arduino

This project requires the following Hardware:
	- A WS2812 5050 LED Strip or similar
	- An Arduino Microcontroller (I'm using an older Nano)
	- A 5V DC powersource
	- An NF-audiosignal filtered through a Lowpass-Filter (I'm using 2 kΩ, 470 nF)

The library im using to access the LEDs is Adafruit's NeoPixel library.

My main goal is having the LEDs adjust to the 'intensity' of the music supplied.
One function for example is very similar to a VU-meter. 

Future versions may or may not include:
	- Rainbow effects
	- Multiple audio channels (highpass, bandpass)
	- IR-Remote support

The current stage is adding a second filter for high frequencies, and only have the colour change when a significant value is measured on that.