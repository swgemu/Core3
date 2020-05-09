/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "CustomizationVariables.h"

#include "engine/db/BinaryData.h"

#include "templates/customization/CustomizationIdManager.h"

CustomizationVariables::CustomizationVariables() : VectorMap<uint8, int16>(1, 1) {
	removeAll();

	unknown = 1;
	setNullValue(0);

	keyIndex.removeAll(1, 1);

	setInsertPlan(SortedVector<uint8>::NO_DUPLICATE);
}

CustomizationVariables::~CustomizationVariables() {
	removeAll();
}

CustomizationVariables::CustomizationVariables(const CustomizationVariables& cv) :VectorMap<uint8, int16>(cv) {
	unknown = cv.unknown;

	keyIndex = cv.keyIndex;
}

CustomizationVariables& CustomizationVariables::operator=(const String& custString) {
	parseFromClientString(custString);

	return *this;
}

CustomizationVariables& CustomizationVariables::operator=(const CustomizationVariables& var) {
	if (this == &var)
		return *this;

	unknown = var.unknown;

	keyIndex = var.keyIndex;

	VectorMap<uint8, int16>::operator =(var);

	return *this;
}

void CustomizationVariables::setVariable(uint8 type, int16 value) {
#if DEBUG_CUSTOMIZATION_PARSING
	if (debug) {
		auto msg = Logger::console.info(true);
		msg << "CustomizationVariables::setVariable(type=" << type << " [";
		msg << CustomizationIdManager::instance()->getCustomizationVariable(type) << "], value=" << value << ")";
		msg.flush();
	}
#endif // DEBUG_CUSTOMIZATION_PARSING
	if (!contains(type))
		keyIndex.add(type);

	drop(type);

	put(type, value);
}

void CustomizationVariables::setVariable(const String& type, int16 value) {
	uint16 id = CustomizationIdManager::instance()->getCustomizationId(type);

	setVariable(id, value);
}

void CustomizationVariables::getVariable(int idx, uint8& type, int16& value) const {
	const auto& entry = SortedVector<VectorMapEntry<uint8, int16> >::get(idx);

	type = entry.getKey();
	value = entry.getValue();
}

void CustomizationVariables::getData(String& ascii) const {
	ascii = "";

	if (isEmpty())
		return;

	StringBuffer buf;

	buf.append((char)unknown);
	buf.append((char)size());

	for (int i = 0; i < keyIndex.size(); ++i) {
		uint8 key = keyIndex.get(i);
		int16 val = get(key);

		if (val >= 0) {
			buf.append((char)key);

			if (val == 0x00)	{
				buf.append((char)0xFF);
				buf.append((char)0x01);
			} else if (val == 0xFF) {
				buf.append((char)0xFF);
				buf.append((char)0x02);
			} else
				buf.append((char)val);
		} else {
			buf.append((char)(key | 0x80));

			buf.append((char)val);
			buf.append((char)0xFF);
			buf.append((char)0x02);
		}
	}

	buf.append((char)0xFF);
	buf.append((char)0x03);

	ascii = buf.toString();

	return;
}

void CustomizationVariables::parseFromClientString(const String& custString) {
	removeAll();
	keyIndex.removeAll();

	if (custString.length() < 2)
		return;

	auto logHexDump = [](const String& msg, const String& str, int offset = 0, bool isError = false) -> void {
		auto logmsg = isError ? Logger::console.error() : Logger::console.info(true);

		logmsg << msg << " [" << str.length() << "]" << uppercase << hex;

		while (offset < str.length()) {
			uint8 byte = str.charAt(offset++);

			logmsg << ((byte & 0xF0) ? " " : " 0");
			logmsg << hex << byte;
		}

		logmsg.flush();
	};

#if DEBUG_CUSTOMIZATION_PARSING
	debug = true;
	logHexDump("parsing CustomizationString", custString);
#endif // DEBUG_CUSTOMIZATION_PARSING

	try {
		int offset = 0;

		// Return next decoded byte (after any escapes as needed)
		auto nextByte = [&] () mutable -> uint8 {
			uint8 byte = custString.charAt(offset++);
#if DEBUG_CUSTOMIZATION_PARSING
			auto logmsg = Logger::console.info(true);
			logmsg << "nextByte@" << (offset-1) << " = " << byte;
#endif // DEBUG_CUSTOMIZATION_PARSING

			if (byte == 0xFF) { // Handle escape
				byte = custString.charAt(offset++);
#if DEBUG_CUSTOMIZATION_PARSING
				logmsg << "; escapeCode@" << (offset-1) << " = " << byte;
#endif // DEBUG_CUSTOMIZATION_PARSING

				switch(byte) {
				case 0x01: byte = 0x00; break;
				case 0x02: byte = 0xFF; break;
				case 0x03:
					throw Exception("unexpected EOS at " + String::valueOf(offset));
				default:
					throw Exception("unexpected escape byte [0x" + String::hexvalueOf(byte) + "] at " + String::valueOf(offset));
				}
			}

#if DEBUG_CUSTOMIZATION_PARSING
			logmsg << "; returning " << byte << " [0x" << hex << byte << "]";
			logmsg.flush();
#endif // DEBUG_CUSTOMIZATION_PARSING
			return byte;
		};

		unknown = nextByte(); // Always 1

		if (unknown != 1) {
			Logger::console.error("unexpected value for unknown in parseFromClientString: " + String::valueOf(unknown));
		}

		int totalVars = nextByte();

		if (totalVars == 0xFF)
			return;

		for (int i = 0; i < totalVars; ++i) {
#if DEBUG_CUSTOMIZATION_PARSING
			logHexDump("Variable #" + String::valueOf(i+1), custString, offset);
#endif // DEBUG_CUSTOMIZATION_PARSING

			uint8 type = nextByte();
			int16 value = nextByte();

			if (type & 0x80) { // signed value
				type &= 0x7F;
				value |= (nextByte() << 8);
			}

			setVariable(type, value);
		}

#if DEBUG_CUSTOMIZATION_PARSING
		logHexDump("after parsing CustomizationString", custString, offset);
		debug = false;
#endif // DEBUG_CUSTOMIZATION_PARSING

		if (custString.subString(offset) != "\xFF\x03") {
			throw Exception("Did not see EOS after parsing, offset=" + String::valueOf(offset));
		}
	} catch (Exception& e) {
		removeAll();
		StackTrace::printStackTrace();
		logHexDump("Exception in " + String(__FUNCTION__) + " " + e.getMessage(), custString, 0, true);
	}
}


bool CustomizationVariables::toString(String& ascii) {
	String binData;
	getData(binData);

	BinaryData cust(binData);

	cust.encode(ascii);

	return true;
}

bool CustomizationVariables::parseFromString(const String& str, int version) {
	String data = str;
	BinaryData cust(data);

	String custStr;
	cust.decode(custStr);

	*this = custStr;

	return true;
}

bool CustomizationVariables::toBinaryStream(ObjectOutputStream* stream) {
	String str;
	getData(str);

	str.toBinaryStream(stream);

	return true;
}

bool CustomizationVariables::parseFromBinaryStream(ObjectInputStream* stream) {
	String str;
	str.parseFromBinaryStream(stream);

	*this = str;

	return true;
}

void to_json(nlohmann::json& j, const CustomizationVariables& vars) {
	String binData;
	vars.getData(binData);

	BinaryData cust(binData);

	String ascii;
	cust.encode(ascii);

	j = ascii;
}
