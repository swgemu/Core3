SuiCalibrationGame4 = {}
SuiCalibrationGame4.new = function (defaultCallback, defaultFunction)
	local self = SuiTemplate.new("/Script.calibration.game4")
	local data = {}

	self.setDefaultCallback(defaultCallback, defaultFunction)

	self.setTitle = function (value)
		self.setProperty("bg.caption.lblTitle", "Text", value)
	end

	self.setDescription = function (value)
		self.setProperty("top.description.desc", "Text", value)
	end

	self.setAttemptsDesc = function (value)
		self.setProperty("top.description.attempts", "Text", value)
	end

	self.setCancelButtonText = function (text)
		self.setProperty("btnCancel", "Text", text)
	end

	self.setOkButtonText = function (text)
		self.setProperty("btnOk", "Text", text)
	end

	return self
end
