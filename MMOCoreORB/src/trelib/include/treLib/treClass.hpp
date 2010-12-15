/** -*-c++-*-
 *  \class  treClass
 *  \file   treClass.hpp
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
#include <sstream>
#include <string>
#include <vector>
#include <treLib/treFileRecord.hpp>
#include <treLib/treDataBlock.hpp>

#ifndef TRECLASS_HPP
#define TRECLASS_HPP

class treClass
{
public:
  treClass();
  ~treClass();

  bool readFile( const std::string &treName );
  bool readFile( std::ifstream &file );

  bool writeFile( const std::string &treName );

  void setFileBlockCompression( const unsigned int &f );
  void setNameBlockCompression( const unsigned int &f );
  unsigned int getFileBlockCompression() { return fileCompression; }
  unsigned int getNameBlockCompression() { return nameCompression; }

  const std::string &getVersion() const { return version; }
  void setVersion( const std::string &v ) { version = v; }

  void printHeader() const;
  void printFileBlock() const;
  void printNameBlock() const;

  bool saveRecordAsFile( const unsigned int &recordNum );
  std::stringstream *saveRecordAsStream( const unsigned int &recordNum,
					 bool verbose = false );

  std::vector<treFileRecord> &getFileRecordList() { return fileRecordList; }
  bool getFileRecordIndex( const std::string &recordName, 
			   unsigned int &index ) const;
  const std::string &getFilename() const
  {
    return filename;
  }

  unsigned int getNumRecords() const
  {
    return numRecords;
  }

protected:
  bool readHeader( std::ifstream &file );
  bool readFileBlock( std::ifstream &file );
  bool readNameBlock( std::ifstream &file );
  bool readMD5sums( std::ifstream &file );

  bool writeHeader( std::ofstream &file );
  bool writeFileBlock( std::ofstream &file );

  std::string filename;
  std::ifstream treFile;

  std::string version;
  unsigned int numRecords;
  unsigned int fileOffset;
  unsigned int fileCompression;
  unsigned int fileSize;
  unsigned int fileFinalSize;
  unsigned int nameCompression;
  unsigned int nameSize;
  unsigned int nameFinalSize;

  std::vector<treFileRecord> fileRecordList;
  treDataBlock fileBlock;
  treDataBlock nameBlock;
};

#endif
