/*
 * DataTableIff.cpp
 *
 *  Created on: Feb 11, 2011
 *      Author: crush
 */

#include "DataTableIff.h"
#include "DataTableCell.h"
#include "DataTableRow.h"

DataTableIff::DataTableIff() {

}

DataTableIff::~DataTableIff() {
	while (rows.size() > 0) {
		DataTableRow* row = rows.remove(0);

		delete row;
		row = NULL;
	}
}

void DataTableIff::readObject(IffStream* iffStream) {
	iffStream->openForm('DTII');

	uint32 version = iffStream->getNextFormType();
	iffStream->openForm(version);

	//Parse the columns
	Chunk* chunk = iffStream->openChunk('COLS');
	uint32 totalColumns = chunk->readInt();

	for (int i = 0; i < totalColumns; ++i) {
		String columnName;
		chunk->readString(columnName);

		columns.add(columnName);
	}

	iffStream->closeChunk('COLS');

	//Parse the types
	chunk = iffStream->openChunk('TYPE');

	for (int i = 0; i < totalColumns; ++i) {
		String typeName;
		chunk->readString(typeName);

		columnTypes.add(typeName.charAt(0)); //Just need the first character to know the type. Default value doesn't seem to matter.
	}

	iffStream->closeChunk('TYPE');

	chunk = iffStream->openChunk('ROWS');
	uint32 totalRows = chunk->readInt();

	for (int i = 0; i < totalRows; ++i) {
		DataTableRow* row = new DataTableRow();

		for (int j = 0; j < totalColumns; ++j) {
			byte type = columnTypes.get(j);

			DataTableCell* cell = NULL;

			switch (type) {
			case 'f':
				cell = new DataTableCellFloat();
				cell->parse(chunk);
				break;
			case 's':
				cell = new DataTableCellString();
				cell->parse(chunk);
				break;
			case 'c':
				break;
			case 'h':
				cell = new DataTableCellHex();
				cell->parse(chunk);
				break;
			case 'p':
				break;
			case 'b':
				cell = new DataTableCellBinary();
				cell->parse(chunk);
				break;
			case 'e':
				break;
			case 'z':
				break;
			case 'i':
			default:
				cell = new DataTableCellInt();
				cell->parse(chunk);
				break;
			}

			row->addCell(cell);
		}

		rows.add(row);
	}

	iffStream->closeChunk('ROWS');

	iffStream->closeForm(version);

	iffStream->closeForm('DTII');
}
