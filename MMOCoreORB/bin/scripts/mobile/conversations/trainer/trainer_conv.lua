function createTrainerConversationTemplate(templateName, typeOfTrainer)
	trainerConvoTemplate = ConvoTemplate:new {
		initialScreen = "",
		templateType = "Lua",
		luaClassHandler = "trainerConvHandler",
		screens = {}
	}

	trainerType = ConvoScreen:new {
		id = "trainerType",
		leftDialog = "trainerType", -- Storage for the type of trainer, so it can be pulled in the convo handler.
		stopConversation = "false",
		options = {
			{ "trainerType" , typeOfTrainer }
		}
	}
	trainerConvoTemplate:addScreen(trainerType);

	intro = ConvoScreen:new {
		id = "intro",
		leftDialog = "",
		stopConversation = "false",
		options = {}
	}
	trainerConvoTemplate:addScreen(intro);

	trainer_unknown = ConvoScreen:new {
		id = "trainer_unknown",
		leftDialog = "@skill_teacher:trainer_unknown",
		stopConversation = "true",
		options = {}
	}
	trainerConvoTemplate:addScreen(trainer_unknown);

	topped_out = ConvoScreen:new {
		id = "topped_out",
		leftDialog = "",
		stopConversation = "true",
		options = {}
	}
	trainerConvoTemplate:addScreen(topped_out);

	no_qualify = ConvoScreen:new {
		id = "no_qualify",
		leftDialog = "",
		stopConversation = "true",
		options = {}
	}
	trainerConvoTemplate:addScreen(no_qualify);

	msg2_1 = ConvoScreen:new {
		id = "msg2_1",
		leftDialog = "",
		stopConversation = "false",
		options = {}
	}
	trainerConvoTemplate:addScreen(msg2_1);

	msg2_2 = ConvoScreen:new {
		id = "msg2_2",
		leftDialog = "",
		stopConversation = "false",
		options = {}
	}
	trainerConvoTemplate:addScreen(msg2_2);

	learn = ConvoScreen:new {
		id = "learn",
		leftDialog = "",
		stopConversation = "false",
		options = {}
	}
	trainerConvoTemplate:addScreen(learn);

	confirm_learn = ConvoScreen:new {
		id = "confirm_learn",
		leftDialog = "",
		stopConversation = "false",
		options = {}
	}
	trainerConvoTemplate:addScreen(confirm_learn);

	cancel_learn = ConvoScreen:new {
		id = "cancel_learn",
		leftDialog = "",
		stopConversation = "false",
		options = {
			{"@skill_teacher:opt1_1", "msg2_1"}, -- I'm interested in learning a skill.
			{"@skill_teacher:opt1_2", "msg2_2"} -- What skills will I be able to learn next?
		}
	}
	trainerConvoTemplate:addScreen(cancel_learn);

	info = ConvoScreen:new {
		id = "info",
		leftDialog = "",
		stopConversation = "false",
		options = {}
	}
	trainerConvoTemplate:addScreen(info);

	nsf_skill_points = ConvoScreen:new {
		id = "nsf_skill_points",
		leftDialog = "",
		stopConversation = "false",
		options = {}
	}
	trainerConvoTemplate:addScreen(nsf_skill_points);

	addConversationTemplate(templateName, trainerConvoTemplate);
end

createTrainerConversationTemplate("artisanTrainerConvoTemplate", "trainer_artisan")
createTrainerConversationTemplate("brawlerTrainerConvoTemplate", "trainer_brawler")
createTrainerConversationTemplate("entertainerTrainerConvoTemplate", "trainer_entertainer")
createTrainerConversationTemplate("marksmanTrainerConvoTemplate", "trainer_marksman")
createTrainerConversationTemplate("medicTrainerConvoTemplate", "trainer_medic")
createTrainerConversationTemplate("scoutTrainerConvoTemplate", "trainer_scout")

createTrainerConversationTemplate("1hswordTrainerConvoTemplate", "trainer_1hsword")
createTrainerConversationTemplate("2hswordTrainerConvoTemplate", "trainer_2hsword")
createTrainerConversationTemplate("architectTrainerConvoTemplate", "trainer_architect")
createTrainerConversationTemplate("armorsmithTrainerConvoTemplate", "trainer_armorsmith")
createTrainerConversationTemplate("bioengineerTrainerConvoTemplate", "trainer_bioengineer")
createTrainerConversationTemplate("bountyhunterTrainerConvoTemplate", "trainer_bountyhunter")
createTrainerConversationTemplate("carbineTrainerConvoTemplate", "trainer_carbine")
createTrainerConversationTemplate("chefTrainerConvoTemplate", "trainer_chef")
createTrainerConversationTemplate("combatmedicTrainerConvoTemplate", "trainer_combatmedic")
createTrainerConversationTemplate("commandoTrainerConvoTemplate", "trainer_commando")
createTrainerConversationTemplate("creaturehandlerTrainerConvoTemplate", "trainer_creaturehandler")
createTrainerConversationTemplate("dancerTrainerConvoTemplate", "trainer_dancer")
createTrainerConversationTemplate("doctorTrainerConvoTemplate", "trainer_doctor")
createTrainerConversationTemplate("droidengineerTrainerConvoTemplate", "trainer_droidengineer")
createTrainerConversationTemplate("imagedesignerTrainerConvoTemplate", "trainer_imagedesigner")
createTrainerConversationTemplate("merchantTrainerConvoTemplate", "trainer_merchant")
createTrainerConversationTemplate("musicianTrainerConvoTemplate", "trainer_musician")
createTrainerConversationTemplate("pistolTrainerConvoTemplate", "trainer_pistol")
createTrainerConversationTemplate("polearmTrainerConvoTemplate", "trainer_polearm")
createTrainerConversationTemplate("politicianTrainerConvoTemplate", "trainer_politician")
createTrainerConversationTemplate("rangerTrainerConvoTemplate", "trainer_ranger")
createTrainerConversationTemplate("riflemanTrainerConvoTemplate", "trainer_rifleman")
createTrainerConversationTemplate("shipwrightTrainerConvoTemplate", "trainer_shipwright")
createTrainerConversationTemplate("smugglerTrainerConvoTemplate", "trainer_smuggler")
createTrainerConversationTemplate("squadleaderTrainerConvoTemplate", "trainer_squadleader")
createTrainerConversationTemplate("tailorTrainerConvoTemplate", "trainer_tailor")
createTrainerConversationTemplate("unarmedTrainerConvoTemplate", "trainer_unarmed")
createTrainerConversationTemplate("weaponsmithTrainerConvoTemplate", "trainer_weaponsmith")

createTrainerConversationTemplate("fsTrainerConvoTemplate", "trainer_fs")
createTrainerConversationTemplate("jediTrainerConvoTemplate", "trainer_jedi")
