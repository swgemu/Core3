VisionsJohnRoyConvoTemplate= ConvoTemplate:new {
  initialScreen = "InitialConvo",
  templateType = "Lua",
  luaClassHandler = "VisionsJohnRoy_convo_handler",
  screens = {}
}

InitialConvo = ConvoScreen:new {
  id = "InitialConvo",
  customDialogText = "Hello, my name is John Roy, SpecForce Procurement Specialist for the Rebellion. Did you make contact with our informant?",
  stopConversation = "false",
  options = {
		{"Yes, she sent me to speak with you.", "SentByInformant"},
  }
}
VisionsJohnRoyConvoTemplate:addScreen(InitialConvo);

SentByInformant = ConvoScreen:new {
  id = "SentByInformant",
  customDialogText = "Thank you for coming all this way, and I am sorry for how little you had to go on, but we have reason to believe that parts of the destroyed Death Star, which are in orbit have fallen in large quantities nearby, and we need to get to them as fast as we can, the Empire is likely already moving to acquire them as well.",
  stopConversation = "false",
  options = {
		{"Let's find these before the Empire does!", "Response_01"},
    {"Are you positive I can be helpful here, what does this stuff even look like?", "Response_02"},
  }
}
VisionsJohnRoyConvoTemplate:addScreen(SentByInformant);

Response_01 = ConvoScreen:new {
  id = "Response_01",
  customDialogText = "Take a look at the waypoint I just sent you, we believe there is a spread of around a few hundred meters from what was spotted earlier.",
  stopConversation = "true",
  options = {
  }
}
VisionsJohnRoyConvoTemplate:addScreen(Response_01);

Response_02 = ConvoScreen:new {
  id = "Response_02",
  customDialogText = "Take a look at the waypoint I just sent you, we believe there is a spread of around a few hundred meters from what was spotted earlier.",
  stopConversation = "true",
  options = {
  }
}
VisionsJohnRoyConvoTemplate:addScreen(Response_02);

TurnIn = ConvoScreen:new {
  id = "TurnIn",
  customDialogText = "Well, did you find it? Let's see what you have there.",
  stopConversation = "false",
  options = {
      {"I found these, are they what you were hoping to find?", "Turnin_Response_01"},
      {"I hope this is worth the trouble, it's a lot of mangled wreckage, but here it is.", "Turnin_Response_02"},
  }
}
VisionsJohnRoyConvoTemplate:addScreen(TurnIn);

Turnin_Response_01 = ConvoScreen:new {
  id = "Turnin_Response_01",
  customDialogText = "Yes, this will work I think. I'll send it off after my team packs up, thank you for assisting us.",
  stopConversation = "true",
  options = {
  }
}
VisionsJohnRoyConvoTemplate:addScreen(Turnin_Response_01);

Turnin_Response_02 = ConvoScreen:new {
  id = "Turnin_Response_02",
  customDialogText = "Yes, this will work I think. I'll send it off after my team packs up, thank you for assisting us.",
  stopConversation = "true",
  options = {
  }
}
VisionsJohnRoyConvoTemplate:addScreen(Turnin_Response_02);

Deny_Faction = ConvoScreen:new {
  id = "Deny_Faction",
  customDialogText = "You've made your choices, haven't you? Best you leave now, before my friends take notice.",
  stopConversation = "true",
  options = {
  }
}
VisionsJohnRoyConvoTemplate:addScreen(Deny_Faction);

Cant_Give_Reward = ConvoScreen:new {
	id = "Cant_Give_Reward",
	customDialogText = "It seems your bags are full and you have no room for your reward.",
	stopConversation = "true",
	options = {
	}
}
VisionsDianeBrackConvoTemplate:addScreen(Cant_Give_Reward)

Time_Wasted= ConvoScreen:new {
	id = "Time_Wasted",
	customDialogText = "Please hurry and return with any wreckage you can!",
	stopConversation = "true",
	options = {
	}
}
VisionsDianeBrackConvoTemplate:addScreen(Time_Wasted)

addConversationTemplate("VisionsJohnRoyConvoTemplate", VisionsJohnRoyConvoTemplate);
