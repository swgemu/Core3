#ifndef BLACKBOARDDATA_H_
#define BLACKBOARDDATA_H_

#include <type_traits>
#include <utility>
#include <typeinfo>
#include <memory>
#include <cassert>

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {

enum DataVal : uint32 { WALK, RUN, DEFAULT, WEAPON, RANDOM, PLAYER, CREATURE, NPC, TANGIBLE, AGENT, PRIMARYWEAPON, SECONDARYWEAPON, MONSTER, DROID, ANDROID, HUMANOID, BADVAL };

template <typename T>
using BlackboardType = typename std::decay<T>::type;

class BlackboardData : public Object {
private:
	class AbstractData {
	public:
		virtual ~AbstractData() {
		}
		virtual bool operator==(const AbstractData&) const = 0;
	};

	template <typename T>
	class Data : public AbstractData {
	public:
		Data() : value(static_cast<T>(0)) {
		}

		Data(T in) : value(in) {
		}

		Data(const Data<T>& in) : value(in.value) {
		}

		Data(Data<T>&& in) : Data() {
			swap(*this, in);
		}

		friend void swap(Data<T>& a, Data<T>& b) {
			std::swap(a.value, b.value);
		}

		Data<T>& operator=(Data<T> in) {
			swap(*this, in);
			return *this;
		}

		~Data() {
		}

		T value;

		bool operator==(const AbstractData& b) const {
			try {
				return value == dynamic_cast<const Data<T>&>(b).value;
			} catch (std::bad_cast&) {
				// this isn't necessarily a bad thing, it just means our
				// data types aren't the same
				return false;
			}
		}
	};

	// this is a shared_ptr because this ends up in vectors which need to copy
	std::shared_ptr<AbstractData> data;

public:
	BlackboardData() : Object(), data(NULL) {
	}

	template <typename T>
	BlackboardData(T&& in) : Object(), data(new Data<BlackboardType<T>>(std::forward<T>(in))) {
	}

	BlackboardData(const BlackboardData& in) : Object(), data(in.data) {
	}

	BlackboardData(BlackboardData&& in) : BlackboardData() {
		swap(*this, in);
	}

	friend void swap(BlackboardData& a, BlackboardData& b) {
		std::swap(a.data, b.data);
	}

	BlackboardData& operator=(BlackboardData in) {
		swap(*this, in);
		return *this;
	}

	// define this as a member function to avoid ambiguous operator== overloads
	bool operator==(const BlackboardData& b) const {
		return *data == *b.data;
	}

	template <typename T>
	BlackboardType<T>& get() {
		typedef BlackboardType<T> TBASE;
		// this with throw bad_cast if the type is wrong
		return dynamic_cast<Data<TBASE>&>(*data).value;
	}

	template <typename T>
	void set(T&& in) {
		data.reset(new Data<BlackboardType<T>>(std::forward<T>(in)));
	}
};

// template specializations to avoid passing BlackboardData into the input ctor
template <>
inline BlackboardData::BlackboardData(const BlackboardData& in) : Object(), data(in.data) {
}

template <>
inline BlackboardData::BlackboardData(BlackboardData& in) : Object(), data(in.data) {
}

template <>
inline BlackboardData::BlackboardData(BlackboardData&& in) : BlackboardData() {
	swap(*this, in);
}

} // namespace bt
} // namespace ai
} // namespace creature
} // namespace objects
} // namespace zone
} // namespace server

#endif // BLACKBOARDDATA_H_
