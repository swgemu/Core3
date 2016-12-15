SuiListBox = {}
SuiListBox.new = function (defaultCallback, defaultFunction)
	local self = SuiTemplate.new("Script.listBox")
	local data = {}

	self.setDefaultCallback(defaultCallback, defaultFunction)

	-- Subscribe to selected listbox row so that it sends back an argument
	self.subscribeToPropertyForEvent(SuiEventType.SET_onClosedOk, "List.lstList", "SelectedRow")

	self.setTitle = function (value)
		self.setProperty("bg.caption.lblTitle", "Text", value)
	end

	self.setPrompt = function (value)
		self.setProperty("Prompt.lblPrompt", "Text", value)
	end

	self.showOtherButton = function (value)
		self.subscribeToPropertyForEvent(SuiEventType.SET_onClosedOk, "this", "otherPressed")
		self.subscribeToPropertyForEvent(SuiEventType.SET_onClosedCancel, "this", "otherPressed")

		self.setProperty("btnOther", "Visible", "true")
		self.setProperty("btnOther", "Location", "102,262")
		self.setProperty("btnOther", "Size", "81,19")
		self.setProperty("btnOther", "ScrollExtent", "81,19")
		self.setProperty("btnOk", "Location", "188,262")
		self.setProperty("btnOk", "Size", "81,19")
		self.setProperty("btnOk", "ScrollExtent", "81,19")
		self.setProperty("btnCancel", "Size", "81,19")
		self.setProperty("btnCancel", "ScrollExtent", "81,19")
	end

	self.setCancelButtonText = function (text)
		self.setProperty("btnCancel", "Text", text)
	end

	self.hideCancelButton = function ()
		self.setProperty("btnCancel", "Enabled", "false")
		self.setProperty("btnCancel", "Visible", "false")
	end

	self.setOkButtonText = function (text)
		self.setProperty("btnOk", "Text", text)
	end

	self.setOtherButtonText = function (text)
		self.setProperty("btnOther", "Text", text)
	end

	self.add = function (text, value)
		self.addDataItem("List.dataList", "Name", tostring(#data))
		self.setProperty("List.dataList." .. tostring(#data), "Text", text)
		
		if (value ~= "") then
			self.setStoredData(tostring(#data), value)
		end
		
		table.insert(data, {['text'] = text, ['value'] = value})
	end

	self.remove = function (index)
		table.remove(data, index)
	end

	self.get = function (index)
		return data[index]
	end

	self.size = function ()
		return #data
	end

	return self
end
