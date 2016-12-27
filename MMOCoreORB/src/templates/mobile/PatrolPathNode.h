/*
 * PatrolPathNode.h
 *
 *  Created on: 20/01/2012
 *      Author: victor
 */

#ifndef PATROLPATHNODE_H_
#define PATROLPATHNODE_H_

class PatrolPathNode : public Object {
	String id, link;
	Vector3 position;
	uint32 cellid;
	String command;
	String arguments;
	uint32 pause;

public:
	PatrolPathNode() {
		cellid = 0;
		pause = 0;
	}

	PatrolPathNode(const PatrolPathNode& node) : Object() {
		id = node.id;
		link = node.link;
		position = node.position;
		cellid = node.cellid;
		command = node.command;
		arguments = node.arguments;
		pause = node.pause;
	}

	PatrolPathNode& operator=(const PatrolPathNode& node) {
		if (this == &node)
			return *this;

		id = node.id;
		link = node.link;
		position = node.position;
		cellid = node.cellid;
		command = node.command;
		arguments = node.arguments;
		pause = node.pause;

		return *this;
	}

	void readObject(LuaObject* luaObject) {
		id = luaObject->getStringField("id");
		link = luaObject->getStringField("link");
		position.set(luaObject->getFloatField("x"), luaObject->getFloatField("z"), luaObject->getFloatField("y"));
		cellid = luaObject->getIntField("cellid");
		pause = luaObject->getIntField("pause");
		command = luaObject->getStringField("command");
		arguments = luaObject->getStringField("arguments");
	}

	String getArguments() const {
		return arguments;
	}

	uint32 getCellid() const {
		return cellid;
	}

	String getCommand() const {
		return command;
	}

	String getId() const {
		return id;
	}

	Vector3 getPosition() const {
		return position;
	}

	void setArguments(const String& arguments) {
		this->arguments = arguments;
	}

	void setCellid(uint32 cellid) {
		this->cellid = cellid;
	}

	void setCommand(const String& command) {
		this->command = command;
	}

	void setId(String id) {
		this->id = id;
	}

	void setPosition(Vector3 position) {
		this->position = position;
	}

};

#endif /* PATROLPATHNODE_H_ */
