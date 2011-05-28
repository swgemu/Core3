ConvoScreen = {
	id = "",
	leftDialog = "",
	
	optionText = "",
	optionLink = "",
	children = { }
}

function ConvoScreen:new (o)
	o = o or { }
	setmetatable(o, self)
    self.__index = self
    return o
end

function ConvoScreen:setId(td)
	self.id = td
end

function ConvoScreen:getId()
	return self.id
end

function ConvoScreen:setDialog(text)
    self.leftDialog = text
end

function ConvoScreen:getDialog()
    return self.leftDialog
end

function ConvoScreen:getOptionCount()
    return # self.children
end

function ConvoScreen:addOption(convoScreen)
    table.insert(self.children, convoScreen)
end
 