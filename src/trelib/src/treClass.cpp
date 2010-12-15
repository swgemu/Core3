/** -*-c++-*-
 *  \class  treClass
 *  \file   treClass.cpp
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
#include <sstream>
#include <zlib.h> // For compress, uncompress...
#include <md5.h> // For md5
#include <cstring> // For memcpy

#include <sys/stat.h> // For mkdir()
#include <sys/types.h> // For mkdir()

#ifdef WIN32
#include <direct.h> // For _mkdir()
#endif

treClass::treClass()
    :
    version( "0000" ),
    numRecords( 0 ),
    fileOffset( 0 ),
    fileCompression( 0 ),
    fileSize( 0 ),
    fileFinalSize( 0 ),
    nameCompression( 0 ),
    nameSize( 0 ),
    nameFinalSize( 0 )
{
}

treClass::~treClass()
{
    // indexBlock and nameBlock are cleaned up by treDataBlock destructor.
    if( treFile.is_open() )
    {
	treFile.close();
    }

}

bool treClass::readHeader( std::ifstream &file )
{
    // Read 36-byte header, regardless of version

    // First 4 bytes is fileType, should be 'EERT'
    std::string fileType;
    file.width( 4 );
    file >> fileType;
    if( "EERT" != fileType )
    {
	std::cout << "Not a .tre file!" << std::endl;
	return false;
    }
    // Second 4 bytes is format version in ascii
    file.width(4);
    file >> version;

    if( "5000" == version )
    {
	file.read( reinterpret_cast<char*>(&numRecords),
		   sizeof( numRecords ));
	file.read( reinterpret_cast<char*>(&fileOffset),
		   sizeof( fileOffset ));
	file.read( reinterpret_cast<char*>(&fileCompression),
		   sizeof( fileCompression ));
	file.read( reinterpret_cast<char*>(&fileSize),
		   sizeof( fileSize ));
	fileFinalSize = numRecords * treFileRecord::SIZE;
	file.read( reinterpret_cast<char*>(&nameCompression),
		   sizeof( nameCompression ));
	file.read( reinterpret_cast<char*>(&nameSize),
		   sizeof( nameSize ));
	file.read( reinterpret_cast<char*>(&nameFinalSize),
		   sizeof( nameFinalSize ));
    }
    else if( "6000" == version )
    {
	// Rest of the header is unused in version 6000
	file.seekg( 36, std::ios_base::beg );
    }


    return true;
}

bool treClass::writeHeader( std::ofstream &file )
{
    // Write 36-byte header, regardless of version

    // First 4 bytes is fileType, should be 'EERT'
    file.width(4);
    file << "EERT";
    // Second 4 bytes is format version in ascii
    file.width(4);
    file << version;
    if( "5000" == version )
    {
	file.write( reinterpret_cast<char*>(&numRecords),
		    sizeof( numRecords ));
	file.write( reinterpret_cast<char*>(&fileOffset),
		    sizeof( fileOffset ));
	file.write( reinterpret_cast<char*>(&fileCompression),
		    sizeof( fileCompression ));
	file.write( reinterpret_cast<char*>(&fileSize),
		    sizeof( fileSize ));
	file.write( reinterpret_cast<char*>(&nameCompression),
		    sizeof( nameCompression ));
	file.write( reinterpret_cast<char*>(&nameSize),
		    sizeof( nameSize ));
	file.write( reinterpret_cast<char*>(&nameFinalSize),
		    sizeof( nameFinalSize ));
    }
    else if( "6000" == version )
    {
	// Zero out last 28 bytes of header...
	char zero = 0;
	for( int i = 0; i < 28; ++i )
	{
	    file.write( &zero, 1 );
	}
    }

    return true;
}

void treClass::printHeader() const
{
    if( "5000" == version )
    {
	std::cout << "File type: EERT" << std::endl;
	std::cout << "Version: " << version << std::endl;
	std::cout << "Num records: " << numRecords << std::endl;
	std::cout << "File Block Offset: " << fileOffset << std::endl;
	std::cout << "File Block Compression: "
		  << fileCompression << std::endl;
	std::cout << "File Block Size: " << fileSize << std::endl;
	std::cout << "File Block Final Size: " << fileFinalSize << std::endl;
	std::cout << "Name Block Compression: "
		  << nameCompression << std::endl;
	std::cout << "Name Block Size: " << nameSize << std::endl;
	std::cout << "Name Block Final Size: " << nameFinalSize << std::endl;
    }
    else if( "6000" == version )
    {
	std::cout << "File type: EERT" << std::endl;
	std::cout << "Version: " << version << std::endl;
    }
    else
    {
	std::cout << "File type: EERT" << std::endl;
	std::cout << "Version: " << version << " unsupported" << std::endl;
    }
}

bool treClass::readFileBlock( std::ifstream &file )
{
    // Seek to the offset in header...
    file.seekg( fileOffset, std::ios_base::beg );

    // Read and uncompress(if required)...
    if( !fileBlock.readAndUncompress(
	    file,
	    fileCompression,
	    fileSize,
	    fileFinalSize
	    ) )
    {
      std::cout << __FILE__ << ": " << __LINE__
		<< ": Failed to read/uncompress data!" << std::endl;
      return false;
    }
    
    // Fail if block is null...
    if( NULL == fileBlock.getUncompressedDataPtr() ) { return false; }

    // Allocate enough space for records
    fileRecordList.clear();
    fileRecordList.reserve( numRecords );

    // One index should exist for each record...
    treFileRecord fr;
    int offset = 0;
    for( unsigned int i = 0; i < numRecords; ++i )
    {
	offset += fr.readFromBuffer(
	    fileBlock.getUncompressedDataPtr()+offset
	    );
	fileRecordList.push_back( fr );
    }

    return true;
}

void treClass::printFileBlock() const
{
    std::vector<treFileRecord>::const_iterator i;
    for( i = fileRecordList.begin(); i != fileRecordList.end(); ++i )
    {
	i->print();
	std::cout << std::endl;
    }
}

bool treClass::readNameBlock( std::ifstream &file )
{
    // Seek to the offset in header+fileblock offset...
    file.seekg( fileOffset+fileSize, std::ios_base::beg );

    // Make sure there are file records to use...
    if( fileRecordList.empty() )
    {
	return false;
    }

    // Read and uncompress(if required)...
    if( !nameBlock.readAndUncompress(
	    file,
	    nameCompression,
	    nameSize,
	    nameFinalSize
	    ) )
    {
	std::cout << __FILE__ << ": " << __LINE__
		  << ": Failed to read/uncompress data!" << std::endl;
	return false;
    }
    
    // Fail if block is null...
    if( NULL == nameBlock.getUncompressedDataPtr() ) { return false; }

    // One name should exist for each record...
    std::vector<treFileRecord>::iterator i;
    for( i = fileRecordList.begin(); i != fileRecordList.end(); ++i )
    {
	unsigned int charOffset = i->getNameOffset();

	std::string name;
	// Stop when a null is found...
	while( 0 != nameBlock.getUncompressedDataPtr()[charOffset] )
	{
	    // Append char and move on to next...
	    name.push_back( nameBlock.getUncompressedDataPtr()[charOffset] );
	    ++charOffset;
	}

	// Add name to file record...
	i->setFileName( name );

    }

    return true;
 }

void treClass::printNameBlock() const
{
    unsigned int count = 0;
    std::vector<treFileRecord>::const_iterator i;
    for( i = fileRecordList.begin(); i != fileRecordList.end(); ++i )
    {
	std::cout << count << ": " << i->getFileName()
		  << " " << i->getFormat() << std::endl;
	++count;
    }
}

bool treClass::readMD5sums( std::ifstream &file )
{
    // Seek to position just after the name block...
    file.seekg( fileOffset+fileSize+nameSize, std::ios_base::beg );

    // One MD5 should exist for each record...
    for( unsigned int i = 0; i < numRecords; ++i )
    {
	std::vector<unsigned char> sum;
	sum.reserve( 16 );

	unsigned char c;
	for( int j = 0; j < 16; ++j )
	{
	    file.read( reinterpret_cast<char*>(&c), sizeof( c ) );
	    sum.push_back( c );
	}
	
	fileRecordList[i].setMD5sum( sum );
    }

    return true;
}

std::stringstream *
treClass::saveRecordAsStream( const unsigned int &recordNum, bool verbose )
{
    // Fail if record is out of range...
    if( recordNum >= fileRecordList.size() )
    {
	std::cout << "Record out of range" << std::endl;
	return NULL;
    }

    if( verbose )
      {
	std::cout << "Found record: " << fileRecordList[recordNum].getFileName()
		  << std::endl;
	fileRecordList[recordNum].print();
      }

    // Open file, exit on failure...
    treFile.open( filename.c_str(), std::ios_base::binary );
    if( !treFile.is_open() )
    {
	return NULL;
    }

    // Seek to location of datablock...
    treFile.seekg( fileRecordList[recordNum].getOffset(), std::ios_base::beg );
    treDataBlock dataBlock;

    // Read and uncompress(if required)...
    if( !dataBlock.readAndUncompress(
	    treFile,
	    fileRecordList[recordNum].getFormat(),
	    fileRecordList[recordNum].getSize(),
	    fileRecordList[recordNum].getUncompressedSize()
	    ) )
    {
      std::cout << __FILE__ << ": " << __LINE__
		<< ": Failed to read/uncompress data!" << std::endl;
      return NULL;
    }

    treFile.close();

    // Get a pointer to the uncompressed data...
    char *data = dataBlock.getUncompressedDataPtr();
    if( NULL == data )
    {
	return false;
    }

    md5_context md5;
    md5_starts( &md5 );
    
    // Calculate MD5 sum 
    if( 2 == fileRecordList[recordNum].getFormat() )
    {
	md5_update(
	    &md5,
	    (unsigned char *)dataBlock.getCompressedDataPtr(),
	    fileRecordList[recordNum].getSize()
	    );
    }
    else if( 0 == fileRecordList[recordNum].getFormat() )
    {
	md5_update(
	    &md5,
	    (unsigned char *)dataBlock.getUncompressedDataPtr(),
	    fileRecordList[recordNum].getUncompressedSize()
	    );
    }

    unsigned char mdArray[16];
    md5_finish( &md5, mdArray );

    /*std::cout << "Calculated MD5: ";
    for( int i = 0; i < 16; ++i )
    {
	std::cout << std::hex<< (unsigned int)mdArray[i];
    }
    std::cout << std::dec << std::endl;*/

    // Write uncompressed data to stringstream...
    std::stringstream *sstr = new std::stringstream;
    sstr->write( data, fileRecordList[recordNum].getUncompressedSize() );

    return sstr;
}

bool treClass::saveRecordAsFile( const unsigned int &recordNum )
{
    // Fail if record is out of range...
    if( recordNum >= fileRecordList.size() )
    {
	std::cout << "Record out of range" << std::endl;
	return false;
    }

    std::cout << "Found record: " << fileRecordList[recordNum].getFileName()
	      << std::endl;
    fileRecordList[recordNum].print();


    // Starting at the root directory of the filename..
    // make each directory, then save file
    std::string fullpath;
    std::string::size_type start=0, end;
    bool done = false;
    while( !done )
    {
	// Search for directory deliminators...
	end = (fileRecordList[recordNum].getFileName()).find( "/", start );
	
	// "/" was successfully found...
	if( std::string::npos != end )
	{
	    // Extract directory substring...
	    std::string directory(fileRecordList[recordNum].getFileName(),
				  start, end-start);

	    // Append a "/" unless this is the first directory...
	    if( !fullpath.empty() )
	    {
		fullpath += "/";
	    }
	    fullpath += directory;

	    //std::cout << "Making directory: " << fullpath << std::endl;
#ifdef WIN32
	    _mkdir( fullpath.c_str() );
#else
	    mkdir( fullpath.c_str(), 0777 );
#endif

	    // Point start to character just after last '/'...
	    start = end+1;
	}
	else
	{
	    // End of string was found...
	    done = true;
	}
    }

    // Open file, exit on failure...
    treFile.open( filename.c_str(), std::ios_base::binary );
    if( !treFile.is_open() )
    {
	return false;
    }

    // Seek to location of datablock...
    treFile.seekg( fileRecordList[recordNum].getOffset(), std::ios_base::beg );
    treDataBlock dataBlock;

    // Read and uncompress(if required)...
    if( !dataBlock.readAndUncompress(
	    treFile,
	    fileRecordList[recordNum].getFormat(),
	    fileRecordList[recordNum].getSize(),
	    fileRecordList[recordNum].getUncompressedSize()
	    ) )
    {
      std::cout << __FILE__ << ": " << __LINE__
		<< ": Failed to read/uncompress data!" << std::endl;
      return false;
    }

    treFile.close();

    // Get a pointer to the uncompressed data...
    char *data = dataBlock.getUncompressedDataPtr();
    if( NULL == data )
    {
	return false;
    }

    md5_context md5;
    md5_starts( &md5 );
    
    // Calculate MD5 sum 
    if( 2 == fileRecordList[recordNum].getFormat() )
    {
	md5_update(
	    &md5,
	    (unsigned char *)dataBlock.getCompressedDataPtr(),
	    fileRecordList[recordNum].getSize()
	    );
    }
    else if( 0 == fileRecordList[recordNum].getFormat() )
    {
	md5_update(
	    &md5,
	    (unsigned char *)dataBlock.getUncompressedDataPtr(),
	    fileRecordList[recordNum].getUncompressedSize()
	    );
    }

    unsigned char mdArray[16];
    md5_finish( &md5, mdArray );

    std::cout << "Calculated MD5: ";
    for( int i = 0; i < 16; ++i )
    {
	std::cout << std::hex<< (unsigned int)mdArray[i];
    }
    std::cout << std::dec << std::endl;


    // Attempt to open output file...
    std::ofstream dataFile;
    dataFile.open( fileRecordList[recordNum].getFileName().c_str(),
		   std::ofstream::binary );
    if( !dataFile.is_open() )
    {
      std::cout << __FILE__ << ": " << __LINE__
		<< ": Failed to open output file!" << std::endl;
      return false;
    }

    // Write uncompressed data to file...
    dataFile.write( data, fileRecordList[recordNum].getUncompressedSize() );

    // Close output file...
    dataFile.close();

    return true;
}

bool treClass::readFile( std::ifstream &file )
{
    // Only call these functions if the previous ones were successful.
    bool rv = readHeader( file );
    if( rv ) { readFileBlock( file ); }
    if( rv ) { readNameBlock( file ); }
    if( rv ) { readMD5sums( file ); }

    return rv;
}

bool treClass::readFile( const std::string &treName )
{
    filename = treName;

    // Open file, exit on failure...
    treFile.open( filename.c_str(), std::ios_base::binary );
    if( !treFile.is_open() )
    {
	return false;
    }
    
    bool rv = readFile( treFile );

    // Close input file...
    treFile.close();

    return rv;
}

bool treClass::writeFile( const std::string &treName )
{
    filename = treName;

    std::ofstream outTreFile;
    // Open file, exit on failure...
    outTreFile.open( filename.c_str(), std::ios_base::binary );
    if( !outTreFile.is_open() )
    {
	return false;
    }
    
    // Only call these functions if the previous ones were successful.
    bool rv = writeHeader( outTreFile );
    if( rv ) { writeFileBlock( outTreFile ); }

    // Close input file...
    outTreFile.close();

    return rv;
}

bool treClass::writeFileBlock( std::ofstream &file )
{
    if( fileRecordList.empty() )
    {
	std::cout << "No file records to write!" << std::endl;
	return false;
    }

    // Seek to position just after header...
    file.seekp( 36, std::ios_base::beg );

    unsigned int totalDataSize = 0;
    unsigned int totalNameBlockSize = 0;

    std::vector<treFileRecord>::iterator i;
    for( i = fileRecordList.begin(); i != fileRecordList.end(); ++i )
    {
	// Try to open file, return false if failed...
	std::ifstream dataFile( i->getFileName().c_str() );
	if( !dataFile.is_open() )
	{
	  std::cout << __FILE__ << ": " << __LINE__
		    << ": Failed to open file: " 
		    << i->getFileName() << std::endl;
	  return false;
	}

	// Get file size...
	dataFile.seekg( 0, std::ios::end );
	unsigned int dataFileSize = dataFile.tellg();

	if( !(i->getDataBlock().allocateUncompressedData( dataFileSize )) )
	{
	  std::cout << __FILE__ << ": " << __LINE__
		    << ": Failed to allocate " << dataFileSize
		    << " bytes for data file!" << std::endl;
	  return false;
	}

	// Position file pointer and beginning of file...
	dataFile.seekg( 0, std::ios::beg );
	dataFile.read( i->getDataBlock().getUncompressedDataPtr(),
		       dataFileSize );

	// Get offset (from beginning of file) to where data will be written.
	i->setOffset( file.tellp() );

	// Write datablock...
	if( !(i->getDataBlock().compressAndWrite( file, i->getFormat() ) ) )
	{
	    std::cout << "compress/write failed!" << std::endl;
	    return false;
	}

	// Set uncompressed size...
	i->setUncompressedSize( dataFileSize );

	// Size is 0 for uncompressed records..
	if( i->getFormat() == 0 )
	{
	    i->setSize( 0 );
	    totalDataSize += dataFileSize;
	}
	else
	{
	    // Store size of actual data written to file...
	    i->setSize( i->getDataBlock().getCompressedSize() );
	    totalDataSize += i->getDataBlock().getCompressedSize();
	}

	// MD5 is calculated when written, store in file record now...
	i->setMD5sum( i->getDataBlock().getMD5sum() );

	// Store offset to filename in uncompressed nameblock...
	i->setNameOffset( totalNameBlockSize );

	// Calculate total size for uncompressed nameblock...
	totalNameBlockSize +=
	  static_cast<unsigned int>( i->getFileName().size() ) + 1;
    }


    // Get postion in file where compressed file records start...
    fileOffset = file.tellp();

    // Allocate file record block...
    fileFinalSize =
      static_cast<unsigned int>( fileRecordList.size()) * treFileRecord::SIZE;
    fileBlock.allocateUncompressedData( fileFinalSize );
    char *fileData = fileBlock.getUncompressedDataPtr();
    unsigned int currentOffset = 0;
    for( i = fileRecordList.begin(); i != fileRecordList.end(); ++i )
    {
	i->generateChecksum();
	currentOffset += i->writeToBuffer( &(fileData[ currentOffset ]) );
    }
    // Write file datablock...
    if( !(fileBlock.compressAndWrite( file, fileCompression ) ) )
    {
	std::cout << "compress/write failed!" << std::endl;
	return false;
    }

    /**
       Not sure about this.  Need to find .tre that doesn't
       use compression for fileblock to compare.
    */
    if( 0 == fileCompression )
    {
	fileSize = 0;
    }
    else
    {
	fileSize = fileBlock.getCompressedSize();
    }

    // Allocate uncompressed name block...
    nameFinalSize = totalNameBlockSize;
    nameBlock.allocateUncompressedData( nameFinalSize );
    char *nameData = nameBlock.getUncompressedDataPtr();
    for( i = fileRecordList.begin(); i != fileRecordList.end(); ++i )
    {
	// Copy filename(with terminating null) into datablock...
	memcpy(
	    &(nameData[i->getNameOffset()]),
	    i->getFileName().c_str(),
	    i->getFileName().size()+1
	    );
    }

    // Write name datablock...
    if( !(nameBlock.compressAndWrite( file, nameCompression ) ) )
    {
	std::cout << "compress/write failed!" << std::endl;
	return false;
    }

    /**
       Not sure about this.  Need to find .tre that doesn't
       use compression for nameblock to compare.
    */
    if( 0 == nameCompression )
    {
	nameSize = 0;
    }
    else
    {
	nameSize = nameBlock.getCompressedSize();
    }

    // Write MD5 sums...
    for( i = fileRecordList.begin(); i != fileRecordList.end(); ++i )
    {
	i->writeMD5( file );
    }

    // Set number of records in archive...
    numRecords = static_cast<unsigned int>( fileRecordList.size() );

    // Jump to beginning of file and write header...
    file.seekp( 0, std::ios::beg );
    writeHeader( file );

    return true;
}

void treClass::setFileBlockCompression( const unsigned int &f )
{
    if( (0 == f) || (2 == f) )
    {
	fileCompression = f;
    }
    else
    {
      std::cout << __FILE__ << ": " << __LINE__
		<< ": Failed: Unknown compression" << std::endl;
    }
}

void treClass::setNameBlockCompression( const unsigned int &f )
{
    if( (0 == f) || (2 == f) )
    {
	nameCompression = f;
    }
    else
    {
      std::cout << __FILE__ << ": " << __LINE__
		<< ": Failed: Unknown compression" << std::endl;
    }
}

bool treClass::getFileRecordIndex( const std::string &recordName,
				   unsigned int &index ) const
{
  // Not found if list is empty
  if( fileRecordList.empty() )
    {
      return false;
    }

  // Loop through list, incrementing index along the way
  std::vector<treFileRecord>::const_iterator i;
  index = 0;
  for( i = fileRecordList.begin(); i != fileRecordList.end(); ++i, ++index )
    {
      // Return true if filenames match
      if( recordName == i->getFileName() )
	{
	  return true;
	}
    }
  
  // Otherwise record not found
  return false;
}
