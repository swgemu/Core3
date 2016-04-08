/*
 * Sgmt.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef SGMT_H_
#define SGMT_H_

#include "../TemplateVariable.h"

class Point3D {
public:
	float x, z, y;
};

class Segment : public TemplateVariable<'SGMT'> {
	Vector<Point3D*> positions;

public:
	~Segment() {
		for (int i = 0; i < positions.size(); ++i)
			delete positions.get(i);
	}

	void readObject(engine::util::IffStream* iffStream) {
		iffStream->openChunk('SGMT');

		int count = iffStream->getDataSize() / 12;

		for (int i = 0; i < count; i++) {
			Point3D* position = new Point3D();
			position->x = iffStream->getFloat();
			position->z = iffStream->getFloat();
			position->y = iffStream->getFloat();

			positions.add(position);
		}

		iffStream->closeChunk('SGMT');
	}


};


#endif /* SGMT_H_ */
