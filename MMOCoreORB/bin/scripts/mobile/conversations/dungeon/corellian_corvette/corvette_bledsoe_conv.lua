corvetteBledsoeConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "corvetteBledsoeConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/corvette_bledsoe_imperial_rescue_target:s_5b99b059", -- Finally, took you long enough! For a while there I actually thought these stinking traitors would take me to where ever they were heading. Did you leave any of them alive?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bledsoe_imperial_rescue_target:s_7dbf5a70","good_work"}, -- No, they are all taken care of.
		{"@conversation/corvette_bledsoe_imperial_rescue_target:s_5128536b","cleanse_ship"}, -- There might be some around still.
	}
}
corvetteBledsoeConvoTemplate:addScreen(intro);

already_rescued = ConvoScreen:new {
	id = "already_rescued",
	leftDialog = "@conversation/corvette_bledsoe_imperial_rescue_target:s_339b706e", -- Pardon me, and don't think me rude... afterall I am dutifully thankful for your part in my escape... but I should think it necessary to effect the completion of that escape rather than stand around talking like new recruits at an Imperial gala.
	stopConversation = "true",
	options = { }
}
corvetteBledsoeConvoTemplate:addScreen(already_rescued);

good_work = ConvoScreen:new {
	id = "good_work",
	leftDialog = "@conversation/corvette_bledsoe_imperial_rescue_target:s_715b64d7", -- Good work soldier. I'd hate to see all my ground-breaking work fall in to the hands of these Rebel scum. I will make my way to one of the escape pods now. I will also make sure to let your commanding officer know how well you took care of the vermin on this ship.
	stopConversation = "true",
	options = {}
}
corvetteBledsoeConvoTemplate:addScreen(good_work);

cleanse_ship = ConvoScreen:new {
	id = "cleanse_ship",
	leftDialog = "@conversation/corvette_bledsoe_imperial_rescue_target:s_855a26e7", -- Well you have to take care of them then soldier! They are not worth more than a womp rat but twice as annoying. Cleanse this ship of their filthy presence!
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bledsoe_imperial_rescue_target:s_7dbf5a70","great_work"}, -- Yes...Sir.
		{"@conversation/corvette_bledsoe_imperial_rescue_target:s_8bc64ef3","breed_and_spread"}, -- Genocide is not my thing doctor. I think our work here is done.
	}
}
corvetteBledsoeConvoTemplate:addScreen(cleanse_ship);

great_work = ConvoScreen:new {
	id = "great_work",
	leftDialog = "@conversation/corvette_bledsoe_imperial_rescue_target:s_2a121860", -- Good! I will make my way to the escape pods. Great work here soldier, I will make sure your commanding officer hears about it.
	stopConversation = "true",
	options = {}
}
corvetteBledsoeConvoTemplate:addScreen(great_work);

breed_and_spread = ConvoScreen:new {
	id = "breed_and_spread",
	leftDialog = "@conversation/corvette_bledsoe_imperial_rescue_target:s_715b64d7", -- What?! They're vermin! If you leave any of them alive, they will breed and spread like the rodents they are. I will make sure to report your insolence to your commanding officer! Now where were those escape pods..
	stopConversation = "true",
	options = {}
}
corvetteBledsoeConvoTemplate:addScreen(breed_and_spread);

addConversationTemplate("corvetteBledsoeConvoTemplate", corvetteBledsoeConvoTemplate);
