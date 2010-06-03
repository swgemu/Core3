ObjectTemplates = { }

function ObjectTemplates:addTemplate(obj, file)
	crc = crcString(file)
	
	--addTemplateCRC(file, obj)
	
	if self[crc] == nil then
		self[crc] = obj 
	else
		print("error conflicting server template crc " .. crc .. " file " .. file)
	end
end

function getTemplate(crc)
	return ObjectTemplates[crc]
end

includeFile("allobjects.lua")
--includeFile("serverobjects.lua")