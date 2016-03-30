/*
 * TargaBitmap.cpp
 *
 *  Created on: 06/09/2013
 *      Author: victor
 */

#include "engine/engine.h"
#include "TargaBitmap.h"

class TargaBlackPixel : public TargaPixel {
public:
	unsigned char val;

	TargaBlackPixel() {
		val = 0;
	}

	TargaBlackPixel(const TargaBlackPixel& c) {
		val = c.val;
	}

	void read(ObjectInputStream* data, int bytes) {
		val = data->readByte();
	}

	void clear() {
		val = 0;
	}
};

class TargaColorPixel : public TargaPixel {
public:
	unsigned char r, g, b, a;

	void clear() {
		r = 0, g = 0, b = 0, a = 0;
	}

	void read(ObjectInputStream* data, int bytes) {
		switch (bytes) {
		case 4:
			r = data->readByte();
			g = data->readByte();
			b = data->readByte();
			a = data->readByte();
			break;
		case 3:
			r = data->readByte();
			g = data->readByte();
			b = data->readByte();
			a = 0;
			break;
		case 2: {
			byte one = data->readByte();
			byte two = data->readByte();

			r = (one & 0x7c) << 1;
			g = ((one & 0x03) << 6) | ((two & 0xe0) << 2);
			b = (two & 0x1f) << 3;
			a = (one & 0x80);
			break;
		}

		}
	}
};


TargaBitmap::TargaBitmap() {
	pixelData = NULL;
}

TargaBitmap::~TargaBitmap() {
	if (pixelData != NULL) {
		for (int i = 0; i < header.width; ++i) {
			for (int j = 0; j < header.height; ++j) {
				delete pixelData[i * header.width + j];
			}
		}

		delete [] pixelData;
		pixelData = NULL;
	}
}

void TargaBitmap::readObject(ObjectInputStream* stream) {
	header.readData(stream);

	if (header.datatypecode != 3 && header.datatypecode != 2) {
		throw Exception("unsopported targa format " + String::valueOf(header.datatypecode));
	}

	if (header.colourmaptype != 0 && header.colourmaptype != 1) {
		throw Exception("unsopported targa coulourmaptype " + String::valueOf(header.colourmaptype));
	}

	pixelData = new TargaPixel*[header.width * header.height];

	for (int i = 0; i < header.width * header.height; ++i) {
		TargaPixel* obj = NULL;
		switch (header.datatypecode) {
		case 3:
			obj = new TargaBlackPixel();
			break;
		case 10:
		case 2:
			obj = new TargaColorPixel();
			break;

		}

		pixelData[i] = obj;

		obj->clear();
	}

	int skip = header.idlength + (header.colourmaptype * header.colourmaplength);

	//printf("reading tga %d x %d type:%d skipping:%d after header\n", header.width, header.height, header.datatypecode, skip);

	stream->shiftOffset(skip);

	int read = header.bitsperpixel / 8;
	int n = 0;

	for (int i = header.width - 1; i >= 0; --i) {
		for (int j = 0; j < header.height; ++j) {
			pixelData[i * header.width + j]->read(stream, read);
		}
	}
}

unsigned char TargaBitmap::getData(int offset) {
	if (offset < 0 || offset >= header.width * header.height)
		throw ArrayIndexOutOfBoundsException(offset);

	TargaBlackPixel* tbp = dynamic_cast<TargaBlackPixel*>(pixelData[offset]);

	if (tbp == NULL)
		throw Exception("pixelData[" + String::valueOf(offset) + "] is not a TargaBlackPixel");

	return tbp->val;
}
