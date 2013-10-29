import math
import random
import getopt, sys

class Point(object):
  def __init__(self, x, y):
    self.x = x
    self.y = y

  def __str__(self):
    return '{0} {1}'.format(self.x, self.y)

class RangeXY(object):
  def __init__(self, low_x, high_x, low_y, high_y):
    self.low_x = low_x
    self.high_x = high_x
    self.low_y = low_y
    self.high_y = high_y

def print_segments(segments):
  print(len(segments))
  for start, end in segments:
    print(str(start) + " " + str(end));

def generate_b_set():
  points_number = 3000
  width = 100
  plane_range = RangeXY(-width, width, -width, width)


  width2 = 1
  plane_range2 = RangeXY(-width2, width2, -width2, width2)


  points = [create_random_point(plane_range) 
            for i in range(points_number)]

  points2 = [create_random_point(plane_range2) 
             for i in range(points_number)]

  segments = [(point, Point(point.x + point2.x, point.y + point2.y))
              for point, point2 in zip(points, points2)]

  print_segments(segments)
  

def generate_a_set():
  points_number = 1000
  width = 100
  plane_range = RangeXY(-width, width, -width, width)

  segments = [(create_random_point(plane_range), create_random_point(plane_range)) 
              for i in range(points_number)]
  print_segments(segments)
  

def main():
  try:
    opts, args = getopt.getopt(sys.argv[1:], "abcd", [])
  except getopt.GetoptError as err:
    print(str(err))
    sys.exit(2)

  for o, a in opts:
    if o == "-a":
      generate_a_set()
      break
    if o == "-b":
      generate_b_set()
      break
  else:
    print('No option selected')

def create_random_point(plane_range):
  x = random.uniform(plane_range.low_x, plane_range.high_x)
  y = random.uniform(plane_range.low_y, plane_range.high_y)
  return Point(x, y)

if __name__ == '__main__':
  main()

