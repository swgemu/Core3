/*
 * PaletteColor.h
 *
 *  Created on: 19/03/2012
 *      Author: victor
 */

#ifndef PALETTECOLOR_H_
#define PALETTECOLOR_H_

class PaletteColor : public Object {
	uint8 red;
	uint8 green;
	uint8 blue;
	uint8 unknown;

public:
	PaletteColor() {
		red = green = blue = unknown = 0;
	}

	PaletteColor(const PaletteColor& c) : Object() {
		red = c.red;
		green = c.green;
		blue = c.blue;
		unknown = c.unknown;
	}

	PaletteColor& operator=(const PaletteColor& c) {
		if (this == &c)
			return *this;

		red = c.red;
		green = c.green;
		blue = c.blue;
		unknown = c.unknown;

		return *this;
	}

	void readObject(ObjectInputStream* stream) {
		red = stream->readByte();
		green = stream->readByte();
		blue = stream->readByte();
		unknown = stream->readByte();
	}

	uint8 getRed() {
		return red;
	}

	uint8 getGreen() {
		return green;
	}

	uint8 getBlue() {
		return blue;
	}
};

#endif /* PALETTECOLOR_H_ */
