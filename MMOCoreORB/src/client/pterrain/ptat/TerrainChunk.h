/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#include <memory>

#ifndef TERRAINCHUNK_H_
#define TERRAINCHUNK_H_

class TerrainChunk {
protected:
	int* shaderData;
	int* colorData;
	float* heightData;

	float originX;
	float originY;

	int numRows;
	int numColumns;

public:
	TerrainChunk(float originX, float originY, int numRows, int numColumns) {
		this->numRows = numRows;
		this->numColumns = numColumns;

		int intSize = sizeof(int) * numRows * sizeof(int) * numColumns;
		int floatSize = sizeof(float) * numRows * sizeof(float) * numColumns;

		shaderData = (int*) malloc(intSize);
		memset(shaderData, 0, (intSize));

		colorData = (int*) malloc(intSize);

		for (int i = 0; i < numRows ; i++) {
			for (int j = 0; j < numColumns; ++j) {
				setColor(i, j, 0xFFFFFFFF);
			}
			
		}
		//memset(colorData, 0, (intSize));

		heightData = (float*) malloc((floatSize));
		memset(heightData, 0, (floatSize));

		this->originX = originX;
		this->originY = originY;
	}

	~TerrainChunk() {
		free(shaderData);
		free(colorData);
		free(heightData);
	}

	void setHeight(int i, int j, float val) {
		if (i >= numRows || j >= numColumns || i < 0 || j < 0)
			return;

		heightData[i * numColumns + j] = val;
	}

	float getHeight(int i, int j) {
		if (i >= numRows || j >= numColumns || i < 0 || j < 0)
			return -1;

		return heightData[i * numColumns + j];
	}

	int getShader(int i, int j) {
		if (i >= numRows || j >= numColumns || i < 0 || j < 0)
			return -1;

		return shaderData[i * numColumns + j];
	}

	int getColor(int i, int  j) {
		if (i >= numRows || j >= numColumns || i < 0 || j < 0)
			return - 1;

		return colorData[i * numColumns + j];
	}

	void setShader(int i, int j, int shaderID) {
		if (i >= numRows || j >= numColumns || i < 0 || j < 0)
			return;

		shaderData[i * numColumns + j] = shaderID;
	}

	void setColor(int i, int j, int color) { // 0 r g b <- 4 bytes
		if (i >= numRows || j >= numColumns || i < 0 || j < 0)
			return;

		colorData[i * numColumns + j] = color;
	}

	int* takeColorData() {
		int* temp = colorData;
		colorData = NULL;
		return temp;
	}

	float getOriginY() {
		return originY;
	}

	float getOriginX() {
		return originX;
	}

	int* getShaderData() {
		return shaderData;
	}

	float* getHeightData() {
		return heightData;
	}

	int* getColorData() {
		return colorData;
	}

};

#endif