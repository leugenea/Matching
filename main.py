import wave, sys, struct
from numpy import zeros, array, hamming, abs, log10
from numpy.fft import rfft

wavefile = "file.mp3.wav"
fft_length_in_frames = 1024
sample_width = 4
ch_num = 2

formats = { 1 : 'B', 2 : 'i', 4 : 'l' }

types = { 1 : numpy.int8, 2 : numpy.int16, 4 : numpy.int32 }

def convert_input(sample_width, input):
  pass

def split_channels(ch, converted_input):
  pass

def process_8bit():
  pass

def process_16bit():
  pass

def process_32bit():
  pass

def main():
  format = formats[sample_width]
  input = wave.open(wavefile, 'rb')
  sample_rate = input.getframerate()
  samples_num = input.getnframes()
  ch_num = input.getnchannels()
  fft_length_in_format = fft_length_in_frames * ch_num
  num_of_ffts = (samples_num / int(fft_length_in_frames)) - 2
  temp = zeros((num_of_ffts, fft_length_in_format), float) 
  
  for i in range(num_of_ffts):
    temp[i, :] = array(struct.unpack(("%d" %(fft_length_in_format))+format, input.readframes(fft_length_in_frames)), float)- 2**(8*sample_width)
  
  ham = hamming(fft_length_in_format)
  for i in range(num_of_ffts):
    temp[i, :] = temp[i, :] * ham
  
  points_out = (fft_length_in_format / 2) + 1
  powers = zeros((num_of_ffts, points_out), complex)
  
  for i in range(num_of_ffts):
    powers[i, :] = rfft(temp[i, :])
  
  powers = 10 * log10(1e-20 + abs(powers))
  
  print powers

if __name__ == "__main__":
  main()
