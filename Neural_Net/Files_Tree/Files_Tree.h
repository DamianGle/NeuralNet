/*
 * File_Manager.h
 *
 *  Created on: 20 paź 2018
 *      Author: damian
 */

#ifndef FILES_TREE_FILES_TREE_H_
#define FILES_TREE_FILES_TREE_H_

#include <iostream>
#include <iomanip>
#include <dirent.h>
#include <cstdio>
#include <cerrno>
#include <cstring>
#include <string>
#include <fstream>
#include <list>
#include <boost/ptr_container/ptr_set.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/tuple/tuple.hpp>

using namespace std;
using namespace boost;

class Element
{
	public:
		string adres;
	    string nazwa;
	    int nr_seryjny;
	    unsigned typ;

	    Element( string adress, string nazwa, int nr_seryjny, unsigned typ );

	    virtual ostream & drukuj(unsigned glebokosc = 0, ostream & os = cout, unsigned dlugosc_nazwy = 30 );
	    virtual long unsigned drzewoKatalogowDoPliku( ostream & strumien, string odstep = "\n") = 0;

	    virtual ~Element() {};
};

inline bool operator <( const Element & l, const Element & r )
{
    return l.nazwa < r.nazwa;
}

class Plik : public Element
{
	public:
    	Plik( string adres, string nazwa, int nr_seryjny, unsigned typ )
        : Element( adres, nazwa, nr_seryjny, typ ) { }

    	virtual long unsigned drzewoKatalogowDoPliku( ostream & strumien, string odstep = "\n");
};

class Katalog : public Element
{
	public:
    	ptr_set < Element > elementy;
    	DIR * sciezka;

    	Katalog( string adres, string nazwa = "", int nr_seryjny = 0, unsigned typ = DT_DIR )
        		: Element( adres, nazwa, nr_seryjny, typ )
    		{
    			sciezka = NULL;
    			reorganizujSciezke( adres );
    		}

    	void reorganizujSciezke( string & adres );
    	virtual ostream & drukuj(ostream & os = cout, unsigned glebokosc = 0, unsigned dlugosc_nazwy = 30);
    	static bool jestKatalogiek( dirent * plik ) {return( plik->d_type ) == DT_DIR;}
    	virtual long unsigned drzewoKatalogowDoPliku( ostream & strumien, string odstep = "\n");
};

#endif /* FILES_TREE_FILES_TREE_H_ */
