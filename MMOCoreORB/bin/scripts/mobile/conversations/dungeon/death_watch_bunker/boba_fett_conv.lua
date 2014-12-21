bobaFettConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "deathWatchBobaFettConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/boba_fett:s_8e66f1ea", -- Another of Jabba's little toys... You may want to make yourself useful by checking something out when you get a chance. You're of no use wandering around the palace aimlessly. There's a rumor that Death Watch operatives can be found on Endor somewhere in the northwestern area of the planet.
	stopConversation = "false",
	options = {
		{"@conversation/boba_fett:s_ab11aabd", "formidable_opponent"}, -- Okay. Anything else you can tell me?
	}
}
bobaFettConvoTemplate:addScreen(intro);

formidable_opponent = ConvoScreen:new {
	id = "formidable_opponent",
	leftDialog = "@conversation/boba_fett:s_d586da5f", -- The Death Watch can be a formidable opponent and shouldn't be taken lightly. Be careful fighting against them.
	stopConversation = "false",
	options = {
		{"@conversation/boba_fett:s_f215b084", "mind_your_business"}, -- Sounds like you've dealt with them before.
		{"@conversation/boba_fett:s_783590a2", "experience_is_reward"}, -- Do I get a reward for completing this mission?
		{"@conversation/boba_fett:s_515da73f", "pass_on_job"},-- Can't somebody else do it?
	}
}
bobaFettConvoTemplate:addScreen(formidable_opponent);

mind_your_business = ConvoScreen:new {
	id = "mind_your_business",
	leftDialog = "@conversation/boba_fett:s_58de331a", -- Mind your business. The Hutt wants this Death Watch and their leader dead before they cut into his business. My informants tell me they're cutting a deal with Black Sun even as we speak.
	stopConversation = "false",
	options = {
		{"@conversation/boba_fett:s_4c801419", "dont_give_opinions"}, -- Are you sure that's all there is to it?
		{"@conversation/boba_fett:s_783590a2", "experience_is_reward"}, -- Do I get a reward for completing this mission?
		{"@conversation/boba_fett:s_515da73f", "pass_on_job"},-- Can't somebody else do it?
	}
}
bobaFettConvoTemplate:addScreen(mind_your_business);

dont_give_opinions = ConvoScreen:new {
	id = "dont_give_opinions",
	leftDialog = "@conversation/boba_fett:s_262c1b3f", -- I don't usually give my opinion to barves like you, but in this case I'll make an exception. All I have to say is, the Mandalorians are dead and nobody is bringin' them back. Now go.
	stopConversation = "true",
	options = {
	}
}
bobaFettConvoTemplate:addScreen(dont_give_opinions);

experience_is_reward = ConvoScreen:new {
	id = "experience_is_reward",
	leftDialog = "@conversation/boba_fett:s_f959107f", -- The experience itself will be its own reward. Don't come to me or the Hutt looking for a hand out, you're likely to end up on the wrong end of a blaster if you keep that up.
	stopConversation = "false",
	options = {
		{"@conversation/boba_fett:s_4c801419", "dont_give_opinions"}, -- Are you sure that's all there is to it?
		{"@conversation/boba_fett:s_515da73f", "pass_on_job"},-- Can't somebody else do it?
	}
}
bobaFettConvoTemplate:addScreen(experience_is_reward);

back_again = ConvoScreen:new {
	id = "back_again",
	leftDialog = "@conversation/boba_fett:s_3c8497c", -- You're back again? Didn't we already have this discussion?
	stopConversation = "false",
	options = {
		{"@conversation/boba_fett:s_1122d80a", "formidable_opponent"},-- Can you tell me again about the Death Watch?
		{"@conversation/boba_fett:s_515da73f", "pass_on_job"},-- Can't somebody else do it?
	}
}
bobaFettConvoTemplate:addScreen(back_again);

pass_on_job = ConvoScreen:new {
	id = "pass_on_job",
	leftDialog = "@conversation/boba_fett:s_6ad7d226", -- You won't make any friends around here by passing on what's sure to be a lucrative job like this.
	stopConversation = "true",
	options = {
	}
}
bobaFettConvoTemplate:addScreen(pass_on_job);

not_completed_jabbas = ConvoScreen:new {
	id = "not_completed_jabbas",
	leftDialog = "@conversation/boba_fett:s_4386e081", -- I've no time for the likes of you. I have more pressing matters to deal with.
	stopConversation = "true",
	options = {
	}
}
bobaFettConvoTemplate:addScreen(not_completed_jabbas);

addConversationTemplate("bobaFettConvoTemplate", bobaFettConvoTemplate);
