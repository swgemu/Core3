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
		cells.forEach([](auto cell) { delete cell; });
	}

	void addCell(DataTableCell* c) {
		cells.add(c);
	}

	DataTableCell* getCell(int idx) {
		return cells.get(idx);
	}

	const DataTableCell* getCell(int idx) const {
		return cells.get(idx);
	}

	int getCellsSize() const {
		return cells.size();
	}

	template <typename V>
	void getValue(int idx, V& out) const {
		cells.get(idx)->getValue(out);
	}
};

#endif /* DATATABLEROW_H_ */
