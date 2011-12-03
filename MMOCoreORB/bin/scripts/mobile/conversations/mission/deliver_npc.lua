deliver_npc_convotemplate = ConvoTemplate:new {
	initialScreen = "convoscreenstart",
	templateType = "DeliverNPC",
	screens = {}
}

deliver_npc_convoscreenstart = ConvoScreen:new {
	id = "convoscreenstart",
	leftDialog = "@mission/mission_deliver_neutral_easy:m1d",
	options = { }
}
deliver_npc_convotemplate:addScreen(deliver_npc_convoscreenstart);

addConversationTemplate("deliver_npc", deliver_npc_convotemplate);