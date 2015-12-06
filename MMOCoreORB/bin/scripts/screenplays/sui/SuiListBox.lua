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
		self.setProperty("btnOther", "Visible", "true")
	end

	self.setCancelButtonText = function (text)
		self.setProperty("btnCancel", "Text", text)
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
