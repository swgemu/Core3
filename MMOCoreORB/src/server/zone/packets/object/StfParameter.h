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

#ifndef STFPARAMETER_H_
#define STFPARAMETER_H_

class StfParameter;

class StfPointerParameter : public Packet {
	StfPointerParameter(uint64 p) {
		insertLong(p);
		insertAscii("");
		insertInt(0);
		insertAscii("");
		insertUnicode("");
	}

	friend class StfParameter;
};

class StfFileParameter : public Packet {
	StfFileParameter(const string& file, const string& str) {
		insertLong(0);
		insertAscii(file);
		insertInt(0);
		insertAscii(str);
		insertUnicode("");
	}

	friend class StfParameter;
};

class StfUnicodeParameter : public Packet {
	StfUnicodeParameter(const unicode& str) {
		insertLong(0);
		insertAscii("");
		insertInt(0);
		insertAscii("");
		insertUnicode(str);
	}

	friend class StfParameter;
};


class StfParameter : public Packet {
	Stream * toParam;
	Stream * tuParam;
	Stream * ttParam;
	int di;
	float df;

public:
	StfParameter() {
		toParam = new StfPointerParameter(0);
		tuParam = new StfPointerParameter(0);
		ttParam = new StfPointerParameter(0);
		di = 0;
		df = 0;
	}

	~StfParameter() {
		delete(toParam);
		delete(tuParam);
		delete(ttParam);
	}

	void addTO(uint64 to) {
		delete toParam;
		toParam = new StfPointerParameter(to);
	}

	void addTO(const string& file, const string& str) {
		delete toParam;
		toParam = new StfFileParameter(file, str);
	}

	void addTO(const unicode& str) {
		delete toParam;
		toParam = new StfUnicodeParameter(str);
	}

	void addTO(const string& str) {
		delete toParam;
		toParam = new StfUnicodeParameter(unicode(str));
	}

	void addTU(uint64 to) {
		delete tuParam;
		tuParam = new StfPointerParameter(to);
	}

	void addTU(const string& file, const string& str) {
		delete tuParam;
		tuParam = new StfFileParameter(file, str);
	}

	void addTU(const unicode& str) {
		delete tuParam;
		tuParam = new StfUnicodeParameter(str);
	}

	void addTU(const string& str) {
		delete tuParam;
		tuParam = new StfUnicodeParameter(unicode(str));
	}

	void addTT(uint64 to) {
		delete ttParam;
		ttParam = new StfPointerParameter(to);
	}

	void addTT(const string& file, const string& str) {
		delete ttParam;
		ttParam = new StfFileParameter(file, str);
	}

	void addTT(const unicode& str) {
		delete ttParam;
		ttParam = new StfUnicodeParameter(str);
	}

	void addTT(const string& str) {
		delete ttParam;
		ttParam = new StfUnicodeParameter(unicode(str));
	}

	void addDI(int i) {
		di = i;
	}

	void addDF(float f) {
		df = f;
	}

	void generate() {
		clear();
		reset();

		insertStream(tuParam);
		insertStream(ttParam);
		insertStream(toParam);
		insertInt(di);
		insertFloat(df);
		insertByte(0);
		insertShort(0);
	}

};
#endif /* STFPARAMETER_H_ */
