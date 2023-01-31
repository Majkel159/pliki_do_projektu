#pragma once

#include "class.h"

vector<nation> nations( string file_name );      //funkcja tworzy wektor narodowo�ci strzelc�w
vector<nation> load_data( string file_name );    //funkcja uzupe�nia w wektorze nations informacje o strzelcach
bool compG( player &l, player &p );              //funkcja sortuj�ca ze wzgl�du na liczb� strzelonych bramek
vector<nation> sortG( vector<nation> data );    //funkcja sortuj�ca ze wzgl�du na liczb� strzelonych bramek
void NationRankings( vector<nation> data );    //wydrukowanie ranking�w krajowych strzelc�w i zapis do plik�w
vector<player> all_scorers( vector<nation> data ); //funkcja zwraca wektor wszystkich pi�karzy do ranking�w og�lnych 
void world_ranking( vector<nation> data );     //funkcja tworzy �wiatowy ranking strzelc�w
bool compO( player &l, player &p );    //funkcja sortuj�ca ze wzgl�du na liczb� samob�j�w
void own_goal_ranking( vector<nation> data );      //funkcja tworzy �wiatowy ranking samob�j�w
void check_nation_ranking();                      //funkcja drukuje zawarto�� pliku z danym rankingiem
