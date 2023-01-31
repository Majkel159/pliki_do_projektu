#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

#include "scorers_functions.h"
#include "class.h"        

vector<nation> nations( string file_name )      //funkcja tworzy wektor narodowoœci strzelców ( wybiera unikalne nazwy krajów )
{
  vector<nation> errors;            //do zwracania podczas b³êdów
  fstream f{ file_name };           //za³adowanie pliku z danymi
  if( !f.good() )
  {
    cout << "ERROR: FILE IS NOT LOADED!" << endl;
    return errors;
  }
  string temp;                         //zmienna na pomijane dane
  string name;                         //nazwa pañstwa
  vector<string> nationalities;        //wektor na nazwy pañstw
  while( !f.eof() )                    //wczytywanie danych z pliku
  {
    for( int i = 0; i < 3; i++ )
    {
      getline( f, temp, ',' );
    }
    getline( f, name, ',' );
    nationalities.push_back( name );
    getline( f, temp );
  }
  f.close();

  sort( nationalities.begin(), nationalities.end() );                //tak jak w turniejach i nazwach krajów, posortowanie i usuniêcie duplikatów
  vector<string>::iterator it;
  int k = 0;                                                  
                                                             
  while( 1 )
  {
    int count = 0; 
    for( it = nationalities.begin() + k; it < nationalities.end() - 1; it++ )
    {
      count++;
      if( *it == *( it + 1 ) )
      {
        nationalities.erase( it );
        break;
      }
      k++;
    }
    if( count == 0 )break;
  }
  cout << "Number of nations: " << size( nationalities ) << endl;
  
  vector<nation> nations;                                 //wektor na narodowoœci i ich strzelców
  for( it = nationalities.begin(); it < nationalities.end(); it++ )
  {
    string name = *it;                                    //pobranie narodowoœci
    nation x( name );                                     //stworzeniu obiektu, który jako element name ma t¹ nazwe
    nations.push_back( x );                               //do³¹czenie obiektu na koniec wektora
  }
  if( size( nations ) != size( nationalities ) )          //wydruk kontrolny czy siê uda³o skopiowaæ wszystkie nazwy
  {
    cout << "ERROR: DATA WAS NOT SENDED TO VECTOR!" << endl;
    return errors;
  }

  return nations;
}

vector<nation> load_data( string file_name )      //funkcja uzupe³nia w wektorze nations informacje o strzelcach
{
  vector<nation> errors;                 //wektor, który zostanie zwrócony podczas b³êdów
  vector<nation> nationalities = nations( file_name );  //wykreowanie wektora narodowoœci

  fstream f{ file_name };                //wczytanie pliku z danymi
  if( !f.good() )
  {
    cout << "ERROR: FILE DID NOT LOADED!" << endl;
    return errors;
  }

  string temp;                         //zmienna na pomijane dane
  string n1;                           //kraj gospodarz
  string n2;                           //kraj goœæ
  string nationality;                  //kraj, który zdoby³ bramkê
  string name;                         //imiê i nazwisko strzelca
  string own_goal;                     //czy samobój
  string penalty;                      //czy gol z karnego

  while( !f.eof() )                    //wczytanie danych z pliku
  {
    getline( f, temp, ',' );
    getline( f, n1, ',' );
    getline( f, n2, ',' );
    getline( f, nationality, ',' );
    getline( f, name, ',' );
    getline( f, temp, ',' );
    getline( f, own_goal, ',' );
    getline( f, penalty );

    if( own_goal == "TRUE" )           //jeœli gol by³ samobójczy to strzelca trzeba przyporz¹dkowaæ do narodowoœci, która nie zdoby³a w tej sytuacji bramki
    {
      if( n1 == nationality )
      {
        nationality = n2;
      }
      else 
      {
        nationality = n1;
      }
    }
    
    int find = 0;             //flaga poszukuj¹ca, czy pi³karz ju¿ jest w wektorze
    for( int i = 0; i < size( nationalities ); i++ )     //uzupe³nienie wektora o dane strzelców
    {
      if( nationalities[i].getName() == nationality )    //najpierw poszukiwania narodowoœci
      {
        vector<player> temp = nationalities[i].getScorers(); //a potem w niej czy dany pi³karz ju¿ jest zapisany
        for( int j = 0; j < size( temp ); j++ )
        {
          if( temp[j].getName() == name )
          {
            temp[j].setGoal( own_goal, penalty );
            find = 1;              //jeœli tak to zmieniamy flagê
            break;
          }
        }
        if( find == 0 )           //a jeœli nie to tworzymy nowy obiekt ju¿ z dodanym golem obecnie rozpatrywanym
        {
          player newp( name, nationality );
          newp.setGoal( own_goal, penalty );
          temp.push_back( newp );
        }
        nationalities[i].setScorers( temp );       //zast¹pienie wektora zaaktualizowanym
        break;
      }
    }

  }
  return nationalities;
}

bool compG( player &l, player &p )    //funkcja sortuj¹ca ze wzglêdu na liczbê strzelonych bramek
{
  return l.getGoals() > p.getGoals();
}

vector<nation> sortG( vector<nation> data ) //funkcja sortuj¹ca ze wzglêdu na liczbê strzelonych bramek
{
  for( int i = 0; i < size( data ); i++ )
  {
    vector<player> temp = data[i].getScorers();
    sort( temp.begin(), temp.end(), compG );
    data[i].setScorers( temp );
  }
  return data;
}

void NationRankings( vector<nation> data )  //wydrukowanie rankingów krajowych strzelców i zapis do plików
{
  vector<nation> rankings = sortG( data );
  for( int i = 0; i < size( rankings ); i++ )
  {
    string nationality = rankings[i].getName();
    cout << nationality << ":" << endl;
    string file_name = nationality + ".txt";
    fstream ranking{ file_name, ios::out };   //plik do zapisu rankingu ( nazwa: narodowoœæ.txt ( nie dzia³a jedynie dla Wyspy Œwiêtego Tomasza i Ksi¹¿êcej ) )
    if( !ranking.good() )
    {
      cout << "ERROR: FILE IS NOT LOADED!" << endl;
    }
    vector<player> y = rankings[i].getScorers();
    for( int j = 0; j < size( y ); j++ )   //wypisuje do pliku jak i na ekran
    {
      ranking << j + 1 << ", " << y[j].getName() << ": " << y[j].getGoals() << "(" << y[j].getPenalty() << ")" << endl;
      cout << j + 1 << ", " << y[j].getName() << ": " << y[j].getGoals() << "(" << y[j].getPenalty() << ")" << endl;
    }
    ranking.close();
    cout << endl;
  }
}

vector<player> all_scorers( vector<nation> data ) //funkcja zwraca wektor wszystkich pi³karzy do rankingów ogólnych 
{
  vector<player> scorers;
  for( int i = 0; i < size( data ); i++ )
  {
    vector<player> temp = data[i].getScorers();
    for( int j = 0; j < size( temp ); j++ )
    {
      scorers.push_back( temp[j] );
    }
  }
  return scorers;
}

void world_ranking( vector<nation> data )      //funkcja tworzy œwiatowy ranking strzelców
{
  vector<player> scorers = all_scorers( data );
  sort( scorers.begin(), scorers.end(), compG );
  fstream ranking{ "goal_ranking.txt", ios::out };   //plik do zapisu rankingu ( nazwa: narodowoœæ.txt ( nie dzia³a jedynie dla Wyspy Œwiêtego Tomasza i Ksi¹¿êcej ) )
  if( !ranking.good() )
  {
    cout << "ERROR: FILE IS NOT LOADED!" << endl;
  }
  for( int j = 0; j < size( scorers ); j++ )   //wypisuje do pliku jak i na ekran
  {
    if( scorers[j].getGoals() == 0 ) break;
    ranking << j + 1 << ", " << scorers[j].getName() << " (" << scorers[j].getNationality() << ")" << ": " << scorers[j].getGoals() << "(" << scorers[j].getPenalty() << ")" << endl;
    cout << j + 1 << ", " << scorers[j].getName() << " (" << scorers[j].getNationality() << ")" << ": " << scorers[j].getGoals() << "(" << scorers[j].getPenalty() << ")" << endl;
  }
  ranking.close();
}

bool compO( player &l, player &p )    //funkcja sortuj¹ca ze wzglêdu na liczbê samobójów
{
  return l.getOwn() > p.getOwn();
}

void own_goal_ranking( vector<nation> data )      //funkcja tworzy œwiatowy ranking samobójów
{
  vector<player> scorers = all_scorers( data );
  sort( scorers.begin(), scorers.end(), compO );
  fstream ranking{ "owngoal_ranking.txt", ios::out };   //plik do zapisu rankingu ( nazwa: narodowoœæ.txt ( nie dzia³a jedynie dla Wyspy Œwiêtego Tomasza i Ksi¹¿êcej ( chyba ze wzglêdu na jakiœ znak w nazwie ) ) )
  if( !ranking.good() )
  {
    cout << "ERROR: FILE IS NOT LOADED!" << endl;
  }
  for( int j = 0; j < size( scorers ); j++ )   //wypisuje do pliku jak i na ekran
  {
    if( scorers[j].getOwn() == 0 ) break;
    ranking << j + 1 << ", " << scorers[j].getName() << " (" << scorers[j].getNationality() << ")" << ": " << scorers[j].getOwn() << endl;
    cout << j + 1 << ", " << scorers[j].getName() << " (" << scorers[j].getNationality() << ")" << ": " << scorers[j].getOwn() << endl;
  }
  ranking.close();
}

void check_nation_ranking()
{
  cout << "Which country ranking do you want to see?" << endl;
  string nationality;
  cin >> nationality;          //nie dzia³a dla pañstw, których nazwa sk³ada siê z wiêcej ni¿ jednego s³owa ( próbwa³em z getlinem, ale wtedy program wariowa³ )
  string file_name = nationality + ".txt";
  fstream f{ file_name };           //za³adowanie pliku z danymi
  if( !f.good() )
  {
    cout << "ERROR: FILE IS NOT LOADED!" << endl;
    return;
  }

  string temp;
  while( !f.eof() )
  {
    getline( f, temp );
    cout << temp << endl;
  }
  f.close();
}