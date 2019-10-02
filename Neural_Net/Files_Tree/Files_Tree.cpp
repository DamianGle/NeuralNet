/*
 * File_Manager.cpp
 *
 *  Created on: 20 paź 2018
 *      Author: damian
 */
#include "Files_Tree.h"

using namespace std;
using namespace boost;

Element::Element(string adress, string nazwa, int nr_seryjny, unsigned typ)
	        : adres(adress), nazwa(nazwa), nr_seryjny(nr_seryjny), typ(typ)
{
	trim_left_if(adres, is_any_of( "." ));
	trim_left_if(nazwa, is_any_of( "." ));
}

ostream & Element:: drukuj(unsigned glebokosc, ostream & os, unsigned dlugosc_nazwy)
{
        string tmp( glebokosc, '\t' );
        os << tmp;

        if(nazwa.find(".") != std::string::npos)
        	os << setw( dlugosc_nazwy ) << left << "File:" << nazwa << "\tAddress: " << adres << '\n';
        else
        	os << setw( dlugosc_nazwy ) << left << "Folder:" << nazwa << "\tAddress: " << adres << '\n';

    return os;
}

long unsigned Plik::drzewoKatalogowDoPliku( ostream & strumien, string odstep)
{
    if( typ == DT_REG ) {
            trim_left_if( adres, is_any_of( "/" ) );
            ifstream plik( adres.c_str() );
            if( plik.bad() )
                 cout << "!!! Nie mozna otworzyc pliku\n";
            else {
                string tmp;
                     strumien << '\t' << nazwa << '\t' << adres << ":\n";

                while( !plik.eof() ) {
                    getline( plik, tmp );
                    strumien << tmp << '\n';
                }
                strumien << odstep;
                return 1;
            }
    }
    return 0;
}

void Katalog::reorganizujSciezke( string & adres )
{
    struct dirent * plik;

    string tmp_adres = adres;
    elementy.clear();

    if( tmp_adres.empty() )
         tmp_adres = ".";

    trim_left_if( tmp_adres, is_any_of( "/" ) );

    if( sciezka != NULL )
         closedir( sciezka );

    if(( sciezka = opendir( tmp_adres.c_str() ) ) == NULL )
    {}   //    pokazErrno();
    else {
    	plik = readdir( sciezka );
        while( plik ) {
            string adres_obecnego_pliku =( tmp_adres + "/" + plik->d_name );
            if( !strcmp( plik->d_name, "." ) ) {
            }
            else if( !strcmp( plik->d_name, ".." ) ) {
            }
            else if( jestKatalogiek( plik ) )
                 elementy.insert( new Katalog( adres_obecnego_pliku, plik->d_name, plik->d_ino, plik->d_type ) );
            else
                 elementy.insert( new Plik( adres_obecnego_pliku, plik->d_name, plik->d_ino, plik->d_type ) );
            plik = readdir( sciezka );
        }
    }
    closedir( sciezka );
    sciezka = NULL;
}

ostream & Katalog::drukuj(ostream & os, unsigned glebokosc, unsigned dlugosc_nazwy)
{
        string tmp( glebokosc, '\t' );
        os << tmp;
        os << setw( dlugosc_nazwy ) << nazwa << '\t' << adres << '\n';

        for( ptr_set < Element >::iterator it = elementy.begin(); it != elementy.end(); ++it )
        		it->drukuj(glebokosc + 1, os, dlugosc_nazwy );
        return os;
}

long unsigned Katalog::drzewoKatalogowDoPliku( ostream & strumien, string odstep)
{
    unsigned ilosc_plikow = 0;
    for( ptr_set < Element >::iterator it = elementy.begin(); it != elementy.end(); ++it )
         ilosc_plikow += it->drzewoKatalogowDoPliku( strumien, odstep);

    return ilosc_plikow;
}
