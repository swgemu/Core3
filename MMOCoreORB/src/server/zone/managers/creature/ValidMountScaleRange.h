#ifndef VALIDMOUNTSCALERANGE_H_
#define VALIDMOUNTSCALERANGE_H_

#include "engine/engine.h"
#include "server/zone/templates/datatables/DataTableRow.h"
#include "server/zone/templates/params/primitives/StringParam.h"

namespace server {
namespace zone {
namespace managers {
namespace creature {
class PetManager;
}
}
}
}

using namespace server::zone::managers::creature;

class ValidMountScaleRange : public Object {
protected:
	StringParam appearanceFilename;
	int saddleCapacity;
	float validScaleMin;
	float validScaleMax;

public:
	ValidMountScaleRange() {
		saddleCapacity = 0;
		validScaleMin = 1;
		validScaleMax = 1;
	}

	~ValidMountScaleRange() {
	}

	void parseDataTableRow(DataTableRow* row) {
		String filename;
		row->getValue(0, filename);
		appearanceFilename.setValue(filename);

		row->getValue(1, saddleCapacity);
		row->getValue(2, validScaleMin);
		row->getValue(3, validScaleMax);
	}

	inline String getAppearanceFilename() const {
		return appearanceFilename;
	}

	inline int getSaddleCapacity() {
		return saddleCapacity;
	}

	inline float getValidScaleMin() {
		return validScaleMin;
	}

	inline float getValidScaleMax() {
		return validScaleMax;
	}

	friend class server::zone::managers::creature::PetManager;
};

#endif /* VALIDMOUNTSCALERANGE_H_ */
