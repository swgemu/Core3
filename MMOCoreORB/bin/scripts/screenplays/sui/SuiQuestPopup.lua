SuiQuestPopup = {}
SuiQuestPopup.new = function ()
	local self = SuiTemplate.new("/PDA.Questpopup")
	local data = {}

	self.setTitle = function (value)
		self.setProperty("comp.vP.lbl", "Text", value)
	end

	self.setPrompt = function (value)
		self.setProperty("comp.info.text", "Text", value)
	end

	self.setViewerObjectId = function (value)
		self.setProperty("comp.vP.viewer", "setObject", value)
	end
	
	return self
end
