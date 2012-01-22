function printf(...) io.write(string.format(unpack(arg))) end

function writeData(key, data)
	keyUnpacked = string.format(key)
		
	writeSharedMemory(keyUnpacked, data)
end

function deleteData(key)
	deleteSharedMemory(string.format(key))
end

function readData(key)
	return readSharedMemory(string.format(key))
end

Object = { 
}

-- for creation of new instances
function Object:new (o)
	o = o or { }
	setmetatable(o, self)
    self.__index = self
    return o
end

ScreenPlay = Object:new {
	numerOfActs = 0,
	startingEvent = nil
}

Act = Object:new {
		
}


includeFile("tutorial.lua")
includeFile("recruiters/recruiters.lua")
includeFile("tasks/mozo_bondog.lua")
includeFile("tasks/dolac_legasi.lua")
includeFile("recruiters/imperialrecruiter.lua")
includeFile("recruiters/rebelrecruiter.lua")