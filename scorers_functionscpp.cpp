#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

#include "scorers_functions.h"
#include "class.h"        

vector<nation> nations( string file_name )      //funkcja tworzy wektor narodowo�ci strzelc�w ( wybiera unikalne nazwy kraj�w )
{
  vector<nation> errors;            //do zwracania podczas b��d�w
  fstream f{ file_name };           //za�adowanie pliku z danymi
  if( !f.good() )
  {
    cout << "ERROR: FILE IS NOT LOADED!" << endl;
    return errors;
  }
  string temp;                         //zmienna na pomijane dane
  string name;                         //nazwa pa�stwa
  vector<string> nationalities;        //wektor na nazwy pa�stw
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

  sort( nationalities.begin(), nationalities.end() );                //tak jak w turniejach i nazwach kraj�w, posortowanie i usuni�cie duplikat�w
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
  
  vector<nation> nations;                                 //wektor na narodowo�ci i ich strzelc�w
  for( it = nationalities.begin(); it < nationalities.end(); it++ )
  {
    string name = *it;                                    //pobranie narodowo�ci
    nation x( name );                                     //stworzeniu obiektu, kt�ry jako element name ma t� nazwe
    nations.push_back( x );                               //do��czenie obiektu na koniec wektora
  }
  if( size( nations ) != size( nationalities ) )          //wydruk kontrolny czy si� uda�o skopiowa� wszystkie nazwy
  {
    cout << "ERROR: DATA WAS NOT SENDED TO VECTOR!" << endl;
    return errors;
  }

  return nations;
}

vector<nation> load_data( string file_name )      //funkcja uzupe�nia w wektorze nations informacje o strzelcach
{
  vector<nation> errors;                 //wektor, kt�ry zostanie zwr�cony podczas b��d�w
  vector<nation> nationalities = nations( file_name );  //wykreowanie wektora narodowo�ci

  fstream f{ file_name };                //wczytanie pliku z danymi
  if( !f.good() )
  {
    cout << "ERROR: FILE DID NOT LOADED!" << endl;
    return errors;
  }

  string temp;                         //zmienna na pomijane dane
  string n1;                           //kraj gospodarz
  string n2;                           //kraj go��
  string nationality;                  //kraj, kt�ry zdoby� bramk�
  string name;                         //imi� i nazwisko strzelca
  string own_goal;                     //czy samob�j
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

    if( own_goal == "TRUE" )           //je�li gol by� samob�jczy to strzelca trzeba przyporz�dkowa� do narodowo�ci, kt�ra nie zdoby�a w tej sytuacji bramki
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
    
    int find = 0;             //flaga poszukuj�ca, czy pi�karz ju� jest w wektorze
    for( int i = 0; i < size( nationalities ); i++ )     //uzupe�nienie wektora o dane strzelc�w
    {
      if( nationalities[i].getName() == nationality )    //najpierw poszukiwania narodowo�ci
      {
        vector<player> temp = nationalities[i].getScorers(); //a potem w niej czy dany pi�karz ju� jest zapisany
        for( int j = 0; j < size( temp ); j++ )
        {
          if( temp[j].getName() == name )
          {
            temp[j].setGoal( own_goal, penalty );
            find = 1;              //je�li tak to zmieniamy flag�
            break;
          }
        }
        if( find == 0 )           //a je�li nie to tworzymy nowy obiekt ju� z dodanym golem obecnie rozpatrywanym
        {
          player newp( name, nationality );
          newp.setGoal( own_goal, penalty );
          temp.push_back( newp );
        }
        nationalities[i].setScorers( temp );       //zast�pienie wektora zaaktualizowanym
        break;
      }
    }

  }
  return nationalities;
}

bool compG( player &l, player &p )    //funkcja sortuj�ca ze wzgl�du na liczb� strzelonych bramek
{
  return l.getGoals() > p.getGoals();
}

vector<nation> sortG( vector<nation> data ) //funkcja sortuj�ca ze wzgl�du na liczb� strzelonych bramek
{
  for( int i = 0; i < size( data ); i++ )
  {
    vector<player> temp = data[i].getScorers();
    sort( temp.begin(), temp.end(), compG );
    data[i].setScorers( temp );
  }
  return data;
}

void NationRankings( vector<nation> data )  //wydrukowanie ranking�w krajowych strzelc�w i zapis do plik�w
{
  vector<nation> rankings = sortG( data );
  for( int i = 0; i < size( rankings ); i++ )
  {
    string nationality = rankings[i].getName();
    cout << nationality << ":" << endl;
    string file_name = nationality + ".txt";
    fstream ranking{ file_name, ios::out };   //plik do zapisu rankingu ( nazwa: narodowo��.txt ( nie dzia�a jedynie dla Wyspy �wi�tego Tomasza i Ksi���cej ) )
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

vector<player> all_scorers( vector<nation> data ) //funkcja zwraca wektor wszystkich pi�karzy do ranking�w og�lnych 
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

void world_ranking( vector<nation> data )      //funkcja tworzy �wiatowy ranking strzelc�w
{
  vector<player> scorers = all_scorers( data );
  sort( scorers.begin(), scorers.end(), compG );
  fstream ranking{ "goal_ranking.txt", ios::out };   //plik do zapisu rankingu ( nazwa: narodowo��.txt ( nie dzia�a jedynie dla Wyspy �wi�tego Tomasza i Ksi���cej ) )
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

bool compO( player &l, player &p )    //funkcja sortuj�ca ze wzgl�du na liczb� samob�j�w
{
  return l.getOwn() > p.getOwn();
}

void own_goal_ranking( vector<nation> data )      //funkcja tworzy �wiatowy ranking samob�j�w
{
  vector<player> scorers = all_scorers( data );
  sort( scorers.begin(), scorers.end(), compO );
  fstream ranking{ "owngoal_ranking.txt", ios::out };   //plik do zapisu rankingu ( nazwa: narodowo��.txt ( nie dzia�a jedynie dla Wyspy �wi�tego Tomasza i Ksi���cej ( chyba ze wzgl�du na jaki� znak w nazwie ) ) )
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
  cin >> nationality;          //nie dzia�a dla pa�stw, kt�rych nazwa sk�ada si� z wi�cej ni� jednego s�owa ( pr�bwa�em z getlinem, ale wtedy program wariowa� )
  string file_name = nationality + ".txt";
  fstream f{ file_name };           //za�adowanie pliku z danymi
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