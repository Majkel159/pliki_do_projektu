#pragma once

#include "class.h"

void CupTypes( string file_name );                  //funkcja zapisuje do pliku tekstowego wszystkie nazwy turniejów, w jakich dru¿yny bra³y udzia³
vector<country> countries( string file_name );      //funkcja zwraca wektor typu country z nadanymi ju¿ nazwami krajów gotowymi do przyjêcia informacji o punktach rankingowych
vector<country> FIFA_ranking( string file_name );           //funkcja u¿ywa wektora z klasami country do dodania ka¿demu pañstwu punktów do ogólnego i rocznego rankingu
bool comp( country &l, country &p );
bool comp1( country &l, country &p );
bool comp2( country &l, country &p );
bool comp3( country &l, country &p );
bool comp4( country &l, country &p );
bool comp5( country &l, country &p );
bool comp6( country &l, country &p );
bool comp7( country &l, country &p );
bool comp8( country &l, country &p );
bool comp9( country &l, country &p );
bool comp10( country &l, country &p );
bool comp11( country &l, country &p );
bool comp12( country &l, country &p );
bool comp13( country &l, country &p );
bool comp14( country &l, country &p );
bool comp15( country &l, country &p );
bool comp16( country &l, country &p );
bool comp17( country &l, country &p ); 
bool comp18( country &l, country &p );
bool comp19( country &l, country &p );
bool comp20( country &l, country &p );
bool comp21( country &l, country &p );
bool comp22( country &l, country &p );
void year_rankings( int count, string file_name, vector<country> nations );  //funkcja do tworzenia rocznych rankingów
void find_country( string file_name, string country_name );   //funkcja do znalezienia pozycji kraju w danym rankingu
