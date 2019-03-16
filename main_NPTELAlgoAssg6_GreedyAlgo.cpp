/*
 * Sports Events in Stadium
 *
 * https://onlinecourses.nptel.ac.in/noc19_cs11/progassignment?name=114
 *
 * Design and Analysis of Algorithms
 * Week 6 Programming Assignment
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define DEBUG 0

class SportEvent {
    int m_startDate;
    int m_eventDays;
    int m_endDate;

public:
    SportEvent(const int& start_date, const int& event_days) : m_startDate(start_date), m_eventDays(event_days) {
        m_endDate = m_startDate + m_eventDays;
    }

    int GetStart() const { return m_startDate; }
    int GetEnd() const { return m_endDate; }

    friend bool compare_end_date(const SportEvent& event1, const SportEvent& event2);

    void print(void) {
        cout << "(" << m_startDate << ", " << m_eventDays << ")";
    }
};

bool compare_end_date(const SportEvent& event1, const SportEvent& event2) {
    return (event1.m_endDate < event2.m_endDate);
}

int main(int argc, char** argv) {
    int event_count;
    int i;
    int start_date, event_days;
    vector<SportEvent> all_events;

    cin >> event_count;
    for( i = 0 ; i < event_count ; i++ ) {
        cin >> start_date >> event_days;
        all_events.push_back(SportEvent(start_date, event_days));
    }

#if DEBUG
    cout << endl;
    for( auto event : all_events ) {
        event.print();
        cout << " ";
    }
    cout << endl;
#endif

    sort(all_events.begin(), all_events.end(), compare_end_date);

    auto itr = all_events.begin();
    int free_at = 0;
    while( itr != all_events.end() ) {
        if( itr->GetStart() < free_at )
            all_events.erase(itr);
        else {
            free_at = itr->GetEnd();
            itr++;
        }
    }

    cout << all_events.size() << endl;
#if DEBUG
    for( auto event : all_events ) {
        event.print();
        cout << " ";
    }
    cout << endl;
#endif

    return 0;
}
