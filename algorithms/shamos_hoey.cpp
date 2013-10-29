#include "shamos_hoey.h"
#include "../lib/core.h"
#include "../lib/print.h"
#include <iostream>
#include <queue>
#include <set>

using namespace std;
using namespace geo;

const double EPSILON = 1e-12;

enum EventType {
  SEGMENT_START = 1, INTERSECTION = 2, SEGMENT_END = 3
};

// TODO: extract somewher
struct SweepEvent {
  EventType type;
  core::Point point;
  int segment_id;
  int segment2_id;

  SweepEvent(EventType _type, core::Point _point, int _segment_id) : 
             type(_type), point(_point), segment_id(_segment_id) {}

  SweepEvent(EventType _type, core::Point _point,
             int _segment1_id, int _segment2_id) :
             type(_type), point(_point), segment_id(_segment1_id),
             segment2_id(_segment2_id) {}

  friend bool operator<(const SweepEvent& a, const SweepEvent& b);
};

// TODO: move to util::compare_lower_x_first_then_lower_y
bool compare_lower_x_first_then_lower_y(const core::Point& a, const core::Point& b) {
  return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool operator<(const SweepEvent& a, const SweepEvent& b) {
  // priority queue takes highest first so we have to reverse order
  return ! (compare_lower_x_first_then_lower_y(a.point, b.point)
            || (a.point == b.point && a.type < b.type));
}

void add_segments_to_event_queue(
    const vector<core::Segment>& segments, priority_queue<SweepEvent>& sweep_events) {
  
  for(int i=0; i<segments.size(); ++i) {
    const core::Segment& segment = segments[i];
    sweep_events.push(SweepEvent(SEGMENT_START, segment.first, i));
    sweep_events.push(SweepEvent(SEGMENT_END, segment.second, i));
  }
}


class SweepComparatorState {
  double sweep_position_x;
public:
  void set_sweep_x_position(double x) {
    sweep_position_x = x;
  }

  double get_sweep_x_position() {
    return sweep_position_x;
  }
};

class SweepComparator {
  vector<core::Segment>& segments;
  SweepComparatorState& state;

  double get_cross_y_with_sweep(const core::Segment& segment) {
    double segment_dx = segment.second.x - segment.first.x;
    double sweep_dx = state.get_sweep_x_position() - segment.first.x;
    double segment_dy = segment.second.y - segment.first.y;

    double sweep_dy = segment_dy * (sweep_dx / segment_dx);
    return segment.first.y + sweep_dy;      
  }

  bool is_above(const core::Segment& segment1, const core::Segment& segment2) {
    double segment1_y = get_cross_y_with_sweep(segment1);
    double segment2_y = get_cross_y_with_sweep(segment2);

    return segment1_y > segment2_y;
  }
 
public:
  SweepComparator(SweepComparatorState& _state, vector<core::Segment>& _segments)
                 : state(_state), segments(_segments) {}

  bool operator()(int segment_id, int segment2_id) {
    return is_above(segments.at(segment_id), segments.at(segment2_id));
  }
};

typedef multiset<int, SweepComparator> SweepState;

void print_set(SweepState& int_set) {
  cout.precision(15);
  cout << "sweep state: ";
  for(SweepState::iterator it = int_set.begin(); it != int_set.end(); ++it) {
    cout << *it << ", ";
  }
  cout << endl;
}
  


vector<pair<int, int> > insert_and_get_new_neighbours(SweepState& sweep_state, int new_segment_id) {
  vector<pair<int, int> > new_neighbours;

  SweepState::iterator it = sweep_state.insert(new_segment_id);

  if(it != sweep_state.begin()) {
    --it;
    new_neighbours.push_back(make_pair(*it, new_segment_id));
    ++it;
  }

  ++it;
  if(it != sweep_state.end()) {
    new_neighbours.push_back(make_pair(*it, new_segment_id)); 
  }

  return new_neighbours;
}

vector<pair<int, int> > erase_and_get_new_neighbours(SweepState& sweep_state, int segment_id) {
  vector<pair<int, int> > new_neighbours;

    // TODO: EXTRACT
  SweepState::iterator it = sweep_state.find(segment_id);
  if(it != sweep_state.begin()) {
    it--;
    int before = *it;
    it++;
    it++;
    if(it != sweep_state.end()) {
      int after = *it;
      new_neighbours.push_back(make_pair(before, after));
    }
  }

  sweep_state.erase(sweep_state.find(segment_id));

  return new_neighbours;
}

vector<pair<int, int> > swap_and_get_new_neighbours(
    SweepState& sweep_state, int segment_id, int segment2_id, SweepComparatorState& sweep_position) {
  vector<pair<int, int> > new_neighbours, new_neighbours1, new_neighbours2;

  double sweep_x = sweep_position.get_sweep_x_position();

  sweep_position.set_sweep_x_position(sweep_x - EPSILON);
  new_neighbours1 = erase_and_get_new_neighbours(sweep_state, segment_id);
  sweep_position.set_sweep_x_position(sweep_x +  EPSILON);
  new_neighbours2 = insert_and_get_new_neighbours(sweep_state, segment_id);
  sweep_position.set_sweep_x_position(sweep_x);

  new_neighbours1.insert(new_neighbours1.end(), new_neighbours2.begin(),
                        new_neighbours2.end());



  for(int i=0; i<new_neighbours1.size(); ++i) {
    if(new_neighbours1[i] != make_pair(segment_id, segment2_id)
       && new_neighbours1[i] != make_pair(segment2_id, segment_id)) {
      
      new_neighbours.push_back(new_neighbours1[i]);
    }
  }

  return new_neighbours;
}

bool is_already_in(set<pair<int, int> >& intersections, pair<int, int> segment_pair) {
  pair<int, int> reversed_pair = make_pair(segment_pair.second, segment_pair.first);

  return intersections.find(segment_pair) != intersections.end()
         || intersections.find(reversed_pair) != intersections.end();
}

vector<core::SegmentPair> algo::get_intersections_with_shamos_hoey(vector<core::Segment> segments) {
  // make sure that start of segment is more to the left
  for(int i=0; i<segments.size(); ++i) {
    core::Segment& segment = segments[i];

    if(segment.first.x > segment.second.x) {
      swap(segment.first, segment.second);
    }
  }

  set<pair<int, int> > intersections;

  priority_queue<SweepEvent> sweep_events;
  add_segments_to_event_queue(segments, sweep_events);

  SweepComparatorState sweep_position;
  SweepState sweep_state(SweepComparator(sweep_position, segments));

  while(!sweep_events.empty()) {
    //print_set(sweep_state);
    SweepEvent event = sweep_events.top(); sweep_events.pop();
    //cout << event.type << " " << util::to_printable(event.point) << endl;
    sweep_position.set_sweep_x_position(event.point.x);

    std::vector<pair<int, int> > new_neighbours;

    if(event.type == SEGMENT_START) {
      new_neighbours = insert_and_get_new_neighbours(
          sweep_state, event.segment_id);
    }
    else if(event.type == SEGMENT_END) {
      new_neighbours = erase_and_get_new_neighbours(
          sweep_state, event.segment_id);
    }
    else { // INTERSECTION
      new_neighbours = swap_and_get_new_neighbours(
          sweep_state, event.segment_id, event.segment2_id, sweep_position);
    }

    // test new neighbours
    for(int i=0; i<new_neighbours.size(); ++i) {
      pair<int, int>& neighbours = new_neighbours[i];
      core::Segment segment1 = segments[neighbours.first];
      core::Segment segment2 = segments[neighbours.second];

      if(core::intersects(segment1, segment2)) {
        if(is_already_in(intersections, 
                         make_pair(neighbours.first, neighbours.second))) {
          continue;
        }

        core::Point intersection_point = core::get_intersection(
            segment1, segment2);

        sweep_events.push(SweepEvent(INTERSECTION, intersection_point,
                                     neighbours.first, neighbours.second));

        intersections.insert(make_pair(neighbours.first, neighbours.second));
      }
    }
  }
  
  vector<core::SegmentPair> result;
  for(set<pair<int, int> >::iterator it = intersections.begin(); it != intersections.end(); ++it) {
    result.push_back(core::SegmentPair(segments[it->first], segments[it->second]));
  }

  return result;
}
