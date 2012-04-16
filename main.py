import wave, sys, struct, numpy
from numpy import zeros, array, hamming, abs, log10, fromstring
from numpy.fft import rfft

wavefile = "file.mp3.wav"
fft_length_in_frames = 1024
sample_width = 4
ch_num = 2

formats = { 1 : 'B', 2 : 'i', 4 : 'l' }

types = { 1 : numpy.int8, 2 : numpy.int16, 4 : numpy.int32 }

def convert_input(input):
  readed = input.readframes(input.getnframes())
  return fromstring(readed, dtype=types[input.getsampwidth()])

def split_channels(converted_input, ch):
  return [converted_input[i::ch] for i in range(ch)]

def process(converted_input, sample_width, fft_length, ham):
  if (sample_width == 1):
    peak = 256 / 2
    converted_input -= peak
  
  num_of_ffts = (len(converted_input) / int(fft_length)) - 2
  
  temp = zeros((num_of_ffts, fft_length), float)
  for i in range(num_of_ffts):
    temp[i, :] = converted_input[i * fft_length : (i+1) * fft_length]
    
  for i in range(num_of_ffts):
    temp[i, :] = temp[i, :] * ham
  
  points_out = (fft_length / 2) + 1
  powers = zeros((num_of_ffts, points_out), complex)
  for i in range(num_of_ffts):
    powers[i, :] = rfft(temp[i, :])
  
  powers = 10 * log10(1e-20 + abs(powers))
  return powers

def merge_channels(channels):
  return reduce( lambda x, y : x + y, channels)

def new_main():
  input = wave.open(wavefile, 'rb')
  converted_input = convert_input(input)
  splitted = split_channels(converted_input, input.getnchannels())
  processed = []
  ham = hamming(fft_length_in_frames)
  for i in range(input.getnchannels()):
    processed.append(process(splitted[i], input.getsampwidth(), fft_length_in_frames, ham))
  result = merge_channels(processed)
  print result

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
  new_main()
