VisionsSheriRayConvoTemplate = ConvoTemplate:new {
  initialScreen = "InitialConvo",
  templateType = "Lua",
  luaClassHandler = "VisionsSheriRay_convo_handler",
  screens = {}
}

InitialConvoScreen = ConvoScreen:new {
  id = "InitialConvo",
  customDialogText = "Oh, Hello. I just got a holocall from an old friend, he is looking for help on behalf of the Alliance to Restore the Republic. It sounds like arduous work on an out of the way moon but he says it's very important to the cause. Are you interested?",
  stopConversation = "false",
  options = {
      {"What can I do to help you with this?", "Branch_Response_01"},
      {"Are you sure this is legit? You don't see random guys offering a mission for the Alliance just anywhere these days.", "Branch_Response_02"},
      {"I don't think I can help, good luck with your mission.", "Branch_Response_03"},
  }
}
VisionsSheriRayConvoTemplate:addScreen(InitialConvoScreen);

Branch_Response_01 = ConvoScreen:new {
  id = "Branch_Response_01",
  customDialogText = "Don't worry, he will fill you in once you arrive. Let me see, yes here is the waypoint to his location, I sent him a message and he will be expecting your arrival.",
  stopConversation = "true",
  options = {
  }
}
VisionsSheriRayConvoTemplate:addScreen(Branch_Response_01);

Branch_Response_02 = ConvoScreen:new {
  id = "Branch_Response_02",
  customDialogText = "Don't worry, he will fill you in once you arrive. Let me see, yes here is the waypoint to his location, I sent him a message and he will be expecting your arrival.",
  stopConversation = "true",
  options = {
  }
}
VisionsSheriRayConvoTemplate:addScreen(Branch_Response_02);

Branch_Response_03 = ConvoScreen:new {
  id = "Branch_Response_03",
  customDialogText = "He seems to think there was only a short time to complete this, I'll be in town for awhile longer, if you reconsider.",
  stopConversation = "true",
  options = {
  }
}
VisionsSheriRayConvoTemplate:addScreen(Branch_Response_03);

Response_Accepted = ConvoScreen:new {
	id = "Response_Accepted",
	customDialogText = "Please hurry to Yavin IV, the Rebellion desperately needs your assistance!",
	stopConversation = "true",
	options = {
	}
}
VisionsSheriRayConvoTemplate:addScreen(Response_Accepted);

Deny_Faction = ConvoScreen:new {
	id = "Deny_Faction",
	customDialogText = "Wonderful weather out here today, isn't it?",
	stopConversation = "true",
	options = {
	}
}
VisionsSheriRayConvoTemplate:addScreen(Deny_Faction);

Service_Noted = ConvoScreen:new {
	id = "Deny_Faction",
	customDialogText = "The Alliance thanks you for your aid!",
	stopConversation = "true",
	options = {
	}
}
VisionsSheriRayConvoTemplate:addScreen(Service_Noted);

addConversationTemplate("VisionsSheriRayConvoTemplate", VisionsSheriRayConvoTemplate);
