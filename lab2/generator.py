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

WIDTH = 1e3
POINTS_NUMBER = 10**1

def print_points(points):
  print(len(points))
  for point in points:
    print(point)

def get_vertices(rect_range):
  return [Point(rect_range.low_x, rect_range.low_y),
          Point(rect_range.high_x, rect_range.low_y),
          Point(rect_range.low_x, rect_range.high_y),
          Point(rect_range.high_x, rect_range.high_y)]


def get_point_on_bottom_border(rect_range):
  x = random.uniform(rect_range.low_x, rect_range.high_x)
  return Point(x, rect_range.low_y)

def get_point_on_left_border(rect_range):
  y = random.uniform(rect_range.low_y, rect_range.high_y)
  return Point(rect_range.low_x, y)

def get_point_on_down_top_diagonal(rect_range):
  part_size = random.uniform(0.0, 1.0)
  x = part_size * (rect_range.high_x - rect_range.low_x) + rect_range.low_x
  y = part_size * (rect_range.high_y - rect_range.low_y) + rect_range.low_y
  return Point(x, y)

def get_point_on_top_down_diagonal(rect_range):
  part_size = random.uniform(0.0, 1.0)
  x = part_size * (rect_range.high_x - rect_range.low_x) + rect_range.low_x
  y = (1.0 - part_size) * (rect_range.high_y - rect_range.low_y) + rect_range.low_y
  return Point(x, y)

def generate_d_set():
  axis_points_number = 2500
  diagonal_points_number = 2000
  rect_range = RangeXY(0, 10, 0, 10)

  points = get_vertices(rect_range) + (
      [get_point_on_bottom_border(rect_range) for i in range(axis_points_number)]) + (
      [get_point_on_left_border(rect_range) for i in range(axis_points_number)]) + (
      [get_point_on_top_down_diagonal(rect_range) for i in range(diagonal_points_number)]) + (
      [get_point_on_down_top_diagonal(rect_range) for i in range(diagonal_points_number)])

  print_points(points)

def generate_c_set():
  points_number = 100000
  width = 10
  rect_range = RangeXY(-width, width, -width, width)

  points = [create_random_point_on_border(rect_range) for i in range(points_number)]
  print_points(points)

def generate_b_set():
  r = 10
  points_number = 10000

  points = [create_random_point_on_circle(r) for i in range(points_number)]
  print_points(points)

def generate_a_set():
  points_number = 100000
  width = 100
  plane_range = RangeXY(-width, width, -width, width)

  points = [create_random_point(plane_range) for i in range(points_number)]
  print_points(points)
  

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

BOTTOM = 1
TOP = 2
LEFT = 3
RIGHT = 4

def get_random_edge(x_range):
  dy = x_range.high_y - x_range.low_y
  dx = x_range.high_x - x_range.low_x
  ratio =  dx / (dx + dy) 
  which_border = random.uniform(0.0, 2.0)

  if which_border < ratio:
    return BOTTOM
  elif which_border < 1.0:
    return LEFT
  elif which_border < (ratio + 1.0):
    return TOP
  else:
    return RIGHT


def create_random_point_on_border(x_range):
  edge = get_random_edge(x_range)

  if edge == BOTTOM or edge == TOP:
    x = random.uniform(x_range.low_x, x_range.high_x)
  else:
    y = random.uniform(x_range.low_y, x_range.high_y)

  if edge == BOTTOM:
    y = x_range.low_y
  elif edge == TOP:
    y = x_range.high_y
  elif edge == LEFT:
    x = x_range.low_x
  else:
    x = x_range.high_x

  return Point(x, y)

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

