#include "shamos_hoey.h"
#include "../lib/core.h"
#include "../lib/print.h"
#include <iostream>
#include <queue>
#include <set>

using namespace std;
using namespace geo;

enum EventType {
  SEGMENT_START, SEGMENT_END, INTERSECTION
};

// TODO: extract somewher
struct SweepEvent {
  EventType type;
  core::Point point;
  int segment_id;
  int segment2_id;

  SweepEvent(EventType _type, core::Point _point, int _segment_id) : 
             type(_type), point(_point), segment_id(_segment_id) {}

  friend bool operator<(const SweepEvent& a, const SweepEvent& b);
};

// TODO: move to util::compare_lower_x_first_then_lower_y
bool compare_lower_x_first_then_lower_y(const core::Point& a, const core::Point& b) {
  return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool operator<(const SweepEvent& a, const SweepEvent& b) {
  // priority queue takes highest first so we have to reverse order
  return ! compare_lower_x_first_then_lower_y(a.point, b.point);
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
    return get_cross_y_with_sweep(segment1) > get_cross_y_with_sweep(segment2);
  }
public:
  SweepComparator(SweepComparatorState& _state, vector<core::Segment>& _segments)
                 : state(_state), segments(_segments) {}

  bool operator()(int segment_id, int segment2_id) {
    return is_above(segments.at(segment_id), segments.at(segment2_id));
  }
};

void print_set(set<int, SweepComparator>& int_set) {
  cout << "sweep state: ";
  for(set<int>::iterator it = int_set.begin(); it != int_set.end(); ++it) {
    cout << *it << ", ";
  }
  cout << endl;
}
  

typedef set<int, SweepComparator> SweepState;

vector<pair<int, int> > insert_and_get_new_neighbours(SweepState& sweep_state, int new_segment_id) {
  vector<pair<int, int> > new_neighbours;

  SweepState::iterator it = sweep_state.insert(new_segment_id).first;

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

  sweep_state.erase(segment_id);

  return new_neighbours;
}


vector<core::SegmentPair> algo::get_intersections_with_shamos_hoey(vector<core::Segment> segments) {
  vector<core::SegmentPair> result;

  priority_queue<SweepEvent> sweep_events;
  add_segments_to_event_queue(segments, sweep_events);

  SweepComparatorState sweep_position;
  sweep_position.set_sweep_x_position(5.0f);
  SweepState sweep_state(SweepComparator(sweep_position, segments));

  while(!sweep_events.empty()) {
    SweepEvent event = sweep_events.top(); sweep_events.pop();
    cout << util::to_printable(event.point) << " " << event.type << " " << event.segment_id << endl;

    if(event.type == SEGMENT_START) {
      vector<pair<int, int> > new_neighbours = insert_and_get_new_neighbours(
          sweep_state, event.segment_id);

      // TODO
    }
    else if(event.type == SEGMENT_END) {
      vector<pair<int, int> > new_neighbours = erase_and_get_new_neighbours(
          sweep_state, event.segment_id);

      // TODO
    }
    else { // SEGMENT_INTERSECTION
      // reverse segments in set -> reinsert
      // 
    }

    print_set(sweep_state);
  }
  
  return result;
}
