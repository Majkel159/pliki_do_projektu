#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

#include "class.h"                //klasy   
#include "results_functions.h"    //funkcje wyników i ich opisy
#include "scorers_functions.h"    //funkcje strzelców i ich opisy

int main() {
  char end = 'n';
  while( end == 'n' )
  {
    cout << "What you want to see? (write a number):" << endl;
    cout << "1. Cup Types     2. FIFA Rankings    3. Position of country in one of rankings" << endl;
    cout << "4. World Scorers Ranking       5. World Owngoals Ranking     6. National Scorers Rankings" << endl;
    cout << "7. One of Nationalities Scorers Ranking" << endl;
    int choose;
    cin >> choose;
    if( choose == 1 )
    {
      CupTypes( "wyniki.csv" );
    }

    else if( choose == 2 )
    {
      vector<country> ranking = FIFA_ranking( "wyniki.csv" );
    }

    else if( choose == 3 )
    {
      cout << "Write file name of year you want to see country position and a country name: " << endl;
      cout << "( File format: ranking.txt ( ranking of all time ) or rankingx.txt ( x is a year of ranking ( 1-22 ) ) )" << endl;
      cout << "np. ranking3.txt Poland" << endl;
      string file_name;
      string country_name;
      cin >> file_name;
      cin >> country_name;
      find_country( file_name, country_name );
    }

    else if( choose == 4 )
    {
      vector<nation> x = load_data( "strzelcy.csv" );
      world_ranking( x );
    }

    else if( choose == 5 )
    {
      vector<nation> x = load_data( "strzelcy.csv" );
      own_goal_ranking( x );
    }

    else if( choose == 6 )
    {
      vector<nation> x = load_data( "strzelcy.csv" );
      NationRankings( x );
    }

    else if( choose == 7 )
    {
      check_nation_ranking();
    }

    else
    {
      cout << "WRONG NUMBER! TRY AGAIN!" << endl << endl;
      continue;
    }

    cout << "Do you want to finish? [y/n]: " << endl;
    cin >> end;
  }

  return 0;
}