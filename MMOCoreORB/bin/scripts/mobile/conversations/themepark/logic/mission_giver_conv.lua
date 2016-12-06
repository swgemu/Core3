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
			{ ":player_3_1", "npc_4_n" },
			{ ":player_4_1", "npc_5_n" },
			{ ":player_5_1", "npc_6_n" }
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
			{ ":player_2_1", "npc_3_n" },
			{ ":player_4_1", "npc_5_n" },
			{ ":player_5_1", "npc_6_n" }
		}
	}

	mission_giver_convotemplate:addScreen(mission_giver_npc_4_n);

	mission_giver_npc_5_n = ConvoScreen:new {
		id = "npc_5_n",
		leftDialog = ":npc_5_1",
		stopConversation = "false",
		options = {
			{ ":player_1_1", "accept" },
			{ ":player_2_1", "npc_3_n" },
			{ ":player_3_1", "npc_4_n" },
			{ ":player_5_1", "npc_6_n" }
		}
	}

	mission_giver_convotemplate:addScreen(mission_giver_npc_5_n);

	mission_giver_npc_6_n = ConvoScreen:new {
		id = "npc_6_n",
		leftDialog = ":npc_6_1",
		stopConversation = "false",
		options = {
			{ ":player_1_1", "accept" },
			{ ":player_2_1", "npc_3_n" },
			{ ":player_3_1", "npc_4_n" },
			{ ":player_4_1", "npc_5_n" }
		}
	}

	mission_giver_convotemplate:addScreen(mission_giver_npc_6_n);

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

	mission_giver_quit_quest = ConvoScreen:new {
		id = "quit_quest",
		leftDialog = "@static_npc/default_dialog:quit_quest", -- I can see that you're busy working for someone else at the moment. Would you like to continue to do so, or would you like to work for me instead?
		stopConversation = "false",
		options = {
			{ "@static_npc/default_dialog:player_quit", "npc_quit" }, -- I think I'd like to work for you.
			{ "@static_npc/default_dialog:player_continue", "npc_continue" } -- No, I think I'll keep my current job, thanks.
		}
	}

	mission_giver_convotemplate:addScreen(mission_giver_quit_quest);

	mission_giver_npc_quit = ConvoScreen:new {
		id = "npc_quit",
		leftDialog = "@static_npc/default_dialog:npc_quit", -- Fine. You are now free of your prior obligation, and you can freely work for me.
		stopConversation = "true",
		options = {}
	}

	mission_giver_convotemplate:addScreen(mission_giver_npc_quit);

	mission_giver_npc_continue = ConvoScreen:new {
		id = "npc_continue",
		leftDialog = "@static_npc/default_dialog:npc_continue", -- Fine then. Don't bother with me until you're ready to work for me.
		stopConversation = "true",
		options = {}
	}

	mission_giver_convotemplate:addScreen(mission_giver_npc_continue);

	addConversationTemplate(templateName, mission_giver_convotemplate);
end

-- Themeparks
createMissionGiverConvoTemplate("theme_park_imperial_mission_giver_convotemplate", "theme_park_imperial_mission_giver_conv_handler")
createMissionGiverConvoTemplate("theme_park_jabba_mission_giver_convotemplate", "theme_park_jabba_mission_giver_conv_handler")
createMissionGiverConvoTemplate("theme_park_marauder_charal_mission_giver_convotemplate", "theme_park_marauder_charal_mission_giver_conv_handler")
createMissionGiverConvoTemplate("theme_park_marauder_raglith_jorak_mission_giver_convotemplate", "theme_park_marauder_raglith_jorak_mission_giver_conv_handler")
createMissionGiverConvoTemplate("theme_park_marauder_szingo_terak_mission_giver_convotemplate", "theme_park_marauder_szingo_terak_mission_giver_conv_handler")
createMissionGiverConvoTemplate("theme_park_rebel_mission_giver_convotemplate", "theme_park_rebel_mission_giver_conv_handler")
createMissionGiverConvoTemplate("theme_park_valarian_mission_giver_convotemplate", "theme_park_valarian_mission_giver_conv_handler")
createMissionGiverConvoTemplate("theme_park_nightsister_mission_giver_convotemplate", "theme_park_nightsister_mission_giver_conv_handler")
createMissionGiverConvoTemplate("theme_park_smc_zideera_mission_giver_convotemplate", "theme_park_smc_zideera_mission_giver_conv_handler")
createMissionGiverConvoTemplate("theme_park_smc_vhaunda_izaryx_mission_giver_convotemplate", "theme_park_smc_vhaunda_izaryx_mission_giver_conv_handler")
createMissionGiverConvoTemplate("theme_park_smc_vurlene_aujante_mission_giver_convotemplate", "theme_park_smc_vurlene_aujante_mission_giver_conv_handler")

-- Generic
createMissionGiverConvoTemplate("generic_businessman_mission_giver_convotemplate", "generic_businessman_mission_giver_conv_handler")
createMissionGiverConvoTemplate("generic_criminal_mission_giver_convotemplate", "generic_criminal_mission_giver_conv_handler")
createMissionGiverConvoTemplate("generic_noble_mission_giver_convotemplate", "generic_noble_mission_giver_conv_handler")
createMissionGiverConvoTemplate("generic_scientist_mission_giver_convotemplate", "generic_scientist_mission_giver_conv_handler")

-- Epic Quest Chains
createMissionGiverConvoTemplate("krayt_dragon_skull_mission_giver_convotemplate", "krayt_dragon_skull_mission_giver_conv_handler")
createMissionGiverConvoTemplate("zicx_bug_bomb_mission_giver_convotemplate", "zicx_bug_bomb_mission_giver_conv_handler")

--Corellia
createMissionGiverConvoTemplate("blk_sun_tasks_mission_giver_convotemplate","blk_sun_tasks_mission_giver_conv_handler")
createMissionGiverConvoTemplate("chertyl_ruluwoor_mission_giver_convotemplate","chertyl_ruluwoor_mission_giver_conv_handler")
createMissionGiverConvoTemplate("coraline_dynes_mission_giver_convotemplate","coraline_dynes_mission_giver_conv_handler")
createMissionGiverConvoTemplate("corran_horn_mission_giver_convotemplate","corran_horn_mission_giver_conv_handler")
createMissionGiverConvoTemplate("crev_bombaasa_mission_giver_convotemplate","crev_bombaasa_mission_giver_conv_handler")
createMissionGiverConvoTemplate("dalla_solo_mission_giver_convotemplate","dalla_solo_mission_giver_conv_handler")
createMissionGiverConvoTemplate("dannik_malaan_mission_giver_convotemplate","dannik_malaan_mission_giver_conv_handler")
createMissionGiverConvoTemplate("denell_kel_vannon_mission_giver_convotemplate","denell_kel_vannon_mission_giver_conv_handler")
createMissionGiverConvoTemplate("didina_lippinoss_mission_giver_convotemplate","didina_lippinoss_mission_giver_conv_handler")
createMissionGiverConvoTemplate("diktatGiverConvo","diktatGiverHandler")
createMissionGiverConvoTemplate("garm_bel_iblis_mission_giver_convotemplate","garm_bel_iblis_mission_giver_conv_handler")
createMissionGiverConvoTemplate("gilad_pellaeon_mission_giver_convotemplate","gilad_pellaeon_mission_giver_conv_handler")
createMissionGiverConvoTemplate("gilker_budz_mission_giver_convotemplate","gilker_budz_mission_giver_conv_handler")
createMissionGiverConvoTemplate("ging_darjeek_mission_giver_convotemplate","ging_darjeek_mission_giver_conv_handler")
createMissionGiverConvoTemplate("grondorn_muse_mission_giver_convotemplate","grondorn_muse_mission_giver_conv_handler")
createMissionGiverConvoTemplate("hal_horn_mission_giver_convotemplate","hal_horn_mission_giver_conv_handler")
createMissionGiverConvoTemplate("ignar_ominaz_mission_giver_convotemplate","ignar_ominaz_mission_giver_conv_handler")
createMissionGiverConvoTemplate("jadam_questrel_mission_giver_convotemplate","jadam_questrel_mission_giver_conv_handler")
createMissionGiverConvoTemplate("joz_jodhul_mission_giver_convotemplate","joz_jodhul_mission_giver_conv_handler")
createMissionGiverConvoTemplate("kirkin_liawoon_mission_giver_convotemplate","kirkin_liawoon_mission_giver_conv_handler")
createMissionGiverConvoTemplate("lady_hutt_mission_giver_convotemplate","lady_hutt_mission_giver_conv_handler")
createMissionGiverConvoTemplate("luthin_dlunar_mission_giver_convotemplate","luthin_dlunar_mission_giver_conv_handler")
createMissionGiverConvoTemplate("noren_krast_mission_giver_convotemplate","noren_krast_mission_giver_conv_handler")
createMissionGiverConvoTemplate("palejo_reshad_mission_giver_convotemplate","palejo_reshad_mission_giver_conv_handler")
createMissionGiverConvoTemplate("scolex_grath_mission_giver_convotemplate","scolex_grath_mission_giver_conv_handler")
createMissionGiverConvoTemplate("serjix_arrogantus_mission_giver_convotemplate","serjix_arrogantus_mission_giver_conv_handler")
createMissionGiverConvoTemplate("skinkner_mission_giver_convotemplate","skinkner_mission_giver_conv_handler")
createMissionGiverConvoTemplate("thrackan_sal_solo_mission_giver_convotemplate","thrackan_sal_solo_mission_giver_conv_handler")
createMissionGiverConvoTemplate("venthan_chassu_mission_giver_convotemplate","venthan_chassu_mission_giver_conv_handler")
createMissionGiverConvoTemplate("viceprex_tasks_mission_giver_convotemplate","viceprex_tasks_mission_giver_conv_handler")
createMissionGiverConvoTemplate("zakarisz_ghent_mission_giver_convotemplate","zakarisz_ghent_mission_giver_conv_handler")

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
createMissionGiverConvoTemplate("shaki_hamachil_mission_giver_convotemplate", "shaki_hamachil_mission_giver_conv_handler")
createMissionGiverConvoTemplate("shibb_nisshil_mission_giver_convotemplate", "shibb_nisshil_mission_giver_conv_handler")
createMissionGiverConvoTemplate("singular_nak_mission_giver_convotemplate", "singular_nak_mission_giver_conv_handler")
createMissionGiverConvoTemplate("wallaw_loowobbli_mission_giver_convotemplate", "wallaw_loowobbli_mission_giver_conv_handler")
createMissionGiverConvoTemplate("warden_vinzel_haylon_mission_giver_convotemplate", "warden_vinzel_haylon_mission_giver_conv_handler")
createMissionGiverConvoTemplate("xarot_korlin_mission_giver_convotemplate", "xarot_korlin_mission_giver_conv_handler")

-- Naboo
createMissionGiverConvoTemplate("arrek_von_sarko_mission_giver_convotemplate", "arrek_von_sarko_mission_giver_conv_handler")
createMissionGiverConvoTemplate("arven_wendik_mission_giver_convotemplate", "arven_wendik_mission_giver_conv_handler")
createMissionGiverConvoTemplate("athok_dinvar_mission_giver_convotemplate", "athok_dinvar_mission_giver_conv_handler")
createMissionGiverConvoTemplate("bab_esrus_mission_giver_convotemplate", "bab_esrus_mission_giver_conv_handler")
createMissionGiverConvoTemplate("bardo_klinj_mission_giver_convotemplate", "bardo_klinj_mission_giver_conv_handler")
createMissionGiverConvoTemplate("boss_nass_mission_giver_convotemplate", "boss_nass_mission_giver_conv_handler")
createMissionGiverConvoTemplate("brass_marshoo_mission_giver_convotemplate", "brass_marshoo_mission_giver_conv_handler")
createMissionGiverConvoTemplate("brennis_doore_mission_giver_convotemplate", "brennis_doore_mission_giver_conv_handler")
createMissionGiverConvoTemplate("damalia_korde_mission_giver_convotemplate", "damalia_korde_mission_giver_conv_handler")
createMissionGiverConvoTemplate("dilvin_lormurojo_mission_giver_convotemplate", "dilvin_lormurojo_mission_giver_conv_handler")
createMissionGiverConvoTemplate("ebenn_q3_baobab_mission_giver_convotemplate", "ebenn_q3_baobab_mission_giver_conv_handler")
createMissionGiverConvoTemplate("gavyn_sykes_mission_giver_convotemplate", "gavyn_sykes_mission_giver_conv_handler")
createMissionGiverConvoTemplate("huff_zinga_mission_giver_convotemplate", "huff_zinga_mission_giver_conv_handler")
createMissionGiverConvoTemplate("kima_nazith_mission_giver_convotemplate", "kima_nazith_mission_giver_conv_handler")
createMissionGiverConvoTemplate("kritus_morven_mission_giver_convotemplate", "kritus_morven_mission_giver_conv_handler")
createMissionGiverConvoTemplate("lareen_dantara_mission_giver_convotemplate", "lareen_dantara_mission_giver_conv_handler")
createMissionGiverConvoTemplate("leb_slesher_mission_giver_convotemplate", "leb_slesher_mission_giver_conv_handler")
createMissionGiverConvoTemplate("lergo_brazee_mission_giver_convotemplate", "lergo_brazee_mission_giver_conv_handler")
createMissionGiverConvoTemplate("lob_dizz_mission_giver_convotemplate", "lob_dizz_mission_giver_conv_handler")
createMissionGiverConvoTemplate("mullud_bombo_mission_giver_convotemplate", "mullud_bombo_mission_giver_conv_handler")
createMissionGiverConvoTemplate("palo_mission_giver_convotemplate", "palo_mission_giver_conv_handler")
createMissionGiverConvoTemplate("pooja_naberrie_mission_giver_convotemplate", "pooja_naberrie_mission_giver_conv_handler")
createMissionGiverConvoTemplate("radanthus_mandelatara_mission_giver_convotemplate", "radanthus_mandelatara_mission_giver_conv_handler")
createMissionGiverConvoTemplate("rep_been_mission_giver_convotemplate", "rep_been_mission_giver_conv_handler")
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
createMissionGiverConvoTemplate("durgur_pyne_mission_giver_convotemplate", "durgur_pyne_mission_giver_conv_handler")
createMissionGiverConvoTemplate("gravin_attal_mission_giver_convotemplate", "gravin_attal_mission_giver_conv_handler")
createMissionGiverConvoTemplate("green_laser_mission_giver_convotemplate", "green_laser_mission_giver_conv_handler")
createMissionGiverConvoTemplate("haleen_snowline_hagrin_zeed_mission_giver_convotemplate", "haleen_snowline_hagrin_zeed_mission_giver_conv_handler")
createMissionGiverConvoTemplate("igbi_freemo_mission_giver_convotemplate", "igbi_freemo_mission_giver_conv_handler")
createMissionGiverConvoTemplate("jusani_zhord_mission_giver_convotemplate", "jusani_zhord_mission_giver_conv_handler")
createMissionGiverConvoTemplate("kathikiis_ruwahurr_mission_giver_convotemplate", "kathikiis_ruwahurr_mission_giver_conv_handler")
createMissionGiverConvoTemplate("lethin_bludder_mission_giver_convotemplate", "lethin_bludder_mission_giver_conv_handler")
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
createMissionGiverConvoTemplate("melios_purl_mission_giver_convotemplate", "melios_purl_mission_giver_conv_handler")
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
createMissionGiverConvoTemplate("captain_eso_mission_giver_convotemplate","captain_eso_mission_giver_conv_handler")
createMissionGiverConvoTemplate("cx_425_trooper_mission_giver_convotemplate","cx_425_trooper_mission_giver_conv_handler")
createMissionGiverConvoTemplate("gins_darone_mission_giver_convotemplate","gins_darone_mission_giver_conv_handler")
createMissionGiverConvoTemplate("jazeen_thurmm_mission_giver_convotemplate","jazeen_thurmm_mission_giver_conv_handler")
createMissionGiverConvoTemplate("lian_byrne_mission_giver_convotemplate","lian_byrne_mission_giver_conv_handler")
createMissionGiverConvoTemplate("megan_drlar_mission_giver_convotemplate","megan_drlar_mission_giver_conv_handler")
createMissionGiverConvoTemplate("ruwan_tokai_mission_giver_convotemplate","ruwan_tokai_mission_giver_conv_handler")
createMissionGiverConvoTemplate("vraker_orde_mission_giver_convotemplate","vraker_orde_mission_giver_conv_handler")
createMissionGiverConvoTemplate("yith_seenath_mission_giver_convotemplate","yith_seenath_mission_giver_conv_handler")
