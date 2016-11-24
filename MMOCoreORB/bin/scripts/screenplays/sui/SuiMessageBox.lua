SuiMessageBox = {}
SuiMessageBox.new = function (defaultCallback, defaultFunction)
	local self = SuiTemplate.new("Script.messageBox")
	local data = {}

	self.setDefaultCallback(defaultCallback, defaultFunction)

	self.setProperty("btnRevert", "Enabled", "false")
	self.setProperty("btnRevert", "Visible", "false")

	self.setTitle = function (value)
		self.setProperty("bg.caption.lblTitle", "Text", value)
	end

	self.setPrompt = function (value)
		self.setProperty("Prompt.lblPrompt", "Text", value)
	end

	self.setCancelButtonText = function (text)
		self.setProperty("btnCancel", "Text", text)
	end

	self.setOkButtonText = function (text)
		self.setProperty("btnOk", "Text", text)
	end
	
	self.setOtherButtonText = function (text)
		self.setProperty("btnRevert", "Text", text)
		self.setProperty("btnRevert", "Enabled", "true")
		self.setProperty("btnRevert", "Visible", "true")
	end

	self.hideCancelButton = function (text)
		self.setProperty("btnCancel", "Enabled", "false")
		self.setProperty("btnCancel", "Visible", "false")
	end

	return self
end
