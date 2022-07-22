/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef QUADTREE_H_
#define QUADTREE_H_

/*
   Quad tree interface
   Copyright (C) 2003 by The Arianne Team
   Copyright (C) 2005 Team OpenWoW
   Copyright (C) 2006 Team SWGEmu

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "system/lang.h"

#include "engine/log/Logger.h"

/**
 * A quad tree is a 2D data structure that keeps lots of objects nicely
 * sorted in a tree with four children in every node, so that queries like
 * "give me a list of objects that are near the point X,Y" works lighting
 * fast.
 */

#include "server/zone/TreeEntry.h"

#include "TreeNode.h"

namespace server {
  namespace zone {

	class QuadTree : public Object {
		Reference<TreeNode*> root;

		static bool logTree;

		mutable ReadWriteLock mutex;

	public:
		QuadTree();
		QuadTree(float minx, float miny, float maxx, float maxy);
		~QuadTree();

		Object* clone();
		Object* clone(void* object);

		void free() {
			TransactionalMemoryManager::instance()->destroy(this);
		}
		void setSize(float minx, float miny, float maxx, float maxy);

		void insert(TreeEntry *obj);

		void remove(TreeEntry *obj);

		void removeAll();

		void inRange(TreeEntry *obj, float range);

		/**
		 * Updates COV, adds new in range objects
		 */
		void safeInRange(TreeEntry* obj, float range);

		/**
		 * Searches for entries that contain x, y point
		 */
		int inRange(float x, float y, SortedVector<ManagedReference<TreeEntry*> >& objects) const;
		int inRange(float x, float y, SortedVector<TreeEntry*>& objects) const;

		int inRange(float x, float y, float range, SortedVector<ManagedReference<TreeEntry*> >& objects) const;
		int inRange(float x, float y, float range, SortedVector<TreeEntry*>& objects) const;

		bool update(TreeEntry *obj);

	private:
		void _insert(const Reference<TreeNode*>& node, TreeEntry *obj);
		bool _update(const Reference<TreeNode*>& node, TreeEntry *obj);

		void _inRange(const Reference<TreeNode*>& node, TreeEntry *obj, float range);
		int _inRange(const Reference<TreeNode*>& node, float x, float y, float range, SortedVector<ManagedReference<TreeEntry*> >& objects) const;
		int _inRange(const Reference<TreeNode*>& node, float x, float y, float range, SortedVector<TreeEntry* >& objects) const;
		int _inRange(const Reference<TreeNode*>& node, float x, float y, SortedVector<ManagedReference<TreeEntry*> >& objects) const;
		int _inRange(const Reference<TreeNode*>& node, float x, float y, SortedVector<TreeEntry*>& objects) const;

		void copyObjects(const Reference<TreeNode*>& node, float x, float y, float range, SortedVector<ManagedReference<TreeEntry*> >& objects);
		void copyObjects(const Reference<TreeNode*>& node, float x, float y, float range, SortedVector<TreeEntry*>& objects);

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

#endif /*QUADTREE_H_*/
