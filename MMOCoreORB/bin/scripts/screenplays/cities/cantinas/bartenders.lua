BartendersScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "BartendersScreenPlay",

	CHAT_LISTEN_DELAY = 10000,

	-- {"bartender_name", "zoneName", cellID}
	bartenderSpawns = {
		{"wuher", "tatooine", 1082877}, -- Tatooine Mos Eisely
		{"bartender", "tatooine", 1256058}, -- Tatooine Mos Espa
		{"bartender", "tatooine", 1134560}, -- Tatooine Wayfar
		{"bartender", "tatooine", 1028647}, -- Tatooine Bestine
		{"bartender", "lok", 8145378}, -- Lok Nym's Stronghold
		{"bartender", "naboo", 91}, -- Naboo Theed
		{"bartender", "naboo", 64}, -- Naboo Kaadara
		{"bartender", "naboo", 5}, -- Naboo Keren
		{"bartender", "naboo", 111}, -- Naboo Moenia
		{"bartender", "corellia", 8105496}, -- Corellia Coronet
		{"bartender", "corellia", 3005697}, -- Corellia Vreni Island
		{"bartender", "corellia", 3375355}, -- Corellia Bela Vistal
		{"bartender", "corellia", 2625355}, -- Corellia Tyrena
		{"bartender", "corellia", 3005399}, -- Corellia Kor Vella
		{"bartender", "corellia", 3075429}, -- Corellia Doaba Guerfel
		{"bartender", "talus", 3175391}, -- Talus Dearic
		{"bartender", "talus", 4265375}, -- Talus Nashal
	},

	patrolLocations = {
		{-11.1, -0.9, 2.4},
		{3.0, -0.9, 3.4},
		{7.2, -0.9, 2.6},
		{7.5, -0.9, -1.5},
		{8.2, -0.9, 1.4},
		{6.7, -0.9, -2.2},
		{7.2, -0.9, -1.8},
		{6.3, -0.9, -2.3},
		{1.4, -0.9, -2.4},
		{-7.2, -0.9, -2.2},
		{-10.5, -0.9, -2.2},
	},

	facingPlayerAnimations = {
		"worship",
		"greet",
		"nod_head_multiple",
		"nod",
		"applause_excited",
		"slow_down",
		"manipulate_medium",
		"point_left",
		"point_right",
		"beckon",
		"stretch",
		"bounce",
		"applause_polite",
		"2shot4u",
		"expect_tip",
		"he_dies",
		"he_lives",
		"hold_nose",
		"rub_chin_thoughtful",
		"thank",
		"udaman",
		"tiphat",
		"wtf",
		"entertained",
		"thumbs_up_double_fisted",
	},

	makeDrinkAnimations = {
		"tap_foot",
		"look_right",
		"look_left",
		"manipulate_high",
		"manipulate_medium",
		"scratch_head",
		"slump_head",
		"smell_armpit",
	},

	rumorWords = {"jedi", "spice", "pixie", "muon", "slice", "smuggler", "frs", "rebel", "rebellion", "giggledust", "neutron"},
}

registerScreenPlay("BartendersScreenPlay", true)

function BartendersScreenPlay:start()
	self:spawnBartenders()
end

function BartendersScreenPlay:spawnBartenders()
	local x = self.patrolLocations[1][1]
	local z = self.patrolLocations[1][2]
	local y = self.patrolLocations[1][3]

	local bartenders = self.bartenderSpawns

	for i = 1, #bartenders, 1 do
		local bartenderTable = bartenders[i]

		--print("BartendersScreenPlay:spawnBartenders -- spawning: " ..  bartenderTable[1] .. " on " .. bartenderTable[2] .. " Cell ID: " .. bartenderTable[3])

		local pNpc = spawnMobile(bartenderTable[2], bartenderTable[1], -1, x, z, y, 0, bartenderTable[3])

		if (pNpc ~= nil) then
			local npcID = SceneObject(pNpc):getObjectID()

			AiAgent(pNpc):addCreatureFlag(AI_STATIONARY)
			AiAgent(pNpc):setMovementState(AI_PATROLLING)

			createEvent(15 * 1000, "BartendersScreenPlay", "assignPatrolPoint", pNpc, "")

			-- Create Observers for arrival and chat
			createObserver(DESTINATIONREACHED, "BartendersScreenPlay", "reachedBartenderPoint", pNpc)

			-- 15% chance to be a rumor bartender
			if (getRandomNumber(100) < 99) then
				createObserver(SPATIALCHAT, "BartendersScreenPlay", "chatListen", pNpc)

				writeData(npcID .. ":BartenderRumorFlag:", 1)

				local newStamp = getTimestampMilli() + self.CHAT_LISTEN_DELAY
				writeData(npcID .. ":BartenderChatListen:", newStamp)
			end
		end
	end
end

function BartendersScreenPlay:chatListen(pNpc, pChatMessage, playerID)
	if (pNpc == nil or pChatMessage == nil) then
		return 1
	end

	--print("BartendersScreenPlay:chatListen for " .. SceneObject(pNpc):getDisplayedName() .. " Player ID: " .. playerID)

	local pObject = getSceneObject(playerID)

	if (pObject == nil or not SceneObject(pObject):isPlayerCreature()) then
		return 0
	end

	local npcID = SceneObject(pNpc):getObjectID()
	local hasRumors = readData(npcID .. ":BartenderPlayerRumors:")

	if (hasRumors == 1) then
		return 0
	end

	local currentTime = getTimestampMilli()
	local lastObservation = readData(npcID .. ":BartenderChatListen:")

	if (lastObservation > currentTime) then
		return 0
	end

	local spatialMsg = getChatMessage(pChatMessage)

	if (spatialMsg == nil or spatialMsg == "") then
		return 0
	end

	local newStamp = currentTime + self.CHAT_LISTEN_DELAY

	deleteData(npcID .. ":BartenderChatListen:")
	writeData(npcID .. ":BartenderChatListen:", newStamp)

	local messageTable = {}
	for word in spatialMsg:gmatch("%w+") do table.insert(messageTable, word) end

	local tableSize = #messageTable

	if (tableSize < 10 or tableSize > 60) then
		return 0
	end

	local foundWord = false

	for i = 1, tableSize, 1 do
		local checkWord = messageTable[i]

		for j = 1, #self.rumorWords, 1 do
			local rumorWord = self.rumorWords[j]

			if (checkWord == rumorWord) then
				foundWord = true
				goto skip
			end
		end

		::skip::
	end

	if (foundWord == false) then
		return 0
	end

	spatialChat(pNpc, "Ya never know what ya'll hear 'round these parts...")

	writeStringData(npcID .. ":BartenderRumorMessage:", spatialMsg)
	writeStringData(npcID .. ":BartenderRumorPlayer:", CreatureObject(pObject):getFirstName())

	writeData(npcID .. ":BartenderPlayerRumors:", 1)

	return 0
end

function BartendersScreenPlay:reachedBartenderPoint(pNpc)
	if (pNpc == nil) then
		return 1
	end

	local randomTime = getRandomNumber(15, 45)

	-- schedule next movement
	createEvent(randomTime * 1000, "BartendersScreenPlay", "assignPatrolPoint", pNpc, "")

	-- Schedule an animation and bartender direction
	createEvent(5 * 1000, "BartendersScreenPlay", "doAnimation", pNpc, "")
	createEvent(2 * 1000, "BartendersScreenPlay", "updateDirection", pNpc, "")

	return 0
end

function BartendersScreenPlay:assignPatrolPoint(pNpc)
	if (pNpc == nil) then
		return
	end

	local randomPoint = getRandomNumber(#self.patrolLocations)
	local point = self.patrolLocations[randomPoint]
	local parentID = SceneObject(pNpc):getParentID()

	AiAgent(pNpc):setNextPosition(point[1], point[2], point[3], parentID)
end

function BartendersScreenPlay:updateDirection(pNpc)
	if (pNpc == nil) then
		return
	end

	local direction = getRandomNumber(360)
	local positionX = SceneObject(pNpc):getPositionX()
	local positionY = SceneObject(pNpc):getPositionY()

	if (positionX < -10.5) then
		direction = 90
	elseif (positionX > 7.3 and positionY < 3.0) then
		-- Front End of bar
		if (getRandomNumber(100) < 30) then
			direction = 270
		else
			direction = 90
		end
	elseif (positionY > 2.1) then
		-- Right side of bar, choose to face players or bar
		if (getRandomNumber(100) < 30) then
			direction = 180
		else
			direction = 0
		end
	else
		-- Left Side of Bar
		if (getRandomNumber(100) < 30) then
			direction = 0
		else
			direction = 180
		end
	end

	SceneObject(pNpc):updateDirection(math.rad(direction))
end

function BartendersScreenPlay:doAnimation(pNpc)
	if (pNpc == nil) then
		return
	end

	local animation = ""
	local facingPlayers = true

	local direction = CreatureObject(pNpc):getDirectionAngle()
	local positionX = SceneObject(pNpc):getPositionX()
	local positionY = SceneObject(pNpc):getPositionY()

	if (positionX < -10.5) then
		-- Back of End back
		facingPlayers = false
	elseif (positionX > 6.5 and positionY < 3.0) then
		-- Front End of bar
		if (direction > 260 and direction < 280) then
			facingPlayers = false
		end
	elseif (positionY > 2.1) then
		-- Right side of bar, choose to face players or bar
		if (direction > 175 and direction < 190) then
			facingPlayers = false
		end
	else
		-- Left Side of Bar
		if (direction > -10 and direction < 10) then
			facingPlayers = false
		end
	end

	if (facingPlayers) then
		local randomFacingAnim = getRandomNumber(#self.facingPlayerAnimations)
		animation = self.facingPlayerAnimations[randomFacingAnim]

		--print("facing players animation")
	else
		local randomBarAnim = getRandomNumber(#self.makeDrinkAnimations)
		animation = self.makeDrinkAnimations[randomBarAnim]

		--print("facing bar animation")
	end

	CreatureObject(pNpc):doAnimation(animation)
end
