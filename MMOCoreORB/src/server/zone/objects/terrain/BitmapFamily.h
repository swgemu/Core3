/*
 * BitmapFamily.h
 *
 *  Created on: 06/09/2013
 *      Author: victor
 */

#ifndef BITMAPFAMILY_H_
#define BITMAPFAMILY_H_

#include "TemplateVariable.h"
#include "TargaBitmap.h"
#include "server/zone/managers/templates/DataArchiveStore.h"

class BitMapFamily : public TemplateVariable<'MFAM'> {
	int var1;
	String name;
	String file;

	TargaBitmap map;
public:
	void parseFromIffStream(engine::util::IffStream* iffStream) {
		iffStream->openChunk('DATA');

		var1 = iffStream->getInt();
		iffStream->getString(name);
		iffStream->getString(file);

		iffStream->closeChunk('DATA');

		int size = 0 ;
		byte* data = DataArchiveStore::instance()->getData(file, size);

		if (data != NULL) {
			ObjectInputStream stream((char*)data, size);

			try {
				map.readObject(&stream);
			} catch (Exception& e) {
				Logger::console.error("could not parse targa file for BitMapFamily " + file);
				Logger::console.error(e.getMessage());
			}

			delete [] data;
		}
	}

	inline TargaBitmap* getMap() {
		return &map;
	}

	inline String getName() {
		return name;
	}

	inline int getVar1() {
		return var1;
	}

	inline String getFile() {
		return file;
	}
};

#endif /* BITMAPFAMILY_H_ */
