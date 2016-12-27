/*
 * DataTableRow.h
 *
 *  Created on: Feb 11, 2011
 *      Author: crush
 */

#ifndef DATATABLEROW_H_
#define DATATABLEROW_H_

#include "templates/datatables/DataTableCell.h"

class DataTableRow {
	Vector<DataTableCell*> cells;

public:
	DataTableRow() {

	}

	~DataTableRow() {
		while (cells.size() > 0) {
			DataTableCell* cell = cells.remove(0);

			delete cell;
			cell = NULL;
		}
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

	template <typename V>
	void getValue(int idx, V& out) {
		cells.get(idx)->getValue(out);
	}
};

#endif /* DATATABLEROW_H_ */
