/*
 * BankInstallationImplementation.cpp
 *
 *  Created on: 09/08/2010
 *      Author: victor
 */

#include "BankInstallation.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/terminal/bank/BankTerminal.h"

void BankInstallationImplementation::spawnBankObjects() {
	if (zone == NULL || banks.size() != 0)
		return;

	uint32 crc = String("object/tangible/terminal/terminal_bank.iff").hashCode();

	float directionRadians = direction.getRadians();

	float newX = (1 * Math::sin(directionRadians) + 0 * Math::cos(directionRadians)) + positionX;
	float newY = (1 * Math::cos(directionRadians) - 0 * Math::sin(directionRadians)) + positionY;

	ManagedReference<BankTerminal*> bank = (BankTerminal*) zone->getZoneServer()->createObject(crc, 1);
	bank->initializePosition(newX, positionZ, newY);
	bank->setDirection(*this->getDirection());
	bank->insertToZone(zone);
	bank->updateToDatabase();
	banks.add(bank);

	newX = (0 * Math::sin(directionRadians) + 1 * Math::cos(directionRadians)) + positionX;
	newY = (0 * Math::cos(directionRadians) - 1 * Math::sin(directionRadians)) + positionY;

	bank = (BankTerminal*) zone->getZoneServer()->createObject(crc, 1);
	bank->initializePosition(newX, positionZ, newY);
	bank->setDirection(*this->getDirection());
	bank->rotate(90);
	bank->insertToZone(zone);
	bank->updateToDatabase();
	banks.add(bank);

	newX = (0 * Math::sin(directionRadians) + -1 * Math::cos(directionRadians)) + positionX;
	newY = (0 * Math::cos(directionRadians) - -1 * Math::sin(directionRadians)) + positionY;

	bank = (BankTerminal*) zone->getZoneServer()->createObject(crc, 1);
	bank->initializePosition(newX, positionZ, newY);
	bank->setDirection(*this->getDirection());
	bank->rotate(270);
	bank->insertToZone(zone);
	bank->updateToDatabase();
	banks.add(bank);

	/*
	newX = (-1 * Math::sin(directionRadians) + 0 * Math::cos(directionRadians)) + positionX;
	newY = (-1 * Math::cos(directionRadians) - 0 * Math::sin(directionRadians)) + positionY;

	bank = (BankTerminal*) zone->getZoneServer()->createObject(crc, 1);
	bank->initializePosition(newX, positionZ, newY);
	bank->setDirection(*this->getDirection());
	bank->rotate(180);
	bank->insertToZone(zone);
	bank->updateToDatabase();
	banks.add(bank);*/


	updateToDatabase();
		//ticketCollector->setDirection(direction.getW(), 0, direction.getY(), 0);
}

void BankInstallationImplementation::despawnBankObjects() {
	if (zone == NULL)
		return;

	for (int i = 0; i < banks.size(); ++i) {
		banks.get(i)->removeFromZone();
		banks.get(i)->updateToDatabaseWithoutChildren();
	}
}
