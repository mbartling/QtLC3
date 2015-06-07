#!/usr/bin/env python2.7
"""Sorting Simulation
    This script is meant to simulate testing + grading of a LC3 programming Assignment
    Assignment: sort a list of (student_id, grades) in place. 
      Note: sorted by grade in descending order
    
    List Entries:
      student_id: uint8_t (unique)
      grade: uint8_t in [0,100]

    Student Program Starts at x3000
    Grade List starts at x3200
"""
import pylc3
import unittest
from LC3Helper import *
import random

# Helper Functions
def upperHalf(x):
  return (x << 8) & 0xFF00

def lowerHalf(x):
  return x & 0xFF

class SortingTest(unittest.TestCase):

  def setUp(self):
    self.sim = pylc3.simulator()
    self.sim.load("sort.obj")
    print("Done Initializing Simulator")

  def test_ProvidedInDocument(self):
    gradeList = [upperHalf(23) | lowerHalf(78), \
                 upperHalf(10) | lowerHalf(91), \
                 upperHalf(56) | lowerHalf(5),  \
                 upperHalf(2) | lowerHalf(87)]
    
    self.sim.mem[x3200:(x3200 + len(gradeList))] = gradeList
    self.run()

    progOutList = self.sim.mem[x3200:(x3200 + len(gradeList))]

    #Python Sorts are guaranteed to be stable, so we can check if their output is correctly sorted
    # in just one line :) (We dont care whether the student implemented stable vs unstable sort)
    self.assertEqual(sorted(progOutList, key = lambda grade : grade & 0xFF), progOutList)

  # Generate A random Test
  def test_random_1(self):
    numStudents = 50
    gradeList = []
    
    for i in range(numStudents):
      gradeList.append( upperHalf(i + 1), lowerHalf(random.randint(0,100)))

    self.sim.mem[x3200:(x3200 + len(gradeList))] = gradeList
    self.run()

    progOutList = self.sim.mem[x3200:(x3200 + len(gradeList))]

    #Python Sorts are guaranteed to be stable, so we can check if their output is correctly sorted
    # in just one line :) (We dont care whether the student implemented stable vs unstable sort)
    self.assertEqual(sorted(progOutList, key = lambda grade : grade & 0xFF), progOutList)