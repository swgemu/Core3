/*
 * Outfit.h
 *
 *  Created on: Mar 31, 2011
 *      Author: polonel
 */

#ifndef OUTFIT_H_
#define OUTFIT_H_

#include "engine/engine.h"

class Outfit : public Object {
	String outfitName;

	Vector<uint32> clothingCRC;

public:
	Outfit() : Object() {
		outfitName = "";

	}

	Outfit(const Outfit& outfit) : Object() {
		outfitName = outfit.outfitName;
		clothingCRC = outfit.clothingCRC;

	}

	Outfit& operator= (const Outfit& outfit) {
		if (this == &outfit)
			return *this;

		outfitName = outfit.outfitName;
		clothingCRC = outfit.clothingCRC;

		return *this;
	}

	inline int compareTo(const Outfit& outfit) const {
		return 0;
	}

	inline void addClothingCRC(unsigned int clothingcrc) {
		clothingCRC.add(clothingcrc);
	}

	inline String& getOutfitName() {
		return outfitName;
	}

	inline Vector<uint32>* getClothing() {
		return &clothingCRC;
	}

	inline int getClothingSize() {
		return clothingCRC.size();
	}

};

#endif /* OUTFIT_H_ */
