
captain_eso_missions =
	{
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "swamp_trooper", npcName = "" },
				{ npcTemplate = "swamp_trooper", npcName = "" },
				{ npcTemplate = "swamp_trooper", npcName = "" },
				{ npcTemplate = "swamp_trooper", npcName = "" }
			--*The string-file dialog says a "squad" ^. By definition, a squad = 9 or more.  The only evidence we
				--have is the forums guide though, which says "3" .  So, i went with 4, rather than 9, since the point is
				--that the Rebels are supposed to be "pinned down" by a SQUAD (aka out-numbered & overwhelmed) .
			},
			secondarySpawns =
			{--**Because of the recent fix to prevent mobs from the SAME SPAWN from fighting eachother, we have also
				--unfortunately prevented these types of tp logic mission-spawns from aggro'ing eachother, as they should
				--be doing as per within string-file dialogs (plus being opposite FACTION spawns)
				{ npcTemplate = "rebel_recon_quest_eso", npcName = "" },
				{ npcTemplate = "rebel_recon_quest_eso", npcName = "" }
			},
			itemSpawns =
			{
			},
			rewards =
			{
				{ rewardType = "faction", faction = "rebel", amount = 10 },
			}
		},
		{
			missionType = "assassinate",
			--buildingSpawn = triageCamp, --*Is there a way to spawn the "triage" (string-file dialog) with
				--"Bacta Tanks" (purple wp name) without making it a destructible/destroy building w/ footprint?
				-- Like, can we spawn childObjects with tp logic mission spawns???
			primarySpawns =
			{
				{ npcTemplate = "imperial_medic", npcName = "" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "swamp_trooper", npcName = "" },
				{ npcTemplate = "swamp_trooper", npcName = "" },
				{ npcTemplate = "swamp_trooper", npcName = "" }
			},
			itemSpawns =
			{
			},
			rewards =
			{
				{ rewardType = "faction", faction = "rebel", amount = 15 },
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "deranged_rebel_quest_eso", npcName = "a Deranged Rebel" }
			},
			secondarySpawns =
			{
			},
			itemSpawns =
			{
			},
			rewards =
			{
				{ rewardType = "faction", faction = "rebel", amount = 20 },
			}
		},
		{
			missionType = "assassinate",
			primarySpawns =
			{
				{ npcTemplate = "scout_trooper", npcName = "" }
			},
			secondarySpawns =
			{
				{ npcTemplate = "swamp_trooper", npcName = "" },
				{ npcTemplate = "swamp_trooper", npcName = "" },
				{ npcTemplate = "swamp_trooper", npcName = "" },
				{ npcTemplate = "swamp_trooper", npcName = "" }
			},
			itemSpawns =
			{
			},
			rewards =
			{
				{ rewardType = "faction", faction = "rebel", amount = 25 },
			}
		}
	}

npcMapCaptainEso =
	{
		{
			spawnData = { npcTemplate = "captain_eso", x = 1593.0, z = 102.0, y = 1535.1, direction = 160, cellID = 0, position = STAND },
			npcNumber = 1,
			stfFile = "@static_npc/yavin/eso",
			missions = captain_eso_missions
		},
	}

CaptainEso = ThemeParkLogic:new {
	npcMap = npcMapCaptainEso,
	className = "CaptainEso",
	screenPlayState = "captain_eso_tasks",
	planetName = "yavin4",
	distance = 700,
	faction = FACTIONREBEL
}

registerScreenPlay("CaptainEso", true)

captain_eso_mission_giver_conv_handler = mission_giver_conv_handler:new {
	themePark = CaptainEso
}
captain_eso_mission_target_conv_handler = mission_target_conv_handler:new {
	themePark = CaptainEso
}
