function printf(...) io.write(string.format(unpack(arg))) end

function writeData(key, data)
	keyUnpacked = string.format(key)
	dataUnpacked = string.format(data)
	
	--printf(keyUnpacked)
	--printf(dataUnpacked)
	
	writeSharedMemory(keyUnpacked, dataUnpacked)
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