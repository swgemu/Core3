/*
 * SuiListBoxImplementation.cpp
 *
 *  Created on: 10/04/2010
 *      Author: victor
 */

#include "ResourceDeedListBox.h"

void ResourceDeedListBoxImplementation::finalize() {

}

void ResourceDeedListBoxImplementation::initializeTransientMembers() {
	SuiListBoxImplementation::initializeTransientMembers();

}

String ResourceDeedListBoxImplementation::getPreviousBox() {

	int i = boxes.size();

	if(i > 1)
		return boxes.get(i - 2);

	if(i > 0)
		return boxes.get(i - 1);

	return "";
}

void ResourceDeedListBoxImplementation::removeBox() {
	if(boxes.size() > 0)
		boxes.remove(boxes.size() - 1);

	if(boxes.size() == 0)
		boxes.add("resources");
}
