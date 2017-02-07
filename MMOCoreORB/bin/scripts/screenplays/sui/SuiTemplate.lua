SuiEventType = {
	SET_none = 0x00,
	SET_onButton = 0x01,
	SET_onCheckbox = 0x02,
	SET_onEnabledChanged = 0x03,
	SET_onGenericSelection = 0x04,
	SET_onSliderbar = 0x05,
	SET_onTabbedPane = 0x06,
	SET_onTextbox = 0x07,
	SET_onVisibilityChanged = 0x08,
	SET_onClosedOk = 0x09, -- OK Button
	SET_onClosedCancel = 0x0A, -- Cancel button
	SET_numEventTypes = 0x0B,
}

SuiWindowType = {
	FS_EXP_CONVERT = 1042
}

SuiTemplate = {}
SuiTemplate.new = function (templateName)
	local self = {}
	local luaCallback = {}
	local windowType = 0

	local suiPageData = LuaSuiPageData(templateName)

	self.setWindowType = function (type)
		windowType = type
	end

	self.setForceCloseDistance = function (distance)
		suiPageData:setForceCloseDistance(distance)
	end

	self.setProperty = function (widget, property, value)
		suiPageData:setProperty(widget, property, value)
	end

	self.addDataItem = function (widget, property, value)
		suiPageData:addDataItem(widget, property, value)
	end

	self.clearDataSource = function (dataSource)
		suiPageData:clearDataSource(dataSource)
	end

	self.addDataSourceContainer = function (parent, name)
		suiPageData:addDataSourceContainer(parent, name)
	end

	self.clearDataSourceContainer = function (dataSourceContainer)
		suiPageData:clearDataSourceContainer(dataSourceContainer)
	end

	self.addChildWidget = function (parent, type, name)
		suiPageData:addChildWidget(parent, type, name)
	end

	self.subscribeToEvent = function (eventType, parent, callback)
		suiPageData:subscribeToEvent(eventType, parent, callback)
	end

	self.setDefaultCallback = function (play, callback)
		luaCallback.play = play
		luaCallback.callback = callback
		suiPageData:setDefaultCallback(play .. ":" .. callback)
	end

	self.setTargetNetworkId = function (id)
		suiPageData:setTargetNetworkId(id)
	end

	self.subscribeToPropertyForEvent = function (eventType, widget, property)
		suiPageData:subscribeToPropertyForEvent(eventType, widget, property)
	end

	self.setStoredData = function (key, value)
		suiPageData:setStoredData(key, value)
	end

	self.deleteStoredData = function (key)
		suiPageData:deleteStoredData(key)
	end

	self.sendTo = function (pPlayer)
		if (luaCallback.play == nil or luaCallback.callback == nil) then
			printLuaError("SuiTemplate:sendTo, nil callback data.")
		end

		local pPageData = suiPageData:_getObject()

		if (pPageData == nil) then
			printLuaError("SuiTemplate:sendTo, nil page data.")
		end

		local suiManager = LuaSuiManager()
		return suiManager:sendSuiPage(pPlayer, pPageData, luaCallback.play, luaCallback.callback, windowType)
	end

	return self
end
