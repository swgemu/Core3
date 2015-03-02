local ObjectManager = require("managers.object.object_manager")

heroOfTatooineRockCrevice = { }

function heroOfTatooineRockCrevice:canAddObject(pCrevice, pIngredient, slot)
	if pIngredient == nil then
		return TRANSFERCANTADD
	end

	if slot ~= -1 then
		return TRANSFERCANTADD
	end

	local pParent = DeathWatchBunkerScreenPlay:getObjOwner(pIngredient)

	if (pParent == nil or not SceneObject(pParent):isPlayerCreature()) then
		return TRANSFERCANTADD
	end

	return ObjectManager.withCreatureObject(pParent, function(player)
		if player:hasScreenPlayState(1, "hero_of_tatooine_altruism") == 0 or player:hasScreenPlayState(2, "hero_of_tatooine_altruism") == 1 then
			return TRANSFERCANTADD
		elseif (SceneObject(pIngredient):getTemplateObjectPath() ~= "object/tangible/item/quest/hero_of_tatooine/explosives.iff") then
			player:sendSystemMessage("@quest/hero_of_tatooine/system_messages:altruism_no_reason")
			return TRANSFERCANTADD
		else
			return TRANSFERCANADD
		end
	end)
end

function heroOfTatooineRockCrevice:transferObject(pCrevice, pIngredient, slot)
	if (pIngredient == nil) then
		return TRANSFERFAIL
	end

	if slot ~= -1 then
		return TRANSFERFAIL
	end

	local pParent = DeathWatchBunkerScreenPlay:getObjOwner(pIngredient)

	if (pParent == nil or not SceneObject(pParent):isPlayerCreature()) then
		return TRANSFERFAIL
	end

	if (SceneObject(pIngredient):getTemplateObjectPath() == "object/tangible/item/quest/hero_of_tatooine/explosives.iff") then
		writeData("hero_of_tat:explosivePlanterID", SceneObject(pParent):getObjectID())
		CreatureObject(pParent):sendSystemMessage("@quest/hero_of_tatooine/system_messages:altruism_explosive_set")
		SceneObject(pIngredient):destroyObjectFromWorld()
		createEvent(1000 * 10, "HeroOfTatooineScreenPlay", "destroyCaveWall", pCrevice)
		return TRANSFERSUCCESS
	end

	return TRANSFERFAIL
end

function heroOfTatooineRockCrevice:removeObject(pCrevice, pIngredient, slot)
	return TRANSFERFAIL
end