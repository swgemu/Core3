require("include/sui/SuiTemplate.lua")

SuiMessageBox = {}
SuiMessageBox.new = function ()
	local self = SuiTemplate.new("Script.messageBox")
	
	self.setTitle = function (value)
		self.setProperty("bg.caption.lblTitle", "Text", value)
	end
	
	self.setPrompt = function (value)
		self.setProperty("Prompt.lblPrompt", "Text", value)
	end
end