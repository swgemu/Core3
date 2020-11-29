VisionsDianeBrackConvoTemplate = ConvoTemplate:new {
	initialScreen = "InitialConvo",
	templateType = "Lua",
	luaClassHandler = "VisionsDianeBrack_convo_handler",
	screens = {}
}

InitialConvo = ConvoScreen:new {
	id = "InitialConvo",
	customDialogText = "Name is Diane Brack, Imperial Security Bureau, what business do you have with me?",
	stopConversation = "false",
	options = {
		{"I have been sent by the informant.", "SentByInformant"},
	}
}
VisionsDianeBrackConvoTemplate:addScreen(InitialConvo);

SentByInformant = ConvoScreen:new {
	id = "SentByInformant",
	customDialogText = "I assume you have some idea why you were asked to come, but it was a farce. We had no other choice to keep this under wraps as long as we could. We have evidence that portions of the Death Star are still raining down on this moon, and we need you to brave this forest moon and acquire those pieces before any scavengers or rebels manage to.",
	stopConversation = "false",
	options = {
		{"I will accept this mission, Ma'am.", "Response_01"},
		{"Are you positive this is it, wow. I have to see this, what do you need me to do?", "Response_02"},
	}
}
VisionsDianeBrackConvoTemplate:addScreen(SentByInformant);

Response_01 = ConvoScreen:new {
	id = "Response_01",
	customDialogText = "Here is a waypoint to the area, look for larger pieces of wreckage within a few hundred meters of that location, there should be plenty to look through, bring back what you can",
	stopConversation = "true",
	options = {
	}
}
VisionsDianeBrackConvoTemplate:addScreen(Response_01);

Response_02 = ConvoScreen:new {
	id = "Response_02",
	customDialogText = "Here is a waypoint to the area, look for larger pieces of wreckage within a few hundred meters of that location, there should be plenty to look through, bring back what you can",
	stopConversation = "true",
	options = {
	}
}
VisionsDianeBrackConvoTemplate:addScreen(Response_02);

TurnIn = ConvoScreen:new {
	id = "TurnIn",
	customDialogText = "I hope that you're carrying the salvage that we were looking for, my superiors are very clear about the priority of this mission and it's success.",
	stopConversation = "false",
	options = {
		{"Here is what I found, I hope it helps. Sir.", "Turnin_Response_01"},
		{"There is a lot of damage, I'm not sure this is worth even the time it took to find it.", "Turnin_Response_02"},
	}
}
VisionsDianeBrackConvoTemplate:addScreen(TurnIn);

Turnin_Response_01 = ConvoScreen:new {
	id = "Turnin_Response_01",
	customDialogText = "I'll send it to the engineers and technicians, you have done a great service to the Empire.",
	stopConversation = "true",
	options = {
	}
}
VisionsDianeBrackConvoTemplate:addScreen(Turnin_Response_01);

Turnin_Response_02 = ConvoScreen:new {
	id = "Turnin_Response_02",
	customDialogText = "I'll send it to the engineers and technicians, you have done a great service to the Empire.",
	stopConversation = "true",
	options = {
	}
}
VisionsDianeBrackConvoTemplate:addScreen(Turnin_Response_02);

Deny_Faction = ConvoScreen:new {
	id = "Deny_Faction",
	customDialogText = "Leaving now is a good idea for your health...",
	stopConversation = "true",
	options = {
	}
}
VisionsDianeBrackConvoTemplate:addScreen(Deny_Faction)

Cant_Give_Reward = ConvoScreen:new {
	id = "Cant_Give_Reward",
	customDialogText = "I don't have time for this. You have no room for your reward...",
	stopConversation = "true",
	options = {
	}
}
VisionsDianeBrackConvoTemplate:addScreen(Cant_Give_Reward)

Time_Wasted = ConvoScreen:new {
	id = "Time_Wasted",
	customDialogText = "Why haven't you collected any of the wreckage yet? Get going.",
	stopConversation = "true",
	options = {
	}
}
VisionsDianeBrackConvoTemplate:addScreen(Time_Wasted)

addConversationTemplate("VisionsDianeBrackConvoTemplate", VisionsDianeBrackConvoTemplate);
