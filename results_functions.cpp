#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

#include "results_functions.h"
#include "class.h"

void CupTypes( string file_name )  //funkcja, która z pliku wyodrêbnia wszystkie unikalne nazwy turniejów i zapisuje je do innego, bardziej pomocnicza,
//do u³o¿enia punktacji do rankingu
//argument jest nazw¹ pliku
{
  fstream f{ file_name };        //plik z danymi
  if( !f.good() )
  {
    cout << "ERROR: FILE IS NOT LOADED!" << endl;    //wydruk b³êdu za³adowania pliku
    return;
  }
  string temp;           //zmienna do pomijania nieu¿ywanych danych
  string tournament;     //zmienna na nazwê turnieju
  vector<string> cups;  //wektor zbieraj¹cy wszystkie nazwy turniejów
  while( !f.eof() )
  {
    for( int i = 0; i < 5; i++ )
    {
      getline( f, temp, ',' );       //pomijanie nieu¿ywanych danych
    }
    getline( f, tournament, ',' );   //pobranie nazwy turnieju
    cups.push_back( tournament );   //i zapisanie na koñcu wektora
    getline( f, temp );              //pominiêcie reszty linii
  }
  f.close();
  cout<< "Number of loaded data: " << size( cups ) << endl;     //wydruk kontrolny czy uda³o siê pobraæ dane
  sort( cups.begin(), cups.end() );                            //posortowanie w celu usuniêcia duplikatów
  vector<string>::iterator it;
  int k = 0;                                                     //ta zmienna bêdzie pamiêtaæ, do którego indeksu nie ma ju¿ duplikatów, ¿eby ich
                                                                 //nie sprawdzaæ niepotrzebnie
  while( 1 )
  {
    int count = 0;         //jeœli po pêtli ta wartoœæ jest wci¹¿ 0 tzn. ¿e pêtla siê nie wykona³a, a to znaczy, ¿e ju¿ nie ma duplikatów i mo¿na zakoñczyæ while'a
    for( it = cups.begin() + k; it < cups.end() - 1; it++ )
    {
      count++;
      if( *it == *( it + 1 ) )
      {
        cups.erase( it );        //usuwa element i przerywa pêtle, bo po usuniêciu elementu iterator mo¿e nie dzia³aæ poprawnie
        break;
      }
      k++;
    }
    if( count == 0 )break;
  }

  cout << size( cups ) << endl;  //kontrolne sprawdzenie czy siê uda³o (dla mnie przy tworzeniu programu, gdy ju¿ wiedzia³em jaka powinna byæ iloœæ)
  fstream puchary{ "puchary.txt", ios::out };   //plik do zapisu nazw turniejów
  if( !puchary.good() )
  {
    cout << "ERROR: FILE IS NOT LOADED!" << endl;
    return;
  }
  for( it = cups.begin(); it < cups.end(); it++ )
  {
    puchary << *it << endl;    //zapis unikalnych nazw do pliku
    cout << *it << endl;       //wypisanie na ekran równie¿
  }
  puchary.close();
}


vector<country> countries( string file_name )  //funkcja tworzy wektor typu country. Zawiera elementy z nadanymi nazwami krajów, jak w poprzedniej funkcji,
                                     //argumentem jest nazwa pliku. Wektor ten nastêpnie bêdzie przechowywa³ wszystkie inforamcje o ka¿dym pañstwie
                                     //funkcja u¿yta w kolejnej funkcji
{
  vector<country> errors;            //pusty wektor do zwracania podczas b³êdów
  fstream f{ file_name };            //otwarcie pliku z danymi
  if( !f.good() )
  {
    cout << "ERROR: FILE IS NOT LOADED!" << endl;
    return errors;
  }
  string temp;                         //zmienna na pomijane dane
  string c1;                           //kraj gospodarz
  string c2;                           //kraj goœæ
  vector<string> temporary;            //ta sama operacja co w przypadku uzyskiwania unikalnych nazw turniejów, tu pozyskujemy nazwy pañstw
  while( !f.eof() )
  {
    getline( f, temp, ',' );
    getline( f, c1, ',' );
    temporary.push_back( c1 );
    getline( f, c2, ',' );
    temporary.push_back( c2 );
    getline( f, temp );
  }
  f.close();
  sort( temporary.begin(), temporary.end() );
  vector<string>::iterator it;

  int k = 0;                                                  
  while( 1 )
  {
    int count = 0;
    for( it = temporary.begin() + k; it < temporary.end() - 1; it++ )
    {
      count++;
      if( *it == *( it + 1 ) )
      {
        temporary.erase( it );
        break;
      }
      k++;
    }
    if( count == 0 )break;
  }
  cout << "Number of nations: " << size( temporary ) << endl;  //wydruk kontrolny czy dobrze usuniêto duplikaty

  vector<country> nations;                                     //wektor na pañstwa
  for( it = temporary.begin(); it < temporary.end(); it++ )
  {
    string name = *it;                                         //pobranie nazwy kraju
    country nation( name );                                    //stworzeniu obiektu, który jako element name ma t¹ nazwe
    nations.push_back( nation );                               //do³¹czenie obiektu na koniec wektora
  }
  if( size( nations ) != size( temporary ) )                   //wydruk kontrolny czy siê uda³o
  {
    cout << "ERROR: DATA WAS NOT SENDED TO VECTOR!" << endl;
    return errors;
  }
  return nations;
}

vector<country> FIFA_ranking( string file_name )   //funkcja u¿ywa wektora z klasami country do dodania ka¿demu pañstwu punktów do ogólnego i rocznego rankingu
{
  vector<country> errors;                 //wektor, który zostanie zwrócony podczas b³êdów
  vector<country> nations = countries( file_name );  //wykreowanie wektora pañstw
  vector<country>::iterator it;

  fstream f{ file_name };        //otworzenie pliku z danymi
  if( !f.good() )
  {
    cout << "ERROR: FILE DID NOT LOADED!" << endl;
    return errors;
  }

  char c;           //znak, do pobierania znaku z pliku do stworzenia roku
  string year;      //rok odbycia meczu
  string n1;        //nazwa "gospodarza"
  string n2;        //nazwa "goœcia"
  string sc1;       //iloœæ goli "gospodarza"
  int sco1;         //iloœæ goli "gospodarza" zamieniona na int
  string sc2;       //iloœæ goli "goœcia"
  int sco2;         //iloœæ goli "goœcia" zamieniona na int
  string cup;       //nazwa turnieju
  string temp;      //zmienna na niepotrzebne dane
  string winner;    //nazwa pañstwa, które wygra³o
  int pkt;          //iloœæ punktów, jakie kraj dostanie za ten mecz
  for( int i = 0; i < 3; i++ )        //pominiêcie 3 znaków na pocz¹tku pliku (nie wiem co znacz¹ te znaki)
  {
    c = f.get();   
  }
  while( !f.eof() )
  {
    for( int i = 0; i < 4; i++ )       //wczytywanie linijki
    {
      c = f.get();
      year += c;
    }
    getline( f, temp, ',' );
    getline( f, n1, ',' );
    getline( f, n2, ',' );
    getline( f, sc1, ',' );
    getline( f, sc2, ',' );
    getline( f, cup, ',' );
    getline( f, temp );

    sco1 = atoi( sc1.c_str() );
    sco2 = atoi( sc2.c_str() );
    if( sco1 > sco2 ) winner = n1;            //wskazanie zwyciê¿cy
    else if( sco2 > sco1 ) winner = n2;
    else                                     //jeœli by³ remis to nikt nie zdobywa punktów, wiêc dalsza czêœæ funkcji nie musi siê wykonywaæ
    {
      year = "";                             //ta zmienna powstaje nie przez getline, tylko przed dodawanie znaków, wiêc za ka¿dym razem trzeba j¹ wyzerowaæ
      continue;
    }

    /* Punktacja rankingu:
    1. Mecz towarzyski - 1pkt
    2. Turniej towarzyski - 2pkt
    3. el. turniejów reg. - 3pkt
    4. Turniej regionalny - 4pkt
    5. Liga Narodów - 5pkt
    6. el. do mistrz. kontytnentu - 6pkt
    7. el . do mistrz. œwiata - 7pkt
    8. mistrz. oceanii - 8pkt
    9. mistrz. am. pó³n. - 9pkt
    10. mistrz. afryki, azji - 12pkt 
    11. mistrz. europy, am. p³d. - 20pkt
    12. mistrz. œw. - 25pkt */

    //obliczenie iloœci punktów za dany mecz dla zwyciê¿cy

    if( cup == "FIFA World Cup" ) pkt = 25;
    else if( cup == "Copa América" || cup == "UEFA Euro" ) pkt = 20;
    else if( cup == "AFC Asian Cup" || cup == "African Cup of Nations" ) pkt = 12;
    else if( cup == "Confederations Cup" ) pkt = 9;
    else if( cup == "Oceania Nations Cup" ) pkt = 8;
    else if( cup == "FIFA World Cup qualification" ) pkt = 7;
    else if( cup == "Oceania Nations Cup qualification" || cup == "African Cup of Nations qualification" || cup == "AFC Asian Cup qualification" ||
      cup == "Copa América qualification" || cup == "UEFA Euro qualification" ) pkt = 6;
    else if( cup == "UEFA Nations League" ) pkt = 5;
    else if( cup == "UNCAF Cup" || cup == "African Nations Championship" || cup == "AFC Challenge Cup" ||
      cup == "SAFF Cup" || cup == "Arab Cup" || cup == "AFF Championship" || cup == "CFU Caribbean Cup" || cup == "CONCACAF Nations League" ||
      cup == "VFF Cup" || cup == "CONMEBOL–UEFA Cup of Champions" || cup == "EAFF Championship" || cup == "COSAFA Cup" || cup == "Gold Cup" ||
      cup == "WAFF Championship" || cup == "Nordic Championship" ) pkt = 4;
    else if( cup == "Gold Cup qualification" || cup == "AFF Championship qualification" || cup == "Arab Cup qualification" ||
      cup == "AFC Challenge Cup qualification" || cup == "COSAFA Cup qualification" || cup == "African Nations Championship qualification" ||
      cup == "CFU Caribbean Cup qualification" || cup == "CONCACAF Nations League qualification" ) pkt = 3;
    else if( cup == "Friendly" ) pkt = 1;
    else pkt = 2;

    for( int i = 0; i < size( nations ); i++ )   //szuka po przygotowanym wektorze pola zwyciê¿cy danego meczu
    {
      string name = nations[i].getName();
      if( name == winner )
      {
        nations[i].setSum_pkt( pkt );      //jeœli znajdzie to powiêksza punkty i przerywa pêtle
        nations[i].setY_pkt( year, pkt );
        break;
      }
    }
    year = "";      //zerowanie roku
  }

  for( int i = 0; i < 23; i++ )            //zapisywanie do 23 plików ogólnego rankingu i rocznych
  {
    if( i == 0 )
    {
      fstream ranking{ "ranking.txt", ios::out };     //plik do zapisu rankingu
      if( !ranking.good() )
      {
        cout << "ERROR: FILE IS NOT LOADED!" << endl;
        return errors;
      }

      int j = 1;                        //zmienna na miejsce w rankingu
      sort( nations.begin(), nations.end(), comp );           //posortowanie wzglêdem odpowiedniego elementu ( pkt z danego roku )
      for( it = nations.begin(); it < nations.end(); it++ )      
      {
        country nation = *it;
        ranking << j << ", " << nation.getName() << ", " << nation.getSum_pkt() << endl;
        j++;
      }
      ranking.close();
    }

    else if( i == 1 )
    {
      sort( nations.begin(), nations.end(), comp1 );
      year_rankings( i, "ranking1.txt", nations );        //funkcja wpisuj¹ca do odpowiedniego pliku
    }

    else if( i == 2 )
    {
      sort( nations.begin(), nations.end(), comp2 );
      year_rankings( i, "ranking2.txt", nations );
    }

    else if( i == 3 )
    {
      sort( nations.begin(), nations.end(), comp3 );
      year_rankings( i, "ranking3.txt", nations );
    }

    else if( i == 4 )
    {
      sort( nations.begin(), nations.end(), comp4 );
      year_rankings( i, "ranking4.txt", nations );
    }

    else if( i == 5 )
    {
      sort( nations.begin(), nations.end(), comp5 );
      year_rankings( i, "ranking5.txt", nations );
    }

    else if( i == 6 )
    {
      sort( nations.begin(), nations.end(), comp6 );
      year_rankings( i, "ranking6.txt", nations );
    }

    else if( i == 7 )
    {
      sort( nations.begin(), nations.end(), comp7 );
      year_rankings( i, "ranking7.txt", nations );
    }

    else if( i == 8 )
    {
      sort( nations.begin(), nations.end(), comp8 );
      year_rankings( i, "ranking8.txt", nations );
    }

    else if( i == 9 )
    {
      sort( nations.begin(), nations.end(), comp9 );
      year_rankings( i, "ranking9.txt", nations );
    }

    else if( i == 10 )
    {
      sort( nations.begin(), nations.end(), comp10 );
      year_rankings( i, "ranking10.txt", nations );
    }

    else if( i == 11 )
    {
      sort( nations.begin(), nations.end(), comp11 );
      year_rankings( i, "ranking11.txt", nations );
    }

    else if( i == 12 )
    {
      sort( nations.begin(), nations.end(), comp12 );
      year_rankings( i, "ranking12.txt", nations );
    }

    else if( i == 13 )
    {
      sort( nations.begin(), nations.end(), comp13 );
      year_rankings( i, "ranking13.txt", nations );
    }

    else if( i == 14 )
    {
      sort( nations.begin(), nations.end(), comp14 );
      year_rankings( i, "ranking14.txt", nations );
    }

    else if( i == 15 )
    {
      sort( nations.begin(), nations.end(), comp15 );
      year_rankings( i, "ranking15.txt", nations );
    }

    else if( i == 16 )
    {
      sort( nations.begin(), nations.end(), comp16 );
      year_rankings( i, "ranking16.txt", nations );
    }

    else if( i == 17 )
    {
    sort( nations.begin(), nations.end(), comp17 );
    year_rankings( i, "ranking17.txt", nations );
    }

    else if( i == 18 )
    {
    sort( nations.begin(), nations.end(), comp18 );
    year_rankings( i, "ranking18.txt", nations );
    }

    else if( i == 19 )
    {
    sort( nations.begin(), nations.end(), comp19 );
    year_rankings( i, "ranking19.txt", nations );
    }

    else if( i == 20 )
    {
    sort( nations.begin(), nations.end(), comp20 );
    year_rankings( i, "ranking20.txt", nations );
    }

    else if( i == 21 )
    {
    sort( nations.begin(), nations.end(), comp21 );
    year_rankings( i, "ranking21.txt", nations );
    }

    else if( i == 22 )
    {
    sort( nations.begin(), nations.end(), comp22 );
    year_rankings( i, "ranking22.txt", nations );
    }
  }
  return nations;
}

void year_rankings( int count, string file_name, vector<country> nations )  //tworzy odpowiedni plik i zapisuje do niego tak samo jak dla rankingu ogólnego
{
  fstream f{ file_name, ios::out };                             
  if( !f.good() )
  {
    cout << "ERROR: FILE IS NOT LOADED!" << endl;
    return;
  }
  vector<country>::iterator it;
  int i = 1;
  for( it = nations.begin(); it < nations.end(); it++ )
  {
    country nation = *it;
    f << i << ", " << nation.getName() << ", " << nation.getY_pkt( count ) << endl;
    i++;
  }
  f.close();
}

bool comp( country &l,  country &p )    //funkcje sortuj¹ce
{
  return l.getSum_pkt() > p.getSum_pkt();
}

bool comp1( country &l, country &p )
{
  return l.getY_pkt( 1 ) > p.getY_pkt( 1 );
}

bool comp2( country &l, country &p )
{
  return l.getY_pkt( 2 ) > p.getY_pkt( 2 );
}

bool comp3( country &l, country &p )
{
  return l.getY_pkt( 3 ) > p.getY_pkt( 3 );
}

bool comp4( country &l, country &p )
{
  return l.getY_pkt( 4 ) > p.getY_pkt( 4 );
}

bool comp5( country &l, country &p )
{
  return l.getY_pkt( 5 ) > p.getY_pkt( 5 );
}

bool comp6( country &l, country &p )
{
  return l.getY_pkt( 6 ) > p.getY_pkt( 6 );
}

bool comp7( country &l, country &p )
{
  return l.getY_pkt( 7 ) > p.getY_pkt( 7 );
}

bool comp8( country &l, country &p )
{
  return l.getY_pkt( 8 ) > p.getY_pkt( 8 );
}

bool comp9( country &l, country &p )
{
  return l.getY_pkt( 9 ) > p.getY_pkt( 9 );
}

bool comp10( country &l, country &p )
{
  return l.getY_pkt( 10 ) > p.getY_pkt( 10 );
}

bool comp11( country &l, country &p )
{
  return l.getY_pkt( 11 ) > p.getY_pkt( 11 );
}

bool comp12( country &l, country &p )
{
  return l.getY_pkt( 12 ) > p.getY_pkt( 12 );
}

bool comp13( country &l, country &p )
{
  return l.getY_pkt( 13 ) > p.getY_pkt( 13 );
}

bool comp14( country &l, country &p )
{
  return l.getY_pkt( 14 ) > p.getY_pkt( 14 );
}

bool comp15( country &l, country &p )
{
  return l.getY_pkt( 15 ) > p.getY_pkt( 15 );
}

bool comp16( country &l, country &p )
{
  return l.getY_pkt( 16 ) > p.getY_pkt( 16 );
}

bool comp17( country &l, country &p )
{
  return l.getY_pkt( 17 ) > p.getY_pkt( 17 );
}

bool comp18( country &l, country &p )
{
  return l.getY_pkt( 18 ) > p.getY_pkt( 18 );
}

bool comp19( country &l, country &p )
{
  return l.getY_pkt( 19 ) > p.getY_pkt( 19 );
}

bool comp20( country &l, country &p )
{
  return l.getY_pkt( 20 ) > p.getY_pkt( 20 );
}

bool comp21( country &l, country &p )
{
  return l.getY_pkt( 21 ) > p.getY_pkt( 21 );
}

bool comp22( country &l, country &p )
{
  return l.getY_pkt( 22 ) > p.getY_pkt( 22 );
}

void find_country( string file_name, string country_name )  //parametrami funkcji s¹ plik z rankingiem oraz nazwa kraju do znalezienia
{
  fstream f{ file_name };       //otwarcie pliku z rankingiem
  if( !f.good() )
  {
    cout << "ERROR: FILE IS NOT LOADED!" << endl;
    return;
  }
  string pos, name, pkt;    //zmienne na pozycje, nazwê pañstwa i iloœæ punktów
  char c; //pomija spacje w pliku
  while( !f.eof() )
  {
    getline( f, pos, ',' );
    c = f.get();
    getline( f, name, ',' );
    c = f.get();
    getline( f, pkt );
    if( name == country_name )  //jeœli znajdzie odpowiedni kraj to wypisuje pozycje, nazwê i iloœæ punktów i przerywa funkcjê
    {
      f.close();
      cout << pos << ". " << name << ": " << pkt << "pkt" << endl;
      return;
    }
  }
  f.close();
  cout << "ERROR: COUNTRY NOT FOUND!" << endl;   //jeœli nie znalaz³ odpowiedniej linijki
  return;
}