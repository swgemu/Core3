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

	message = message .. " - "

	if info.name ~= nil then
		message = message .. "Function: " .. info.name .. " "
	end

	if (info.source ~= nil) then
		message = message .. " Source: " .. info.source .. " "
	end

	if (info.currentline ~= nil) then
		message = message .. " Line: " .. info.currentline
	end

	logLua(level, message)
end

return Logger
