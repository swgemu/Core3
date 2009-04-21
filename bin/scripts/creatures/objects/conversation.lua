ConvoScreen = Object:new {
    id = "",
    leftDialog = "",

    optionCount = 0,
    compOptionText = "",
    compOptionLinks = "",
}

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
    return self.optionCount
end

function ConvoScreen:addOption(optText, linkParameter)
    if optionCount==0 then
        self.compOptionText = optText
        self.compOptionLinks = linkParameter
    else
        self.compOptionText = self.compOptionText .. "|" .. optText
        self.compOptionLinks = self.compOptionLinks .. "|" .. linkParameter
    end
    self.optionCount = self.optionCount + 1
end

function ConvoScreen:getCompiledOptionText()
    return self.compOptionText
end

function ConvoScreen:getCompiledOptionLinks()
    return self.compOptionLinks
end
