import math
import random

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

WIDTH = 1e3
POINTS_NUMBER = 10**1

def print_points(points):
  print(len(points))
  for point in points:
    print(point)

def generate_d_set():
  points_x_range = (-1000.0, 1000.0)
  points_number = 1000
  vector_a = Point(-1.0, 0.0)
  vector_b = Point(1.0, 0.1)

  f = create_line_func_from_two_points(vector_a, vector_b)
  points = [create_random_point_on_line(f, points_x_range) for i in range(points_number)]
  print_points(points)


def generate_c_set():
  r = 100
  points_number = 1000

  points = [create_random_point_on_circle(r) for i in range(points_number)]
  print_points(points)

def generate_b_set():
  points_number = 10**5
  width = 1e-14
  plane_range = RangeXY(-width, width, -width, width)

  points = [create_random_point(plane_range) for i in range(points_number)]
  print_points(points)
  
def generate_a_set():
  points_number = 10**5
  width = 1e3
  plane_range = RangeXY(-width, width, -width, width)

  points = [create_random_point(plane_range) for i in range(points_number)]
  print_points(points)
  

import getopt, sys

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
    elif o == "-b":
      generate_b_set()
      break
    elif o == "-c":
      generate_c_set()
      break
    elif o == "-d":
      generate_d_set()
      break
  else:
    print('No option selected')

def create_line_func_from_two_points(a, b):
  direction_coeficient = (b.y - a.y) / (b.x - a.x)
  translation_coeficient = b.y - direction_coeficient * b.x
  return lambda x: direction_coeficient * x + translation_coeficient


def create_random_point_on_line(f, x_range):
  low_x, high_x = x_range
  x = random.uniform(low_x, high_x)
  return Point(x, f(x))

def create_random_point(plane_range):
  x = random.uniform(plane_range.low_x, plane_range.high_x)
  y = random.uniform(plane_range.low_y, plane_range.high_y)
  return Point(x, y)

def create_random_point_on_circle(r):
  angle = random.uniform(0.0, 2*math.pi)
  x = r * math.cos(angle)
  y = r * math.sin(angle)

  return Point(x, y)

if __name__ == '__main__':
  main()

