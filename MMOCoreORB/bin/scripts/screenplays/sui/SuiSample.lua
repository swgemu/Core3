SuiSample = {}
function SuiSample:openSample(pCreatureObject)
	local sui = SuiListBox.new()

	-- Default callback for ok and cancel, must always be called before subscribing to any other events
	sui.setDefaultCallback("SuiSample", "defaultCallback")

	-- Not needed as OK button is subscribed by default callback above
	-- sui.subscribeToEvent(SuiEventType.SET_onClosedOk, "", "SuiSample:eventCallback")

	sui.setTitle("test title")
	sui.setPrompt("test prompt")

	sui.add("List Item 1", "Value1")
	sui.add("List Item 2", "Value2")

	sui.sendTo(pCreatureObject)
end

-- cancelPressed not used here
function SuiSample:eventCallback(pPlayer, pSui, cancelPressed, args)
	printf("Event callback triggered.")
end

function SuiSample:defaultCallback(pPlayer, pSui, cancelPressed, args)
	printf("Default callback triggered.")
end
