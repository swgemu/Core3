SuiSample = {}
function SuiSample:openSample(pPlayer, pUsingObject)
	local sui = SuiListBox.new("SuiSample", "defaultCallback")

	-- Using object ID, stored in PageData
	if (pUsingObject == nil) then
		sui.setTargetNetworkId(0)
	else
		sui.setTargetNetworkId(SceneObject(pUsingObject):getObjectID())
	end

	sui.setForceCloseDistance(16)

	-- Not needed as OK button is subscribed by default callback above
	-- sui.subscribeToEvent(SuiEventType.SET_onClosedOk, "", "SuiSample:eventCallback")

	sui.setTitle("test title")
	sui.setPrompt("test prompt")

	sui.add("List Item 1", "Value1")
	sui.add("List Item 2", "Value2")

	sui.sendTo(pPlayer)
end

function SuiSample:eventCallback(pPlayer, pSui, eventIndex, args)
end

function SuiSample:defaultCallback(pPlayer, pSui, eventIndex, args)
end
