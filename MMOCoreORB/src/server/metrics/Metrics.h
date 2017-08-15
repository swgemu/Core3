/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef METRICS_H_
#define METRICS_H_

#include <chrono>

#include "engine/engine.h"
#include "engine/core/MetricsManager.h"

#include "conf/ConfigManager.h"

using namespace std::chrono;

namespace server {
namespace metrics {
	class Metrics {
		String path;
		bool active;

	protected:
		void setPath(const String& s) {
			path = s;
		}

	public:
		void publish(const String& name, const String& value, const String& type) {
			if (!active) return;

			int64 now = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();

			MetricsManager::Result result = MetricsManager::instance()->publish(
					String(path + "." + name).toCharArray(),
					value.toCharArray(),
					type.toCharArray(),
					String::valueOf(now).toCharArray());

			switch (result) {
				case MetricsManager::NO_CONNECTION:
					System::out << "Metrics failed to get connection." << endl;
					return;
				case MetricsManager::SOCKET_EXCEPTION:
					System::out << "Metrics encountered a socket exception." << endl;
					return;
				case MetricsManager::GENERAL_ERROR:
					System::out << "Metrics encountered a general error." << endl;
					return;
				case MetricsManager::SUCCESS:
					System::out << "Metrics success!" << endl;
				default:
					return;
			};
		}

		void publishGauge(const String& name, const String& value) {
			publish(name, value, "g");
		}

		void publishCounter(const String& name, const String& value) {
			publish(name, value, "c");
		}

		void publishTimer(const String& name, const String& value) {
			publish(name, value, "ms");
		}

		void publishHist(const String& name, const String& value) {
			publish(name, value, "h");
		}

		void publishMeter(const String& name, const String& value) {
			publish(name, value, "m");
		}

	public:
		Metrics() {
			Metrics("");
		}
		Metrics(const char* path) {
			Metrics(String(path));
		}
		Metrics(String path) {
			this->path = path;
			active = ConfigManager::instance()->shouldUseMetrics();
		}
	};
} // namespace metrics
} // namespace server

using namespace server::metrics;

#endif // METRICS_H_
