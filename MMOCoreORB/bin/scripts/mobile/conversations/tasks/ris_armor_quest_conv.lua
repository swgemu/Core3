ris_armor_quest_convotemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "ris_armor_quest_handler",
	screens = {}
}

greeting = ConvoScreen:new {
	id = "greeting",
	leftDialog = "@quest_armorsmith:greeting", --Bah! You waste my time...
	stopConversation = "true",
	options = {}
}
ris_armor_quest_convotemplate:addScreen(greeting);

quest_1_start = ConvoScreen:new {
	id = "quest_1_start",
	leftDialog = "@quest_armorsmith:quest_1_start", --You believe you have learned all there is...
	stopConversation = "false",
	options = {
		{"@quest_armorsmith:yes_to_quest_1_start", "quest_1_start_yes"}, -- I am ready to begin...
		{"@quest_armorsmith:no_to_quest_1_start", "quest_1_start_no"} -- Sorry, I am not interested...
	}
}
ris_armor_quest_convotemplate:addScreen(quest_1_start);

quest_1_start_yes = ConvoScreen:new {
	id = "quest_1_start_yes",
	leftDialog = "@quest_armorsmith:quest_1_start_yes", --I suspected you would agree to my terms...
	stopConversation = "false",
	options = {
		{"@quest_armorsmith:yes", "quest_1_description"}, -- Yes
		{"@quest_armorsmith:no", "quest_1_start_no"}, -- No
	}
}
ris_armor_quest_convotemplate:addScreen(quest_1_start_yes);

quest_1_start_no = ConvoScreen:new {
	id = "quest_1_start_yes",
	leftDialog = "@quest_armorsmith:quest_1_start_no", --Bah! Then be off....
	stopConversation = "true",
	options = {}
}
ris_armor_quest_convotemplate:addScreen(quest_1_start_no);

quest_1_description = ConvoScreen:new {
	id = "quest_1_description",
	leftDialog = "@quest_armorsmith:quest_1_description", --As you know, creating armor starts...
	stopConversation = "true",
	options = {}
}
ris_armor_quest_convotemplate:addScreen(quest_1_description);

quest_2_query = ConvoScreen:new {
	id = "quest_2_query",
	leftDialog = "@quest_armorsmith:quest_2_query", -- The student returns! Show me what you have learned...
	stopConversation = "false",
	options = {
		{"@quest_armorsmith:yes_to_quest_2_query", "quest_2_complete"}, -- I have it right here
		{"@quest_armorsmith:no_to_quest_2_query", "quest_2_incomplete"} -- I haven't yet been able to craft it
	}
}
ris_armor_quest_convotemplate:addScreen(quest_2_query);

quest_2_complete = ConvoScreen:new {
	id = "quest_2_complete",
	leftDialog = "@quest_armorsmith:quest_2_complete", -- Let's see how you did ...
	stopConversation = "false",
	options = {
		{"@quest_armorsmith:yes_to_quest_3_start", "quest_3_start"}, -- Yes, I am ready to continue
		{"@quest_armorsmith:no_to_quest_3_start", "quest_3_start_no"} -- No. I'd rather practice...
	}
}
ris_armor_quest_convotemplate:addScreen(quest_2_complete);


quest_2_incomplete = ConvoScreen:new {
	id = "quest_2_incomplete",
	leftDialog = "@quest_armorsmith:quest_2_incomplete", -- Bah!  Then why are you here...
	stopConversation = "true",
	options = {}
}
ris_armor_quest_convotemplate:addScreen(quest_2_incomplete);

quest_3_start = ConvoScreen:new {
	id = "quest_3_start",
	leftDialog = "@quest_armorsmith:quest_3_start", -- Next I will teach you how to craft the... 
	stopConversation = "true",
	options = {}
}
ris_armor_quest_convotemplate:addScreen(quest_3_start);

quest_3_start_no = ConvoScreen:new {
	id = "quest_3_start_no",
	leftDialog = "@quest_armorsmith:quest_3_start_no", -- Fine, fine.  Practice up... 
	stopConversation = "true",
	options = {}
}		
ris_armor_quest_convotemplate:addScreen(quest_3_start_no);

quest_4_query = ConvoScreen:new {
	id = "quest_4_query",
	leftDialog = "@quest_armorsmith:quest_4_query", -- You return again.  OK, let's see it...
	stopConversation = "false",
	options = {
		{"@quest_armorsmith:yes_to_quest_4_query", "quest_4_complete"}, -- I have it right here
		{"@quest_armorsmith:no_to_quest_4_query", "quest_4_incomplete"} -- I haven't yet been able to craft it
	}
}
ris_armor_quest_convotemplate:addScreen(quest_4_query);

quest_4_complete = ConvoScreen:new {
	id = "quest_4_complete",
	leftDialog = "@quest_armorsmith:quest_4_complete", -- Let's see how you did ...
	stopConversation = "false",
	options = {
		{"@quest_armorsmith:yes_to_quest_5_start", "quest_5_start"}, -- Yes, I am ready to continue
		{"@quest_armorsmith:no_to_quest_5_start", "quest_5_start_no"} -- No. I'd rather practice...
	}
}
ris_armor_quest_convotemplate:addScreen(quest_4_complete);


quest_4_incomplete = ConvoScreen:new {
	id = "quest_4_incomplete",
	leftDialog = "@quest_armorsmith:quest_4_incomplete", -- Bah!  Then why are you here...
	stopConversation = "true",
	options = {}
}
ris_armor_quest_convotemplate:addScreen(quest_4_incomplete);

quest_5_start = ConvoScreen:new {
	id = "quest_5_start",
	leftDialog = "@quest_armorsmith:quest_5_start", -- Next I will teach you how to craft the... 
	stopConversation = "true",
	options = {}
}
ris_armor_quest_convotemplate:addScreen(quest_5_start);

quest_5_start_no = ConvoScreen:new {
	id = "quest_5_start_no",
	leftDialog = "@quest_armorsmith:quest_5_start_no", -- Fine, fine.  Practice up... 
	stopConversation = "true",
	options = {}
}		
ris_armor_quest_convotemplate:addScreen(quest_5_start_no);

quest_6_query = ConvoScreen:new {
	id = "quest_6_query",
	leftDialog = "@quest_armorsmith:quest_6_query", -- You return again.  OK, let's see it...
	stopConversation = "false",
	options = {
		{"@quest_armorsmith:yes_to_quest_6_query", "quest_6_complete"}, -- I have it right here
		{"@quest_armorsmith:no_to_quest_6_query", "quest_6_incomplete"} -- I haven't yet been able to craft it
	}
}
ris_armor_quest_convotemplate:addScreen(quest_6_query);

quest_6_complete = ConvoScreen:new {
	id = "quest_6_complete",
	leftDialog = "@quest_armorsmith:quest_6_complete", -- Let's see how you did ...
	stopConversation = "true",
	options = {}
}
ris_armor_quest_convotemplate:addScreen(quest_6_complete);


quest_6_incomplete = ConvoScreen:new {
	id = "quest_6_incomplete",
	leftDialog = "@quest_armorsmith:quest_6_incomplete", -- Bah!  Then why are you here...
	stopConversation = "true",
	options = {}
}
ris_armor_quest_convotemplate:addScreen(quest_6_incomplete);

armorsmith_quest = ConvoScreen:new {
	id = "armorsmith_quest",
	leftDialog = "@quest_armorsmith:armorsmith_quest", -- Bah!  Then why are you here...
	stopConversation = "true",
	options = {}
}
ris_armor_quest_convotemplate:addScreen(armorsmith_quest);

illegal_response = ConvoScreen:new {
	id = "illegal_response",
	leftDialog = "@quest_armorsmith:illegal_response", -- Bah!  Then why are you here...
	stopConversation = "true",
	options = {}
}
ris_armor_quest_convotemplate:addScreen(illegal_response);

addConversationTemplate("ris_armor_quest_convotemplate", ris_armor_quest_convotemplate);
