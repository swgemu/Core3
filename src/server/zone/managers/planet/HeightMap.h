#ifndef HEIGHTMAP_H_
#define HEIGHTMAP_H_

#include "engine/engine.h"

#include "HeightMapPlane.h"

class HeightMap {
	Reader* reader;

	HeightMapPlane** planes;

	ArrayQueue<HeightMapPlane*> planeQueue;

	static const int PLANESSIZE = 64;

	static const int PLANEWIDTH = 256;

	static const int PLANELIMIT = 1;

	static const int HEIGHTSIZE = sizeof(float);

	static const int ORIGOSHIFT = PLANESSIZE * PLANEWIDTH / 2;

public:
	HeightMap();

	~HeightMap();

	void load(const String& path);

	float getHeight(float x, float y);

	static float getHeightFrom(Reader* file, float x, float y);

	static void convert(const String& path);

	static void readPlaneForConversion(Reader* file, float* buffer, int planeX, int planeY);

protected:
	HeightMapPlane* streamPlaneAt(float x, float y);

	int getPlanePosition(float x, float y);
};

#endif /*HEIGHTMAP_H_*/
