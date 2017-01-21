SuiTransferBox = {}
SuiTransferBox.new = function (defaultCallback, defaultFunction)
	local self = SuiTemplate.new("Script.transfer")
	local data = {}

	self.setDefaultCallback(defaultCallback, defaultFunction)

	self.subscribeToPropertyForEvent(SuiEventType.SET_onClosedOk, "transaction.txtInputFrom", "Text")
	self.subscribeToPropertyForEvent(SuiEventType.SET_onClosedOk, "transaction.txtInputTo", "Text")

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

	self.setRevertButtonText = function (text)
		self.setProperty("btnRevert", "Text", text)
	end

	self.setTransferFromText = function (text)
		self.setProperty("transaction.lblFrom", "Text", text)
	end

	self.setTransferFromValue = function (text)
		self.setProperty("transaction.lblStartingFrom", "Text", text)
	end

	self.setTransferFromInputValue = function (text)
		self.setProperty("transaction.txtInputFrom", "Text", text)
	end

	self.setTransferToText = function (text)
		self.setProperty("transaction.lblTo", "Text", text)
	end

	self.setTransferToValue = function (text)
		self.setProperty("transaction.lblStartingTo", "Text", text)
	end

	self.setTransferToInputValue = function (text)
		self.setProperty("transaction.txtInputTo", "Text", text)
	end

	self.setConversionFromRatio = function (text)
		self.setProperty("transaction", "ConversionRatioFrom", text)
	end

	self.setConversionToRatio = function (text)
		self.setProperty("transaction", "ConversionRatioTo", text)
	end

	return self
end
