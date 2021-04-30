ConvoTemplate = {
	initialScreen = "",
	screens = {}
}

function ConvoTemplate:new (o)
	o = o or { }
	setmetatable(o, self)
    self.__index = self
    return o
end

function ConvoTemplate:addScreen(screen)
	table.insert(self.screens, screen)
end

ConvoScreen = {
	id = "",
	leftDialog = "",
	customDialogText = "",
	options = {}
}

function ConvoScreen:new (o)
	o = o or { }
	setmetatable(o, self)
    self.__index = self
    return o
end