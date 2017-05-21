SuiKeypad = {}
SuiKeypad.new = function (defaultCallback, defaultFunction)
	local self = SuiTemplate.new("Script.Keypad")
	local data = {}

	self.setDefaultCallback(defaultCallback, defaultFunction)

	self.subscribeToPropertyForEvent(SuiEventType.SET_onClosedOk, "result.numberBox", "localtext")
	self.subscribeToPropertyForEvent(SuiEventType.SET_onClosedCancel, "result.numberBox", "localtext")

	self.subscribeToPropertyForEvent(SuiEventType.SET_onClosedOk, "buttonEnter", "ButtonPressed")
	self.subscribeToPropertyForEvent(SuiEventType.SET_onClosedCancel, "buttonEnter", "ButtonPressed")

	self.hideSliceButton = function ()
		self.setProperty("buttonSlice", "Enabled", "false")
		self.setProperty("buttonSlice", "Visible", "false")
	end

	self.hideKeycardButton = function ()
		self.setProperty("buttonKeycard", "Enabled", "false")
		self.setProperty("buttonKeycard", "Visible", "false")
	end

	return self
end
