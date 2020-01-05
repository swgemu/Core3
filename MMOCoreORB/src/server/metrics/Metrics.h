/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef METRICS_H_
#define METRICS_H_

#include "engine/engine.h"
#include "engine/core/MetricsManager.h"

#include "conf/ConfigManager.h"

namespace server {
namespace metrics {
	class Metrics {
		String path;
		bool active;

	public:
		Metrics() {
			active = ConfigManager::instance()->shouldUseMetrics();
		}

		Metrics(const char* path) : path(path) {
			active = ConfigManager::instance()->shouldUseMetrics();
		}

		Metrics(String&& path) : path(std::move(path)) {
			active = ConfigManager::instance()->shouldUseMetrics();
		}

		Metrics(const String& path) : path(path) {
			active = ConfigManager::instance()->shouldUseMetrics();
		}

		void publishMetrics(const String& name, const char* value, const char* type) const {
			if (!active)
				return;

			MetricsManager::Result result = MetricsManager::instance()->publish(
					String(path + "." + name).toCharArray(),
					value,
					type);

			static Logger logger("Metrics", Logger::INFO);

			switch (result) {
				case MetricsManager::NO_CONNECTION:
					logger.debug("Metrics failed to get connection.");
					return;
				case MetricsManager::SOCKET_EXCEPTION:
					logger.debug("Metrics encountered a socket exception.");
					return;
				case MetricsManager::GENERAL_ERROR:
					logger.debug("Metrics encountered a general error.");
					return;
				case MetricsManager::SUCCESS:
					logger.debug("Metrics success!");
				default:
					return;
			};

		}

		void publishGauge(const String& name, const String& value) const {
			publishMetrics(name, value.toCharArray(), "g");
		}

		// TODO: Add a publish that can send a sample rate (a ratio of the
		// number of actual samples the server will use)
		void publishCounter(const String& name, const String& value) const {
			publishMetrics(name, value.toCharArray(), "c");
		}

		void publishTimer(const String& name, const String& value) const {
			publishMetrics(name, value.toCharArray(), "ms");
		}

		void publishHist(const String& name, const String& value) const {
			publishMetrics(name, value.toCharArray(), "h");
		}

		void publishMeter(const String& name, const String& value) const {
			publishMetrics(name, value.toCharArray(), "m");
		}

		const String& getMetricsPath() const {
			return path;
		}

		bool areMetricsActive() const {
			return active;
		}

	protected:
		void setPath(const String& s) {
			path = s;
		}

	};
} // namespace metrics
} // namespace server

using namespace server::metrics;

#endif // METRICS_H_
