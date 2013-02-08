function createMissionTargetConvoTemplate(templateName, convoHandler)
	mission_target_convotemplate = ConvoTemplate:new {
		initialScreen = "npc_breech_n",
		templateType = "Lua",
		luaClassHandler = convoHandler,
		screens = {}
	}
	
	mission_target_npc_breech_n = ConvoScreen:new {
		id = "npc_breech_n",
		leftDialog = ":npc_breech_1",
		stopConversation = "false",
		options = {
			{ "@mission/mission_generic:yes", "missiontype" }
		}
	}
	
	mission_target_convotemplate:addScreen(mission_target_npc_breech_n);
	
	mission_target_missiontype = ConvoScreen:new {
		id = "missiontype",
		leftDialog = "",
		stopConversation = "false",
		options = {
		}
	}
	
	mission_target_convotemplate:addScreen(mission_target_missiontype);
	
	mission_target_npc_smuggle_n = ConvoScreen:new {
		id = "npc_smuggle_n",
		leftDialog = ":npc_smuggle_1",
		stopConversation = "true",
		options = {
		}
	}
	
	mission_target_convotemplate:addScreen(mission_target_npc_smuggle_n);
	
	mission_target_npc_takeme_n = ConvoScreen:new {
		id = "npc_takeme_n",
		leftDialog = ":npc_takeme_1",
		stopConversation = "true",
		options = {
		}
	}
	
	mission_target_convotemplate:addScreen(mission_target_npc_takeme_n);
	
	mission_target_dontknowyou_n = ConvoScreen:new {
		id = "dontknowyou_n",
		leftDialog = ":dontknowyou_1",
		stopConversation = "true",
		options = {
		}
	}
	
	mission_target_convotemplate:addScreen(mission_target_dontknowyou_n);
	
	mission_target_otherescort_n = ConvoScreen:new {
		id = "otherescort_n",
		leftDialog = ":otherescort_1",
		stopConversation = "true",
		options = {
		}
	}
	
	mission_target_convotemplate:addScreen(mission_target_otherescort_n);
	
	mission_target_notit_n = ConvoScreen:new {
		id = "notit_n",
		leftDialog = ":notit_1",
		stopConversation = "true",
		options = {
		}
	}
	
	mission_target_convotemplate:addScreen(mission_target_notit_n);
	
	addConversationTemplate(templateName, mission_target_convotemplate);
end

--Themeparks
createMissionTargetConvoTemplate("theme_park_rebel_mission_target_convotemplate","theme_park_rebel_mission_target_conv_handler")
createMissionTargetConvoTemplate("theme_park_jabba_mission_target_convotemplate","theme_park_jabba_mission_target_conv_handler")

-- Tatooine
createMissionTargetConvoTemplate("rakir_banai_mission_target_convotemplate","rakir_banai_mission_target_conv_handler")
createMissionTargetConvoTemplate("vardias_tyne_mission_target_convotemplate","vardias_tyne_mission_target_conv_handler")
createMissionTargetConvoTemplate("pfilbee_jhorn_mission_target_convotemplate","pfilbee_jhorn_mission_target_conv_handler")

-- Naboo
createMissionTargetConvoTemplate("gavyn_sykes_mission_target_convotemplate","gavyn_sykes_mission_target_conv_handler")

-- Dantooine
createMissionTargetConvoTemplate("drakka_judarrl_mission_target_convotemplate","drakka_judarrl_mission_target_conv_handler")
createMissionTargetConvoTemplate("jatrian_lytus_mission_target_convotemplate","jatrian_lytus_mission_target_conv_handler")
createMissionTargetConvoTemplate("kelvus_naria_mission_target_convotemplate","kelvus_naria_mission_target_conv_handler")
createMissionTargetConvoTemplate("luthik_uwyr_mission_target_convotemplate","luthik_uwyr_mission_target_conv_handler")
createMissionTargetConvoTemplate("lx_466_mission_target_convotemplate","lx_466_mission_target_conv_handler")
createMissionTargetConvoTemplate("xaan_talmaron_mission_target_convotemplate","xaan_talmaron_mission_target_conv_handler")
