#ifndef BLACKBOARDDATASPACE_H_
#define BLACKBOARDDATASPACE_H_

#include <type_traits>
#include <utility>
#include <typeinfo>
#include <memory>
#include <cassert>

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
namespace btspace {

enum DataValSpace : uint32 { DEFAULT, FLYING, RANDOM, PLAYER, CREATURE, SHIP, SHIPAGENT, BADVAL };

template <typename T>
using BlackboardType = typename std::decay<T>::type;

class BlackboardDataSpace : public Object {
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
	BlackboardDataSpace() : Object(), data(NULL) {
	}

	template <typename T>
	BlackboardDataSpace(T&& in) : Object(), data(new Data<BlackboardType<T>>(std::forward<T>(in))) {
	}

	BlackboardDataSpace(const BlackboardDataSpace& in) : Object(), data(in.data) {
	}

	BlackboardDataSpace(BlackboardDataSpace&& in) : BlackboardDataSpace() {
		swap(*this, in);
	}

	friend void swap(BlackboardDataSpace& a, BlackboardDataSpace& b) {
		std::swap(a.data, b.data);
	}

	BlackboardDataSpace& operator=(BlackboardDataSpace in) {
		swap(*this, in);
		return *this;
	}

	// define this as a member function to avoid ambiguous operator== overloads
	bool operator==(const BlackboardDataSpace& b) const {
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

// template specializations to avoid passing BlackboardDataSpace into the input ctor
template <>
inline BlackboardDataSpace::BlackboardDataSpace(const BlackboardDataSpace& in) : Object(), data(in.data) {
}

template <>
inline BlackboardDataSpace::BlackboardDataSpace(BlackboardDataSpace& in) : Object(), data(in.data) {
}

template <>
inline BlackboardDataSpace::BlackboardDataSpace(BlackboardDataSpace&& in) : BlackboardDataSpace() {
	swap(*this, in);
}

} // namespace btspace
} // namespace ai
} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

#endif // BLACKBOARDDATASPACE_H_
