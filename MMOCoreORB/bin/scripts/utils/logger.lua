-- Simple logger for Lua.

LT_ERROR = 5
LT_WARNING = 4
LT_DEBUG = 3
LT_INFO = 2
LT_TRACE = 1

local MAX_NUMBER_OF_ENTRIES = 100

Logger = {}
Logger.logEntries = {}

-- Log function for text.
-- @param message the text to log.
-- @param level the level of the log message.
function Logger:log(message, level)
	if table.getn(Logger.logEntries) > MAX_NUMBER_OF_ENTRIES then
		table.remove(Logger.logEntries, 1)
	end
	table.insert(Logger.logEntries, { message = message, level = level, info = debug.getinfo(2) })
end

-- Print the log and clear the log.
-- @param detailed detailed information about where logs where made if set to true.
-- @param lowestLevel the lowest message level to dump.
function Logger:dump(detailed, lowestLevel)
	for i = 1, table.getn(Logger.logEntries), 1 do
		local entry = Logger.logEntries[i]
		if entry["level"] >= lowestLevel then
			if detailed then
				print(entry["message"] .. " - " .. entry["info"].name .. ", " .. entry["info"].short_src .. ", " .. entry["info"].currentline)
			else
				print(entry["message"])
			end
		end
	end

	Logger.logEntries = {}
end

return Logger
