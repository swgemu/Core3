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

	mission_giver_failure = ConvoScreen:new {
		id = "failure",
		leftDialog = "",
		stopConversation = "true",
		options = {
		}
	}

	mission_giver_convotemplate:addScreen(mission_giver_failure);

	mission_giver_no_faction = ConvoScreen:new {
		id = "no_faction",
		leftDialog = "",
		stopConversation = "true",
		options = {
		}
	}

	mission_giver_convotemplate:addScreen(mission_giver_no_faction);

	mission_giver_cant_work = ConvoScreen:new {
		id = "cant_work",
		leftDialog = ":cant_work",
		stopConversation = "true",
		options = {
		}
	}

	mission_giver_convotemplate:addScreen(mission_giver_cant_work);

	mission_giver_cantwork = ConvoScreen:new {
		id = "cantwork",
		leftDialog = ":cantwork",
		stopConversation = "true",
		options = {
		}
	}

	mission_giver_convotemplate:addScreen(mission_giver_cantwork);

	mission_giver_invfull = ConvoScreen:new {
		id = "inv_full",
		leftDialog = "",
		stopConversation = "true",
		options = {
		}
	}

	mission_giver_convotemplate:addScreen(mission_giver_invfull);

	mission_giver_too_weak = ConvoScreen:new {
		id = "too_weak",
		leftDialog = "",
		stopConversation = "true",
		options = {
		}
	}

	mission_giver_convotemplate:addScreen(mission_giver_too_weak);

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

	mission_giver_notit_n = ConvoScreen:new {
		id = "notit_n",
		leftDialog = ":notit_1",
		stopConversation = "true",
		options = {
		}
	}

	mission_giver_convotemplate:addScreen(mission_giver_notit_n);

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

	mission_giver_npc_reset = ConvoScreen:new {
		id = "npc_reset",
		leftDialog = ":npc_reset",
		stopConversation = "true",
		options = {
		}
	}

	mission_giver_convotemplate:addScreen(mission_giver_npc_reset);

	mission_giver_npc_backtowork_n = ConvoScreen:new {
		id = "npc_backtowork_n",
		leftDialog = ":npc_backtowork_1",
		stopConversation = "true",
		options = {
		}
	}

	mission_giver_convotemplate:addScreen(mission_giver_npc_backtowork_n);

	mission_giver_npc_backtowork = ConvoScreen:new {
		id = "npc_backtowork",
		leftDialog = ":npc_backtowork",
		stopConversation = "true",
		options = {
		}
	}

	mission_giver_convotemplate:addScreen(mission_giver_npc_backtowork);

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
createMissionGiverConvoTemplate("theme_park_imperial_mission_giver_convotemplate", "theme_park_imperial_mission_giver_conv_handler")
createMissionGiverConvoTemplate("theme_park_jabba_mission_giver_convotemplate", "theme_park_jabba_mission_giver_conv_handler")
createMissionGiverConvoTemplate("theme_park_marauder_mission_giver_convotemplate", "theme_park_marauder_mission_giver_conv_handler")
createMissionGiverConvoTemplate("theme_park_rebel_mission_giver_convotemplate", "theme_park_rebel_mission_giver_conv_handler")
createMissionGiverConvoTemplate("theme_park_valarian_mission_giver_convotemplate", "theme_park_valarian_mission_giver_conv_handler")

-- Epic Quest Chains
createMissionGiverConvoTemplate("krayt_dragon_skull_mission_giver_convotemplate", "krayt_dragon_skull_mission_giver_conv_handler")
createMissionGiverConvoTemplate("zicx_bug_bomb_mission_giver_convotemplate", "zicx_bug_bomb_mission_giver_conv_handler")

--Corellia
createMissionGiverConvoTemplate("chertyl_ruluwoor_mission_giver_convotemplate","chertyl_ruluwoor_mission_giver_conv_handler")
createMissionGiverConvoTemplate("coraline_dynes_mission_giver_convotemplate","coraline_dynes_mission_giver_conv_handler")
createMissionGiverConvoTemplate("corran_horn_mission_giver_convotemplate","corran_horn_mission_giver_conv_handler")
createMissionGiverConvoTemplate("denell_kel_vannon_mission_giver_convotemplate","denell_kel_vannon_mission_giver_conv_handler")
createMissionGiverConvoTemplate("didina_lippinoss_mission_giver_convotemplate","didina_lippinoss_mission_giver_conv_handler")
createMissionGiverConvoTemplate("diktatGiverConvo","diktatGiverHandler")
createMissionGiverConvoTemplate("garm_bel_iblis_mission_giver_convotemplate","garm_bel_iblis_mission_giver_conv_handler")
createMissionGiverConvoTemplate("gilad_pellaeon_mission_giver_convotemplate","gilad_pellaeon_mission_giver_conv_handler")
createMissionGiverConvoTemplate("gilker_budz_mission_giver_convotemplate","gilker_budz_mission_giver_conv_handler")
createMissionGiverConvoTemplate("ging_darjeek_mission_giver_convotemplate","ging_darjeek_mission_giver_conv_handler")
createMissionGiverConvoTemplate("hal_horn_mission_giver_convotemplate","hal_horn_mission_giver_conv_handler")
createMissionGiverConvoTemplate("jadam_questrel_mission_giver_convotemplate","jadam_questrel_mission_giver_conv_handler")
createMissionGiverConvoTemplate("kirkin_liawoon_mission_giver_convotemplate","kirkin_liawoon_mission_giver_conv_handler")
createMissionGiverConvoTemplate("lady_hutt_mission_giver_convotemplate","lady_hutt_mission_giver_conv_handler")
createMissionGiverConvoTemplate("luthin_dlunar_mission_giver_convotemplate","luthin_dlunar_mission_giver_conv_handler")
createMissionGiverConvoTemplate("noren_krast_mission_giver_convotemplate","noren_krast_mission_giver_conv_handler")
createMissionGiverConvoTemplate("palejo_reshad_mission_giver_convotemplate","palejo_reshad_mission_giver_conv_handler")
createMissionGiverConvoTemplate("talon_karrde_mission_giver_convotemplate","talon_karrde_mission_giver_conv_handler")
createMissionGiverConvoTemplate("thrackan_sal_solo_mission_giver_convotemplate","thrackan_sal_solo_mission_giver_conv_handler")

-- Dantooine
createMissionGiverConvoTemplate("drakka_judarrl_mission_giver_convotemplate", "drakka_judarrl_mission_giver_conv_handler")
createMissionGiverConvoTemplate("jatrian_lytus_mission_giver_convotemplate", "jatrian_lytus_mission_giver_conv_handler")
createMissionGiverConvoTemplate("kelvus_naria_mission_giver_convotemplate", "kelvus_naria_mission_giver_conv_handler")
createMissionGiverConvoTemplate("luthik_uwyr_mission_giver_convotemplate","luthik_uwyr_mission_giver_conv_handler")
createMissionGiverConvoTemplate("lx_466_mission_giver_convotemplate", "lx_466_mission_giver_conv_handler")
createMissionGiverConvoTemplate("sg_567_mission_giver_convotemplate", "sg_567_mission_giver_conv_handler")
createMissionGiverConvoTemplate("stoos_olko_mission_giver_convotemplate", "stoos_olko_mission_giver_conv_handler")
createMissionGiverConvoTemplate("xaan_talmaron_mission_giver_convotemplate","xaan_talmaron_mission_giver_conv_handler")

--Dathomir
createMissionGiverConvoTemplate("dolac_legasi_mission_giver_convotemplate", "dolac_legasi_mission_giver_conv_handler")
createMissionGiverConvoTemplate("singular_nak_mission_giver_convotemplate", "singular_nak_mission_giver_conv_handler")
createMissionGiverConvoTemplate("wallaw_loowobbli_mission_giver_convotemplate", "wallaw_loowobbli_mission_giver_conv_handler")
createMissionGiverConvoTemplate("xarot_korlin_mission_giver_convotemplate", "xarot_korlin_mission_giver_conv_handler")

-- Naboo
createMissionGiverConvoTemplate("arven_wendik_mission_giver_convotemplate", "arven_wendik_mission_giver_conv_handler")
createMissionGiverConvoTemplate("boss_nass_mission_giver_convotemplate", "boss_nass_mission_giver_conv_handler")
createMissionGiverConvoTemplate("gavyn_sykes_mission_giver_convotemplate", "gavyn_sykes_mission_giver_conv_handler")
createMissionGiverConvoTemplate("huff_zinga_mission_giver_convotemplate", "huff_zinga_mission_giver_conv_handler")
createMissionGiverConvoTemplate("lareen_dantara_mission_giver_convotemplate", "lareen_dantara_mission_giver_conv_handler")
createMissionGiverConvoTemplate("leb_slesher_mission_giver_convotemplate", "leb_slesher_mission_giver_conv_handler")
createMissionGiverConvoTemplate("lergo_brazee_mission_giver_convotemplate", "lergo_brazee_mission_giver_conv_handler")
createMissionGiverConvoTemplate("mullud_bombo_mission_giver_convotemplate", "mullud_bombo_mission_giver_conv_handler")
createMissionGiverConvoTemplate("rovim_minnoni_mission_giver_convotemplate", "rovim_minnoni_mission_giver_conv_handler")
createMissionGiverConvoTemplate("tamvar_senzen_mission_giver_convotemplate", "tamvar_senzen_mission_giver_conv_handler")
createMissionGiverConvoTemplate("vana_sage_mission_giver_convotemplate", "vana_sage_mission_giver_conv_handler")

--Rori
createMissionGiverConvoTemplate("ajuva_vanasterin_mission_giver_convotemplate","ajuva_vanasterin_mission_giver_conv_handler")
createMissionGiverConvoTemplate("biribas_tarun_mission_giver_convotemplate","biribas_tarun_mission_giver_conv_handler")
createMissionGiverConvoTemplate("booto_lubble_mission_giver_convotemplate","booto_lubble_mission_giver_conv_handler")
createMissionGiverConvoTemplate("draya_korbinari_mission_giver_convotemplate","draya_korbinari_mission_giver_conv_handler")
createMissionGiverConvoTemplate("hefsen_zindalai_mission_giver_convotemplate","hefsen_zindalai_mission_giver_conv_handler")
createMissionGiverConvoTemplate("indintra_imbru_yerevan_mission_giver_convotemplate","indintra_imbru_yerevan_mission_giver_conv_handler")
createMissionGiverConvoTemplate("jaleela_bindoo_mission_giver_convotemplate","jaleela_bindoo_mission_giver_conv_handler")
createMissionGiverConvoTemplate("magur_torigai_mission_giver_convotemplate","magur_torigai_mission_giver_conv_handler")
createMissionGiverConvoTemplate("oxil_sarban_mission_giver_convotemplate","oxil_sarban_mission_giver_conv_handler")
createMissionGiverConvoTemplate("raxa_binn_mission_giver_convotemplate","raxa_binn_mission_giver_conv_handler")
createMissionGiverConvoTemplate("sidoras_bey_mission_giver_convotemplate","sidoras_bey_mission_giver_conv_handler")
createMissionGiverConvoTemplate("sindra_lintikoor_mission_giver_convotemplate","sindra_lintikoor_mission_giver_conv_handler")
createMissionGiverConvoTemplate("sloan_rusper_mission_giver_convotemplate","sloan_rusper_mission_giver_conv_handler")
createMissionGiverConvoTemplate("vordin_sildor_mission_giver_convotemplate","vordin_sildor_mission_giver_conv_handler")
createMissionGiverConvoTemplate("zeelius_kraymunder_mission_giver_convotemplate","zeelius_kraymunder_mission_giver_conv_handler")

-- Talus
createMissionGiverConvoTemplate("champhra_biahin_mission_giver_convotemplate", "champhra_biahin_mission_giver_conv_handler")
createMissionGiverConvoTemplate("haleen_snowline_hagrin_zeed_mission_giver_convotemplate", "haleen_snowline_hagrin_zeed_mission_giver_conv_handler")
createMissionGiverConvoTemplate("igbi_freemo_mission_giver_convotemplate", "igbi_freemo_mission_giver_conv_handler")
createMissionGiverConvoTemplate("kathikiis_ruwahurr_mission_giver_convotemplate", "kathikiis_ruwahurr_mission_giver_conv_handler")
createMissionGiverConvoTemplate("mourno_draver_mission_giver_convotemplate", "mourno_draver_mission_giver_conv_handler")
createMissionGiverConvoTemplate("nurla_slinthiss_mission_giver_convotemplate", "nurla_slinthiss_mission_giver_conv_handler")
createMissionGiverConvoTemplate("radlee_mathiss_mission_giver_convotemplate", "radlee_mathiss_mission_giver_conv_handler")
createMissionGiverConvoTemplate("sigrix_slix_mission_giver_convotemplate", "sigrix_slix_mission_giver_conv_handler")
createMissionGiverConvoTemplate("slooni_jong_mission_giver_convotemplate", "slooni_jong_mission_giver_conv_handler")
createMissionGiverConvoTemplate("xalox_guul_mission_giver_convotemplate", "xalox_guul_mission_giver_conv_handler")

-- Tatooine
createMissionGiverConvoTemplate("aaph_koden_mission_giver_convotemplate", "aaph_koden_mission_giver_conv_handler")
createMissionGiverConvoTemplate("blerx_tango_mission_giver_convotemplate", "blerx_tango_mission_giver_conv_handler")
createMissionGiverConvoTemplate("bren_kingal_mission_giver_convotemplate", "bren_kingal_mission_giver_conv_handler")
createMissionGiverConvoTemplate("farious_gletch_mission_giver_convotemplate", "farious_gletch_mission_giver_conv_handler")
createMissionGiverConvoTemplate("fixer_mission_giver_convotemplate", "fixer_mission_giver_conv_handler")
createMissionGiverConvoTemplate("gramm_rile_mission_giver_convotemplate", "gramm_rile_mission_giver_conv_handler")
createMissionGiverConvoTemplate("hedon_istee_mission_giver_convotemplate", "hedon_istee_mission_giver_conv_handler")
createMissionGiverConvoTemplate("ikka_gesul_mission_giver_convotemplate", "ikka_gesul_mission_giver_conv_handler")
createMissionGiverConvoTemplate("jilljoo_jab_mission_giver_convotemplate", "jilljoo_jab_mission_giver_conv_handler")
createMissionGiverConvoTemplate("kaeline_ungasan_mission_giver_convotemplate", "kaeline_ungasan_mission_giver_conv_handler")
createMissionGiverConvoTemplate("kitster_banai_mission_giver_convotemplate", "kitster_banai_mission_giver_conv_handler")
createMissionGiverConvoTemplate("kormund_thrylle_mission_giver_convotemplate", "kormund_thrylle_mission_giver_conv_handler")
createMissionGiverConvoTemplate("lorne_prestar_mission_giver_convotemplate", "lorne_prestar_mission_giver_conv_handler")
createMissionGiverConvoTemplate("lt_harburik_mission_giver_convotemplate", "lt_harburik_mission_giver_conv_handler")
createMissionGiverConvoTemplate("mat_rags_mission_giver_convotemplate", "mat_rags_mission_giver_conv_handler")
createMissionGiverConvoTemplate("nitra_vendallan_mission_giver_convotemplate", "nitra_vendallan_mission_giver_conv_handler")
createMissionGiverConvoTemplate("om_aynat_mission_giver_convotemplate", "om_aynat_mission_giver_conv_handler")
createMissionGiverConvoTemplate("pfilbee_jhorn_mission_giver_convotemplate", "pfilbee_jhorn_mission_giver_conv_handler")
createMissionGiverConvoTemplate("phinea_shantee_mission_giver_convotemplate", "phinea_shantee_mission_giver_conv_handler")
createMissionGiverConvoTemplate("prefect_talmont_mission_giver_convotemplate", "prefect_talmont_mission_giver_conv_handler")
createMissionGiverConvoTemplate("rakir_banai_mission_giver_convotemplate", "rakir_banai_mission_giver_conv_handler")
createMissionGiverConvoTemplate("stella_mission_giver_convotemplate", "stella_mission_giver_conv_handler")
createMissionGiverConvoTemplate("tekil_barje_mission_giver_convotemplate", "tekil_barje_mission_giver_conv_handler")
createMissionGiverConvoTemplate("tolan_nokkar_mission_giver_convotemplate", "tolan_nokkar_mission_giver_conv_handler")
createMissionGiverConvoTemplate("vardias_tyne_mission_giver_convotemplate", "vardias_tyne_mission_giver_conv_handler")

--Yavin4
createMissionGiverConvoTemplate("gins_darone_mission_giver_convotemplate","gins_darone_mission_giver_conv_handler")
createMissionGiverConvoTemplate("lian_byrne_mission_giver_convotemplate","lian_byrne_mission_giver_conv_handler")
createMissionGiverConvoTemplate("ruwan_tokai_mission_giver_convotemplate","ruwan_tokai_mission_giver_conv_handler")

