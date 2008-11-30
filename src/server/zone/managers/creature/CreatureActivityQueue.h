/*
Copyright (C) 2007 <SWGEmu>
 
This File is part of Core3.
 
This program is free software; you can redistribute 
it and/or modify it under the terms of the GNU Lesser 
General Public License as published by the Free Software
Foundation; either version 2 of the License, 
or (at your option) any later version.
 
This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU Lesser General Public License for
more details.
 
You should have received a copy of the GNU Lesser General 
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 
Linking Engine3 statically or dynamically with other modules 
is making a combined work based on Engine3. 
Thus, the terms and conditions of the GNU Lesser General Public License 
cover the whole combination.
 
In addition, as a special exception, the copyright holders of Engine3 
give you permission to combine Engine3 program with free software 
programs or libraries that are released under the GNU LGPL and with 
code included in the standard release of Core3 under the GNU LGPL 
license (or modified versions of such code, with unchanged license). 
You may copy and distribute such a system following the terms of the 
GNU LGPL for Engine3 and the licenses of the other code concerned, 
provided that you include the source code of that other code when 
and as the GNU LGPL requires distribution of source code.
 
Note that people who make modified versions of Engine3 are not obligated 
to grant this special exception for their modified versions; 
it is their choice whether to do so. The GNU Lesser General Public License 
gives permission to release a modified version without this exception; 
this exception also makes it possible to release a modified version 
which carries forward this exception.
*/

#ifndef CREATUREACTIVITYQUEUE_H_
#define CREATUREACTIVITYQUEUE_H_

#include "engine/engine.h"

class CreatureActivityQueue : public AdvancedBinaryHeap, public Condition, public Logger {
	Mutex* condMutex;

	bool blocked;

	bool waitingForEvent;
	bool changePlan;

public:
	CreatureActivityQueue() : AdvancedBinaryHeap(), Condition(), Logger("EventQueue") {
		condMutex = new Mutex("EventQueue");

		blocked = false;

		waitingForEvent = false;
		changePlan = false;
		
		setLogging(false);
		condMutex->setMutexLogging(false);
	}

	void add(Event* e, uint64 time) {
		condMutex->lock();

		if (e->isQueued())
			remove(e, false);

		if (time != 0)
			e->update(time);
		
		add(e, false);

		condMutex->unlock();
	}

	void add(Event* e, Time& time) {
		condMutex->lock();

		if (e->isQueued())
			remove(e, false);

		e->set(time);
		add(e, false);

		condMutex->unlock();
	}

	void add(Event* e, bool doLock) {
		condMutex->lock(doLock);

		if (blocked) {
			condMutex->unlock(doLock);
			return;
		} else if (e->getTimeStamp().isPast()) {
			error("past event scheduled - " + e->toString());
		
			StackTrace trace;
			trace.print();
		}
		
		if (e->isQueued())
			remove(e, false);

		e->setQueued(true);

		#ifdef TRACE_EVENTS
			StringBuffer s;
			s << "added event " << e->getTimeStamp().getMiliTime() << "(" << e << ")";
			info(s);
		#endif

		AdvancedBinaryHeap::add(e);
		
		if (AdvancedBinaryHeap::getMin() == e && waitingForEvent) {
			changePlan = true;
			signal(condMutex);
		}
				
		condMutex->unlock(doLock);
	}
	
	Event* get() {
		condMutex->lock();
	
		waitingForEvent = true;
		
		while (true) {
			while (AdvancedBinaryHeap::isEmpty()) {
				if (blocked) {
					condMutex->unlock();
					return NULL;
				}
	
				#ifdef TRACE_EVENTS
					info("waiting event");
				#endif
	
				wait(condMutex);
			}
	
			Event* e = (Event*) AdvancedBinaryHeap::getMin();
			Time& time = e->getTimeStamp();
	
			if (blocked || !time.isFuture())
				break;
	
			#ifdef TRACE_EVENTS
				StringBuffer s;
				s << "scheduling " << e->toString();
				info(s);
			#endif
				
			int res = timedWait(condMutex, &time);
	
			#ifdef TRACE_EVENTS
				StringBuffer s2;
				s2 << "timedwait finished with (" << res << ")";
				info(s2);
			#endif
			
			if (res != 0 && res != ETIMEDOUT) {
				StringBuffer msg;
	
				if (res == 22)
					msg << "invalid condition parameters";
				else if (time.isFuture())
					msg << "misstiming (" << res << ") - future event happened" << e->getTimeStamp().getMiliTime();
				else
					msg << "condition error (" << res << ")";
	
				error(msg);
				continue;
			}
	
			if (changePlan) {
				#ifdef TRACE_EVENTS
					info("changing plan");
				#endif
			
				changePlan = false;
			} else
				break;
		}
	
		Event* e = (Event*) AdvancedBinaryHeap::removeMin();
		e->setQueued(false);
	
		if (!blocked && e->getTimeStamp().isFuture()) {
			StringBuffer msg;
			msg << "future event happenend " << -e->getTimeStamp().getMiliTime() << " (" 
				<< e->getTimeStamp().miliDifference() << ")";
			error(msg);
		} /*if (!blocked && e->getTimeStamp().miliDifference() > 250) {
			StringBuffer msg;
			msg << "WARNING too high delay " << e->getTimeStamp().getMiliTime() << " (" 
				<< e->getTimeStamp().miliDifference() << ")";
			error(msg);
		}*/
			
		#ifdef TRACE_EVENTS
			StringBuffer s;
			s << "got event " << e->getTimeStamp().getMiliTime() << " [" << size() << "]";
			info(s);
		#endif
			
		waitingForEvent = false;				
		condMutex->unlock();
	
		return e;
	}
	
	bool remove(Event* e, bool doLock) {
		condMutex->lock(doLock);
	
		if (!e->isQueued()) {
			condMutex->unlock(doLock);
			return false; 
		}
			
		Event* next = (Event*) AdvancedBinaryHeap::getMin();
			
		AdvancedBinaryHeap::remove(e);
		e->setQueued(false);
	
		#ifdef TRACE_EVENTS
			StringBuffer s;
			s << "removed event " << e->getTimeStamp().getMiliTime() << " [" << size() << "]";
			info(s);
		#endif
	
		if (waitingForEvent && next == e) {
			changePlan = true;
			signal(condMutex);
		}		
	
		condMutex->unlock(doLock);
	}	
	
	void flush() {
		condMutex->lock();
	
		blocked = true;
			
		if (waitingForEvent) 
			broadcast(condMutex);
	
		condMutex->unlock();
	}

};

#endif /*CREATUREACTIVITYQUEUE_H_*/
