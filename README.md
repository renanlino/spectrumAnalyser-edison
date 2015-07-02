#Spectrum Analyser for Intel Edison#
##A simple spectrum analyser for Intel Edison##
With this program you will be able to use your Intel Edison to visualize electric signals in frequency domain.

The output is a simple text-graphic interface, showing the Amplitude x Frequency graphic in serial console.

Due to mraa library and hardware limitations, the maximum frequency is limited to ~5,1kHz.

Also, with some adaptations this program works with Intel Galileo Gen 2 (probably with Gen 1 too), limited to ~1,8 KHz. Raspberry Pi may be used too (not tested).

##Dependencies##
- mraa library (https://github.com/intel-iot-devkit/mraa)

##Tests and performance considerations##
- Intel Edison (main processor) with Ublinux:
   * Sampling rate: 10,2k samples/sec
   * Highest frequency: ~5,1k Hz
   * Frequency resolution (256 samples): ~40 Hz

- Intel Edison (main processor) with Yocto:
  * Equal to Ubilinux

- Intel Galileo with Yocto:
   * Sampling rate: 3,6k samples/sec
   * Highest frequency: ~1,8k Hz
