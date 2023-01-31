#pragma once

#include "class.h"

vector<nation> nations( string file_name );      //funkcja tworzy wektor narodowoœci strzelców
vector<nation> load_data( string file_name );    //funkcja uzupe³nia w wektorze nations informacje o strzelcach
bool compG( player &l, player &p );              //funkcja sortuj¹ca ze wzglêdu na liczbê strzelonych bramek
vector<nation> sortG( vector<nation> data );    //funkcja sortuj¹ca ze wzglêdu na liczbê strzelonych bramek
void NationRankings( vector<nation> data );    //wydrukowanie rankingów krajowych strzelców i zapis do plików
vector<player> all_scorers( vector<nation> data ); //funkcja zwraca wektor wszystkich pi³karzy do rankingów ogólnych 
void world_ranking( vector<nation> data );     //funkcja tworzy œwiatowy ranking strzelców
bool compO( player &l, player &p );    //funkcja sortuj¹ca ze wzglêdu na liczbê samobójów
void own_goal_ranking( vector<nation> data );      //funkcja tworzy œwiatowy ranking samobójów
void check_nation_ranking();                      //funkcja drukuje zawartoœæ pliku z danym rankingiem
