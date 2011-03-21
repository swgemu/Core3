/*
 * AuctionItemImplementation.cpp
 *
 *  Created on: 12/03/2010
 *      Author: victor
 */

#include "AuctionItem.h"

void AuctionItemImplementation::setLocation(const String& planet, const String& header, uint64 vendorid, int x, int z, bool vendor) {
	location = header;

	StringBuffer title;
	title << planet << ".@";

	if (vendor)
		title << "planet_n:" << planet <<  ".Vendor: " << header;
	else
		title << planet << "_region_names:" << header << ".@:";

	title << "." << vendorid << "#" << x << "," << z;
	terminalTitle = title.toString();
}
