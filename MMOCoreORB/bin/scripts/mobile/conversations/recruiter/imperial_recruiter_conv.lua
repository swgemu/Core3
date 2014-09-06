imperialRecruiterConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "RecruiterConvoHandler",
	screens = {}
}

greet_hated = ConvoScreen:new {
	id = "greet_hated",
	leftDialog = "@conversation/faction_recruiter_imperial:s_306", -- I do not talk to terrorists and insurgents.
	stopConversation = "true",
	options = {
	}
}

imperialRecruiterConvoTemplate:addScreen(greet_hated);

greet_changing_status = ConvoScreen:new {
	id = "greet_changing_status",
	leftDialog = "@conversation/faction_recruiter_imperial:s_444", -- Your paperwork is currently going through the channels. Come back when it goes through. I can't do much to help you right now.
	stopConversation = "true",
	options = {
	}
}

imperialRecruiterConvoTemplate:addScreen(greet_changing_status);

greet_enemy = ConvoScreen:new {
	id = "greet_enemy",
	leftDialog = "@conversation/faction_recruiter_imperial:s_308", -- Leave my sight, scum. Insurrectionists like you should be punished.
	stopConversation = "true",
	options = {
	}
}

imperialRecruiterConvoTemplate:addScreen(greet_enemy);

member_covert_start = ConvoScreen:new {
	id = "greet_member_start_covert",
	leftDialog = "@conversation/faction_recruiter_imperial:s_310", -- Greetings, soldier. What may I do for you?
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_imperial:s_352", "confirm_go_overt"}, -- I would like to reevaluate my active military status.
		{"@conversation/faction_recruiter_imperial:s_374", "leave_time_covert"}, -- I would like to use my personal leave time.
		{"@conversation/faction_recruiter_imperial:s_386", "resign_covert"}, -- I believe it is time to end my tour of duty. I would like to resign.
	}
}

imperialRecruiterConvoTemplate:addScreen(member_covert_start);


member_overt_start = ConvoScreen:new {
	id = "greet_member_start_overt",
	leftDialog = "@conversation/faction_recruiter_imperial:s_310", -- Greetings, soldier. What may I do for you?
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_imperial:s_352", "confirm_go_covert"}, -- I would like to reevaluate my active military status.
		{"@conversation/faction_recruiter_imperial:s_374", "leave_time_overt"}, -- I would like to use my personal leave time.
		{"@conversation/faction_recruiter_imperial:s_386", "resign_overt"}, -- I believe it is time to end my tour of duty. I would like to resign.
	}
}

imperialRecruiterConvoTemplate:addScreen(member_overt_start);

neutral_start = ConvoScreen:new {
	id = "greet_neutral_start",
	leftDialog = "@conversation/faction_recruiter_imperial:s_414", -- Greetings, civilian. Would you be interested in joining the military?
	stopConversation = "false",
	options = {
	}
}

imperialRecruiterConvoTemplate:addScreen(neutral_start);

onleave_start = ConvoScreen:new {
	id = "greet_onleave_start",
	leftDialog = "@conversation/faction_recruiter_imperial:s_80", -- Hello, soldier. Are you ready to resume active duty?
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_imperial:s_294", "resume_duties"}, -- Yes, sir, I am ready to resume my duties.
	}
}

imperialRecruiterConvoTemplate:addScreen(onleave_start);

join_military = ConvoScreen:new {
	id = "join_military",
	leftDialog = "@conversation/faction_recruiter_imperial:s_432", -- Joining the military is a big commitment. Are you sure that you are ready? You realize that those upstart rebels will attack you on sight? Not the so-called 'special forces' but their main troops.
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_imperial:s_434", "accept_join"}, -- Absolutely. It would be a great honor to serve the Empire.
		{"@conversation/faction_recruiter_imperial:s_440", "think_more"}, -- Perhaps I should think about it a bit longer.
	}
}

imperialRecruiterConvoTemplate:addScreen(join_military);

neutral_need_more_points = ConvoScreen:new {
	id = "neutral_need_more_points",
	leftDialog = "@conversation/faction_recruiter_imperial:s_430", -- The Empire appreciates your enthusiasm, but we do not believe that you have the dedication necessary. Once you prove to us that you are committed to the Imperial doctrine, you may reapply then.
	stopConversation = "true",
	options = {
	}
}

imperialRecruiterConvoTemplate:addScreen(neutral_need_more_points);

accept_join = ConvoScreen:new {
	id = "accept_join",
	leftDialog = "@conversation/faction_recruiter_imperial:s_436", -- Welcome to the Imperial Military. I expect good things from you, recruit!
	stopConversation = "true",
	options = {
	}
}

imperialRecruiterConvoTemplate:addScreen(accept_join);

think_more = ConvoScreen:new {
	id = "think_more",
	leftDialog = "@conversation/faction_recruiter_imperial:s_442", -- Stop wasting my time. If you are serious, come back and talk to me.
	stopConversation = "true",
	options = {
	}
}

imperialRecruiterConvoTemplate:addScreen(think_more);

confirm_go_overt = ConvoScreen:new {
	id = "confirm_go_overt",
	leftDialog = "@conversation/faction_recruiter_imperial:s_364", -- Special Forces is recruiting. Would you like to submit your application? This means that you will be authorized to hunt the Rebel 'special forces', as they like to call themselves.
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_imperial:s_366", "accepted_go_overt"}, -- Yes, I want to join Special Forces, sir!
		{"@conversation/faction_recruiter_imperial:s_370", "greet_member_start_overt"} -- Maybe not, sir.
	}
}

imperialRecruiterConvoTemplate:addScreen(confirm_go_overt);

confirm_go_covert = ConvoScreen:new {
	id = "confirm_go_covert",
	leftDialog = "@conversation/faction_recruiter_imperial:s_354", -- You are currently enrolled in Special Forces. Would you like to request a reassignment? I can change your status to combatant, which means that the rebel 'special forces' riffraff will not concern themselves with you.
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_imperial:s_356", "accepted_go_covert"}, -- Unfortunately yes, sir. I am no longer interested in Special Forces.
		{"@conversation/faction_recruiter_imperial:s_360", "stay_special_forces"} -- I have reconsidered, for the glory of the Empire!
	}
}

imperialRecruiterConvoTemplate:addScreen(confirm_go_covert);

stay_special_forces = ConvoScreen:new {
	id = "stay_special_forces",
	leftDialog = "@conversation/faction_recruiter_imperial:s_362", -- I find your dedication admirable. You will go far in the Empire. Is there something else you need?
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_imperial:s_352", "confirm_go_covert"}, -- I would like to reevaluate my active military status.
		{"@conversation/faction_recruiter_imperial:s_374", "leave_time_overt"}, -- I would like to use my personal leave time.
		{"@conversation/faction_recruiter_imperial:s_386", "resign_overt"}, -- I believe it is time to end my tour of duty. I would like to resign.
	}
}

imperialRecruiterConvoTemplate:addScreen(stay_special_forces);

accepted_go_overt = ConvoScreen:new {
	id = "accepted_go_overt",
	leftDialog = "@conversation/faction_recruiter_imperial:s_368", -- Very good. I'll fast-track this application and you will be active in 30 seconds.
	stopConversation = "true",
	options = {
	}
}

imperialRecruiterConvoTemplate:addScreen(accepted_go_overt);

accepted_go_covert = ConvoScreen:new {
	id = "accepted_go_covert",
	leftDialog = "@conversation/faction_recruiter_imperial:s_358", -- Give me a moment to change your status and alert your superior. This process will take approximately 5 minutes.
	stopConversation = "true",
	options = {
	}
}

imperialRecruiterConvoTemplate:addScreen(accepted_go_covert);

leave_time_covert = ConvoScreen:new {
	id = "leave_time_covert",
	leftDialog = "@conversation/faction_recruiter_imperial:s_376", -- Are you certain that this is what you want to do? You may be missing out on some important battles. Going on leave means that you will not be recognized as a member of the Imperial military and will be ignored by the Rebel Alliance.
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_imperial:s_378", "accepted_go_on_leave"}, -- I am certain.
		{"@conversation/faction_recruiter_imperial:s_382", "stay_covert"} -- I will stay active. I know that the war effort needs me.
	}
}

imperialRecruiterConvoTemplate:addScreen(leave_time_covert);

stay_covert = ConvoScreen:new {
	id = "stay_covert",
	leftDialog = "@conversation/faction_recruiter_imperial:s_384", -- Your sense of duty is admirable. Long live the Emperor!
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_imperial:s_352", "confirm_go_overt"}, -- I would like to reevaluate my active military status.
		{"@conversation/faction_recruiter_imperial:s_374", "leave_time_covert"}, -- I would like to use my personal leave time.
		{"@conversation/faction_recruiter_imperial:s_386", "resign_covert"}, -- I believe it is time to end my tour of duty. I would like to resign.
	}
}

imperialRecruiterConvoTemplate:addScreen(stay_covert);

leave_time_overt = ConvoScreen:new {
	id = "leave_time_overt",
	leftDialog = "@conversation/faction_recruiter_imperial:s_376", -- Are you certain that this is what you want to do? You may be missing out on some important battles. Going on leave means that you will not be recognized as a member of the Imperial military and will be ignored by the Rebel Alliance.
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_imperial:s_378", "accepted_go_on_leave"}, -- I am certain.
		{"@conversation/faction_recruiter_imperial:s_382", "stay_overt"} -- I will stay active. I know that the war effort needs me.
	}
}

imperialRecruiterConvoTemplate:addScreen(leave_time_overt);

stay_overt = ConvoScreen:new {
	id = "stay_overt",
	leftDialog = "@conversation/faction_recruiter_imperial:s_384", -- Your sense of duty is admirable. Long live the Emperor!
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_imperial:s_352", "confirm_go_covert"}, -- I would like to reevaluate my active military status.
		{"@conversation/faction_recruiter_imperial:s_374", "leave_time_covert"}, -- I would like to use my personal leave time.
		{"@conversation/faction_recruiter_imperial:s_386", "resign_covert"}, -- I believe it is time to end my tour of duty. I would like to resign.
	}
}

imperialRecruiterConvoTemplate:addScreen(stay_overt);

accepted_go_on_leave = ConvoScreen:new {
	id = "accepted_go_on_leave",
	leftDialog = "@conversation/faction_recruiter_imperial:s_380", -- I need to process your paperwork. You will officially be on leave in 5 minutes.
	stopConversation = "true",
	options = {
	}
}

imperialRecruiterConvoTemplate:addScreen(accepted_go_on_leave);

leave_resign_covert = ConvoScreen:new {
	id = "resign_covert",
	leftDialog = "@conversation/faction_recruiter_imperial:s_388", -- I beg your pardon? You would leave the greatest opportunity of your life? You must be mad...or a traitor.
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_imperial:s_390", "accepted_resign"}, -- I am no traitor. I would just like to leave the military.
		{"@conversation/faction_recruiter_imperial:s_394", "dont_resign_covert"} -- No no, I was only kidding. I'm a loyal member of the military.
	}
}

imperialRecruiterConvoTemplate:addScreen(leave_resign_covert);

dont_resign_covert = ConvoScreen:new {
	id = "dont_resign_covert",
	leftDialog = "@conversation/faction_recruiter_imperial:s_396", -- That type of humor is unbecoming of an officer. I'll thank you to not engage in it again. You will remain in the military.
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_imperial:s_352", "confirm_go_overt"}, -- I would like to reevaluate my active military status.
		{"@conversation/faction_recruiter_imperial:s_374", "leave_time_covert"}, -- I would like to use my personal leave time.
		{"@conversation/faction_recruiter_imperial:s_386", "resign_covert"}, -- I believe it is time to end my tour of duty. I would like to resign.
	}
}

imperialRecruiterConvoTemplate:addScreen(dont_resign_covert);

leave_resign_overt = ConvoScreen:new {
	id = "resign_overt",
	leftDialog = "@conversation/faction_recruiter_imperial:s_388", -- I beg your pardon? You would leave the greatest opportunity of your life? You must be mad...or a traitor.
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_imperial:s_390", "accepted_resign"}, -- I am no traitor. I would just like to leave the military.
		{"@conversation/faction_recruiter_imperial:s_394", "dont_resign_overt"} -- No no, I was only kidding. I'm a loyal member of the military.
	}
}

imperialRecruiterConvoTemplate:addScreen(leave_resign_overt);

dont_resign_overt = ConvoScreen:new {
	id = "dont_resign_overt",
	leftDialog = "@conversation/faction_recruiter_imperial:s_396", -- That type of humor is unbecoming of an officer. I'll thank you to not engage in it again. You will remain in the military.
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_imperial:s_352", "confirm_go_covert"}, -- I would like to reevaluate my active military status.
		{"@conversation/faction_recruiter_imperial:s_374", "leave_time_covert"}, -- I would like to use my personal leave time.
		{"@conversation/faction_recruiter_imperial:s_386", "resign_covert"}, -- I believe it is time to end my tour of duty. I would like to resign.
	}
}

imperialRecruiterConvoTemplate:addScreen(dont_resign_overt);

accepted_resign = ConvoScreen:new {
	id = "accepted_resign",
	leftDialog = "@conversation/faction_recruiter_imperial:s_392", -- So be it. I'll put the paperwork through. We will watch you closely to make sure that you don't cross any lines, citizen.
	stopConversation = "true",
	options = {
	}
}

imperialRecruiterConvoTemplate:addScreen(accepted_resign);

resume_duties = ConvoScreen:new {
	id = "resume_duties",
	leftDialog = "@conversation/faction_recruiter_imperial:s_296", -- Good for you! Before I start the paperwork, though, I want to make sure that you are serious about returning to active duty. If you run into most rebels, they will attack you on sight. Are you returning to active duty?
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_imperial:s_298", "accepted_resume_duties"}, -- Yes, sir!
		{"@conversation/faction_recruiter_imperial:s_302", "stay_on_leave"} -- Excuse me, sir, I misspoke. I need a few more days of leave.
	}
}

imperialRecruiterConvoTemplate:addScreen(resume_duties);

stay_on_leave = ConvoScreen:new {
	id = "stay_on_leave",
	leftDialog = "@conversation/faction_recruiter_imperial:s_304", -- Don't waste my time. Come back to duty when you are serious about your responsibilities.
	stopConversation = "true",
	options = {
	}
}

imperialRecruiterConvoTemplate:addScreen(stay_on_leave);

accepted_resume_duties = ConvoScreen:new {
	id = "accepted_resume_duties",
	leftDialog = "@conversation/faction_recruiter_imperial:s_300", -- It will take the system about 30 seconds to process your status. After that, you are good to go.
	stopConversation = "true",
	options = {
	}
}

imperialRecruiterConvoTemplate:addScreen(accepted_resume_duties);

confirm_promotion = ConvoScreen:new {
	id = "confirm_promotion",
	leftDialog = "@conversation/faction_recruiter_imperial:s_314", -- Ah yes. According to your record, I am authorized to promote you to %TO.
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_imperial:s_93", "accepted_promotion"}, -- I would like that promotion, sir.
		{"@conversation/faction_recruiter_imperial:s_320", "declined_promotion"}
	}
}

imperialRecruiterConvoTemplate:addScreen(confirm_promotion);

accepted_promotion = ConvoScreen:new {
	id = "accepted_promotion",
	leftDialog = "@conversation/faction_recruiter_imperial:s_318", -- Congratulations and good luck with your new duties. Make us proud!
	stopConversation = "true",
	options = {
	}
}

imperialRecruiterConvoTemplate:addScreen(accepted_promotion);

declined_promotion = ConvoScreen:new {
	id = "declined_promotion",
	leftDialog = "@conversation/faction_recruiter_imperial:s_322", -- Afraid of a little more work? I'm disappointed, but it is your choice.
	stopConversation = "true",
	options = {
	}
}

imperialRecruiterConvoTemplate:addScreen(declined_promotion);

not_enough_points = ConvoScreen:new {
	id = "not_enough_points",
	leftDialog = "@faction_recruiter:not_enough_for_promotion", -- You do not have enough faction standing to spend. You must maintain at least %DI to remain part of the %TO faction.
	stopConversation = "true",
	options = {
	}
}

imperialRecruiterConvoTemplate:addScreen(not_enough_points);

confirm_bribe = ConvoScreen:new {
	id = "confirm_bribe",
	leftDialog = "@conversation/faction_recruiter_imperial:s_400", -- What kind of trade are you talking about? I may be amenable to gifts of friendship.
	stopConversation = "false",
	options = {
		{"@conversation/faction_recruiter_imperial:s_402", "accepted_bribe_20k"} -- How about a 20000 credit gift of friendship?
	}
}

imperialRecruiterConvoTemplate:addScreen(confirm_bribe);

accepted_bribe_20k = ConvoScreen:new {
	id = "accepted_bribe_20k",
	leftDialog = "@conversation/faction_recruiter_imperial:s_404", -- An acceptable offer once I check to make sure that it is a genuine gift and not an empty box.
	stopConversation = "true",
	options = {
	}
}

imperialRecruiterConvoTemplate:addScreen(accepted_bribe_20k);

accepted_bribe_100k = ConvoScreen:new {
	id = "accepted_bribe_100k",
	leftDialog = "@conversation/faction_recruiter_imperial:s_408", -- Friendship indeed. Let me make sure that this transaction is genuine.
	stopConversation = "true",
	options = {
	}
}

imperialRecruiterConvoTemplate:addScreen(accepted_bribe_100k);

faction_purchase = ConvoScreen:new {
	id = "faction_purchase",
	leftDialog = "@conversation/faction_recruiter_imperial:s_326",  -- What are you looking for?
	stopConversation = "false",
	options = {
		{ "@conversation/faction_recruiter_imperial:s_328", "fp_installations" }, -- I need a base of operations.
		{ "@conversation/faction_recruiter_imperial:s_332", "fp_uniforms"}, -- I need a new uniform.
		{ "@conversation/faction_recruiter_imperial:s_336", "fp_weapons_armor" }, -- I need personal protection and armament.
		--{ "@conversation/faction_recruiter_imperial:s_340", "fp_schematics" }, -- I want to see what schematics you have.
		{ "@conversation/faction_recruiter_imperial:s_344", "fp_furniture"}, -- Furniture. I am improving my quality of my life.
		{ "@conversation/faction_recruiter_imperial:s_348", "fp_hirelings" }, -- I would like to requisition additional troops.
	},
}

imperialRecruiterConvoTemplate:addScreen(faction_purchase);

fp_uniforms = ConvoScreen:new {
	id = "fp_uniforms",
	leftDialog = "@conversation/faction_recruiter_imperial:s_334", -- I will show you our selection. Wear the uniform proudly.
	stopConversation = "true",
	options = {	},
}
imperialRecruiterConvoTemplate:addScreen(fp_uniforms);

fp_furniture = ConvoScreen:new {
	id = "fp_furniture",
	leftDialog = "@conversation/faction_recruiter_imperial:s_346", -- Submit your purchase order and I will get right on it.
	stopConversation = "true",
	options = {	},
}
imperialRecruiterConvoTemplate:addScreen(fp_furniture);

fp_weapons_armor = ConvoScreen:new {
	id = "fp_weapons_armor",
	leftDialog = "@conversation/faction_recruiter_imperial:s_338", -- Always a good choice. I have a new shipment to look through.
	stopConversation = "true",
	options = {},
}
imperialRecruiterConvoTemplate:addScreen(fp_weapons_armor);

fp_installations = ConvoScreen:new {
	id = "fp_installations",
	leftDialog = "@conversation/faction_recruiter_imperial:s_330", -- Very well. I will show you what is available.
	stopConversation = "true",
	options = {},
}
imperialRecruiterConvoTemplate:addScreen(fp_installations);

fp_schematics = ConvoScreen:new {
	id = "fp_schematics",
	leftDialog = "@conversation/faction_recruiter_imperial:s_342", -- Review this list. Quite a few are available.
	stopConversation = "true",
	options = {},
}
imperialRecruiterConvoTemplate:addScreen(fp_schematics);

fp_hirelings = ConvoScreen:new {
	id = "fp_hirelings",
	leftDialog = "@conversation/faction_recruiter_imperial:s_350", -- I believe that can be arranged. We have some spare units in maneuvers. Let me show you what you can requisition.
	stopConversation = "true",
	options = {},

}
imperialRecruiterConvoTemplate:addScreen(fp_hirelings);

addConversationTemplate("imperialRecruiterConvoTemplate", imperialRecruiterConvoTemplate);