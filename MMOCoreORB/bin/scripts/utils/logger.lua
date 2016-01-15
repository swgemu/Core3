-- Simple logger for Lua.

LT_ERROR = 5
LT_WARNING = 4
LT_DEBUG = 3
LT_INFO = 2
LT_TRACE = 1

local MAX_NUMBER_OF_ENTRIES = 100

local FORCE_PRINT = false

Logger = {}
Logger.logEntries = {}

-- Log function for text.
-- @param message the text to log.
-- @param level the level of the log message.
function Logger:log(message, level)
	if #Logger.logEntries > MAX_NUMBER_OF_ENTRIES then
		table.remove(Logger.logEntries, 1)
	end

	local info = debug.getinfo(2)
	if info.name == nil then
		info.name = "unknown function"
	end

	table.insert(Logger.logEntries, { message = message, level = level, info = info })

	if not _TEST and FORCE_PRINT then
		print(message .. " - " .. info.name .. ", " .. info.short_src .. ", " .. info.currentline)
	end
end

-- Print the log and clear the log.
-- @param detailed detailed information about where logs where made if set to true.
-- @param lowestLevel the lowest message level to dump.
function Logger:dump(detailed, lowestLevel)
	for i = 1, #Logger.logEntries, 1 do
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
