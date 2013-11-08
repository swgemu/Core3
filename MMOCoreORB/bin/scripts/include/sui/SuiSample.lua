require("sui.SuiListBox")

SuiSample = {}
function SuiSample:onLoggedIn(pCreatureObject)
	local sui = SuiListBox.new()
	sui.subscribeToEvent(SuiEventType.NotifyAccept, "", "SuiSample:onAccept")
	
	sui.setTitle("crush title")
	sui.setPrompt("crush prompt")
	
	sui.add("List Item 1", "Value1")
	sui.add("List Item 2", "Value2")
	
	sui.sendTo(pCreatureObject)
end

function SuiSample:onAccept()
	print("Accepted!")
end