#!/usr/bin/python

import array, wave
from numpy.fft import *

def main():
  file = wave.open("file.wav", 'r')
  params = file.getparams()
  frames = array.array('B', file.readframes(100000))
  print frames
  out = wave.open("out.wav", 'w')
  out.setparams(params)
  out.writeframes(frames.tostring())
  out.close()

if __name__ == "__main__":
  main()