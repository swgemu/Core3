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

	learn_1 = ConvoScreen:new {
		id = "learn_1",
		leftDialog = "",
		stopConversation = "false",
		options = {}
	}
	trainerConvoTemplate:addScreen(learn_1);

	learn_2 = ConvoScreen:new {
		id = "learn_2",
		leftDialog = "",
		stopConversation = "false",
		options = {}
	}
	trainerConvoTemplate:addScreen(learn_2);

	learn_3 = ConvoScreen:new {
		id = "learn_3",
		leftDialog = "",
		stopConversation = "false",
		options = {}
	}
	trainerConvoTemplate:addScreen(learn_3);

	learn_4 = ConvoScreen:new {
		id = "learn_4",
		leftDialog = "",
		stopConversation = "false",
		options = {}
	}
	trainerConvoTemplate:addScreen(learn_4);

	confirm_learn_1 = ConvoScreen:new {
		id = "confirm_learn_1",
		leftDialog = "",
		stopConversation = "false",
		options = {}
	}
	trainerConvoTemplate:addScreen(confirm_learn_1);

	confirm_learn_2 = ConvoScreen:new {
		id = "confirm_learn_2",
		leftDialog = "",
		stopConversation = "false",
		options = {}
	}
	trainerConvoTemplate:addScreen(confirm_learn_2);

	confirm_learn_3 = ConvoScreen:new {
		id = "confirm_learn_3",
		leftDialog = "",
		stopConversation = "false",
		options = {}
	}
	trainerConvoTemplate:addScreen(confirm_learn_3);

	confirm_learn_4 = ConvoScreen:new {
		id = "confirm_learn_4",
		leftDialog = "",
		stopConversation = "false",
		options = {}
	}
	trainerConvoTemplate:addScreen(confirm_learn_4);

	cancel_learn = ConvoScreen:new {
		id = "cancel_learn",
		leftDialog = "",
		stopConversation = "false",
		options = {}
	}
	trainerConvoTemplate:addScreen(cancel_learn);

	info_1 = ConvoScreen:new {
		id = "info_1",
		leftDialog = "",
		stopConversation = "false",
		options = {}
	}
	trainerConvoTemplate:addScreen(info_1);

	info_2 = ConvoScreen:new {
		id = "info_2",
		leftDialog = "",
		stopConversation = "false",
		options = {}
	}
	trainerConvoTemplate:addScreen(info_2);

	info_3 = ConvoScreen:new {
		id = "info_3",
		leftDialog = "",
		stopConversation = "false",
		options = {}
	}
	trainerConvoTemplate:addScreen(info_3);

	info_4 = ConvoScreen:new {
		id = "info_4",
		leftDialog = "",
		stopConversation = "false",
		options = {}
	}
	trainerConvoTemplate:addScreen(info_4);

	info_5 = ConvoScreen:new {
		id = "info_5",
		leftDialog = "",
		stopConversation = "false",
		options = {}
	}
	trainerConvoTemplate:addScreen(info_5);

	nsf_skill_points_1 = ConvoScreen:new {
		id = "nsf_skill_points_1",
		leftDialog = "",
		stopConversation = "false",
		options = {}
	}
	trainerConvoTemplate:addScreen(nsf_skill_points_1);

	nsf_skill_points_2 = ConvoScreen:new {
		id = "nsf_skill_points_2",
		leftDialog = "",
		stopConversation = "false",
		options = {}
	}
	trainerConvoTemplate:addScreen(nsf_skill_points_2);

	nsf_skill_points_3 = ConvoScreen:new {
		id = "nsf_skill_points_3",
		leftDialog = "",
		stopConversation = "false",
		options = {}
	}
	trainerConvoTemplate:addScreen(nsf_skill_points_3);

	nsf_skill_points_4 = ConvoScreen:new {
		id = "nsf_skill_points_4",
		leftDialog = "",
		stopConversation = "false",
		options = {}
	}
	trainerConvoTemplate:addScreen(nsf_skill_points_4);

	nsf_skill_points_4 = ConvoScreen:new {
		id = "nsf_skill_points_4",
		leftDialog = "",
		stopConversation = "false",
		options = {}
	}
	trainerConvoTemplate:addScreen(nsf_skill_points_4);

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
