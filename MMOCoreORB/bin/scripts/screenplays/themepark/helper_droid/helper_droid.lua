local ObjectManager = require("managers.object.object_manager")

HelperDroid = ScreenPlay:new {
	professions = {"brawler", "marksman", "scout", "artisan", "medic", "entertainer"},
	skillStrings = {"combat_brawler_novice", "combat_marksman_novice", "outdoors_scout_novice", "crafting_artisan_novice", "science_medic_novice", "social_entertainer_novice"},

	droidGreetings = {
		"@new_player:droid_greeting_begin_01",
		"@new_player:droid_greeting_begin_02",
		"@new_player:droid_greeting_begin_03",
	},

	droidSounds = {
		"sound/dro_astromech_converse.snd",
		"sound/dro_astromech_whistle.snd",
		"sound/dro_astromech_ok.snd",
	},
}

registerScreenPlay("HelperDroid", false)

function HelperDroid:spaceInformation(pDroid, pPlayer, selection)
	if (pDroid == nil or pPlayer == nil) then
		return
	end

	self:playDroidSound(pPlayer)

	local sui = SuiMessageBox.new("HelperDroid", "noCallback")
	sui.setTitle(SceneObject(pDroid):getCustomObjectName())
	sui.setProperty("", "Size", "500,200")
	sui.setProperty("btnCancel", "Visible", "false")
	sui.setForceCloseDistance(10)

	if (selection == "findShip") then
		sui.setPrompt("@new_player:space_info_how_to_find_ship")
	elseif (selection == "checkEmail") then
		sui.setPrompt("@new_player:space_info_how_to_check_email")
	elseif (selection == "travel") then
		sui.setPrompt("@new_player:space_info_how_to_travel")
	elseif (selection == "makeMoney") then
		sui.setPrompt("@new_player:space_info_how_to_make_money")
	end

	sui.sendTo(pPlayer)
end

function HelperDroid:helperInformation(pDroid, pPlayer, selection)
	if (pDroid == nil or pPlayer == nil) then
		return
	end

	self:playDroidSound(pPlayer)

	if (selection == "general") then
		CreatureObject(pPlayer):sendOpenHolocronToPageMessage("WelcomeToSWG")
	elseif (selection == "travel") then
		CreatureObject(pPlayer):sendOpenHolocronToPageMessage("Navigation.LongDistanceTravel")
	elseif (selection == "cloning") then
		CreatureObject(pPlayer):sendOpenHolocronToPageMessage("ImportantBuildings.CloningFacility")
	elseif (selection == "vehicle") then
		CreatureObject(pPlayer):sendOpenHolocronToPageMessage("WelcomeToSWG")
	end
end

function HelperDroid:noCallback(pPlayer, pSui, eventIndex, ...)
end

function HelperDroid:professionQuest(pDroid, pPlayer, profession)
	if (pDroid == nil or pPlayer == nil) then
		return
	end

	self:playDroidSound(pPlayer)

	--HelperDroidQuest:professionQuestSui(pDroid, pPlayer, profession)
end

function HelperDroid:greetPlayer(pPlayer, pDroid)
	if (pPlayer == nil or pDroid == nil) then
		return
	end

	self:playDroidSound(pPlayer)

	local playerID = SceneObject(pPlayer):getObjectID()
	local droidID = SceneObject(pDroid):getObjectID()

	writeData(playerID .. ":HelperDroidID:", droidID)

	local sui = SuiListBox.new("HelperDroid", "greetingCallback")
	sui.setTitle(SceneObject(pDroid):getCustomObjectName())
	sui.setProperty("", "Size", "500,200")
	sui.setForceCloseDistance(10)

	local randomGreeting = getRandomNumber(3)
	local promptStart = self.droidGreetings[randomGreeting]
	local playerName = " \\#pcontrast1 " .. CreatureObject(pPlayer):getFirstName() .. "\\#.,"
	local promptEnd = "@new_player:droid_greeting_end"

	local firstTime = true
	local professions = self.professions
	local totalProfs = 0
	local playerProfs = {}

	-- Check players current professions to list quest options
	for i = 1, #professions, 1 do
		local string = self.skillStrings[i]

		if (CreatureObject(pPlayer):hasSkill(string)) then
			local profession = professions[i]
			local questStatus = readData(playerID .. ":" .. profession .. ":HelperDroid:questStatus:")

			if (questStatus == 0) then
				firstTime = false
			end

			totalProfs = totalProfs + 1
			playerProfs[totalProfs] = profession

			profession = profession:gsub("^%l", string.upper)
			sui.add(profession, "")
		end
	end

	writeStringVectorSharedMemory(playerID .. ":HelperDroid:playerProfessions:", playerProfs)

	if (not firstTime) then
		promptEnd = "@new_player:droid_periodic_check_end"
	end

	local prompt = promptStart ..  playerName .. " " .. promptEnd
	sui.setPrompt(prompt)

	sui.sendTo(pPlayer)
end

function HelperDroid:greetingCallback(pPlayer, pSui, eventIndex, args)
	if (pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		deleteData(playerID .. ":HelperDroidID:")
		return
	end

	local droidID = readData(playerID .. ":HelperDroidID:")
	local pDroid = getSceneObject(droidID)
	local playerProfs = readStringVectorSharedMemory(playerID .. ":HelperDroid:playerProfessions:")

	local argNum = #playerProfs - tonumber(args)
	local playerProf = playerProfs[argNum]

	deleteData(playerID .. ":HelperDroidID:")
	deleteStringVectorSharedMemory(playerID .. ":HelperDroid:playerProfessions:")

	if (pDroid ~= nil) then
		--HelperDroidQuest:professionQuestSui(pDroid, pPlayer, playerProf)
	end
end

function HelperDroid:skillTrained(pDroid, pPlayer, skill)
	if (pDroid == nil or pPlayer == nil or skill == "") then
		return
	end

	local profession = ""

	for i = 1, #self.skillStrings, 1 do
		local string = self.skillStrings[i]

		if (string == skill) then
			profession = self.professions[i]

			local message = "@new_player:" .. profession .. "_added"

			self:playDroidSound(pPlayer)
			spatialChat(pDroid, message)
			break
		end
	end
end

function HelperDroid:playDroidSound(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local randSound = getRandomNumber(3)
	local sound = self.droidSounds[randSound]

	CreatureObject(pPlayer):playMusicMessage(sound)
end
