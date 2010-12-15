/** -*-c++-*-
 *  \class  treFileRecord
 *  \file   treFileRecord.hpp
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

#include <fstream>
#include <string>
#include <vector>
#include <treLib/treDataBlock.hpp>

#ifndef TREINDEX_HPP
#define TREINDEX_HPP

class treFileRecord
{
public:

    enum Size
    {
	SIZE = sizeof( int ) * 6
    };

    treFileRecord();
    ~treFileRecord(){};
    

    bool read( std::ifstream &file );
    bool write( std::ofstream &file );
    void print() const;
    unsigned int readFromBuffer( const char *buffer );
    unsigned int writeToBuffer( char *buffer ) const;

    void operator=( const treFileRecord &src );
    bool operator==( const treFileRecord &src ) const;
 
    void setChecksum( const unsigned int &x ) { checksum = x; }
    void setUncompressedSize( const unsigned int &x ) { uncompressedSize = x; }
    void setOffset( const unsigned int &x )  { offset  = x; }
    void setFormat( const unsigned int &x )  { format  = x; }
    void setSize( const unsigned int &x )    { size    = x; }
    void setNameOffset( const unsigned int &x ) { nameOffset = x; }
    void setFileName( const std::string &fn ) { fileName = fn; }
    void setMD5sum( const std::vector<unsigned char> &newSum )
	{
	    md5sum = newSum;
	}

    unsigned int getChecksum() const { return checksum; }
    unsigned int getUncompressedSize() const { return uncompressedSize; }
    unsigned int getOffset() const { return offset; }
    unsigned int getFormat() const { return format; }
    unsigned int getSize() const { return size; }
    unsigned int getNameOffset() const { return nameOffset; }
    const std::string &getFileName() const { return fileName; }
    const std::vector<unsigned char> & getMD5sum() const
	{
	    return md5sum;
	}

    bool readMD5( std::ifstream &file );
    bool writeMD5( std::ofstream &file ) const;
    unsigned int generateChecksum() const;

    treDataBlock &getDataBlock() { return dataBlock; }

protected:
    unsigned int checksum;
    unsigned int uncompressedSize;
    unsigned int offset;
    unsigned int format;
    unsigned int size;
    unsigned int nameOffset;
    std::vector<unsigned char> md5sum;
    std::string fileName;
    treDataBlock dataBlock;

};

#endif
