/** -*-c++-*-
 *  \file   treDump.cpp
 *  \author Kenneth R. Sewell III

 treLib is used for the creation and deconstruction of .TRE files.
 Copyright (C) 2006-2009 Kenneth R. Sewell III
 
 This file is part of treLib.
 
 treLib is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 treLib is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with treLib; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <treLib/treClass.hpp>

#include <iostream>
#include <fstream>
#include <cstdlib> // for atoi()
#include <cstring> // For memcpy

int main( int argc, char **argv )
{

    if( (argc < 2) || (argc > 4) )
    {
	std::cout << "Usage: treDump <file.tre>" << std::endl;
	std::cout << "or" << std::endl;
	std::cout << "       treDump <file.tre> <record #>" << std::endl;
	std::cout << "or" << std::endl;
	std::cout << "       treDump <file.tre> all" << std::endl;
	std::cout << "or" << std::endl;
	std::cout << "       treDump <file.tre> <start record #> <end record>"
		  << std::endl;
	return 0;
    }

    treClass tre;
    if( !tre.readFile( std::string(argv[1]) ) )
    {
	std::cout << "Failed to read file: " << argv[1] << std::endl;
	return 0;
    }

    if( 3 == argc )
      {
	if( strncmp( argv[2], "all", 3 ) == 0 )
	  {
	    int startRecord = 0;
	    int endRecord = tre.getNumRecords();
	    for( int i = startRecord; i < endRecord; ++i )
	      {
		// Save
		tre.saveRecordAsFile( i );
	      }
	  }
	else
	  {
	    int recordNum = atoi(argv[2]);
	    // Save
	    tre.saveRecordAsFile( recordNum );
	  }
    }
    else if ( 4 == argc )
    {
	int startRecord = atoi(argv[2]);
	int endRecord = atoi(argv[3]);
	for( int i = startRecord; i <= endRecord; ++i )
	{
	    // Save
	    tre.saveRecordAsFile( i );
	}
    }
    else
    {
	// Print data
	//tre.printHeader();
	//tre.printIndexBlock();
	tre.printNameBlock();
    }

    return 0;
}
