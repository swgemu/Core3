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
	protected:
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
		// --- Octree subdivision safety limits ---
		// Minimum allowed size of a node before we stop subdividing
		static constexpr float MIN_NODE_SIZE = 1024.f;

		// Maximum depth of recursion to prevent pathological stack overflow
		static constexpr int MAX_DEPTH = 4;

		// Minimum objects inserted into node before subdivision
		static constexpr int OBJECTS_PER_NODE_MIN = 16;

		// Maximum inRange distance threshold
		constexpr static float INRANGE_DISTANCE_MAX = 28361.2305f; // 8192 * 2 * sqrt(3)

		void _insert(const Reference<TreeNode*>& node, TreeEntry *obj);
		bool _update(const Reference<TreeNode*>& node, TreeEntry *obj);

		void _inRange(const Reference<TreeNode*>& node, TreeEntry *obj, float range);
		int _inRange(const Reference<TreeNode*>& node, float x, float y, float z, float range, SortedVector<ManagedReference<TreeEntry*> >& objects) const;
		int _inRange(const Reference<TreeNode*>& node, float x, float y, float z, float range, SortedVector<TreeEntry* >& objects) const;
		int _inRange(const Reference<TreeNode*>& node, float x, float y, float z, SortedVector<ManagedReference<TreeEntry*> >& objects) const;
		int _inRange(const Reference<TreeNode*>& node, float x, float y, float z, SortedVector<TreeEntry*>& objects) const;

		void copyObjects(const Reference<TreeNode*>& node, float x, float y, float z, float range, SortedVector<ManagedReference<TreeEntry*> >& objects);
		void copyObjects(const Reference<TreeNode*>& node, float x, float y, float z, float range, SortedVector<TreeEntry*>& objects);

		void safeCopyObjects(const Reference<TreeNode*>& node, SortedVector<ManagedReference<TreeEntry*>>& objects) const;
		void safeCopyObjects(const Reference<TreeNode*>& node, SortedVector<TreeEntry*>& objects) const;

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
