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

	/**
	 * Returns a collection of rows whose column specified by the column index matches the specified column value.
	 * @param columnIdx Which column to lookup.
	 * @param columnValue What value should be compared.
	 * @return Returns a collection of DataTableRow objects.
	 */
	Vector<DataTableRow*> getRowsByColumn(int columnIdx, const String& columnValue);

	inline DataTableRow* getRow(int idx) {
		return rows.get(idx);
	}

	inline int getTotalRows() {
		return rows.size();
	}
};


#endif /* DATATABLEIFF_H_ */
