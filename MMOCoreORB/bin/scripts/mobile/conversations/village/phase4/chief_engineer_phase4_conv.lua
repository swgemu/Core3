villageChiefEngineerPhase4ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "villageChiefEngineerPhase4ConvoHandler",
	screens = {}
}

intro_not_eligible = ConvoScreen:new {
	id = "intro_not_eligible",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_e77051e7", -- "I don't have time to speak. Too much to do. Too much to do and not enough time. Too frantic. Arrgh."
	stopConversation = "true",
	options = {}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(intro_not_eligible);

intro_already_completed = ConvoScreen:new {
	id = "intro_already_completed",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_199cece6", -- "Ah, good to see you again. Have you had a chance to develop your mastery of crafting and repair? No wait... don't answer. I wish I had more time to speak, but I'm so very busy. I must get back to work."
	stopConversation = "true",
	options = {}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(intro_already_completed);

intro_wrong_phase = ConvoScreen:new {
	id = "intro_wrong_phase",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_acbab09c", -- "Those freaks are attacking. Everything is breaking. I can't believe I accepted this chief engineering post. What was I thinking. Ah well, there's nothing for it now but to muddle through."
	stopConversation = "true",
	options = {}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(intro_wrong_phase);

intro_quest1to5 = ConvoScreen:new {
	id = "intro_quest1to5",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_6c741657", -- "No, no, no... it'll have to wait. Sorry, sorry. Just trying to sort some things out. You're the one helping with the replacement core, right? If I can answer any questions, just ask."
	stopConversation = "false",
	options = {
	--{"@conversation/fs_phase4_chief_engineer:s_29622c26", "location_reminder"}, -- "Can you remind me where I need to go to find a replacement computer core?"
	--{"@conversation/fs_phase4_chief_engineer:s_c7baf80c", "build_device"}, -- "What do I do with this tracking device kit?"
	--{"@conversation/fs_phase4_chief_engineer:s_bab2829b", "go_to_droid"}, -- "How do I get tracking data for a fallen satellite?"
	--{"@conversation/fs_phase4_chief_engineer:s_7496bddd", "activate_device"}, -- "Do you know how this satellite tracking device works?"
	--{"@conversation/fs_phase4_chief_engineer:s_e3e36f42", "interface_needs_modified"}, -- "I have a replacement computer core for the village."
	--{"@conversation/fs_phase4_chief_engineer:s_a69082f1", "good_come_back"}, -- "No, I'm doing just fine. I'll leave you to your work."
	}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(intro_quest1to5);

build_device = ConvoScreen:new {
	id = "build_device",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_4bcdc402", -- "You need to collect or craft all of the required components and place them in the kit. Once you have all of the components, the kit's automated system will build the tracking device."
	stopConversation = "true",
	options = {}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(build_device);

go_to_droid = ConvoScreen:new {
	id = "go_to_droid",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_65f76975", -- "Go to any ticket droid at a starport. They have access to the database with information about fallen and abandoned satellites around the galaxy. You can purchase the rights to one of them from the droid."
	stopConversation = "true",
	options = {}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(go_to_droid);

activate_device = ConvoScreen:new {
	id = "activate_device",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_f9732f00", -- "Simply use the device's menu and choose to activate the tracking device. If you're on the wrong planet, it will tell you which planet the satellite is on. Once you're on the correct planet, the device can then pinpoint the exact location of the satellite."
	stopConversation = "true",
	options = {}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(activate_device);

interface_needs_modified = ConvoScreen:new {
	id = "interface_needs_modified",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_8ef5f872", -- "Ah yes. The core's current interface will need to be modified so that it will be compatible with computers here in the village. There should be a simple menu you can access on the core itself that will allow you to attempt the modification. Be careful though... if you fail too often you could short out the core and render it useless."
	stopConversation = "true",
	options = {}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(interface_needs_modified);

good_come_back = ConvoScreen:new {
	id = "good_come_back",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_29e5661", -- "Right. Good. Come back if you find a replacement. Or if you have any questions."
	stopConversation = "true",
	options = {}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(good_come_back);

location_reminder = ConvoScreen:new {
	id = "location_reminder",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_29622c26", -- "There's one in Keren on Naboo, on in Mos Entha on Tatooine, and one in Coronet on Corellia. I can upload a waypoint to their location if you'd like?"
	stopConversation = "false",
	options = {
		{"@conversation/fs_phase4_chief_engineer:s_f75c2f80", "waypoint_keren"}, -- "I'd like a waypoint to the gadget specialist in Keren."
		{"@conversation/fs_phase4_chief_engineer:s_59f634d7", "waypoint_coronet"}, -- "I'd like a waypoint to the gadget specialist in Coronet."
		{"@conversation/fs_phase4_chief_engineer:s_7f1e8a0c", "waypoint_mos_entha"}, -- "I'd like a waypoint to the gadget specialist in Mos Entha."
		{"@conversation/fs_phase4_chief_engineer:s_69b44245", "return_to_me"}, -- "No waypoint needed. I'll speak to them and get you a replacement computer core."
		{"@conversation/fs_phase4_chief_engineer:s_174ddced", "ill_manage"}, -- "I've changed my mind. You're on your own. Good luck... I guess."
	}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(location_reminder);

intro_quest7 = ConvoScreen:new {
	id = "intro_quest7",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_ec479e11", -- "Yes, hello. You've returned the rest of your reward?"
	stopConversation = "false",
	options = {
	--{"@conversation/fs_phase4_chief_engineer:s_6516bd5a", "no_space_for_reward"}, -- "Yes, I've made room and returned as you asked"
	--{"@conversation/fs_phase4_chief_engineer:s_6516bd5a", "present_statue"}, -- "Yes, I've made room and returned as you asked"
	}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(intro_quest7);

intro_quest6 = ConvoScreen:new {
	id = "intro_quest6",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_64391455", -- "It's you... good. Did you find a replacement computer core? Have you configured it so that it will be compatible with our computers?"
	stopConversation = "false",
	options = {
	--{"@conversation/fs_phase4_chief_engineer:s_ff872480", "get_you_started"}, -- "Success, the replacement computer core is ready!"
	--{"@conversation/fs_phase4_chief_engineer:s_ff872480", "dont_have_it"}, -- "Success, the replacement computer core is ready!"
	--{"@conversation/fs_phase4_chief_engineer:s_a69082f1", "please_hurry"}, -- "No, It's... um... not ready yet."
	}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(intro_quest6);

get_you_started = ConvoScreen:new {
	id = "get_you_started",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_860baf7e", -- "Yes! Thank you! This will work perfectly. In exchange for your services, I will happily get you started on the road to the Mastery of Crafting Repair."
	stopConversation = "false",
	options = {
	--{"@conversation/fs_phase4_chief_engineer:s_4136c2df", "no_space_for_reward"}, -- "Thank you very much."
	--{"@conversation/fs_phase4_chief_engineer:s_4136c2df", "present_statue"}, -- "Thank you very much."
	}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(get_you_started);

no_space_for_reward = ConvoScreen:new {
	id = "no_space_for_reward",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_bce29099", -- "We would also like to present you with this section of an Aurilian sculpture as further thanks for your help. But it seems that you do not have room in your inventory for it at the moment. Please make some room and then speak with me again."
	stopConversation = "true",
	options = {}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(no_space_for_reward);

present_statue = ConvoScreen:new {
	id = "present_statue",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_8b482724", -- "As further token of the village's thanks, we would like to present to you this section of an Aurilian sculpture."
	stopConversation = "true",
	options = {}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(present_statue);

dont_have_it = ConvoScreen:new {
	id = "dont_have_it",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_50191de0", -- "Hmmm... you don't appear to have the computer core with you. Please return when you have it."
	stopConversation = "true",
	options = {}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(dont_have_it);

please_hurry = ConvoScreen:new {
	id = "please_hurry",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_742ff942", -- "Oh, that's not good. Please hurry. Our backup is not going to last much longer."
	stopConversation = "true",
	options = {}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(please_hurry);

intro_continue = ConvoScreen:new {
	id = "intro_continue",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_5062e892", -- "You worked with the last chief engineer, right? But weren't able to find a replacement in time. Would you like to try again? Continue from where you left off?"
	stopConversation = "false",
	options = {
		{"@conversation/fs_phase4_chief_engineer:s_ff872480", "excellent_continue"}, -- "Yes I would. Thank you for the second chance."
		{"@conversation/fs_phase4_chief_engineer:s_a69082f1", "thanks_for_coming"}, -- "No thanks. Not this time."
	}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(intro_continue);

excellent_continue = ConvoScreen:new {
	id = "excellent_continue",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_3031b4c9", -- "Excellent. Continue from where you left off. Come speak with me again if you have any questions."
	stopConversation = "true",
	options = {}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(excellent_continue);

thanks_for_coming = ConvoScreen:new {
	id = "thanks_for_coming",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_96e10fe0", -- "I see. Thank you for coming by. If you'll excuse me, I've much to do."
	stopConversation = "true",
	options = {}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(thanks_for_coming);

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_cbc96768", -- "Arrrgh! It's too much! I'm only one person... and new to this position no less. How can I be expected to keep the village defenses working while we're under attack? It's too much!!"
	stopConversation = "false",
	options = {
	--{"@conversation/fs_phase4_chief_engineer:s_59f5cee6", "very_kind"}, -- "Is there anything I can do to help?"
	--{"@conversation/fs_phase4_chief_engineer:s_59f5cee6", "yes_there_is"}, -- "Is there anything I can do to help?"
	--{"@conversation/fs_phase4_chief_engineer:s_5542b04b", "quite_alright"}, -- "Oh, my apologies. I'll let you get back to work."
	}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(intro);

quite_alright = ConvoScreen:new {
	id = "quite_alright",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_caa53683", -- "That's quite alright. Okay, first I need to... something. Maybe I'll start... no no. Obviously. Well. Something."
	stopConversation = "true",
	options = {}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(quite_alright);

very_kind = ConvoScreen:new {
	id = "very_kind",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_9caa26f9", -- "Thank you, that's very kind. Normally I would gladly accept your help, but at the moment I'm already juggling more people and problems than I can handle. Please come back after some time has passed and I'll see if I can phase you in."
	stopConversation = "true",
	options = {}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(very_kind);

yes_there_is = ConvoScreen:new {
	id = "yes_there_is",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_1a960799", -- "Yes. Yes there is. During the first of the recent attacks on the village, our primary computer was damaged, and the computer core has become unstable. A new core must be found as soon as possible. Thanks to all the damage being caused by the attacks, I am unable go find a replacement, but you could go get one in my place."
	stopConversation = "false",
	options = {
		{"@conversation/fs_phase4_chief_engineer:s_61fa9d29", "know_some_people"}, -- "Hmm... what would that mean I'd have to do?"
	}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(yes_there_is);

know_some_people = ConvoScreen:new {
	id = "know_some_people",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_bf01c6a4", -- "Well, I know some people who might be able to help you find one. You'd need to contact one of them and see what they have to say. From there, both they and I can advise you."
	stopConversation = "false",
	options = {
		{"@conversation/fs_phase4_chief_engineer:s_8e1d9e8a", "you_should_know"}, -- "I'll do it. Where can I find a replacement computer core?"
		{"@conversation/fs_phase4_chief_engineer:s_94925b50", "wasted_enough_time"}, -- "Eh, no thanks. Sounds boring. I'll pass."
	}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(know_some_people);

wasted_enough_time = ConvoScreen:new {
	id = "wasted_enough_time",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_3196d2e0", -- "Right. Well then I've wasted enough time talking. There's much for me to attend to."
	stopConversation = "true",
	options = {}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(wasted_enough_time);

you_should_know = ConvoScreen:new {
	id = "you_should_know",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_e0f6c467", -- "Ah enthusiasm... I like that. Before getting started, you should know that in this village, you cannot work with more than one villager. So while you're working with me, you can't work with any other villagers."
	stopConversation = "false",
	options = {
		{"@conversation/fs_phase4_chief_engineer:s_7f1492c", "recommend_specialist"}, -- "That's not a problem. How do I get started on this?"
		{"@conversation/fs_phase4_chief_engineer:s_85cf8e18", "fair_enough"}, -- "Oh. Hmmm... maybe I should think about this a bit more."
	}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(you_should_know);

fair_enough = ConvoScreen:new {
	id = "fair_enough",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_dc34bd9c", -- "Fair enough. If you decide you'll be able to help, I'll be here. Now let's see... which emergency was I working on..."
	stopConversation = "true",
	options = {}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(fair_enough);

recommend_specialist = ConvoScreen:new {
	id = "recommend_specialist",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_b69a10cf", -- "I'd recommend speaking to a gadget specialist. I've done business with a gadget specialist in the past and know where you can find one. Actually, I know of three of them. One in Keren on Naboo, on in Mos Entha on Tatooine, and one in Coronet on Corellia. I can upload a waypoint to their location if you'd like?"
	stopConversation = "false",
	options = {
		{"@conversation/fs_phase4_chief_engineer:s_f75c2f80", "waypoint_keren"}, -- "I'd like a waypoint to the gadget specialist in Keren."
		{"@conversation/fs_phase4_chief_engineer:s_59f634d7", "waypoint_coronet"}, -- "I'd like a waypoint to the gadget specialist in Coronet."
		{"@conversation/fs_phase4_chief_engineer:s_7f1e8a0c", "waypoint_mos_entha"}, -- "I'd like a waypoint to the gadget specialist in Mos Entha."
		{"@conversation/fs_phase4_chief_engineer:s_69b44245", "return_to_me"}, -- "No waypoint needed. I'll speak to them and get you a replacement computer core."
		{"@conversation/fs_phase4_chief_engineer:s_174ddced", "ill_manage"}, -- "I've changed my mind. You're on your own. Good luck... I guess."
	}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(recommend_specialist);

waypoint_keren = ConvoScreen:new {
	id = "waypoint_keren",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_dd8b435", -- "My pleasure. Ask if they can supply a replacement core. Then return here and bring it to me. Thanks and may the Force guide you."
	stopConversation = "true",
	options = {}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(waypoint_keren);

waypoint_coronet = ConvoScreen:new {
	id = "waypoint_coronet",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_dd8b435", -- "My pleasure. Ask if they can supply a replacement core. Then return here and bring it to me. Thanks and may the Force guide you."
	stopConversation = "true",
	options = {}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(waypoint_coronet);

waypoint_mos_entha = ConvoScreen:new {
	id = "waypoint_mos_entha",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_dd8b435", -- "My pleasure. Ask if they can supply a replacement core. Then return here and bring it to me. Thanks and may the Force guide you."
	stopConversation = "true",
	options = {}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(waypoint_mos_entha);

return_to_me = ConvoScreen:new {
	id = "return_to_me",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_d38355d4", -- "Excellent. And may the Force guide you. Return to me once you've obtained the replacement core."
	stopConversation = "true",
	options = {}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(return_to_me);

ill_manage = ConvoScreen:new {
	id = "ill_manage",
	leftDialog = "@conversation/fs_phase4_chief_engineer:s_9c2a9f48", -- "Oh. Okay. Thank you. I think. I suppose I'll manage, Somehow."
	stopConversation = "true",
	options = {}
}
villageChiefEngineerPhase4ConvoTemplate:addScreen(ill_manage);

addConversationTemplate("villageChiefEngineerPhase4ConvoTemplate", villageChiefEngineerPhase4ConvoTemplate);
