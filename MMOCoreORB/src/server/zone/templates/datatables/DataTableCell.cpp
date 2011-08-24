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
void DataTableCellString::getValue(SortedVector<String>& out) {
	String tokenizedString;
	getValue(tokenizedString);

	StringTokenizer tokenizer(tokenizedString);
	tokenizer.setDelimeter(",");

	while (tokenizer.hasMoreTokens()) {
		String token;
		tokenizer.getStringToken(token);

		out.put(token);
	}
}

void DataTableCellString::getValue(Vector<String>& out) {
	String tokenizedString;
	getValue(tokenizedString);

	StringTokenizer tokenizer(tokenizedString);
	tokenizer.setDelimeter(",");

	while (tokenizer.hasMoreTokens()) {
		String token;
		tokenizer.getStringToken(token);

		out.add(token);
	}
}
