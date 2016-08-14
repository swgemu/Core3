#include "HeightMap.h"

HeightMap::HeightMap() : ReadWriteLock("HeightMap"), Logger() {
	planes = (HeightMapPlane**) malloc(PLANESSIZE * PLANESSIZE * sizeof(HeightMapPlane*));

	for (int i = 0; i < PLANESSIZE * PLANESSIZE; ++i) {
		planes[i] = NULL;
	}

	reader = NULL;
	file = NULL;

	setLoggingName("HeightMap");
	setLogging(false);
	setGlobalLogging(true);
}

HeightMap::~HeightMap() {
	if (reader != NULL) {
		delete reader;
		reader = NULL;
	}

	if (file != NULL) {
		delete file;
		file = NULL;
	}

	for (int i = 0; i < PLANESSIZE * PLANESSIZE; ++i) {
		HeightMapPlane* plane = planes[i];

		if (plane != NULL)
			delete plane;
	}

	::free(planes);
}

void HeightMap::load(const String& path) {
	wlock();

	try {
		file = new File(path);

		reader = new FileInputStream(file);

		if (file->exists()) {
			info("loaded " + path);
		} else {
			error("failed to load " + path);

			reader = NULL;
		}
	} catch (FileNotFoundException& e) {
		reader = NULL;
		file = NULL;

		error("failed to load " + path);
	}

	unlock();
}

float HeightMap::getHeight(float x, float y) {
	if (reader == NULL)
		return 0;

	if (std::isinf(x) || std::isnan(x) || std::isinf(y) || std::isnan(y))
		return 0;

	float retHeight = 0;

	try {

		int planePosition = getPlanePosition(x, y);

		rlock();

		HeightMapPlane* plane = planes[planePosition];

		if (plane == NULL) {
			//System::out << "Streaming in heightplane number " << planePosition << ".\n";
			runlock();

			plane = streamPlaneAt(x, y);

			rlock();
		}

		int width = (int) (x + ORIGOSHIFT) % PLANEWIDTH;
		int height = (int) (y + ORIGOSHIFT) % PLANEWIDTH;

		retHeight = plane->getHeight(width, height);

		runlock();
	} catch (...) {
		runlock();

		throw;
	}

	return retHeight;
}

float HeightMap::getHeightFrom(FileInputStream* file, float x, float y) {
	if (x < -7680 || x > 7680 || y < -7680 || y > 7680)
		return 0;

	float buffer;

	int tableX = (int) x + 7680;
	int tableY = (int) y + 7680;

	uint32 offset = ((7680 * 2 + 1) * tableX + tableY) * sizeof(float);

	file->read(reinterpret_cast<byte*>(&buffer), offset, sizeof(float));

	return buffer;
}

HeightMapPlane* HeightMap::streamPlaneAt(float x, float y) {
	wlock();

	int planePosition = getPlanePosition(x, y);

	HeightMapPlane* plane = planes[planePosition];

	if (plane != NULL) {
		unlock();
		return plane;
	}

	if (planeQueue.size() < PLANELIMIT) {
		plane = planes[planePosition] = new HeightMapPlane(planePosition, PLANEWIDTH);
	} else {
		plane = planeQueue.remove();
		planes[plane->getIndex()] = NULL;

		planes[planePosition] = plane;
		plane->setIndex(planePosition);
	}

	planeQueue.add(plane);

	int planeOffset = planePosition * PLANEWIDTH * PLANEWIDTH * HEIGHTSIZE;
	reader->read(plane->getBuffer(), planeOffset, PLANEWIDTH * PLANEWIDTH * HEIGHTSIZE);

	unlock();

	return plane;
}

int HeightMap::getPlanePosition(float x, float y) {
	int planeX = (int) (x + ORIGOSHIFT) / PLANEWIDTH;
	// check needed only for when x == ORIGOSHIFT because the plane with that
	// x value doesn't exist
	if(planeX > PLANESSIZE - 1)
		planeX = PLANESSIZE - 1;

	int planeY = (int) (y + ORIGOSHIFT) / PLANEWIDTH;
	// check needed only for when y == ORIGOSHIFT because the plane with that
	// y value doesn't exist
	if(planeY > PLANESSIZE - 1)
		planeY = PLANESSIZE - 1;

	return planeX + planeY * PLANESSIZE;
}

void HeightMap::convert(const String& path) {
	FileInputStream* reader = NULL;
	try {
		reader = new FileInputStream(new File(path));
	} catch (...) {
		System::out << "could not open reader" << endl;

		exit(1);
	}

	FileOutputStream* writer = NULL;

	try {
		writer = new FileOutputStream(new File("converted_" + path));
	} catch (...) {
		System::out << "could not open writer" << endl;
		exit(1);
	}

	//FileOutputStream* writer = new FileOutputStream(new File("converted_" + path));

	byte emptybuffer[PLANEWIDTH * HEIGHTSIZE];

	for (int i = 0; i < PLANEWIDTH * HEIGHTSIZE; ++i)
		emptybuffer[i] = 0;

	// first 2 lines
	for (int i = 0; i < 2 * 64; ++i) {
		for (int j = 0; j < PLANEWIDTH; ++j)
			writer->write(emptybuffer, PLANEWIDTH * HEIGHTSIZE);
	}

	int planeIndexX = 2;
	int planeIndexY = 2;

	// inner 60 lines
	for (int i = 0; i < 60; ++i) {
		// 2 beginning plane
		for (int j = 0; j < 2 * PLANEWIDTH; ++j)
			writer->write(emptybuffer, PLANEWIDTH * HEIGHTSIZE);

		// inner 60 planes
		for (int j = 0; j < 60; ++j) {
			System::out << "\r writing(" << planeIndexX << ", " << planeIndexY << ")";

			float plane[PLANEWIDTH * PLANEWIDTH];
			readPlaneForConversion(reader, plane, planeIndexX - 2, planeIndexY - 2);

			writer->write((byte*) plane, PLANEWIDTH * PLANEWIDTH * HEIGHTSIZE);

			++planeIndexX;
		}

		planeIndexX = 2;
		++planeIndexY;

		// 2 ending plane
		for (int j = 0; j < 2 * PLANEWIDTH; ++j)
			writer->write(emptybuffer, PLANEWIDTH * HEIGHTSIZE);
	}

	//last 2 lines
	for (int i = 0; i < 2 * 64; ++i) {
		for (int j = 0; j < PLANEWIDTH; ++j)
			writer->write(emptybuffer, PLANEWIDTH * HEIGHTSIZE);
	}

	writer->close();

	delete writer;
	delete reader;
}

void HeightMap::readPlaneForConversion(FileInputStream* file, float* buffer, int planeX, int planeY) {
	int tableX = planeX * PLANEWIDTH - 7680;
	int tableY = planeY * PLANEWIDTH - 7680;

	for (int y = 0; y < PLANEWIDTH; ++y) {
		for (int x = 0; x < PLANEWIDTH; ++x) {
			*(buffer++) = getHeightFrom(file, tableX + x, tableY + y);
		}
	}
}

