Ai = { }

function Ai:new (o)
	o = o or { }
	setmetatable(o, self)
    self.__index = self
    return o
end

Ais = { }

function Ais:addAiTemplate(obj, file)
	if (obj == nil) then
		print("null template specified for " .. file)
	else
		addAiTemplate(file, obj)
	end
end

function getAiTemplate(crc)
	return Ais[crc]
end
