function createTrainerConversationTemplate(trainer, masterskill, templatename)
	trainer_convotemplate = ConvoTemplate:new {
		initialScreen = "convoscreentrainerinfo",
		templateType = "Trainer",
		screens = {}
	}

	trainer_convoscreentrainerinfo = ConvoScreen:new {
		id = "convoscreentrainerinfo",
		leftDialog = "@skill_teacher:" .. trainer, -- Storage for the trainer master skill.
		stopConversation = "false",
		options = { 
			{"masterskill", masterskill }
		}
	}
	trainer_convotemplate:addScreen(trainer_convoscreentrainerinfo);

	trainer_convoscreenstart = ConvoScreen:new {
		id = "convoscreenstart",
		leftDialog = "@skill_teacher:" .. trainer, -- Building, crafting, creating.  It's all in your hands.  How can I help move you along in this profession?
		stopConversation = "false",
		options = { 
			{"@skill_teacher:opt1_1", "convoscreentrainableskills"}, -- I'm interested in learning a skill.
			{"@skill_teacher:opt1_2", "convoscreennextskills"} -- What skills will I be able to learn next?
		}
	}
	trainer_convotemplate:addScreen(trainer_convoscreenstart);

	-- Screen coming with the optionlist of all currently learnable skills
	trainer_convoscreentrainableskills = ConvoScreen:new {
		id = "convoscreentrainableskills",
		leftDialog = "@skill_teacher:msg2_1", -- You may learn the following skills right now...
		stopConversation = "false",
		options = {
			{ "--skillholder--", "convoscreencanlearnskill" }, -- Place holder for a skill.
			{ "--skillholder--", "convoscreencanlearnskill" }, -- Place holder for a skill.
			{ "--skillholder--", "convoscreencanlearnskill" }, -- Place holder for a skill.
			{ "--skillholder--", "convoscreencanlearnskill" }, -- Place holder for a skill.
			{ "@skill_teacher:back", "convoscreenstart" } -- Place holder for go back.
		}
	}
	trainer_convotemplate:addScreen(trainer_convoscreentrainableskills);

	-- coming with the optionlist for all the skills you are able to learn next?
	trainer_convoscreennextskills = ConvoScreen:new {
		id = "convoscreennextskills",
		leftDialog = "@skill_teacher:msg2_2", -- Here are the skills I can teach you next, if you have gained enough experience...
		stopConversation = "false",
		options = {
			{ "--skillholder--", "convoscreenskillinfo" }, -- Place holder for a skill.
			{ "--skillholder--", "convoscreenskillinfo" }, -- Place holder for a skill.
			{ "--skillholder--", "convoscreenskillinfo" }, -- Place holder for a skill.
			{ "--skillholder--", "convoscreenskillinfo" }, -- Place holder for a skill.
			{ "@skill_teacher:back", "convoscreenstart" } -- Place holder for go back.
		}
	}
	trainer_convotemplate:addScreen(trainer_convoscreennextskills);

	-- after clicking on a learable skill
	trainer_convoscreencanlearnskill = ConvoScreen:new {
		id = "convoscreencanlearnskill",
		leftDialog = "@skill_teacher:prose_cost", --It will cost %DI credits to train in %TO. Would you like to continue?
		stopConversation = "false",
		options = {
			{"@skill_teacher:yes", "convoscreentrainskill"},
			{"@skill_teacher:no", "convoscreendonttrain"}
		}
	}
	trainer_convotemplate:addScreen(trainer_convoscreencanlearnskill);

	-- after clicking no when asked "Are you sure..."
	trainer_convoscreendonttrain = ConvoScreen:new {
		id = "convoscreendonttrain",
		leftDialog = "@skill_teacher:msg_no", --Too rich for ya? Well, maybe I can help you with something else?
		stopConversation = "false",
		options = {
			{"@skill_teacher:back", "convoscreenstart" }
		}
	}
	trainer_convotemplate:addScreen(trainer_convoscreendonttrain);

	-- after successfully training a skill and still having skills left to train (enogh xp already or not)
	trainer_convoscreentrainskill = ConvoScreen:new {
		id = "convoscreentrainskill",
		leftDialog = "@skill_teacher:msg3_2", -- You're an exceptionally bright student! Perhaps we shall work together again soon.
		stopConversation = "false",
		options = {
			{"@skill_teacher:back", "convoscreenstart" }
		}
	}
	trainer_convotemplate:addScreen(trainer_convoscreentrainskill);

	-- after successfully learning the last available skill from a trainer
	trainer_convoscreentrainedmaster = ConvoScreen:new {
		id = "convoscreentrainedmaster",
		leftDialog = "@skill_teacher:surpass_trainer", --WOW! You have learned everything I have to teach... I suppose that now it's time for you to find your own path. Farewell %TT.
		stopConversation = "true",
		options = { }
	}
	trainer_convotemplate:addScreen(trainer_convoscreentrainedmaster);

	-- after clicking a skill from the "What skills will I be able to learn next?" optionlist
	trainer_convoscreenskillinfo = ConvoScreen:new {
		id = "convoscreenskillinfo",
		leftDialog = "@skill_teacher:msg3_3", -- Let me give you some information about this skill...
		stopConversation = "false",
		options = { 
			{"@skill_teacher:back", "convoscreenstart" }
		}
	}
	trainer_convotemplate:addScreen(trainer_convoscreenskillinfo);

	-- after clicking "I'm interested in learning a skill." and not having enogh xp for any skill
	trainer_convoscreennotenoughxp = ConvoScreen:new {
		id = "convoscreennotenoughxp",
		leftDialog = "@skill_teacher:error_empty_category", -- Sorry, you aren't quite up to the point where I can teach you anything else.
		stopConversation = "false",
		options = { 
			{"@skill_teacher:back", "convoscreenstart" }
		}
	}
	trainer_convotemplate:addScreen(trainer_convoscreennotenoughxp);

	trainer_convoscreennotenoughskillpoints = ConvoScreen:new {
		id = "convoscreennotenoughskillpoints",
		leftDialog = "@skill_teacher:nsf_skill_pts", -- You must first make %DI skill points available before I can teach you %TO.
		stopConversation = "false",
		options = { 
			{"@skill_teacher:back", "convoscreenstart" }
		}
	}
	trainer_convotemplate:addScreen(trainer_convoscreennotenoughskillpoints);

	trainer_convoscreennotenoughcredits = ConvoScreen:new {
		id = "convoscreennotenoughcredits",
		leftDialog = "@skill_teacher:prose_nfs", -- You lack the %DI credits required for training in %TO.
		stopConversation = "false",
		options = { 
			{"@skill_teacher:back", "convoscreenstart" }
		}
	}
	trainer_convotemplate:addScreen(trainer_convoscreennotenoughcredits);

	trainer_convoscreennotenoughskillpoints = ConvoScreen:new {
		id = "convoscreennotenoughskillpoints",
		leftDialog = "@skill_teacher:no_skill_pts", -- How can I teach you when you do not have any available skill points.
		stopConversation = "false",
		options = { 
			{"@skill_teacher:back", "convoscreenstart" }
		}
	}
	trainer_convotemplate:addScreen(trainer_convoscreennotenoughskillpoints);

	trainer_convoscreenerror = ConvoScreen:new {
		id = "convoscreenerror",
		leftDialog = "@skill_teacher:error_grant_skill", -- Hrmm... seems that I cant teach you that skill due to an internal error. TestTrac?
		stopConversation = "true",
		options = { 
			{"@skill_teacher:back", "convoscreenstart" }
		}
	}
	trainer_convotemplate:addScreen(trainer_convoscreenerror);

	-- conversing with a trainer after reaching master in that profession
	trainer_convoscreenismaster = ConvoScreen:new {
		id = "convoscreenismaster",
		leftDialog = "@skill_teacher:topped_out", -- I'm sorry, but I cannot teach you anymore. You have already learned everything I have to teach.
		stopConversation = "true",
		options = { }
	}
	trainer_convotemplate:addScreen(trainer_convoscreenismaster);

	addConversationTemplate(templatename, trainer_convotemplate);
end

-- -- not sure where to put:
-- @skill_teacher:too_complicated 	-> I can't teach you anything. Everything I know is entirely too complicated for you.

-- -- same as @skill_teacher:topped_out:
-- @skill_teacher:msg3_1		-> There is nothing more I can teach you!

-- -- Messages to console, screenmessages:
-- @skill_teacher:nsf_skill_pts		-> You must first make %DI skill points available before I can teach you %TO.
-- @skill_teacher:prose_cost 		-> It will cost %DI credits to train in %TO. Would you like to continue?
-- @skill_teacher:prose_nsf 		-> You lack the %DI credits required for training in %TO.
-- @skill_teacher:prose_pay		-> Processing %DI credit payment for %TO training.
-- @skill_teacher:prose_skill_learned 	-> You successfully train in the %TO skill.
-- @skill_teacher:prose_train_failed	-> You were unable to complete %TO skill training.
-- @skill_teacher:success		-> You have successfully learned the skill.

-- -- unneeded(?):
-- @skill_teacher:opt1_3	-> Skills you have that I do not...
-- ->	@skill_teacher:msg2_3	-> Skills that I possess that you do not?! Well, what skill are you interested in?
-- @skill_teacher:opt1_4	-> All of your skills...
-- ->	@skill_teacher:msg2_4	-> All of my skills? Oh well, which one do you want to know about?

-- @skill_teacher:error_grant_skill	-> Hrmm... seems that I cant teach you that skill due to an internal error. TestTrac?
-- @skill_teacher:requires_jtl	-> You must enable the Star Wars Galaxies: Jump to Lightspeed expansion in order to converse with this npc.
-- @skill_teacher:msg1_1	-> Heya. What kind of skills would you like to know about

-- -- stuff for the message box popping up when talking to a trainer you are not qualified for:
-- @skill_teacher:no_qualify_prompt	-> You must have, at least, the following skills to learn from this skill trainer.
-- @skill_teacher:no_qualify_title	-> Trainer Skill Requirements


-- ****** Create trainer templates with the function above ******
createTrainerConversationTemplate("trainer_1hsword", "combat_1hsword_master", "trainer_1hsword_convotemplate")
createTrainerConversationTemplate("trainer_2hsword", "combat_2hsword_master", "trainer_2hsword_convotemplate")
createTrainerConversationTemplate("trainer_architect", "crafting_architect_master", "trainer_architect_convotemplate")
createTrainerConversationTemplate("trainer_armorsmith", "crafting_armorsmith_master", "trainer_armorsmith_convotemplate")
createTrainerConversationTemplate("trainer_artisan", "crafting_artisan_master", "trainer_artisan_convotemplate")
createTrainerConversationTemplate("trainer_bioengineer", "outdoors_bio_engineer_master", "trainer_bioengineer_convotemplate")
createTrainerConversationTemplate("trainer_bountyhunter", "combat_bounthunter_master", "trainer_bountyhunter_convotemplate")
createTrainerConversationTemplate("trainer_brawler", "combat_brawler_master", "trainer_brawler_convotemplate")
createTrainerConversationTemplate("trainer_carbine", "combat_carbine_master", "trainer_carbine_convotemplate")
createTrainerConversationTemplate("trainer_chef", "crafting_chef_master", "trainer_chef_convotemplate")
createTrainerConversationTemplate("trainer_combatmedic", "science_combatmedic_master", "trainer_combatmedic_convotemplate")
createTrainerConversationTemplate("trainer_commando", "combat_commando_master", "trainer_commando_convotemplate")
createTrainerConversationTemplate("trainer_creaturehandler", "outdoors_creaturehandler_master", "trainer_creaturehandler_convotemplate")
createTrainerConversationTemplate("trainer_dancer", "social_dancer_master", "trainer_dancer_convotemplate")
createTrainerConversationTemplate("trainer_doctor", "science_doctor_master", "trainer_doctor_convotemplate")
createTrainerConversationTemplate("trainer_droidengineer", "crafting_droidengineer_master", "trainer_droidengineer_convotemplate")
createTrainerConversationTemplate("trainer_entertainer", "social_entertainer_master", "trainer_entertainer_convotemplate")
createTrainerConversationTemplate("trainer_imagedesigner", "social_imagedesigner_master", "trainer_imagedesigner_convotemplate")
createTrainerConversationTemplate("trainer_marksman", "combat_marksman_master", "trainer_marksman_convotemplate")
createTrainerConversationTemplate("trainer_medic", "science_medic_master", "trainer_medic_convotemplate")
createTrainerConversationTemplate("trainer_merchant", "crafting_merchant_master", "trainer_merchant_convotemplate")
createTrainerConversationTemplate("trainer_musician", "social_musician_master", "trainer_musician_convotemplate")
createTrainerConversationTemplate("trainer_pistol", "combat_pistol_master", "trainer_pistol_convotemplate")
createTrainerConversationTemplate("trainer_polearm", "combat_polearm_master", "trainer_polearm_convotemplate")
createTrainerConversationTemplate("trainer_politician", "social_politician_master", "trainer_politician_convotemplate")
createTrainerConversationTemplate("trainer_ranger", "outdoors_ranger_master", "trainer_ranger_convotemplate")
createTrainerConversationTemplate("trainer_rifleman", "combat_rifleman_master", "trainer_rifleman_convotemplate")
createTrainerConversationTemplate("trainer_scout", "outdoors_scout_master", "trainer_scout_convotemplate")
createTrainerConversationTemplate("trainer_shipwright", "crafting_shipwright_master", "trainer_shipwright_convotemplate")
createTrainerConversationTemplate("trainer_smuggler", "combat_smuggler_master", "trainer_smuggler_convotemplate")
createTrainerConversationTemplate("trainer_squadleader", "outdoors_squadleader_master", "trainer_squadleader_convotemplate")
createTrainerConversationTemplate("trainer_tailor", "crafting_tailor_master", "trainer_tailor_convotemplate")
createTrainerConversationTemplate("trainer_unarmed", "combat_unarmed_master", "trainer_unarmed_convotemplate")
createTrainerConversationTemplate("trainer_weaponsmith", "crafting_weaponsmith_master", "trainer_weaponsmith_convotemplate")
--createTrainerConversationTemplate("trainer_rebel_navy", "pilot_rebel_navy_master", "trainer_rebel_navy_convotemplate")
--createTrainerConversationTemplate("trainer_imperial_navy", "pilot_imperial_navy_master", "trainer_imperial_navy_convotemplate")
--createTrainerConversationTemplate("trainer_neutral", "pilot_neutral_master", "trainer_neutral_convotemplate")

-- ****** Create force sensitive and jedi trainer conversation templates ******



