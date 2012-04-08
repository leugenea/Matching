import wave, sys, struct
from numpy import zeros, array, hamming

wavename = "file.mp3.wav"
fft_length = 1024
sample_width = 4
format = "I"

def main():
  input = wave.open(wavefile, 'rb')
  sample_rate = input.getframerate()
  samples = input.getnframes()
  num_of_ffts = (samples / int(fft_length)) - 2
  temp = zeros((num_of_ffts, fft_length)) 
  
  for i in range(num_of_ffts):
    temp(i, :) = array(struct.unpack(("%d" %(fft_length))+format), input.readframes(fft_length), float) - 2**(8*sample_width)

if __name__ == "__main__":
  main()