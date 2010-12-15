/** -*-c++-*-
 *  \file   treBuild.cpp
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
#include <stdlib.h> // for atoi()

int main( int argc, char **argv )
{

    if( 3 != argc )
    {
	std::cout << "Usage: treBuild <filelist.txt> <file.tre>" << std::endl;
	return 0;
    }

    treClass tre;

    // Load file names...
    std::vector<std::string> fileList;
    std::ifstream files( argv[1] );
    while( !files.eof() )
    {
	std::string junk, name;
	unsigned int compression;
	files >> junk >> name >> compression;
	if( !name.empty() )
	{
	    treFileRecord newFile;
	    newFile.setFileName( name );
	    newFile.setFormat( compression );
	    tre.getFileRecordList().push_back( newFile );
	}
    }
    files.close();

    std::cout << "Num file names loaded: "
	      << tre.getFileRecordList().size() << std::endl;

    tre.setVersion( "5000" );
    tre.setFileBlockCompression( 2 );
    tre.setNameBlockCompression( 2 );
    tre.writeFile( std::string( argv[2] ) );

    return 0;
}
