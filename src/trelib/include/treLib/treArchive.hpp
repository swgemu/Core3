/** -*-c++-*-
 *  \class  treArchive
 *  \file   treArchive.hpp
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

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <treLib/treClass.hpp>

#ifndef TREARCHIVE_HPP
#define TREARCHIVE_HPP

class treArchive
{
public:
  treArchive();
  ~treArchive();

  /// Change windows style slashes to c++ style.
  static void fixSlash( std::string &filename );

  /// Add TRE file to archive
  bool addFile( const std::string &filename );

  /// Remove TRE file from archive
  bool removeFile( const std::string &filename );

  /// Remove all TRE files from archive
  bool removeAllFiles();

  void printArchiveContents() const;

  std::stringstream *getFileStream( const std::string &filename );

protected:
  std::list< treClass *> treList;

private:

};

#endif
