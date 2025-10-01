-- Space Screenplays & Conversation Handlers

includeFile("space/SpaceQuestLogic.lua")
includeFile("space/SpaceAssassinateScreenplay.lua")
includeFile("space/SpaceDestroyScreenplay.lua")
includeFile("space/SpaceDutyDestroyScreenplay.lua")
includeFile("space/SpaceEscortScreenplay.lua")
includeFile("space/SpaceInspectScreenplay.lua")
includeFile("space/SpaceDutyEscortScreenplay.lua")
includeFile("space/SpacePatrolScreenplay.lua")
includeFile("space/SpaceSurpriseAttackScreenplay.lua")

includeFile("space/chassis_dealer.lua")

--[[
	Space Stations
]]

includeFile("space/spacestations/spacestation.lua")
includeFile("space/spacestations/spacestation_corellia_conv_handler.lua")
includeFile("space/spacestations/spacestation_dantooine_conv_handler.lua")
includeFile("space/spacestations/spacestation_dathomir_conv_handler.lua")
includeFile("space/spacestations/spacestation_endor_conv_handler.lua")
includeFile("space/spacestations/spacestation_imperial_conv_handler.lua")
includeFile("space/spacestations/spacestation_lok_conv_handler.lua")
includeFile("space/spacestations/spacestation_naboo_conv_handler.lua")
includeFile("space/spacestations/spacestation_rebel_conv_handler.lua")
includeFile("space/spacestations/spacestation_rori_conv_handler.lua")
includeFile("space/spacestations/spacestation_talus_conv_handler.lua")
includeFile("space/spacestations/spacestation_tatooine_conv_handler.lua")
includeFile("space/spacestations/spacestation_yavin4_conv_handler.lua")


--[[
	Ship Components
]]

includeFile("space/ship_components/escape_pod_hatch_menu_component.lua")
includeFile("space/ship_components/pilot_seat_menu_component.lua")
includeFile("space/ship_components/ship_operations_menu_component.lua")
includeFile("space/ship_components/ship_turret_menu_component.lua")
includeFile("space/ship_components/ship_interior_component_menu_component.lua")


--[[
	Conversation Handlers
]]

includeFile("space/conversations/defaultShipConvoHandler.lua")
includeFile("space/conversations/chassisDealerConvoHandler.lua")

-- Greeters

-- Theed
includeFile("space/conversations/greeters/kultonWoodleConvoHandler.lua")
includeFile("space/conversations/greeters/j1p0ConvoHandler.lua")

-- Mos Eisley
includeFile("space/conversations/greeters/vincieKalhoonConvoHandler.lua")
includeFile("space/conversations/greeters/moochDavoneyConvoHandler.lua")
includeFile("space/conversations/greeters/guilloParootchieConvoHandler.lua")

-- Coronet
includeFile("space/conversations/greeters/ioTsomcrenConvoHandler.lua")
includeFile("space/conversations/greeters/ralMundiConvoHandler.lua")
includeFile("space/conversations/greeters/tarthJaxxConvoHandler.lua")

-- Mining Outpost, Dantooine
includeFile("space/conversations/greeters/raneYarrowConvoHandler.lua")
includeFile("space/conversations/greeters/fernYarrowConvoHandler.lua")
includeFile("space/conversations/greeters/kessYarrowConvoHandler.lua")

-- Squadrons


-- Neutral
includeFile("space/conversations/neutral/gilBurtinConvoHandler.lua")

-- Corsec
includeFile("space/CorsecSquadronScreenplay.lua")
includeFile("space/conversations/neutral/corsec_squadron/rheaConvoHandler.lua")
includeFile("space/conversations/neutral/corsec_squadron/rikkhConvoHandler.lua")

-- Smuggler
includeFile("space/SmugglerSquadronScreenplay.lua")

-- RSF
includeFile("space/RsfSquadronScreenplay.lua")


-- Rebel
includeFile("space/conversations/rebel/jPaiBrekConvoHandler.lua")

-- Crimson Phoenix
includeFile("space/CrimsonPhoenixSquadronScreenplay.lua")

-- Havoc
includeFile("space/HavocSquadronScreenplay.lua")

-- Vortex
includeFile("space/VortexSquadronScreenplay.lua")


-- Imperial
includeFile("space/conversations/imperial/imperialBrokerConvoHandler.lua")

-- Black Epsilon
includeFile("space/BlackEpsilonSquadronScreenplay.lua")

-- Imperial Inquisition
includeFile("space/InquisitionSquadronScreenplay.lua")

-- Storm
includeFile("space/StormSquadronScreenplay.lua")


-- Spawning Sub Folder
includeFile("space/spawning/screenplays.lua")
