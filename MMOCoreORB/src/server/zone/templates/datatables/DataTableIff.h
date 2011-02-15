/*
 * DataTableIff.h
 *
 *  Created on: Feb 11, 2011
 *      Author: crush
 */

#ifndef DATATABLEIFF_H_
#define DATATABLEIFF_H_

#include "engine/engine.h"
#include "../IffTemplate.h"

class DataTableRow;

class DataTableIff : public IffTemplate {
	Vector<String> columns;
	Vector<byte> columnTypes;
	Vector<DataTableRow*> rows;

public:
	DataTableIff();
	~DataTableIff();

	void readObject(IffStream* iffStream);

	DataTableRow* getRow(int idx) {
		return rows.get(idx);
	}

	int getRowsSize() {
		return rows.size();
	}
};


#endif /* DATATABLEIFF_H_ */
