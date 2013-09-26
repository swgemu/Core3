NOJEDIPROGRESSION = 0
HOLOCRONJEDIPROGRESSION = 1
VILLAGEJEDIPROGRESSION = 2
CUSTOMJEDIPROGRESSION = 3

jediProgressionType = NOJEDIPROGRESSION

jediManagerName = "JediManager"

function printf(...) io.write(string.format(unpack(arg))) end

Object = {
}

function Object:new (o)
	o = o or { }
	setmetatable(o, self)
    self.__index = self
    return o
end

JediManager = Object:new {
	jediManagerName = jediManagerName,
	jediProgressionType = NOJEDIPROGRESSION,
	startingEvent = nil,
}

function JediManager:onPlayerCreation(pCreature)
	-- Default behaviour for the onPlayerCreation event, do nothing.
end

function JediManager:checkForceStatusCommand(pCreature)
	-- Default behaviour for the checkForceStatus command, do nothing.
end

