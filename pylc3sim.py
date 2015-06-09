#!/usr/bin/env python2.7

import pylc3

class pyLC3Sim(pylc3.simulator):
  
  def __init__(self):
    pylc3.simulator.__init__()
    #OK So this is super hacky and not memory efficient.
    #But it is easier for students to understand
    self.mem =   
