/*
 * AiTemplate.h
 *
 *  Created on: May 17, 2012
 *      Author: da
 */

#ifndef AITEMPLATE_H_
#define AITEMPLATE_H_

class LuaAiTemplate : public Object {
public:
	uint32 id;
	String className;
	uint32 parent;
	uint16 classType;

	LuaAiTemplate() : Object() {
		id = 0;
		className = "";
		parent = 0;
		classType = 0;
	}

	LuaAiTemplate(const LuaAiTemplate& ait) : Object() {
		id = ait.id;
		className = ait.className;
		parent = ait.parent;
		classType = ait.classType;
	}

	LuaAiTemplate& operator=(const LuaAiTemplate& ait) {
		if (this == &ait)
			return *this;

		id = ait.id;
		className = ait.className;
		parent = ait.parent;
		classType = ait.classType;

		return *this;
	}
};

class AiTemplate : public Object {
	String templateName;

	Vector<Reference<LuaAiTemplate*> > tree;

public:
	AiTemplate(const String& name) {
		templateName = name;
	}

	AiTemplate(const AiTemplate& ait) : Object() {
		templateName = ait.templateName;
		tree = ait.tree;
	}

	AiTemplate& operator=(const AiTemplate& ait) {
		if (this == &ait)
			return *this;

		templateName = ait.templateName;
		tree = ait.tree;

		return *this;
	}

	/**
	 * @pre lua is checked for valid table
	 * @post lua is popped
	 */
	void readObject(LuaObject* lua) {
		// should be a valid table, but check anyway
		if (!lua->isValidTable())
			return;

		lua_State* L = lua->getLuaState();

		for (int i = 1; i <= lua->getTableSize(); ++i) {
			lua_rawgeti(L, -1, i);
			LuaObject behavior(L);

			Reference<LuaAiTemplate*> b = new LuaAiTemplate;
			b->id = behavior.getStringAt(1).hashCode();
			b->className = behavior.getStringAt(2);
			b->parent = behavior.getStringAt(3).hashCode();
			b->classType = behavior.getIntAt(4);

			tree.add(b);
			if (b == NULL) {
				System::out << behavior.getStringAt(1) << " " << behavior.getStringAt(2) << " " << behavior.getStringAt(3) << " " << behavior.getStringAt(4) << " ";
			}

			behavior.pop();
		}
	}

	String& getTemplateName() {
		return templateName;
	}

	Vector<Reference<LuaAiTemplate*> >* getTree() {
		return &tree;
	}
};

#endif /* AITEMPLATE_H_ */
