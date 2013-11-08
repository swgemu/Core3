--SuiPageData is just here to simulate the Luna C++ object for now.
SuiPageData = {
	lastId = 0
}

SuiPageData.getNextId = function ()
	SuiPageData.lastId = SuiPageData.lastId + 1
	return SuiPageData.lastId
end

SuiPageData.new = function ()
	local self = {}
	local templateName = 'Script'
	local commands = {}
	local events = {}
	
	self.id = SuiPageData.getNextId()
	self.usingObject = nil
	self.forceCloseDistance = 0
	
	self.setProperty = function (widget, property, value)
		table.insert(commands, {widget, property, value})
	end
	
	self.subscribeToEvent = function (eventType, parent, callback)
	end
	
	self.subscribeToPropertyForEvent = function (eventType, widget, property)
	end
	
	return self
end
--End SuiPageData

SuiEventType = {
	NotifyAccept = 0x09,
	NotifyCancel = 0x0A
}

SuiTemplate = {}
SuiTemplate.new = function (templateName)
	local self = {}
	
	local suiPageData = SuiPageData.new() --This will be replaced with SuiPageData()
	suiPageData.templateName = templateName
	
	self.getId = function () return suiPageData.id end
	
	self.getUsingObject = function ()
		return suiPageData.usingObject
	end
	
	self.setUsingObject = function (object)
		suiPageData.usingObject = object
	end
	
	self.setForceCloseDistance = function (forceCloseDistance)
		suiPageData.forceCloseDistance = forceCloseDistance
	end
	
	self.setProperty = function (widget, property, value)
		suiPageData.setProperty(widget, property, value)
	end
	
	self.subscribeToEvent = function (eventType, parent, callback)
		suiPageData.subscribeToEvent(eventType, parent, callback)
	end
	
	self.subscribeToPropertyForEvent = function (eventType, widget, property)
		suiPageData.subscribeToPropertyForEvent(eventType, widget, property)
	end
	
	return self
end