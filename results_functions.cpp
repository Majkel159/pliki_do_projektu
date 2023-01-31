#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

#include "results_functions.h"
#include "class.h"

void CupTypes( string file_name )  //funkcja, kt�ra z pliku wyodr�bnia wszystkie unikalne nazwy turniej�w i zapisuje je do innego, bardziej pomocnicza,
//do u�o�enia punktacji do rankingu
//argument jest nazw� pliku
{
  fstream f{ file_name };        //plik z danymi
  if( !f.good() )
  {
    cout << "ERROR: FILE IS NOT LOADED!" << endl;    //wydruk b��du za�adowania pliku
    return;
  }
  string temp;           //zmienna do pomijania nieu�ywanych danych
  string tournament;     //zmienna na nazw� turnieju
  vector<string> cups;  //wektor zbieraj�cy wszystkie nazwy turniej�w
  while( !f.eof() )
  {
    for( int i = 0; i < 5; i++ )
    {
      getline( f, temp, ',' );       //pomijanie nieu�ywanych danych
    }
    getline( f, tournament, ',' );   //pobranie nazwy turnieju
    cups.push_back( tournament );   //i zapisanie na ko�cu wektora
    getline( f, temp );              //pomini�cie reszty linii
  }
  f.close();
  cout<< "Number of loaded data: " << size( cups ) << endl;     //wydruk kontrolny czy uda�o si� pobra� dane
  sort( cups.begin(), cups.end() );                            //posortowanie w celu usuni�cia duplikat�w
  vector<string>::iterator it;
  int k = 0;                                                     //ta zmienna b�dzie pami�ta�, do kt�rego indeksu nie ma ju� duplikat�w, �eby ich
                                                                 //nie sprawdza� niepotrzebnie
  while( 1 )
  {
    int count = 0;         //je�li po p�tli ta warto�� jest wci�� 0 tzn. �e p�tla si� nie wykona�a, a to znaczy, �e ju� nie ma duplikat�w i mo�na zako�czy� while'a
    for( it = cups.begin() + k; it < cups.end() - 1; it++ )
    {
      count++;
      if( *it == *( it + 1 ) )
      {
        cups.erase( it );        //usuwa element i przerywa p�tle, bo po usuni�ciu elementu iterator mo�e nie dzia�a� poprawnie
        break;
      }
      k++;
    }
    if( count == 0 )break;
  }

  cout << size( cups ) << endl;  //kontrolne sprawdzenie czy si� uda�o (dla mnie przy tworzeniu programu, gdy ju� wiedzia�em jaka powinna by� ilo��)
  fstream puchary{ "puchary.txt", ios::out };   //plik do zapisu nazw turniej�w
  if( !puchary.good() )
  {
    cout << "ERROR: FILE IS NOT LOADED!" << endl;
    return;
  }
  for( it = cups.begin(); it < cups.end(); it++ )
  {
    puchary << *it << endl;    //zapis unikalnych nazw do pliku
    cout << *it << endl;       //wypisanie na ekran r�wnie�
  }
  puchary.close();
}


vector<country> countries( string file_name )  //funkcja tworzy wektor typu country. Zawiera elementy z nadanymi nazwami kraj�w, jak w poprzedniej funkcji,
                                     //argumentem jest nazwa pliku. Wektor ten nast�pnie b�dzie przechowywa� wszystkie inforamcje o ka�dym pa�stwie
                                     //funkcja u�yta w kolejnej funkcji
{
  vector<country> errors;            //pusty wektor do zwracania podczas b��d�w
  fstream f{ file_name };            //otwarcie pliku z danymi
  if( !f.good() )
  {
    cout << "ERROR: FILE IS NOT LOADED!" << endl;
    return errors;
  }
  string temp;                         //zmienna na pomijane dane
  string c1;                           //kraj gospodarz
  string c2;                           //kraj go��
  vector<string> temporary;            //ta sama operacja co w przypadku uzyskiwania unikalnych nazw turniej�w, tu pozyskujemy nazwy pa�stw
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
  cout << "Number of nations: " << size( temporary ) << endl;  //wydruk kontrolny czy dobrze usuni�to duplikaty

  vector<country> nations;                                     //wektor na pa�stwa
  for( it = temporary.begin(); it < temporary.end(); it++ )
  {
    string name = *it;                                         //pobranie nazwy kraju
    country nation( name );                                    //stworzeniu obiektu, kt�ry jako element name ma t� nazwe
    nations.push_back( nation );                               //do��czenie obiektu na koniec wektora
  }
  if( size( nations ) != size( temporary ) )                   //wydruk kontrolny czy si� uda�o
  {
    cout << "ERROR: DATA WAS NOT SENDED TO VECTOR!" << endl;
    return errors;
  }
  return nations;
}

vector<country> FIFA_ranking( string file_name )   //funkcja u�ywa wektora z klasami country do dodania ka�demu pa�stwu punkt�w do og�lnego i rocznego rankingu
{
  vector<country> errors;                 //wektor, kt�ry zostanie zwr�cony podczas b��d�w
  vector<country> nations = countries( file_name );  //wykreowanie wektora pa�stw
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
  string n2;        //nazwa "go�cia"
  string sc1;       //ilo�� goli "gospodarza"
  int sco1;         //ilo�� goli "gospodarza" zamieniona na int
  string sc2;       //ilo�� goli "go�cia"
  int sco2;         //ilo�� goli "go�cia" zamieniona na int
  string cup;       //nazwa turnieju
  string temp;      //zmienna na niepotrzebne dane
  string winner;    //nazwa pa�stwa, kt�re wygra�o
  int pkt;          //ilo�� punkt�w, jakie kraj dostanie za ten mecz
  for( int i = 0; i < 3; i++ )        //pomini�cie 3 znak�w na pocz�tku pliku (nie wiem co znacz� te znaki)
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
    if( sco1 > sco2 ) winner = n1;            //wskazanie zwyci�cy
    else if( sco2 > sco1 ) winner = n2;
    else                                     //je�li by� remis to nikt nie zdobywa punkt�w, wi�c dalsza cz�� funkcji nie musi si� wykonywa�
    {
      year = "";                             //ta zmienna powstaje nie przez getline, tylko przed dodawanie znak�w, wi�c za ka�dym razem trzeba j� wyzerowa�
      continue;
    }

    /* Punktacja rankingu:
    1. Mecz towarzyski - 1pkt
    2. Turniej towarzyski - 2pkt
    3. el. turniej�w reg. - 3pkt
    4. Turniej regionalny - 4pkt
    5. Liga Narod�w - 5pkt
    6. el. do mistrz. kontytnentu - 6pkt
    7. el . do mistrz. �wiata - 7pkt
    8. mistrz. oceanii - 8pkt
    9. mistrz. am. p�n. - 9pkt
    10. mistrz. afryki, azji - 12pkt 
    11. mistrz. europy, am. p�d. - 20pkt
    12. mistrz. �w. - 25pkt */

    //obliczenie ilo�ci punkt�w za dany mecz dla zwyci�cy

    if( cup == "FIFA World Cup" ) pkt = 25;
    else if( cup == "Copa Am�rica" || cup == "UEFA Euro" ) pkt = 20;
    else if( cup == "AFC Asian Cup" || cup == "African Cup of Nations" ) pkt = 12;
    else if( cup == "Confederations Cup" ) pkt = 9;
    else if( cup == "Oceania Nations Cup" ) pkt = 8;
    else if( cup == "FIFA World Cup qualification" ) pkt = 7;
    else if( cup == "Oceania Nations Cup qualification" || cup == "African Cup of Nations qualification" || cup == "AFC Asian Cup qualification" ||
      cup == "Copa Am�rica qualification" || cup == "UEFA Euro qualification" ) pkt = 6;
    else if( cup == "UEFA Nations League" ) pkt = 5;
    else if( cup == "UNCAF Cup" || cup == "African Nations Championship" || cup == "AFC Challenge Cup" ||
      cup == "SAFF Cup" || cup == "Arab Cup" || cup == "AFF Championship" || cup == "CFU Caribbean Cup" || cup == "CONCACAF Nations League" ||
      cup == "VFF Cup" || cup == "CONMEBOL�UEFA Cup of Champions" || cup == "EAFF Championship" || cup == "COSAFA Cup" || cup == "Gold Cup" ||
      cup == "WAFF Championship" || cup == "Nordic Championship" ) pkt = 4;
    else if( cup == "Gold Cup qualification" || cup == "AFF Championship qualification" || cup == "Arab Cup qualification" ||
      cup == "AFC Challenge Cup qualification" || cup == "COSAFA Cup qualification" || cup == "African Nations Championship qualification" ||
      cup == "CFU Caribbean Cup qualification" || cup == "CONCACAF Nations League qualification" ) pkt = 3;
    else if( cup == "Friendly" ) pkt = 1;
    else pkt = 2;

    for( int i = 0; i < size( nations ); i++ )   //szuka po przygotowanym wektorze pola zwyci�cy danego meczu
    {
      string name = nations[i].getName();
      if( name == winner )
      {
        nations[i].setSum_pkt( pkt );      //je�li znajdzie to powi�ksza punkty i przerywa p�tle
        nations[i].setY_pkt( year, pkt );
        break;
      }
    }
    year = "";      //zerowanie roku
  }

  for( int i = 0; i < 23; i++ )            //zapisywanie do 23 plik�w og�lnego rankingu i rocznych
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
      sort( nations.begin(), nations.end(), comp );           //posortowanie wzgl�dem odpowiedniego elementu ( pkt z danego roku )
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
      year_rankings( i, "ranking1.txt", nations );        //funkcja wpisuj�ca do odpowiedniego pliku
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

void year_rankings( int count, string file_name, vector<country> nations )  //tworzy odpowiedni plik i zapisuje do niego tak samo jak dla rankingu og�lnego
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

bool comp( country &l,  country &p )    //funkcje sortuj�ce
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

void find_country( string file_name, string country_name )  //parametrami funkcji s� plik z rankingiem oraz nazwa kraju do znalezienia
{
  fstream f{ file_name };       //otwarcie pliku z rankingiem
  if( !f.good() )
  {
    cout << "ERROR: FILE IS NOT LOADED!" << endl;
    return;
  }
  string pos, name, pkt;    //zmienne na pozycje, nazw� pa�stwa i ilo�� punkt�w
  char c; //pomija spacje w pliku
  while( !f.eof() )
  {
    getline( f, pos, ',' );
    c = f.get();
    getline( f, name, ',' );
    c = f.get();
    getline( f, pkt );
    if( name == country_name )  //je�li znajdzie odpowiedni kraj to wypisuje pozycje, nazw� i ilo�� punkt�w i przerywa funkcj�
    {
      f.close();
      cout << pos << ". " << name << ": " << pkt << "pkt" << endl;
      return;
    }
  }
  f.close();
  cout << "ERROR: COUNTRY NOT FOUND!" << endl;   //je�li nie znalaz� odpowiedniej linijki
  return;
}