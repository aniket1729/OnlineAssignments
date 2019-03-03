/*
 * Padayatra
 *
 * https://onlinecourses.nptel.ac.in/noc19_cs11/progassignment?name=107
 *
 * Design and Analysis of Algorithms
 * Week 4 Programming Assignment
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define False 0
#define True 1

#define INVALID_TOWN 0
#define INVALID_PATH -1
#define MIN_DISTANCE 0

#define CONTAINER_SEARCH(CONTAINER, SEARCH_VAL) find(CONTAINER.begin(), CONTAINER.end(), SEARCH_VAL)

#define DEBUG 0

class TownNeighbours {
    vector<int> m_neighbouringTownsAt;
    vector<int> m_neighbouringDistances;
    vector<bool> m_neighbouringProcessed;    /* To avoid duplication of processing in Adjecency List */

public:
    void AddNeighbour(const int& to_town_at, const int& to_distance) {
        m_neighbouringTownsAt.push_back(to_town_at);
        m_neighbouringDistances.push_back(to_distance);
        m_neighbouringProcessed.push_back(False);
    }

    int GetNeighboursCount(void) const { return m_neighbouringTownsAt.size(); }

    int GetNeighboursTown(int index, int& to_town_at, int& to_distance, bool& is_processed) {
        if( index < m_neighbouringTownsAt.size() ) {
            to_town_at = m_neighbouringTownsAt[index];
            to_distance = m_neighbouringDistances[index];
            is_processed = m_neighbouringProcessed[index];
            return 0;

        } else {
            to_town_at = INVALID_TOWN;
            to_distance = INVALID_PATH;
            is_processed = False;
            return -1;
        }
    }

    int ChangeRoadDistance(const int& index, const int& distance) {
        if( index < m_neighbouringTownsAt.size() ) {
            m_neighbouringDistances[index] = distance;
            return 0;
        }
        return -1;
    }

    int ChangeNeighbourDistance(const int& neighbour_id, const int& distance) {
        auto neighbour_at = CONTAINER_SEARCH(m_neighbouringTownsAt, neighbour_id);
        if( neighbour_at != m_neighbouringTownsAt.end() ) {
            int neighbour_index = neighbour_at - m_neighbouringTownsAt.begin();
            m_neighbouringDistances[neighbour_index] = distance;
            return 0;
        }
        return -1;
    }

    int IsProcessed(const int& index) {
        if( index < m_neighbouringTownsAt.size() ) {
            return m_neighbouringProcessed[index];

        }
        return -1;
    }

    int ProcessRoad(const int& index, const bool& flag) {
        if( index < m_neighbouringTownsAt.size() ) {
            m_neighbouringProcessed[index] = flag;
            return 0;
        }
        return -1;
    }

    int NeighbourProcessRoad(const int& neighbour_id, const bool& flag) {
        auto neighbour_at = CONTAINER_SEARCH(m_neighbouringTownsAt, neighbour_id);
        if( neighbour_at != m_neighbouringTownsAt.end() ) {
            int neighbour_index = neighbour_at - m_neighbouringTownsAt.begin();
            m_neighbouringProcessed[neighbour_index] = flag;
            return 0;
        }
        return -1;
    }
};

struct VisitedTown {
    bool m_visited;
    int m_distance;

    VisitedTown() : m_visited(False), m_distance(m_minDistance) { }
    VisitedTown(const bool& visited, const int& distance) : m_visited(visited), m_distance(distance) { }


    static int m_minDistance;

    static void ResetMinDistance(const int& distance) { m_minDistance = distance; }
    friend bool IsMinNonvisited(VisitedTown visited_town);
};

int VisitedTown::m_minDistance;

bool IsMinNonvisited(VisitedTown visited_town) {
    return ( visited_town.m_visited == False && visited_town.m_distance < VisitedTown::m_minDistance );
}

class Constituency {
    vector<int> m_townsId;
    vector<TownNeighbours> m_townConnectionsLists;

    int m_maxDistance;


protected:
    int GetShortestPath(const int& town1_at, const int& town2_at) {
        vector<VisitedTown> visited_towns(m_townsId.size(), VisitedTown(False, m_maxDistance+1));
        // OR    vector<VisitedTown> visited_towns(m_townsId.size(), VisitedTown{False, m_maxDistance+1});
        VisitedTown::ResetMinDistance(m_maxDistance+1);

        visited_towns[town1_at].m_distance = MIN_DISTANCE;

        #if DEBUG
        //AdjecentMap();
        for(auto i : visited_towns) {
            cout << " {" << i.m_visited << " " << i.m_distance << "}, ";
        }
        cout << endl;
        #endif

        for( int town_at = 0 ; town_at < m_townsId.size() ; town_at++ ) {
            auto visited_town_itr = find_if(visited_towns.begin(), visited_towns.end(), IsMinNonvisited);
            if( visited_town_itr != visited_towns.end() ) {

                int visited_town_at = visited_town_itr - visited_towns.begin();
                visited_towns[visited_town_at].m_visited = True;
                auto& townConnection = m_townConnectionsLists[visited_town_at];
                for( int neighbour_index = 0 ; neighbour_index < townConnection.GetNeighboursCount() ; neighbour_index++ ) {

                    int neighbour_at;
                    int neighbour_distance;
                    bool neighbour_processed;

                    if( townConnection.GetNeighboursTown(neighbour_index, neighbour_at, neighbour_distance, neighbour_processed) == 0 
                     && neighbour_distance != INVALID_PATH
                     && visited_towns[neighbour_at].m_visited == False
                     && visited_towns[neighbour_at].m_distance > (visited_towns[visited_town_at].m_distance + neighbour_distance) ) {

                        visited_towns[neighbour_at].m_distance = (visited_towns[visited_town_at].m_distance + neighbour_distance);
                    }
                }
                
            }
        }

        #if DEBUG
        for(auto i : visited_towns) {
            cout << " {" << i.m_visited << " " << i.m_distance << "}, ";
        }
        cout << endl;
        #endif

        return visited_towns[town2_at].m_distance;
    }

public:
    Constituency() : m_maxDistance(0) { }
    ~Constituency() { }

    void AddRoad(const int town1_id, const int town2_id, const int distance) {
        /* Create Adjecency List of Towns */

        int town1_at = 0;
        int town2_at = 0;


        auto town1_itr = CONTAINER_SEARCH(m_townsId, town1_id);
        if( town1_itr != m_townsId.end() )
            town1_at = town1_itr - m_townsId.begin();
        else {
            town1_at = m_townsId.size();
            m_townsId.push_back(town1_id);
            TownNeighbours new_town;
            m_townConnectionsLists.push_back(new_town);
        }

        auto town2_itr = CONTAINER_SEARCH(m_townsId, town2_id);
        if( town2_itr != m_townsId.end() )
            town2_at = town2_itr - m_townsId.begin();
        else {
            town2_at = m_townsId.size();
            m_townsId.push_back(town2_id);
            TownNeighbours new_town;
            m_townConnectionsLists.push_back(new_town);
        }


        m_townConnectionsLists[town1_at].AddNeighbour(town2_at, distance);
        m_townConnectionsLists[town2_at].AddNeighbour(town1_at, distance);

        m_maxDistance += distance;
    }

    void AdjecentMap(void) {
        /* Show Adjecency List */

        cout << endl << "Town Adjecent Map" << endl;
        for( int town_at = 0 ; town_at < m_townConnectionsLists.size() ; town_at++ ) {

            cout << "    " << town_at << ") Town " <<  m_townsId[town_at] << " :";

            auto& townConnection = m_townConnectionsLists[town_at];
            for( int neighbour_index = 0 ; neighbour_index < townConnection.GetNeighboursCount() ; neighbour_index++ ) {
                int neighbour_at;
                int neighbour_distance;
                bool neighbour_processed;

                if( townConnection.GetNeighboursTown(neighbour_index, neighbour_at, neighbour_distance, neighbour_processed) == 0 )
                    cout << " {Town " << m_townsId[neighbour_at] << ", Dist " << neighbour_distance << "},";
            }

            cout << endl;
        }
        cout << endl;
    }

    int LocatePadyatraCoverage(void) {
        /* Identify Shortest Cycle of Graph */
        int min_coverage_distance = INVALID_PATH;


        for( int town_at = 0 ; town_at < m_townConnectionsLists.size() ; town_at++ ) {

            auto& townConnection = m_townConnectionsLists[town_at];
            for( int neighbour_index = 0 ; neighbour_index < townConnection.GetNeighboursCount() ; neighbour_index++ ) {

                int neighbour_at;
                int neighbour_distance;
                bool neighbour_processed;

                townConnection.GetNeighboursTown(neighbour_index, neighbour_at, neighbour_distance, neighbour_processed);

                if( neighbour_processed == True )
                    continue;

                #if 1
                cout << "---" << endl;
                cout << "For town_at= " << town_at << " neighbour_index= " << neighbour_index << " => neighbour_at " << neighbour_at << " & _distance= " << neighbour_distance << endl;
                #endif

                townConnection.ProcessRoad(neighbour_index, True);
                m_townConnectionsLists[neighbour_at].NeighbourProcessRoad(town_at, True);

                /* Remove existing Path between 2 Towns */
                townConnection.ChangeRoadDistance(neighbour_index, INVALID_PATH);
                m_townConnectionsLists[neighbour_at].ChangeNeighbourDistance(town_at, INVALID_PATH);

                int alt_path_distance = GetShortestPath(town_at, neighbour_at);
                if( alt_path_distance != INVALID_PATH) {
                    int circle_distance = alt_path_distance + neighbour_distance;
                    if( min_coverage_distance == INVALID_PATH || circle_distance < min_coverage_distance )
                        min_coverage_distance = circle_distance;

                    #if DEBUG
                    cout << "Removed " << town_at << " & " << neighbour_at << " with distance= " << neighbour_distance << " circle= " << circle_distance << " Min= " << min_coverage_distance << endl;
                    #endif
                }

                /* Restore existing Path between 2 Towns */ 
                townConnection.ChangeRoadDistance(neighbour_index, neighbour_distance);
                m_townConnectionsLists[neighbour_at].ChangeNeighbourDistance(town_at, neighbour_distance);

            }
        }


        return min_coverage_distance;
    }
};

int main(int argc, char** argv)
{
    int no_of_roads;
    int town_S, town_T, town_ST_distance;
    Constituency constituency_area;

    int i;

    /* Read Input */
    cin >> no_of_roads;
    for( i = 0 ; i < no_of_roads ; i++ ) {
        cin >> town_S >> town_T >> town_ST_distance;
        constituency_area.AddRoad(town_S, town_T, town_ST_distance);
    }


    #if DEBUG
    /* */
    constituency_area.AdjecentMap();
    #endif


    /* */
    cout << constituency_area.LocatePadyatraCoverage() << endl;

    return 1;
}
