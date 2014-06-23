raxa_binn_missions =
  {
    {
      missionType = "assassinate",
      primarySpawns =
      {
        { npcTemplate = "raxa_stormtrooper_squad_leader", planetName = "rori", npcName = "Stormtrooper Squad Leader" }
      },
      secondarySpawns = {
        { npcTemplate = "raxa_stormtrooper", planetName = "rori", npcName = "" },
        { npcTemplate = "raxa_stormtrooper", planetName = "rori", npcName = "" },
        { npcTemplate = "raxa_stormtrooper", planetName = "rori", npcName = "" }
      },
      itemSpawns = {},
      rewards =
      {
        { rewardType = "credits", amount = 100 },
        { rewardType = "faction", faction = "rebel", amount = 20 },
      }
    },
    {
      missionType = "escort",
      primarySpawns =
      {
        { npcTemplate = "raxa_rebel_scout", planetName = "rori", npcName = "Rebel Scout" }
      },
      secondarySpawns = {
        { npcTemplate = "raxa_stormtrooper_commando", planetName = "rori", npcName = "" },
        { npcTemplate = "raxa_stormtrooper_commando", planetName = "rori", npcName = "" }
      },
      itemSpawns = {},
      rewards =
      {
        { rewardType = "credits", amount = 100 },
        { rewardType = "faction", faction = "rebel", amount = 20 },
      }
    },
    {
      missionType = "assassinate",
      primarySpawns =
      {
        { npcTemplate = "raxa_stormtrooper_squad_leader", planetName = "rori", npcName = "Stormtrooper Squad Leader" }
      },
      secondarySpawns = {
        { npcTemplate = "raxa_stormtrooper", planetName = "rori", npcName = "" },
        { npcTemplate = "raxa_stormtrooper", planetName = "rori", npcName = "" },
        { npcTemplate = "raxa_stormtrooper", planetName = "rori", npcName = "" },
        { npcTemplate = "raxa_stormtrooper", planetName = "rori", npcName = "" },
        { npcTemplate = "raxa_stormtrooper", planetName = "rori", npcName = "" },
        { npcTemplate = "raxa_stormtrooper", planetName = "rori", npcName = "" }
      },
      itemSpawns = {},
      rewards =
      {
        { rewardType = "credits", amount = 200 },
        { rewardType = "faction", faction = "rebel", amount = 30 },
      }
    },
  }

npcMapRaxaBinn =
  {
    {
      spawnData = { planetName = "rori", npcTemplate = "raxa_binn", x = -4.0, z = 0.1, y = -4.2, direction = 140, cellID = 4505669, position = SIT },
      worldPosition = { x = 3643, y = -6465 },
      npcNumber = 1,
      stfFile = "@static_npc/rori/rori_rebeloutpost_raxa_binn",
      missions = raxa_binn_missions
    },

  }

RaxaBinn = ThemeParkLogic:new {
  numberOfActs = 1,
  npcMap = npcMapRaxaBinn,
  className = "RaxaBinn",
  screenPlayState = "raxa_binn_quest",
  distance = 400,
  faction = FACTIONREBEL
}

registerScreenPlay("RaxaBinn", true)

raxa_binn_mission_giver_conv_handler = mission_giver_conv_handler:new {
  themePark = RaxaBinn
}
raxa_binn_mission_target_conv_handler = mission_target_conv_handler:new {
  themePark = RaxaBinn
}