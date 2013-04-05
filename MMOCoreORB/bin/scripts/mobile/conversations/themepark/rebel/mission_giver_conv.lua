function createMissionGiverConvoTemplate(templateName, convoHandler)
	mission_giver_convotemplate = ConvoTemplate:new {
		initialScreen = "init",
		templateType = "Lua",
		luaClassHandler = convoHandler,
		screens = {}
	}
	
	mission_giver_init = ConvoScreen:new {
		id = "init",
		leftDialog = "",
		stopConversation = "false",
		options = {
		}
	}
	
	mission_giver_convotemplate:addScreen(mission_giver_init);
	
	mission_giver_cantwork = ConvoScreen:new {
		id = "cantwork",
		leftDialog = ":cantwork",
		stopConversation = "true",
		options = {
		}
	}
	
	mission_giver_convotemplate:addScreen(mission_giver_cantwork);
	
	mission_giver_next = ConvoScreen:new {
		id = "next",
		leftDialog = ":next",
		stopConversation = "true",
		options = {
		}
	}
	
	mission_giver_convotemplate:addScreen(mission_giver_next);
	
	mission_giver_notyet = ConvoScreen:new {
		id = "notyet",
		leftDialog = ":notyet",
		stopConversation = "true",
		options = {
		}
	}
	
	mission_giver_convotemplate:addScreen(mission_giver_notyet);
	
	mission_giver_npc_1_n = ConvoScreen:new {
		id = "npc_1_n",
		leftDialog = ":npc_1_1",
		stopConversation = "false",
		options = {
			{ ":player_1_1", "accept" },
			{ ":player_2_1", "npc_3_n" },
			{ ":player_3_1", "npc_4_n" }
		}
	}
	
	mission_giver_convotemplate:addScreen(mission_giver_npc_1_n);
	
	mission_giver_accept = ConvoScreen:new {
		id = "accept",
		leftDialog = "",
		stopConversation = "false",
		options = {
		}
	}
	
	mission_giver_convotemplate:addScreen(mission_giver_accept);
	
	mission_giver_npc_2_n = ConvoScreen:new {
		id = "npc_2_n",
		leftDialog = ":npc_2_1",
		stopConversation = "true",
		options = {
		}
	}
	
	mission_giver_convotemplate:addScreen(mission_giver_npc_2_n);
	
	mission_giver_npc_noloc_n = ConvoScreen:new {
		id = "npc_noloc_n",
		leftDialog = ":npc_noloc_1",
		stopConversation = "true",
		options = {
		}
	}
	
	mission_giver_convotemplate:addScreen(mission_giver_npc_noloc_n);
	
	mission_giver_npc_3_n = ConvoScreen:new {
		id = "npc_3_n",
		leftDialog = ":npc_3_1",
		stopConversation = "true",
		options = {
		}
	}
	
	mission_giver_convotemplate:addScreen(mission_giver_npc_3_n);
	
	mission_giver_npc_4_n = ConvoScreen:new {
		id = "npc_4_n",
		leftDialog = ":npc_4_1",
		stopConversation = "false",
		options = {
			{ ":player_1_1", "accept" },
			{ ":player_2_1", "npc_3_n" }
		}
	}
	
	mission_giver_convotemplate:addScreen(mission_giver_npc_4_n);
	
	mission_giver_status = ConvoScreen:new {
		id = "status",
		leftDialog = "",
		stopConversation = "false",
		options = {
		}
	}
	
	mission_giver_convotemplate:addScreen(mission_giver_status);
	
	mission_giver_npc_work_n = ConvoScreen:new {
		id = "npc_work_n",
		leftDialog = ":npc_work_1",
		stopConversation = "false",
		options = {
			{ ":player_reset_1", "npc_reset_n" },
			{ ":player_sorry_1", "npc_backtowork_n" }
		}
	}
	
	mission_giver_convotemplate:addScreen(mission_giver_npc_work_n);
	
	mission_giver_npc_reset_n = ConvoScreen:new {
		id = "npc_reset_n",
		leftDialog = ":npc_reset_1",
		stopConversation = "true",
		options = {
		}
	}
	
	mission_giver_convotemplate:addScreen(mission_giver_npc_reset_n);
	
	mission_giver_npc_backtowork_n = ConvoScreen:new {
		id = "npc_backtowork_n",
		leftDialog = ":npc_backtowork_1",
		stopConversation = "true",
		options = {
		}
	}
	
	mission_giver_convotemplate:addScreen(mission_giver_npc_backtowork_n);
	
	mission_giver_npc_reward_n = ConvoScreen:new {
		id = "npc_reward_n",
		leftDialog = ":npc_reward_1",
		stopConversation = "true",
		options = {
		}
	}
	
	mission_giver_convotemplate:addScreen(mission_giver_npc_reward_n);
	
	addConversationTemplate(templateName, mission_giver_convotemplate);
end

-- Themeparks
createMissionGiverConvoTemplate("theme_park_rebel_mission_giver_convotemplate", "theme_park_rebel_mission_giver_conv_handler")
createMissionGiverConvoTemplate("theme_park_jabba_mission_giver_convotemplate", "theme_park_jabba_mission_giver_conv_handler")
createMissionGiverConvoTemplate("theme_park_imperial_mission_giver_convotemplate", "theme_park_imperial_mission_giver_conv_handler")

-- Tatooine
createMissionGiverConvoTemplate("rakir_banai_mission_giver_convotemplate", "rakir_banai_mission_giver_conv_handler")
createMissionGiverConvoTemplate("tekil_barje_mission_giver_convotemplate", "tekil_barje_mission_giver_conv_handler")
createMissionGiverConvoTemplate("vardias_tyne_mission_giver_convotemplate", "vardias_tyne_mission_giver_conv_handler")
createMissionGiverConvoTemplate("pfilbee_jhorn_mission_giver_convotemplate", "pfilbee_jhorn_mission_giver_conv_handler")
createMissionGiverConvoTemplate("mat_rags_mission_giver_convotemplate", "mat_rags_mission_giver_conv_handler")

-- Naboo
createMissionGiverConvoTemplate("gavyn_sykes_mission_giver_convotemplate", "gavyn_sykes_mission_giver_conv_handler")

-- Dantooine
createMissionGiverConvoTemplate("drakka_judarrl_mission_giver_convotemplate", "drakka_judarrl_mission_giver_conv_handler")
createMissionGiverConvoTemplate("jatrian_lytus_mission_giver_convotemplate", "jatrian_lytus_mission_giver_conv_handler")
createMissionGiverConvoTemplate("kelvus_naria_mission_giver_convotemplate", "kelvus_naria_mission_giver_conv_handler")
createMissionGiverConvoTemplate("luthik_uwyr_mission_giver_convotemplate","luthik_uwyr_mission_giver_conv_handler")
createMissionGiverConvoTemplate("lx_466_mission_giver_convotemplate", "lx_466_mission_giver_conv_handler")
createMissionGiverConvoTemplate("sg_567_mission_giver_convotemplate", "sg_567_mission_giver_conv_handler")
createMissionGiverConvoTemplate("xaan_talmaron_mission_giver_convotemplate","xaan_talmaron_mission_giver_conv_handler")
