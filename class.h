#pragma once

class country             //klasa pañstwa do rankingu FIFA
{
private:
  string name;           //nazwa pañstwa
  int sum_pkt = 0;       //suma ogólna punktów rankingowych z wszystkich lat
  int pkt_01 = 0, pkt_02 = 0, pkt_03 = 0, pkt_04 = 0, pkt_05 = 0, pkt_06 = 0, pkt_07 = 0, pkt_08 = 0, pkt_09 = 0, pkt_10 = 0, pkt_11 = 0,  //roczne punkty
      pkt_12 = 0, pkt_13 = 0, pkt_14 = 0, pkt_15 = 0, pkt_16 = 0, pkt_17 = 0, pkt_18 = 0, pkt_19 = 0, pkt_20 = 0, pkt_21 = 0, pkt_22 = 0;

public:
  country() {};                 //konstruktor domyœlny
  country( string n );          //konstruktor parametrowy ( przy tworzeniu nowego obiektu od razu nadajê mu nazwê )
  country( const country &x );  //konstruktor kopiuj¹cy

  string getName();             //funkcja zwraca nazwê pañstwa
  void setSum_pkt( int pkt );   //funkcja dodaje do aktualnie liczby punktów punkty z danego meczu
  int getSum_pkt();             //funkcja zwraca ogóln¹ liczbê punktów pañstwa
  void setY_pkt( string year, int pkt );  //funkcja dodaje do aktualnej liczby punktów z danego roku punkty z danego meczu
  int getY_pkt( int year );     //funkcja zwraca punkty z danego roku
};

class player                    //klasa strzelca gola
{
private:
  string name;                  //imiê i nazwisko
  string nationality;           //narodowoœæ
  int sum_goals = 0;            //gole zawodnika
  int own_goals = 0;            //gole samobójcze
  int penalty = 0;              //gole z karnych
public:
  player() {};                  //konstruktor domyœlny
  player( string nam, string nat );   //konstruktor parametrowy ( przy tworzeniu nowego obiektu od razu nadajê mu nazwê i narodowoœæ )
  player( const player &x );    //konstruktor kopiuj¹cy

  string getName();             //funkcja zwraca imiê i nazwisko gracza
  void setGoal( string own, string pen );  //funkcja zwiêksza licznik goli w zale¿noœci jaki by³ to gol
  int getGoals();               //funkcja zwraca iloœæ strzelonych goli gracza
  int getPenalty();             //funkcja zwraca iloœæ goli gracza strzelonych z karnych
  int getOwn();                 //funkcja zwraca iloœæ samobójów gracza
  string getNationality();      //funkcja zwraca narodowoœæ gracza
};

class nation                   //klasa narodowoœci strzelców
{
private:
  string name;                //nazwa pañstwa
  vector<player> scorers;     //wektor zawieraj¹cy strzelców z danego pañstwa
public:
  nation() {};                //konstruktor domyœlny
  nation( string n );         //konstruktor parametrowy ( przy tworzeniu nowego obiektu od razu nadajê mu nazwê )
  nation( const nation &x );  //konstruktor kopiuj¹cy
  
  string getName();           //funkcja zwraca nazwê pañstwa
  vector<player> getScorers();   //funkcja zwraca wektor strzelców z danego pañstwa
  void setScorers( vector<player> x );   //funkcja ustawia wektor jako wektor strzelców danego pañstwa
};

