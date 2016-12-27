/*
 * PalleteFile.h
 *
 *  Created on: 19/03/2012
 *      Author: victor
 */

#ifndef PALETTETEMPLATE_H_
#define PALETTETEMPLATE_H_

#include "templates/appearance/PaletteColor.h"

class PaletteTemplate : public Object {
	Vector<PaletteColor> colors;
public:
	PaletteTemplate() {

	}

	void readObject(ObjectInputStream* stream) {
		uint32 riff = stream->readNetInt();

		if (riff != 'RIFF')
			return;

		uint32 size = stream->readInt();

		if (size < 12) // PAL + data + size
			return;

		uint32 type = stream->readNetInt();

		if (type != 'PAL ')
			return;

		uint32 data = stream->readNetInt();

		if (data != 'data')
			return;

		uint32 dataSize = stream->readInt();

		if (dataSize < 4)
			return;

		uint32 unk = stream->readInt();

		for (dataSize -= 4 ; dataSize > 0; dataSize -= 4) {
			PaletteColor color;
			color.readObject(stream);

			colors.add(color);
		}
	}

	Vector<PaletteColor>* getColors() {
		return &colors;
	}

	int getColorCount() {
		return colors.size();
	}
};

#endif /* PALLETEFILE_H_ */
