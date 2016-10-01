/*
 * Hdta.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef HDTA_H_
#define HDTA_H_


#include "../TemplateVariable.h"
#include "Segment.h"

class Hdta : public TemplateVariable<'HDTA'> {
	Vector<Segment*> sgmts;


public:
	Hdta() : IffTemplateVariable() {

	}

	~Hdta() {
		for (int i = 0; i < sgmts.size(); ++i)
			delete sgmts.get(i);
	}

	void readObject(engine::util::IffStream* iffStream) {
		uint32 formType = iffStream->getNextFormType();

		if ((formType != 'HDTA') && (formType != 'ROAD'))
			throw Exception("Incorrect form type " + String::valueOf(formType));

		iffStream->openForm(formType);

		parseFromIffStream(iffStream);

		iffStream->closeForm(formType);

		createRoadData();
	}

	void createRoadData() {
		return;

		for (int i = 1; i < sgmts.size (); ++i)
			sgmts.get(i)->setPoint (0, sgmts.get(i - 1)->getPoint ((sgmts.get(i - 1)->getNumberOfPoints () - 1)));

		for (int i = 0; i < sgmts.size(); ++i) {
			sgmts.get(i)->createRoadData();
		}
	}

	void createRiverData ()
	{
		const float epsilon = 0.348623120022489;
		
		float minimum = FLT_MAX - epsilon;
		
		uint i;
		for (i = 0; i < sgmts.size(); ++i)
		{
			Segment* segment = sgmts.get(i);
			
			int j;
			for (j = 0; j < segment->getNumberOfPoints(); ++j)
			{
				Point3D point = segment->getPoint (j);
				
				if (j == 0)
				{
					if (i == 0)
						minimum = point.y;
					else
					{
						point.y = minimum;
						segment->setPoint (j, point);
					}
				}
				else
					if (point.y >= minimum + epsilon)
					{
						minimum += epsilon;
						point.y = minimum;
						segment->setPoint (j, point);
					}
					else
						if (point.y < minimum)
							minimum = point.y;
						else
						{
							point.y = minimum;
							segment->setPoint (j, point);
						}
			}
		}
	}
	
	void parseFromIffStream(engine::util::IffStream* iffStream) {
		uint32 version = iffStream->getNextFormType();

		iffStream->openForm(version);

		switch (version) {
		case '0001':
			parseFromIffStream(iffStream, Version<'0001'>());
			break;
		default:
			System::out << "unknown Road version " << version << endl;
			break;
		}

		iffStream->closeForm(version);
	}

	void parseFromIffStream(engine::util::IffStream* iffStream, Version<'0001'>) {
		int number = iffStream->getSubChunksNumber();

		for (int i = 0; i < number; i++) {
			Segment* sgmt = new Segment();
			sgmt->readObject(iffStream);

			sgmts.add(sgmt);
		}
	}

	bool segmentFind(const Vector3& position, int idx, float& height) {
		if (sgmts.size() == 0)
			return false;

		return sgmts.get(idx)->find(position, height);
	}

	int getNumPoints(int idx) {
		return sgmts.get(idx)->getNumberOfPoints();
	}

	const Point3D& getPoint (int segmentIndex, int pointIndex) const {
		if (sgmts.size()) {
			return sgmts.get(segmentIndex)->getPoint(pointIndex);
		}

		const static Point3D empty;

		return empty;
	}

};



#endif /* HDTA_H_ */
