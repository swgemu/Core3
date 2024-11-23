/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef OCTREE_H_
#define OCTREE_H_

#include "system/lang.h"
#include "engine/log/Logger.h"
#include "server/zone/TreeEntry.h"
#include "server/zone/TreeNode.h"

namespace server {
  namespace zone {

	class Octree : public Object {
		Reference<TreeNode*> root;

		static bool logTree;

		mutable ReadWriteLock mutex;

	public:
		Octree();
		Octree(float minx, float miny, float minz, float maxx, float maxy, float maxz);
		~Octree();

		Object* clone();
		Object* clone(void* object);

		void free() {
			TransactionalMemoryManager::instance()->destroy(this);
		}

		void setSize(float minx, float miny, float minz, float maxx, float maxy, float maxz);

		void insert(TreeEntry *obj);

		void remove(TreeEntry *obj);

		void removeAll();

		void inRange(TreeEntry *obj, float range);

		void safeInRange(TreeEntry* obj, float range);

		int inRange(float x, float y, float z, SortedVector<ManagedReference<TreeEntry*> >& objects) const;
		int inRange(float x, float y, float z, SortedVector<TreeEntry*>& objects) const;

		int inRange(float x, float y, float z, float range, SortedVector<ManagedReference<TreeEntry*> >& objects) const;
		int inRange(float x, float y, float z, float range, SortedVector<TreeEntry*>& objects) const;

		bool update(TreeEntry *obj);

	private:
		void _insert(const Reference<TreeNode*>& node, TreeEntry *obj);
		bool _update(const Reference<TreeNode*>& node, TreeEntry *obj);

		void _inRange(const Reference<TreeNode*>& node, TreeEntry *obj, float range);
		int _inRange(const Reference<TreeNode*>& node, float x, float y, float z, float range, SortedVector<ManagedReference<TreeEntry*> >& objects) const;
		int _inRange(const Reference<TreeNode*>& node, float x, float y, float z, float range, SortedVector<TreeEntry* >& objects) const;
		int _inRange(const Reference<TreeNode*>& node, float x, float y, float z, SortedVector<ManagedReference<TreeEntry*> >& objects) const;
		int _inRange(const Reference<TreeNode*>& node, float x, float y, float z, SortedVector<TreeEntry*>& objects) const;

		void copyObjects(const Reference<TreeNode*>& node, float x, float y, float z, float range, SortedVector<ManagedReference<TreeEntry*> >& objects);
		void copyObjects(const Reference<TreeNode*>& node, float x, float y, float z, float range, SortedVector<TreeEntry*>& objects);

	public:
		static void setLogging(bool doLog) {
			logTree = doLog;
		}

		inline static bool doLog() {
			return logTree;
		}
	};
  } // namespace zone
} // namespace server

#endif /*OCTREE_H_*/
