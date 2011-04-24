/*
 * DataTableCell.cpp
 *
 *  Created on: Apr 21, 2011
 *      Author: crush
 */

#include "DataTableCell.h"

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
