local ObjectManager = require("managers.object.object_manager")

TatooineJabbasPalaceMobsScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	bomar_monks = {
		{"bomarr_monk", 60, -24, 6.6, 86, 180, 1177490,"Bomarr Monk","bmonk1"},
		{"bomarr_monk", 60, -2, 4, 104, 85, 1177467,"Bomarr Monk","bmonk2"},
		{"bomarr_monk", 60, -18, 9, 73, 196, 1177489,"Bomarr Monk","bmonk3"},
		{"bomarr_monk", 60, 7, 6, 50, 64, 1177487,"Bomarr Monk","bmonk4"},
		{"bomarr_monk", 60, 24, .2, -9, 180, 1177484,"Bomarr Monk","bmonk5"},
		{"bomarr_monk", 60, -18, 7, 9, 207, 1177501,"Bomarr Monk","bmonk6"},
	},

	gamorrean_guards = {
		{"gamorrean_guard", 60, -0.3, 5.8, 87.2, 93, 1177469, "Ortugg", "guard1"},
		{"gamorrean_guard", 60, -11, 5.8, 88, 148, 1177469, "Rogua","guard2"},
		{"gamorrean_guard", 60, -11, 5.8, 88, 180, 1177469, "Gartogg","guard3"},
		{"gamorrean_guard", 60, -1, 5.8, 98, 180, 1177469, "Torrug","guard4"},
		{"gamorrean_guard", 60, 10, 5.8, 71, 180, 1177470, "Grogur", "guard5"},
		{"gamorrean_guard", 60, -30.78, 0.2, 82.64, 180, 1177476, "Urgott","guard6"},
		{"gamorrean_guard", 60, -2.04, 0.2, 82.61, 180, 1177480, "Artogg","guard7"},
		{"gamorrean_guard", 60, -13, 3, 59, 180, 1177474, "Ogtur","guard8"},
		{"gamorrean_guard", 60, -37, 5, 46, 180, 1177486, "Rautog","guard9"},
		{"gamorrean_guard", 60, -25, 3.6, 34, 180, 1177487,  "Agtor","guard10"},
		{"gamorrean_guard", 60, 6, 4, 26, 180, 1177487, "Torgau","guard11"},
		{"gamorrean_guard", 60, 22, -9, 48, 180, 1177502, "Ugtaur","guard12"},
		{"gamorrean_guard", 60, 0.14, 2, 53.1, 180, 1177487,  "Gurgot","guard13"},
	},

	droid_spawns = {
		{"r2", 60, 19.73, 0.2, 90.51, 0, 1177479, "R2-E7", "droid1"},
		{"eg6_power_droid", 60, 17.42, 0.2, 81.22, 0, 1177479, "EG6-M5","droid4"},
		{"eg6_power_droid", 60, 43.29, 0.2, 7.14, 0, 1177499, "EG6-M9", "droid6"},
	},

	jabba_band = {
		{"sy_snootles", 60, -9, 2, 37, 0, 1177487, "Sy Snootles", "themepark_sy_snootles"},
		{"max_rebo", 60, -11, 2, 36, 0, 1177487, "Max Rebo","themepark_music_3"},
		{"droopy_mccool", 60, -13, 2, 37, 0, 1177487, "Droopy McCool","themepark_music_3"},
		{"oola", 60, -10, 2, 43, 180, 1177487, "Oola", "themepark_oola"}
	},

}

registerScreenPlay("TatooineJabbasPalaceMobsScreenPlay", true)

function TatooineJabbasPalaceMobsScreenPlay:start()
	if (isZoneEnabled("tatooine")) then
		spawnSceneObject("tatooine","object/tangible/instrument/organ_max_rebo.iff", -11, 2, 36, 1177487, 0.0707,0,0.0707,0)
		--spawnSceneObject("tatooine", "object/tangible/instrument/instrument_organ_max_rebo.iff", -11.1, 2, 36.2, 1177487, 0.9974847113288691, 0, -0.07088194879630508, 0)
		self:spawnMobiles()
		self:spawnStatics()
	end
end

function TatooineJabbasPalaceMobsScreenPlay:spawnStatics()
	spawnMobile("tatooine", "beissa", 60, 8.11982, 2, 34.2394, 295, 1177487)
	spawnMobile("tatooine", "ev_9d9", 60, 24.47, 0.2, 87.86, 312, 1177479)
	spawnMobile("tatooine", "boba_fett",60,-1,3,31,322.95,1177487)
	spawnMobile("tatooine", "salacious_crumb",60,-16.29,2.81087,42.54,86.0692,1177487)
	spawnMobile("tatooine", "jabba_the_hutt",60,-16.65,2.81087,45,106.884,1177487)
	spawnMobile("tatooine", "le_repair_droid", 60, 23.67, 0.2, 76.43, 130.65, 1177479)
	spawnMobile("tatooine", "malakili", 60, 19, -11, 42, 23.355, 1177502)
	spawnMobile("tatooine", "jabba_rancor", 60, 3.93472, -10.9823, 45.0053, 101.285, 1177503)
	spawnMobile("tatooine", "protocol_droid_3po_red", 60, 10.71, 0.2, 84.27, 216, 1177479)
	spawnMobile("tatooine", "ra7_bug_droid", 60, 13.33, 0.2, 88.72, 111.64,1177479)

	local pNpc = spawnMobile("tatooine", "outlaw", 300, 9.0, 5.8, 73.0, 153, 1177470)
	self:setMoodString(pNpc, "angry")

	pNpc = spawnMobile("tatooine", "commoner_naboo", 60, -33.8, 0.1, 76.6, 329, 1177491)
	self:setMoodString(pNpc, "nervous")

	pNpc = spawnMobile("tatooine", "commoner_tatooine", 60, -37.4, 0.1, 76.9, 242, 1177492)
	self:setMoodString(pNpc, "worried")

	pNpc = spawnMobile("tatooine", "commoner_tatooine", 60, -34.5, 0.1, 88.2, 228, 1177493)
	self:setMoodString(pNpc, "nervous")

	pNpc = spawnMobile("tatooine", "commoner_tatooine", 60, -38.7, 0.1, 88.2, 230, 1177494)
	self:setMoodString(pNpc, "nervous")

	pNpc = spawnMobile("tatooine", "commoner_tatooine", 60, -10.1, 0.1, 77.5, 332, 1177495)
	self:setMoodString(pNpc, "nervous")

	pNpc = spawnMobile("tatooine", "commoner_tatooine", 60, -13.6, 0.1, 77.5, 111, 1177496)
	self:setMoodString(pNpc, "bored")

	pNpc = spawnMobile("tatooine", "commoner_tatooine", 60, -10.9, 0.1, 87.5, 204, 1177497)
	self:setMoodString(pNpc, "angry")

	pNpc = spawnMobile("tatooine", "commoner_tatooine", 60, -15.4, 0.1, 87.7, 42, 1177498)
	self:setMoodString(pNpc, "nervous")

	pNpc = spawnMobile("tatooine", "fringer", 300, -8.7, 2.0, 49.6, 347, 1177487)
	createEvent(5000, "TatooineJabbasPalaceMobsScreenPlay", "palaceConverse", pNpc, "")

	pNpc = spawnMobile("tatooine", "jawa", 300, -23.0, 3.0, 59.0, 0, 1177474)
	createEvent(5000, "TatooineJabbasPalaceMobsScreenPlay", "palaceConverseJawa", pNpc, "")

	pNpc = spawnMobile("tatooine", "jawa", 300, -38.0, 3.0, 53.0, 46, 1177481)
	createEvent(5000, "TatooineJabbasPalaceMobsScreenPlay", "palaceConverseJawa", pNpc, "")

	pNpc = spawnMobile("tatooine", "jawa", 300, -23.0, 3.0, 61.0, 180, 1177474)
	createEvent(5000, "TatooineJabbasPalaceMobsScreenPlay", "palaceConverseJawa", pNpc, "")

	pNpc = spawnMobile("tatooine", "jawa", 300, -1.0, 3.0, 25.0, -23, 1177487)
	createEvent(5000, "TatooineJabbasPalaceMobsScreenPlay", "palaceConverseJawa", pNpc, "")

	pNpc = spawnMobile("tatooine", "jawa", 300, -8.0, 3.0, 20.0, -25, 1177501)
	createEvent(5000, "TatooineJabbasPalaceMobsScreenPlay", "palaceConverseJawa", pNpc, "")

	pNpc = spawnMobile("tatooine", "jawa", 300, -18.0, 3.0, 13.0, 116, 1177501)
	createEvent(5000, "TatooineJabbasPalaceMobsScreenPlay", "palaceConverseJawa", pNpc, "")

	pNpc = spawnMobile("tatooine", "jawa", 300, 8.7, 2.0, 23.6, 16, 1177487)
	createEvent(5000, "TatooineJabbasPalaceMobsScreenPlay", "palaceConverseJawa", pNpc, "")

	pNpc = spawnMobile("tatooine", "jawa", 300, 9.2, 2.0, 25.2, 196, 1177487)
	createEvent(5000, "TatooineJabbasPalaceMobsScreenPlay", "palaceConverseJawa", pNpc, "")

	pNpc = spawnMobile("tatooine", "jawa", 300, 29.4, 0.2, 46.6, 179, 1177472)
	createEvent(5000, "TatooineJabbasPalaceMobsScreenPlay", "palaceConverseJawa", pNpc, "")

	pNpc = spawnMobile("tatooine", "jawa", 300, 29.4, 0.2, 45.4, 359, 1177472)
	createEvent(5000, "TatooineJabbasPalaceMobsScreenPlay", "palaceConverseJawa", pNpc, "")

	pNpc = spawnMobile("tatooine", "roughneck", 300, -9.8, 3.0, 59.7, 274, 1177474)
	createEvent(5000, "TatooineJabbasPalaceMobsScreenPlay", "palaceConverse", pNpc, "")

	pNpc = spawnMobile("tatooine", "roughneck", 300, -5.88, 2.0, 43.1, 8, 1177487)
	createEvent(5000, "TatooineJabbasPalaceMobsScreenPlay", "palaceConverse", pNpc, "")

	pNpc = spawnMobile("tatooine", "roughneck", 300, -5.72, 2.0, 44.1, 188, 1177487)
	createEvent(5000, "TatooineJabbasPalaceMobsScreenPlay", "palaceConverse", pNpc, "")

	pNpc = spawnMobile("tatooine", "scoundrel", 300, 5.0, 2.0, 44.0, 0, 1177487)
	createEvent(5000, "TatooineJabbasPalaceMobsScreenPlay", "palaceConverse", pNpc, "")

	pNpc = spawnMobile("tatooine", "scoundrel", 300, -14.3, 2.0, 52.1, 264, 1177487)
	createEvent(5000, "TatooineJabbasPalaceMobsScreenPlay", "palaceConverse", pNpc, "")

	pNpc = spawnMobile("tatooine", "slicer", 60, -9.0, 2.0, 51.0, 167, 1177487)
	createEvent(5000, "TatooineJabbasPalaceMobsScreenPlay", "palaceConverse", pNpc, "")

	pNpc = spawnMobile("tatooine", "spacer", 300, -9.0, 3.0, 25.0, 303, 1177487)
	createEvent(5000, "TatooineJabbasPalaceMobsScreenPlay", "palaceConverse", pNpc, "")

	pNpc = spawnMobile("tatooine", "thug", 300, -1.6, 3.0, 26.2, 151, 1177487)
	createEvent(5000, "TatooineJabbasPalaceMobsScreenPlay", "palaceConverse", pNpc, "")

	pNpc = spawnMobile("tatooine", "thug", 300, -8.4, 3.0, 21.2, 160, 1177487)
	createEvent(5000, "TatooineJabbasPalaceMobsScreenPlay", "palaceConverse", pNpc, "")

	pNpc = spawnMobile("tatooine", "thug", 300, 1.1, 2.0, 36.7, 180, 1177487)
	createEvent(5000, "TatooineJabbasPalaceMobsScreenPlay", "palaceConverse", pNpc, "")

	pNpc = spawnMobile("tatooine", "thug", 300, -15.8, 2.0, 51.9, 84, 1177487)
	createEvent(5000, "TatooineJabbasPalaceMobsScreenPlay", "palaceConverse", pNpc, "")

	pNpc = spawnMobile("tatooine", "thug", 300, -9.9, 3.0, 25.6, 123, 1177487)
	createEvent(5000, "TatooineJabbasPalaceMobsScreenPlay", "palaceConverse", pNpc, "")

	pNpc = spawnMobile("tatooine", "thug", 300, 1.1, 2.0, 35.1, 0, 1177487)
	createEvent(5000, "TatooineJabbasPalaceMobsScreenPlay", "palaceConverse", pNpc, "")

	pNpc = spawnMobile("tatooine", "wastrel", 300, 5.1, 2.0, 45.5, 180, 1177487)
	createEvent(5000, "TatooineJabbasPalaceMobsScreenPlay", "palaceConverse", pNpc, "")

	spawnMobile("tatooine", "junk_ollobo", 0, -6.35875, 0.2, 134.272, 9.7, 1177466)
end


function TatooineJabbasPalaceMobsScreenPlay:spawnMobiles()

	for i,v in ipairs(self.jabba_band) do
		local pMobile = spawnMobile("tatooine", v[1], v[2], v[3], v[4], v[5], v[6], v[7])
		if (pMobile ~= nil) then
			CreatureObject(pMobile):setCustomObjectName(v[8])
			CreatureObject(pMobile):setMoodString(v[9])
		end
	end


	for i,v in ipairs(self.bomar_monks) do
		local pMobile = spawnMobile("tatooine", v[1], v[2], v[3], v[4], v[5], v[6], v[7])
		if (pMobile ~= nil) then
			writeData(SceneObject(pMobile):getObjectID() .. ":currentLoc", 1)
			writeStringData(SceneObject(pMobile):getObjectID() .. ":name", v[9])
			CreatureObject(pMobile):setCustomObjectName(v[8])
			createEvent(1000, "TatooineJabbasPalaceMobsScreenPlay", "setupJabbaPatrol", pMobile, "")
		end
	end

	for i,v in ipairs(self.gamorrean_guards) do
		local pMobile = spawnMobile("tatooine", v[1], v[2], v[3], v[4], v[5], v[6], v[7])
		if (pMobile ~= nil) then
			writeData(SceneObject(pMobile):getObjectID() .. ":currentLoc", 1)
			writeStringData(SceneObject(pMobile):getObjectID() .. ":name", v[9])
			CreatureObject(pMobile):setCustomObjectName(v[8])
			createEvent(1000, "TatooineJabbasPalaceMobsScreenPlay", "setupJabbaPatrol", pMobile, "")
		end
	end

	for i,v in ipairs(self.droid_spawns) do
		local pMobile = spawnMobile("tatooine", v[1], v[2], v[3], v[4], v[5], v[6], v[7])
		if (pMobile ~= nil) then
			writeData(SceneObject(pMobile):getObjectID() .. ":currentLoc", 1)
			writeStringData(SceneObject(pMobile):getObjectID() .. ":name", v[9])
			CreatureObject(pMobile):setCustomObjectName(v[8])
			createEvent(1000, "TatooineJabbasPalaceMobsScreenPlay", "setupJabbaPatrol", pMobile, "")
		end
	end
end

function TatooineJabbasPalaceMobsScreenPlay:setupJabbaPatrol(pMobile)
	createEvent(getRandomNumber(30,45) * 1000, "TatooineJabbasPalaceMobsScreenPlay", "JabbaPatrol", pMobile, "")
	createObserver(DESTINATIONREACHED, "TatooineJabbasPalaceMobsScreenPlay", "jabbaPatrolDestReached", pMobile)
	AiAgent(pMobile):setAiTemplate("manualescortwalk")
	AiAgent(pMobile):setFollowState(4)
end

function TatooineJabbasPalaceMobsScreenPlay:palaceConverseJawa(pMobile)
	if AiAgent(pMobile):isInCombat() or CreatureObject(pMobile):isDead() then
		return 0
	end

	local action
	local int = getRandomNumber(1,4)
	if int == 1 then action = "explain"
	elseif int == 2 then action = "bow"
	elseif int == 3 then action = "yes"
	elseif int == 4 then action = "shrug_hands" end

	if (action ~= nil) then
		CreatureObject(pMobile):doAnimation(action)
	end

	createEvent(getRandomNumber(40,70) * 100, "TatooineJabbasPalaceMobsScreenPlay", "palaceConverseJawa", pMobile, "")
	return 0
end


function TatooineJabbasPalaceMobsScreenPlay:palaceConverse(pMobile)
	if AiAgent(pMobile):isInCombat() or CreatureObject(pMobile):isDead() then
		return 0
	end

	local action
	local int = getRandomNumber(1,12)
	if int == 1 then action = "check_wrist_device"
	elseif int == 2 then action = "angry"
	elseif int == 3 then action = "cover_mouth"
	elseif int == 4 then action = "dismiss"
	elseif int == 5 then action = "duck"
	elseif int == 6 then action = "embarrassed"
	elseif int == 7 then action = "explain"
	elseif int == 8 then action = "get_hit_light"
	elseif int == 9 then action = "laugh_titter"
	elseif int == 10 then action = "nod_head_once"
	elseif int == 11 then action = "scratch_head"
	elseif int == 12 then action = "shrug_hands" end

	if (action ~= nil) then
		CreatureObject(pMobile):doAnimation(action)
	end

	createEvent(getRandomNumber(40,70) * 100, "TatooineJabbasPalaceMobsScreenPlay", "palaceConverse", pMobile, "")
	return 0
end



function TatooineJabbasPalaceMobsScreenPlay:JabbaPatrol(pMobile)
	if (pMobile == nil) then
		return
	end
	local name = readStringData(SceneObject(pMobile):getObjectID() .. ":name")
	local curLoc = readData(SceneObject(pMobile):getObjectID() .. ":currentLoc")
	local nextLoc

	if (name == "guard1") then
		if (curLoc == 1) then
			nextLoc = { 6.4, .2, 130.7, 1177466 }
		else
			nextLoc = { 0.6, 5.8, 80.4, 1177469 }
		end
	end

	if (name == "guard2") then
		if (curLoc == 1) then
			nextLoc = { -22.22, 10.76, 64.30, 1177489 }
		else
			nextLoc = { 1, 5.8, 80, 1177469 }
		end
	end

	if (name == "guard3") then
		if (curLoc == 1) then
			nextLoc = { -24.89, 6.6, 90.77, 1177490 }
		else
			nextLoc = { -11, 5.8, 88, 1177469 }
		end
	end

	if (name == "guard4") then
		if (curLoc == 1) then
			nextLoc = { -4.8, .2, 134.3, 1177466 }
		else
			nextLoc = { -1, 5.8, 98, 1177469 }
		end
	end

	if (name == "guard5") then
		if (curLoc == 1) then
			nextLoc = { 10, 5.8, 71, 1177470 }
		else
			nextLoc = {-25, 3, 61, 1177474}
		end
	end

	if (name == "guard6") then
		if (curLoc == 1) then
			nextLoc = {-25.9, 0.2, 82.1, 1177475}
		else
			nextLoc ={-50.89, 0.2, 82.37, 1177476}
		end
	end

	if (name == "guard7") then
		if (curLoc == 1) then
			nextLoc = {-19.74, .2, 82.23, 1177475}
		else
			nextLoc = {-2.04, .2, 82.61, 1177480}
		end
	end

	if (name == "guard8") then
		if (curLoc == 1) then
			nextLoc = {-23.73, .82, 76.52, 1177475}
		else
			nextLoc = {-13, 5, 59, 1177474}
		end
	end

	if (name == "guard9") then
		if (curLoc == 1) then
			nextLoc = {-32.17, 3, 55.89, 1177481}
		else
			nextLoc = {-37, 3, 46, 1177486}
		end
	end

	if (name == "guard10") then
		if (curLoc == 1) then
			nextLoc = {-23.78, 3.6, 53.73, 1177487}
		else
			nextLoc = {-25, 5, 34, 1177487}
		end
	end

	if (name == "guard11") then
		if (curLoc == 1) then
			nextLoc = {11.75, .2, -3.62, 1177484}
		else
			nextLoc =  {6, 4, 26, 1177487}
		end
	end

	if (name == "guard12") then
		if (curLoc == 1) then
			nextLoc = {14.12, 5.55, 66.95, 1177471}
		else
			nextLoc = {16.2, -11, 46.2, 1177502}
		end
	end

	if (name == "guard13") then
		if (curLoc == 1) then
			nextLoc = {-28.84, 8.89, 17.1, 1177485}
		else
			nextLoc = {.14, 2, 53.1, 1177487}
		end
	end


	if (name == "bmonk1") then
		if (curLoc == 1) then
			nextLoc = {-24, 6.6, 86, 1177490}
		else
			nextLoc = {-8.94, 3, 55.95, 1177474}
		end
	end
	if (name == "bmonk2") then
		if (curLoc == 1) then
			nextLoc = {8.6, 5.8, 95.2, 1177468}
		else
			nextLoc = {-2, .2, 104, 1177467}
		end
	end
	if (name == "bmonk3") then
		if (curLoc == 1) then
			--nextLoc = {-25, 3, 61, 1177474}
			nextLoc = {21, -11, 45.1, 1177502}
		else
			nextLoc =  {-18, 5.8, 73, 1177489}
		end
	end
	if (name == "bmonk4") then
		if (curLoc == 1) then
			nextLoc = {19.2, 10, 1.5, 1177500}
		else
			nextLoc = {7, 6, 50, 1177487}
		end
	end
	if (name == "bmonk5") then
		if (curLoc == 1) then
			nextLoc = {5.8, 5.8, 60.53, 1177470}
		else
			nextLoc = {24, .2, -9, 1177484}
		end
	end

	if (name == "bmonk6") then
		if (curLoc == 1) then
			nextLoc = {-18, 7, 9, 1177501}
		else
			nextLoc = {24, .2, -9, 1177484}
		end
	end

	if (name == "droid1") then
		if (curLoc == 1) then
			nextLoc = {27.42, 0.2, 90.02, 1177479}
		else
			nextLoc = {19.73, 0.2, 90.51, 1177479}
		end
	end

	if (name == "droid4") then
		if (curLoc == 1) then
			nextLoc = {8.97, 0.2, 88.26, 1177479}
		else
			nextLoc = {17.42, 0.2, 81.22, 1177479}
		end
	end

	if (name == "droid6") then
		if (curLoc == 1) then
			nextLoc = {38, .2, -5.53, 1177499}
		else
			nextLoc = {43.29, .2, 7.14, 1177499}
		end
	end

	if (name == "random2") then
		if (curLoc == 1) then
			nextLoc = {-7.9, 3, 59.61, 1177474}
		else
			nextLoc = {-25, 3, 61, 1177474}
		end
	end

	AiAgent(pMobile):stopWaiting()
	AiAgent(pMobile):setWait(0)
	AiAgent(pMobile):setNextPosition(nextLoc[1], nextLoc[2], nextLoc[3], nextLoc[4])
	AiAgent(pMobile):executeBehavior()
end

function TatooineJabbasPalaceMobsScreenPlay:jabbaPatrolDestReached(pMobile)
	if (pMobile == nil) then
		return 0
	end

	local curLoc = readData(SceneObject(pMobile):getObjectID() .. ":currentLoc")

	if (curLoc == 1) then
		writeData(SceneObject(pMobile):getObjectID() .. ":currentLoc", 2)
	else
		writeData(SceneObject(pMobile):getObjectID() .. ":currentLoc", 1)
	end

	createEvent(getRandomNumber(350,450) * 100, "TatooineJabbasPalaceMobsScreenPlay", "JabbaPatrol", pMobile, "")

	return 0
end

