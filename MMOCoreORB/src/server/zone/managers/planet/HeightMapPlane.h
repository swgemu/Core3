#ifndef HEIGHTMAPPLANE_H_
#define HEIGHTMAPPLANE_H_

#include "engine/engine.h"

class HeightMapPlane {
	byte* buffer;

	int index;

	int planeSize;

public:
	HeightMapPlane(int idx, int size = 256) {
		buffer = new byte[size * size * sizeof(float)];

		index = idx;
		planeSize = size;
	}

	~HeightMapPlane() {
		delete [] buffer;
	}

	// getters
	inline byte* getBuffer() {
		return buffer;
	}

	inline float getHeight(int x, int y) {
		int offset = x + planeSize * y;

		if (x > planeSize || x < 0 || y > planeSize || y < 0)
			throw ArrayIndexOutOfBoundsException(offset);

		return ((float*)buffer)[offset];
	}

	inline int getIndex() {
		return index;
	}

	// setters
	inline void setIndex(int idx) {
		index = idx;
	}
};

#endif /*HEIGHTMAPPLANE_H_*/
