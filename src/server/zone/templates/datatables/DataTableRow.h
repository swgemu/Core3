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
};

#endif /* DATATABLEROW_H_ */
