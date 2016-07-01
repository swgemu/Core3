herald_dathomir_leandra_missions =
  {
    {
      missionType = "recon",
      reconTarget = { waypointTemplate = "waypoint_name_1", waypointName = "Nightsister Cave", planetName = "dathomir", waypointX = -1200, waypointY = 6254 },
      rewards =
      {
        { rewardType = "faction", faction = "nightsister", amount = 5 },
      }
    },
  }

npcMapHeraldDathomirLeandra =
  {
    {
      spawnData = { planetName = "dathomir", npcTemplate = "herald_dathomir_leandra", x = -4082, z = 132.7, y = -210, direction = -25, cellID = 0, position = STAND },
      worldPosition = { x = -4082, y = -210 },
      npcNumber = 1,
      stfFile = "@spawning/static_npc/herald_dathomir_nsister_cave_leandra.stf",
      missions = herald_dathomir_leandra_missions
    },
  }

HeraldDathomirLeandra = ThemeParkLogic:new {
  numberOfActs = 1,
  npcMap = npcMapHeraldDathomirLeandra,
  className = "HeraldDathomirLeandra",
  screenPlayState = "herald_dathomir_leandra_quest",
}

registerScreenPlay("HeraldDathomirLeandra", true)

herald_dathomir_leandra_mission_giver_conv_handler = mission_giver_conv_handler:new {
  themePark = HeraldDathomirLeandra
}
herald_dathomir_mission_target_conv_handler = mission_target_conv_handler:new {
  themePark = HeraldDathomirLeandra
}