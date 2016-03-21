/*
 * TargaBitmap.h
 *
 *  Created on: 06/09/2013
 *      Author: victor
 */

#ifndef TARGABITMAP_H_
#define TARGABITMAP_H_

class TargaHeader {
public:
	char  idlength;
	char  colourmaptype;
	char  datatypecode;
	short int colourmaporigin;
	short int colourmaplength;
	char  colourmapdepth;
	short int x_origin;
	short int y_origin;
	short width;
	short height;
	char  bitsperpixel;
	char  imagedescriptor;

	TargaHeader() {
		idlength = 0;
		colourmaptype = 0;
		datatypecode = 0;
		colourmaporigin = 0;
		colourmaplength = 0;
		colourmapdepth = 0;
		x_origin = 0;
		y_origin = 0;
		width = 0;
		height = 0;
		bitsperpixel = 0;
		imagedescriptor = 0;
	}

	void readData(ObjectInputStream* fileReader) {
		//header
		idlength = fileReader->readByte();
		colourmaptype = fileReader->readByte();
		datatypecode = fileReader->readByte();
		colourmaporigin = fileReader->readShort();
		colourmaplength = fileReader->readShort();
		colourmapdepth = fileReader->readByte();
		x_origin = fileReader->readSignedShort();
		y_origin = fileReader->readSignedShort();
		width = fileReader->readShort();
		height = fileReader->readShort();
		bitsperpixel = fileReader->readByte();
		imagedescriptor = fileReader->readByte();
	}

};

class TargaPixel {
public:
	TargaPixel() {

	}

	virtual ~TargaPixel() {

	}

	virtual void read(ObjectInputStream* data, int bytes) = 0;
	virtual void clear() = 0;
};


class TargaBitmap {
protected:
	TargaHeader header;
	TargaPixel** pixelData;

public:
	TargaBitmap();

	~TargaBitmap();

	void readObject(ObjectInputStream* stream);

	int getWidth() {
		return header.width;
	}

	int getHeight() {
		return header.height;
	}

	unsigned char getData(int offset);
};


#endif /* TARGABITMAP_H_ */
