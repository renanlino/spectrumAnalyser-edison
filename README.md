#Spectrum Analyzer for Intel Edison#
##A simple spectrum analyzer for Intel Edison##

Check the Instructables tutorial! 
http://www.instructables.com/id/Spectrum-Analyzer-with-Intel-Edison/

With this program you will be able to use your Intel Edison to visualize electric signals in frequency domain.

The output is a simple text-graphic interface, showing the Amplitude x Frequency graphic in serial console.

Due to mraa library and hardware limitations, the maximum frequency is limited to ~5,1kHz.

Also, with some adaptations this program works with Intel Galileo Gen 2 (probably with Gen 1 too), limited to ~1,8 KHz. Raspberry Pi may be used too (not tested).

##Dependencies##
- mraa library (https://github.com/intel-iot-devkit/mraa)
- gcc
- a terminal client (for linux, regular terminal will work fine. for windows, use putty or similar client)

##Usage
Just run compileFFT.sh to generate binaries and run:
- ./bin/fft (may require administrative privileges due to mraa ADC read)

Default configuration (N=256) requires at least 128 horizontal lines on serial output screen

Reads analog input from Analog Pin 0 by default (change in define, see below)

Connection with serial port is highly discouraged. The data transfer rate will drop the frame rate of output graphic. Use ssh connection with a good network signal for better results.

##Parameters
Run fft executable with optional parameters to adjust output graphic:
- ./bin/fft yMax (new maximum amplitude to y axis)
- ./bin/fft yMax lines (new maximum amplitude to y axis and new vertical size of output graphic)

Edit the defines in fft.c source file to adjust performance.
- Increase N for better resolutions (output graphic may not work if you pick N > 256! You need to adjust manually. Must be a power of 2)
- Increase DELTA for noise filtering
- Change default Analog In Pin
- Change yMax to set new maximum amplitude to y axis (must be a float)
- Change lines to increase vertical size of output graphic (must be a float)


##Tests and performance considerations##
- Intel Edison (main processor) with Ublinux:
   * Sampling rate: 10.2k samples/sec
   * Highest frequency: ~5.1k Hz
   * Frequency resolution (256 samples): ~40 Hz

- Intel Edison (main processor) with Yocto:
  * Equal to Ubilinux

- Intel Galileo with Yocto:
   * Sampling rate: 3.6k samples/sec
   * Highest frequency: ~1.8k Hz
