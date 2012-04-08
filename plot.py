#!/usr/bin/python

from numpy.fft import *
from pylab import *
from numpy import log10

if __name__ == "__main__":
  x = arange(256.0)
  sig = sin(2*pi*(1250.0/10000.0)*x) + sin(2*pi*(625.0/10000.0)*x)
  plot(arange(0.0, 129.0, 1.0), 10*log10(abs(rfft(sig))))
  show()