-- Simple logger for Lua.

LT_ERROR = 1
LT_WARNING = 2
LT_LOG = 3
LT_INFO = 4
LT_DEBUG = 5
LT_TRACE = 6

Logger = {}

-- Log function for text.
-- @param message the text to log.
-- @param level the level of the log message.
function Logger:log(message, level)
	local info = debug.getinfo(2)
	if info.name == nil then
		info.name = "Function Not Defined"
	else
		info.name = "Function: " .. info.name
	end

	logLua(level, message .. " - " .. info.name)
end

return Logger
