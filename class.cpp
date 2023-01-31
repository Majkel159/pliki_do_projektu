#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "class.h"

//DO KLASY COUNTRY
country::country( string n )
{
  this->name = n;
}

country::country( const country &x )
{
  this->name = x.name;
  this->sum_pkt = x.sum_pkt;
  this->pkt_01 = x.pkt_01;
  this->pkt_02 = x.pkt_02;
  this->pkt_03 = x.pkt_03;
  this->pkt_04 = x.pkt_04;
  this->pkt_05 = x.pkt_05;
  this->pkt_06 = x.pkt_06;
  this->pkt_07 = x.pkt_07;
  this->pkt_08 = x.pkt_08;
  this->pkt_09 = x.pkt_09;
  this->pkt_10 = x.pkt_10;
  this->pkt_11 = x.pkt_11;
  this->pkt_12 = x.pkt_12;
  this->pkt_13 = x.pkt_13;
  this->pkt_14 = x.pkt_14;
  this->pkt_15 = x.pkt_15;
  this->pkt_16 = x.pkt_16;
  this->pkt_17 = x.pkt_17;
  this->pkt_18 = x.pkt_18;
  this->pkt_19 = x.pkt_19;
  this->pkt_20 = x.pkt_20;
  this->pkt_21 = x.pkt_21;
  this->pkt_22 = x.pkt_22;
}

string country::getName()
{
  return this->name;
}

void country::setSum_pkt( int pkt )
{
  this->sum_pkt += pkt;
}

int country::getSum_pkt()
{
  return this->sum_pkt;
}

void country::setY_pkt( string year, int pkt )
{
  if( year == "2001" ) this->pkt_01 += pkt;
  else if( year == "2002" ) this->pkt_02 += pkt; 
  else if( year == "2003" ) this->pkt_03 += pkt;  
  else if( year == "2004" ) this->pkt_04 += pkt; 
  else if( year == "2005" ) this->pkt_05 += pkt;
  else if( year == "2006" ) this->pkt_06 += pkt;
  else if( year == "2007" ) this->pkt_07 += pkt;
  else if( year == "2008" ) this->pkt_08 += pkt;
  else if( year == "2009" ) this->pkt_09 += pkt;
  else if( year == "2010" ) this->pkt_10 += pkt;
  else if( year == "2011" ) this->pkt_11 += pkt;
  else if( year == "2012" ) this->pkt_12 += pkt;
  else if( year == "2013" ) this->pkt_13 += pkt;
  else if( year == "2014" ) this->pkt_14 += pkt;
  else if( year == "2015" ) this->pkt_15 += pkt;
  else if( year == "2016" ) this->pkt_16 += pkt;
  else if( year == "2017" ) this->pkt_17 += pkt;
  else if( year == "2018" ) this->pkt_18 += pkt;
  else if( year == "2019" ) this->pkt_19 += pkt;
  else if( year == "2020" ) this->pkt_20 += pkt;
  else if( year == "2021" ) this->pkt_21 += pkt;
  else if( year == "2022" ) this->pkt_22 += pkt;
  else cout << "ERROR: WRONG ARGUMENT!" << endl; return;   //b³¹d jeœli podany jest z³y argument
}

int country::getY_pkt( int year )  //year jest liczb¹ od 1 do 22 dla prostoty pisania kodu
{
  switch( year )
  {
  case 1: return this->pkt_01;
  case 2: return this->pkt_02;
  case 3: return this->pkt_03;
  case 4: return this->pkt_04;
  case 5: return this->pkt_05;
  case 6: return this->pkt_06;
  case 7: return this->pkt_07;
  case 8: return this->pkt_08;
  case 9: return this->pkt_09;
  case 10: return this->pkt_10;
  case 11: return this->pkt_11;
  case 12: return this->pkt_12;
  case 13: return this->pkt_13;
  case 14: return this->pkt_14;
  case 15: return this->pkt_15;
  case 16: return this->pkt_16;
  case 17: return this->pkt_17;
  case 18: return this->pkt_18;
  case 19: return this->pkt_19;
  case 20: return this->pkt_20;
  case 21: return this->pkt_21;
  case 22: return this->pkt_22;
  default: cout << "ERROR: WRONG ARGUMENT!" << endl;  return -1;    //b³¹d jeœli podany jest z³y argument
  }
}


//DO KLASY PLAYER
player::player( string nam, string nat )
{
  this->name = nam;
  this->nationality = nat;
}

player::player( const player &x )
{
  this->name = x.name;
  this->nationality = x.nationality;
  this->sum_goals = x.sum_goals;
  this->own_goals = x.own_goals;
  this->penalty = x.penalty;
}

string player::getName()
{
  return this->name;
}

void player::setGoal( string own, string pen )
{
  if( own == "TRUE" )        //jeœli gol by³ samobójczy to nie zwiêksza licznik goli prawid³owych
  {
    this->own_goals++;
  }
  else
  {
    this->sum_goals++;
    if( pen == "TRUE" )
    {
      this->penalty++;
    }
  }
}

int player::getGoals()
{
  return this->sum_goals;
}

int player::getPenalty()
{
  return this->penalty;
}

int player::getOwn()
{
  return this->own_goals;
}

string player::getNationality()
{
  return this->nationality;
}


//DO KLASY NATION
nation::nation( string n )
{
  this->name = n;
}

nation::nation( const nation &x )
{
  this->name = x.name;
  this->scorers = x.scorers;
}

string nation::getName()
{
  return this->name;
}

vector<player> nation::getScorers()
{
  return this->scorers;
}

void nation::setScorers( vector<player> x )
{
  this->scorers = x;
}