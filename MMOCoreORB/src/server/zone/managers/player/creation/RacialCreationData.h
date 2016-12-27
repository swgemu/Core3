/*
 * CreationData.h
 *
 *  Created on: Apr 21, 2011
 *      Author: crush
 */

#ifndef RACIALCREATIONDATA_H_
#define RACIALCREATIONDATA_H_

#include "templates/datatables/DataTableRow.h"

namespace server {
namespace zone {
namespace managers {
namespace player {
namespace creation {

class RacialCreationData : public Object {
	Vector<int> minAttributes;
	Vector<int> maxAttributes;
	Vector<int> modAttributes;
	int totalAttributes;

public:
	RacialCreationData() {
		totalAttributes = 0;
	}

	RacialCreationData(const RacialCreationData& cd) : Object() {
		minAttributes = cd.minAttributes;
		maxAttributes = cd.maxAttributes;
		modAttributes = cd.modAttributes;
		totalAttributes = cd.totalAttributes;
	}

	RacialCreationData& operator= (const RacialCreationData& cd) {
		if (this == &cd)
			return *this;

		minAttributes = cd.minAttributes;
		maxAttributes = cd.maxAttributes;
		modAttributes = cd.modAttributes;
		totalAttributes = cd.totalAttributes;

		return *this;
	}

	void parseAttributeData(DataTableRow* row) {
		//The data starts at offset 2.
		int min = 0;
		int max = 0;

		for (int i = 2; i < 20; i+=2) {
			row->getValue(i, min);
			row->getValue(i + 1, max);

			minAttributes.add(min);
			maxAttributes.add(max);
		}

		row->getValue(20, totalAttributes);
	}

	void parseRacialModData(DataTableRow* row) {
		int mod = 0;

		for (int i = 2; i < 11; ++i) {
			row->getValue(i, mod);

			modAttributes.add(mod);
		}
	}

	inline int getAttributeMin(int idx) {
		return minAttributes.get(idx);
	}

	inline int getAttributeMax(int idx) {
		return maxAttributes.get(idx);
	}

	inline int getAttributeMod(int idx) {
		return modAttributes.get(idx);
	}

	inline int getAttributeTotal() {
		return totalAttributes;
	}

	String toString() {
		StringBuffer str;

		for (int i = 0; i < minAttributes.size(); ++i)
			str << "min[" << i << "]:" << minAttributes.get(i) << ";";

		for (int i = 0; i < maxAttributes.size(); ++i)
			str << "max[" << i << "]:" << maxAttributes.get(i) << ";";

		for (int i = 0; i < modAttributes.size(); ++i)
			str << "mod[" << i << "]:" << modAttributes.get(i) << ";";

		return str.toString();
	}
};

}
}
}
}
}

using namespace server::zone::managers::player::creation;

#endif /* RACIALCREATIONDATA_H_ */
