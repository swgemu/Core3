#ifndef CRCSTRINGTABLE_H_
#define CRCSTRINGTABLE_H_

#include "templates/IffTemplate.h"

class CrcStringTable : public IffTemplate {
	VectorMap<uint32, String> tableData;

public:
	CrcStringTable();
	~CrcStringTable();

	void readObject(IffStream* iffStream);

	VectorMap<uint32, String> getTableData() {
		return tableData;
	}
};

#endif /* CRCSTRINGTABLE_H_ */
