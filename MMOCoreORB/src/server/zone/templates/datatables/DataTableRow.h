/*
 * DataTableRow.h
 *
 *  Created on: Feb 11, 2011
 *      Author: crush
 */

#ifndef DATATABLEROW_H_
#define DATATABLEROW_H_

#include "engine/engine.h"

class DataTableCell;

class DataTableRow {
	Vector<DataTableCell*> cells;

public:
	DataTableRow() {

	}

	~DataTableRow() {

	}

	void addCell(DataTableCell* c) {
		cells.add(c);
	}

	DataTableCell* getCell(int idx) {
		return cells.get(idx);
	}

	int getCellsSize() {
		return cells.size();
	}
};

#endif /* DATATABLEROW_H_ */
