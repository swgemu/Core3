/*
 * DataTableIff.h
 *
 *  Created on: Feb 11, 2011
 *      Author: crush
 */

#ifndef DATATABLEIFF_H_
#define DATATABLEIFF_H_

#include "templates/IffTemplate.h"

class DataTableRow;

class DataTableIff : public IffTemplate {
	Vector<String> columns;
	Vector<byte> columnTypes;
	Vector<DataTableRow*> rows;

public:
	DataTableIff();
	~DataTableIff();

	void readObject(IffStream* iffStream);

	void clearDataTable();

	/**
	 * Returns a collection of rows whose column specified by the column index matches the specified column value.
	 * @param columnIdx Which column to lookup.
	 * @param columnValue What value should be compared.
	 * @return Returns a collection of DataTableRow objects.
	 */
	Vector<DataTableRow*> getRowsByColumn(int columnIdx, const String& columnValue);

	/**
	 * Returns the column header name based on the column index.
	 * @param idx The index of the column to retrieve the header name for.
	 * @return Returns the header name as a String.
	 */
	String getColumnNameByIndex(int idx) const {
		return columns.get(idx);
	}

	/**
	 * Returns the index of the column with the header name passed.
	 * @param name The name of the column header to retrieve the index of.
	 * @return The index of the column, or -1 if it wasn't found.
	 */
	int getColumnIndexByName(const String& name) {
		for (int i = 0; i < columns.size(); ++i) {
			if (columns.get(i) == name)
				return i;
		}

		return -1;
	}

	inline DataTableRow* getRow(int idx) {
		return rows.get(idx);
	}

	inline int getTotalRows() {
		return rows.size();
	}

	inline int getTotalColumns() {
		return columns.size();
	}
};

#endif /* DATATABLEIFF_H_ */
