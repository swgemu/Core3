corvetteBledsoeConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "corvetteRescueConvoHandler",
	screens = {}
}

convo_start = ConvoScreen:new {
	id = "convo_start",
	leftDialog = "@conversation/corvette_bledsoe_imperial_rescue_target:s_5b99b059", --Finally, took you long enough! For a while there I actually thought these stinking traitors would take me to where ever they were heading. Did you leave any of them alive?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bledsoe_imperial_rescue_target:s_7dbf5a70","taken_care_of"},-- No, they are all taken care of.
		{"@conversation/corvette_bledsoe_imperial_rescue_target:s_5128536b","still_around"} --There might be some around still.
	}
}
corvetteBledsoeConvoTemplate:addScreen(convo_start);

taken_care_of = ConvoScreen:new {
	id = "taken_care_of",
	leftDialog = "@conversation/corvette_bledsoe_imperial_rescue_target:s_715b64d7", --Good work soldier. I'd hate to see all my ground-breaking work fall in to the hands of these Rebel scum. I will make my way to one of the escape pods now. I will also make sure to let your commanding officer know how well you took care of the vermin on this ship.
	stopConversation = "true",
	options = {	}
}
corvetteBledsoeConvoTemplate:addScreen(taken_care_of);

still_around = ConvoScreen:new {
	id = "still_around",
	leftDialog = "@conversation/corvette_bledsoe_imperial_rescue_target:s_855a26e7", --Well you have to take care of them then soldier! They are not worth more than a womp rat but twice as annoying. Cleanse this ship of their filthy presence!
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bledsoe_imperial_rescue_target:s_da7cd509","yes_sir"},--Yes...Sir.
		{"@conversation/corvette_bledsoe_imperial_rescue_target:s_8bc64ef3","not_my_thing"} --Genocide is not my thing doctor. I think our work here is done.
	}
}
corvetteBledsoeConvoTemplate:addScreen(still_around);

yes_sir = ConvoScreen:new {
	id = "yes_sir",
	leftDialog = "@conversation/corvette_bledsoe_imperial_rescue_target:s_2a121860", --Good! I will make my way to the escape pods. Great work here soldier, I will make sure your commanding officer hears about it.
	stopConversation = "true",
	options = {}
}
corvetteBledsoeConvoTemplate:addScreen(yes_sir);


not_my_thing = ConvoScreen:new {
	id = "not_my_thing",
	leftDialog = "@conversation/corvette_bledsoe_imperial_rescue_target:s_86216dc2", --What?! They're vermin! If you leave any of them alive, they will breed and spread like the rodents they are. I will make sure to report your insolence to your commanding officer! Now where were those escape pods..
	stopConversation = "true",
	options = {}
}
corvetteBledsoeConvoTemplate:addScreen(not_my_thing);

alreadyRescued = ConvoScreen:new {
	id = "alreadyRescued",
	leftDialog = "@conversation/corvette_bledsoe_imperial_rescue_target:s_339b706e", --Pardon me, and don't think me rude... afterall I am dutifully thankful for your part in my escape... but I should think it necessary to effect the completion of that escape rather than stand around talking like new recruits at an Imperial gala.
	stopConversation = "true",
	options = {}
}
corvetteBledsoeConvoTemplate:addScreen(alreadyRescued);

addConversationTemplate("corvetteBledsoeConvoTemplate", corvetteBledsoeConvoTemplate);
