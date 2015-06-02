tutorialScaredSoldierConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "tutorialScaredSoldierConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_4_start", -- Y-you can't go IN there. He cut them to pieces! He's crazy...!
	stopConversation = "false",
	options = {
		{ "@newbie_tutorial/newbie_convo:convo_4_reply_1", "check_for_survivors" }, -- Calm down, I'm sure that everything will be under control soon.
		{ "@newbie_tutorial/newbie_convo:convo_4_reply_2", "past_him" }, -- So how do I get out of here?
	}
}
tutorialScaredSoldierConvoTemplate:addScreen(intro);

check_for_survivors = ConvoScreen:new {
	id = "check_for_survivors",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_4_explain_1", -- Uh huh. Look, y-you look pretty capable. C-could you take a peek and see if there are any survivors in the hallway?
	stopConversation = "false",
	options = {
		{ "@newbie_tutorial/newbie_convo:convo_4_reply_3", "standing_guard" }, -- Why don't you go?
		{ "@newbie_tutorial/newbie_convo:convo_4_reply_4", "need_weapon" }, -- Sure, I'll check for survivors.
	}
}
tutorialScaredSoldierConvoTemplate:addScreen(check_for_survivors);

standing_guard = ConvoScreen:new {
	id = "standing_guard",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_4_explain_3", -- I, uh, need to stand guard. In case reinforcements come.
	stopConversation = "true",
	options = {}
}
tutorialScaredSoldierConvoTemplate:addScreen(standing_guard);

need_weapon = ConvoScreen:new {
	id = "need_weapon",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_4_weapon_1", -- Wait, you'll need a weapon. Uh, this is against regs, but... look, just don't tell anyone. Here.
	stopConversation = "false",
	options = {
		{ "@newbie_tutorial/newbie_convo:convo_4_reply_7", "sure_whatever" }, -- Thank you.
	}
}
tutorialScaredSoldierConvoTemplate:addScreen(need_weapon);

sure_whatever = ConvoScreen:new {
	id = "sure_whatever",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_4_end", -- Sure, whatever. Look, I think I'll stand guard from the other side of the room, Ok? And whatever you do, don't get this maniac angry!
	stopConversation = "true",
	options = {}
}
tutorialScaredSoldierConvoTemplate:addScreen(sure_whatever);

past_him = ConvoScreen:new {
	id = "past_him",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_4_explain_2", -- The only way through is here. Past... him.
	stopConversation = "false",
	options = {
		{ "@newbie_tutorial/newbie_convo:convo_4_reply_5", "need_weapon" }, -- Then I guess I have to go that way.
	}
}
tutorialScaredSoldierConvoTemplate:addScreen(past_him);

intro_repeat = ConvoScreen:new {
	id = "intro_repeat",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_4_repeat", -- What are you doing here? Get a move on. I'm, uh, still guarding here.
	stopConversation = "false",
	options = {}
}
tutorialScaredSoldierConvoTemplate:addScreen(intro_repeat);

addConversationTemplate("tutorialScaredSoldierConvoTemplate", tutorialScaredSoldierConvoTemplate);
