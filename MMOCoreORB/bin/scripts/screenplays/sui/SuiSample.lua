SuiSample = {}
function SuiSample:openSample(pCreatureObject, pUsingObject)
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

	sui.sendTo(pCreatureObject)
end

-- cancelPressed not used here
function SuiSample:eventCallback(pPlayer, pSui, cancelPressed, args)
	printf("Event callback triggered.")
	local pPageData = LuaSuiBoxPage(pSui):getSuiPageData()
	if (pPageData == nil) then
		printf("ppagedata nil\n")
	else
		printf("pageid on callback: " .. LuaSuiPageData(pPageData):getPageId() .. "\n")
	end
end

function SuiSample:defaultCallback(pPlayer, pSui, cancelPressed, args)
	printf("Default callback triggered.")
	local pPageData = LuaSuiBoxPage(pSui):getSuiPageData()
	if (pPageData == nil) then
		printf("ppagedata nil\n")
	else
		printf("pageid on callback: " .. LuaSuiPageData(pPageData):getPageId() .. "\n")
	end
end
