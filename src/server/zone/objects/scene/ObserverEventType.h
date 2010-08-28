/*
 * ObserverEventTypes.h
 *
 *  Created on: 20/06/2010
 *      Author: victor
 */

#ifndef OBSERVEREVENTTYPES_H_
#define OBSERVEREVENTTYPES_H_

class ObserverEventType {
public:
	const static int POSITIONCHANGED = 1;
	const static int CLOSECONTAINER = 2;
	const static int POSTURECHANGED = 3;
	const static int OBJECTDESTRUCTION = 4;
	const static int SAMPLE = 5;
	const static int CONVERSE = 6;
	const static int KILLEDCREATURE = 7;
};

#endif /* OBSERVEREVENTTYPES_H_ */
