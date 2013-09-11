/*
 * FilterBitmap.cpp
 *
 *  Created on: 06/09/2013
 *      Author: victor
 */

#include "FilterBitmap.h"

#include "../../TerrainGenerator.h"

#include "../../TargaBitmap.h"

float FilterBitmap::process(float x, float y, float transformValue, float& baseValue, TerrainGenerator* terrainGenerator, FilterRectangle* rect) {
	if (map == NULL) {
		map = terrainGenerator->getBitmapGroup()->getBitmap(bitmapId);

		if (map == NULL) {
			System::out << "error out of bounds fractal id for filter " << informationHeader.getDescription() << endl;

			return 1;
		}
	}


	float image_width = map->getWidth();
	float image_height = map->getHeight();
	float same_as_width_height = image_width;

	int64 v44 = same_as_width_height;
	float arg6 = image_width;
	//int64 v41 = image_height;

	/*

	float v13 = rect->maxX - rect->minX;
	float v45 = 0;
	float v14 = v13;
	float v36 = rect->maxY - rect->minY;
	long double v15 = (long double)image_width;
	float v40 = v15 - 1.0;
	float arg1 = (x - rect->minX) * v15 / v14;
	float* v6 = &v40;
	if ( v15 - 1.0 >= arg1 ) //if (! image_width -1 >= transformedX ) transformedX = image_width - 1
		v6 = &arg1; // if not
	long double v17 = (long double)v41;
	float v42 = *v6;
	v40 = v17 - 1.0;
	arg1 = (y - rect->minY) * v17 / v36;
	float* v16 = &v40;
	if ( v17 - 1.0 >= arg1 ) // if (! (image_height - 1 >= transformed_y) ) //transformedY = image_height - 1
		v16 = &arg1;
	v40 = *v16; //<- transformed y
	int64 v43 = v42; //<- transformed x
	float v18 = (int64)v40; //<- transformed y
	v41 = v40;
	float arg2 = (int64)v42 + 1; //<- transfromed x + 1
	float* v19 = &arg1;
	if ( arg6 - 1 >= arg2 )// <- if (! (image_width - 1 >= transformedX + 1) ) transformedX = transformedY;
		v19 = &arg2;

	v18 = *v19;
	v18 = v18 + 1;
	arg2 = v18;

	//v22 = __SETO__(image_height - 1, v18);

	//v21 = image_height - 1 - (_DWORD)v18 < 0;
	float v39 = v18;

	float* v20 = &arg1;

	if ( image_height - 1 >= v18 ) //<- if (! (image_height -1 >= transformedY + 1) transformedX = transformY;
		v20 = &arg1;

	arg1 = (int64)*v20;


*/

	float transformedX = (x - rect->minX) * image_width / (rect->maxX - rect->minX);
	float transformedY = (y - rect->minY) * image_height / (rect->maxY - rect->minY);

	if (transformedX > image_width - 1) {
		transformedX = image_width - 1;
	}

	if (transformedY > image_height - 1) {
		transformedY = image_height - 1;
	}

	int v41 = transformedY;
	float v39 = transformedX + 1;
	int v43 = transformedX;
	float v42 = transformedX;
	float v40 = transformedY;

	float arg1 = (int) transformedY + 1;

	//v24 = lockReadOnly__Image(v7, 0);

	int v25 = v44 * (image_height - (int)v41 - 1);
	int v26 = v39 * v44 / arg6;
	int v27 = v43 * v44 / arg6;

	byte v28 = map->getData(v27 + v25);

	byte mapValue = v28;

	//v28 = *(_BYTE *)(v27 + v25 + v24);

	float arg2 = 0;
	//arg2 = *(_BYTE *)(v26 + v25 + v24);
	arg2 = map->getData(v26 + v25) & 0xFF;

	int v29 = v44 * (image_height - int(arg1) - 1);

	v25 = 0;
	v25 = map->getData(v29 + v27) & 0xFF;//*(_BYTE *)(v29 + v27 + v24);
	v27 = 0;
	v27 = map->getData(v26 + v29) & 0xFF;//*(_BYTE *)(v26 + v29 + v24);
	arg6 = v25;
	arg1 = v27;
	//unlock__Image(v38);
	long double v30 = v42 - (long double)v43;
	//arg6 = arg6;
	long double v31 = v40 - (long double)v41;
	float mapResult = v31 * (1.0 - v30) * (long double)arg6 * 0.003921568859368563
			+ v31 * v30 * (long double)arg1 * 0.003921568859368563
			+ (1.0 - v31) * (1.0 - v30) * (long double)v28 * 0.003921568859368563
			+ (1.0 - v31) * v30 * (long double)arg2 * 0.003921568859368563;
	if ( mapResult == 1.0 )
		mapResult = 0.9999899864196777;
	float v32 = featheringAmount;
	float v33 = max;
	arg6 = min;
	arg2 = v32;
	arg1 = v33;
	float result = 0;

	if ( mapResult > arg6 && mapResult < arg1 ) {
		float v35 = (arg1 - arg6) * arg2 * 0.5;
		if ( mapResult >= arg6 + v35 ) {
			if ( mapResult <= arg1 - v35 )
				result = mapResult * 1.0;
			else
				result = mapResult * (arg1 - mapResult) / v35;
		} else {
			result = mapResult * (mapResult - arg6) / v35;
		}
	} else {
		result = mapResult * 0.0;
	}

	return result;
}
