/*
 * DataTableCell.cpp
 *
 *  Created on: Apr 21, 2011
 *      Author: crush
 */

#include "DataTableCell.h"

/**
 * Parses the string as a comma delimited vector into a SortedVector of Strings.
 */
template<> void DataTableCell::getValue<SortedVector<String> >(SortedVector<String>& out) {
	DataTableCellString* cell = dynamic_cast<DataTableCellString*>(this);

	if (cell == NULL)
		throw Exception("Wrong cell type.");

	String tokenizedString;
	cell->getValue(tokenizedString);

	StringTokenizer tokenizer(tokenizedString);
	tokenizer.setDelimeter(",");

	while (tokenizer.hasMoreTokens()) {
		String token;
		tokenizer.getStringToken(token);

		out.put(token);
	}
}

template<> void DataTableCell::getValue<String>(String& out) {
	DataTableCellString* cell = dynamic_cast<DataTableCellString*>(this);

	if (cell == NULL)
		throw Exception("Wrong cell type.");

	cell->getValue(out);
}

template<> void DataTableCell::getValue<int>(int& out) {
	DataTableCellInt* cell = dynamic_cast<DataTableCellInt*>(this);

	if (cell == NULL)
		throw Exception("Wrong cell type.");

	cell->getValue(out);
}

template<> void DataTableCell::getValue<uint32>(uint32& out) {
	DataTableCellHex* cell = dynamic_cast<DataTableCellHex*>(this);

	if (cell == NULL)
		throw Exception("Wrong cell type.");

	cell->getValue(out);
}

template<> void DataTableCell::getValue<float>(float& out) {
	DataTableCellFloat* cell = dynamic_cast<DataTableCellFloat*>(this);

	if (cell == NULL)
		throw Exception("Wrong cell type.");

	cell->getValue(out);
}

template<> void DataTableCell::getValue<bool>(bool& out) {
	DataTableCellBinary* cell = dynamic_cast<DataTableCellBinary*>(this);

	if (cell == NULL)
		throw Exception("Wrong cell type.");

	cell->getValue(out);
}
