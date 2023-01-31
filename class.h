#pragma once

class country             //klasa pa�stwa do rankingu FIFA
{
private:
  string name;           //nazwa pa�stwa
  int sum_pkt = 0;       //suma og�lna punkt�w rankingowych z wszystkich lat
  int pkt_01 = 0, pkt_02 = 0, pkt_03 = 0, pkt_04 = 0, pkt_05 = 0, pkt_06 = 0, pkt_07 = 0, pkt_08 = 0, pkt_09 = 0, pkt_10 = 0, pkt_11 = 0,  //roczne punkty
      pkt_12 = 0, pkt_13 = 0, pkt_14 = 0, pkt_15 = 0, pkt_16 = 0, pkt_17 = 0, pkt_18 = 0, pkt_19 = 0, pkt_20 = 0, pkt_21 = 0, pkt_22 = 0;

public:
  country() {};                 //konstruktor domy�lny
  country( string n );          //konstruktor parametrowy ( przy tworzeniu nowego obiektu od razu nadaj� mu nazw� )
  country( const country &x );  //konstruktor kopiuj�cy

  string getName();             //funkcja zwraca nazw� pa�stwa
  void setSum_pkt( int pkt );   //funkcja dodaje do aktualnie liczby punkt�w punkty z danego meczu
  int getSum_pkt();             //funkcja zwraca og�ln� liczb� punkt�w pa�stwa
  void setY_pkt( string year, int pkt );  //funkcja dodaje do aktualnej liczby punkt�w z danego roku punkty z danego meczu
  int getY_pkt( int year );     //funkcja zwraca punkty z danego roku
};

class player                    //klasa strzelca gola
{
private:
  string name;                  //imi� i nazwisko
  string nationality;           //narodowo��
  int sum_goals = 0;            //gole zawodnika
  int own_goals = 0;            //gole samob�jcze
  int penalty = 0;              //gole z karnych
public:
  player() {};                  //konstruktor domy�lny
  player( string nam, string nat );   //konstruktor parametrowy ( przy tworzeniu nowego obiektu od razu nadaj� mu nazw� i narodowo�� )
  player( const player &x );    //konstruktor kopiuj�cy

  string getName();             //funkcja zwraca imi� i nazwisko gracza
  void setGoal( string own, string pen );  //funkcja zwi�ksza licznik goli w zale�no�ci jaki by� to gol
  int getGoals();               //funkcja zwraca ilo�� strzelonych goli gracza
  int getPenalty();             //funkcja zwraca ilo�� goli gracza strzelonych z karnych
  int getOwn();                 //funkcja zwraca ilo�� samob�j�w gracza
  string getNationality();      //funkcja zwraca narodowo�� gracza
};

class nation                   //klasa narodowo�ci strzelc�w
{
private:
  string name;                //nazwa pa�stwa
  vector<player> scorers;     //wektor zawieraj�cy strzelc�w z danego pa�stwa
public:
  nation() {};                //konstruktor domy�lny
  nation( string n );         //konstruktor parametrowy ( przy tworzeniu nowego obiektu od razu nadaj� mu nazw� )
  nation( const nation &x );  //konstruktor kopiuj�cy
  
  string getName();           //funkcja zwraca nazw� pa�stwa
  vector<player> getScorers();   //funkcja zwraca wektor strzelc�w z danego pa�stwa
  void setScorers( vector<player> x );   //funkcja ustawia wektor jako wektor strzelc�w danego pa�stwa
};

