includeFile("recruiters/factionperkdata.lua")

imperial_recruiter_handler = recruiter_convo_handler:new {
}

function imperial_recruiter_handler:getRecruiterFactionHashCode()
	return 3679112276
end

function imperial_recruiter_handler:getRecruiterFactionString()
	return "imperial"
end

function imperial_recruiter_handler:getEnemyFactionHashCode()
	return 370444368
end

function imperial_recruiter_handler:getEnemyFactionString()
	return "rebel"
end

function imperial_recruiter_handler:addRankReviewOption(screen)
	screen:addOption("@conversation/faction_recruiter_imperial:s_312", "confirm_promotion")
end

function imperial_recruiter_handler:getRejectPromotionString()
	return "@conversation/faction_recruiter_imperial:s_320"
end

function imperial_recruiter_handler:addBribeOption(screen)
	screen:addOption("@conversation/faction_recruiter_imperial:s_398", "confirm_bribe")
end

function imperial_recruiter_handler:add100kBribeOption(screen)
	screen:addOption("@conversation/faction_recruiter_imperial:s_406", "accepted_bribe_100k")
end

function imperial_recruiter_handler:isWeapon(strItem)
	if ( faction_reward_data.imperial_weapons_armor[strItem] ~= nil ) then
		if ( faction_reward_data.imperial_weapons_armor[strItem].type == faction_reward_type.weapon ) then
			return true
		end
	end
	
	return false
end

function imperial_recruiter_handler:isArmor(strItem)
	if ( faction_reward_data.imperial_weapons_armor[strItem] ~= nil ) then
		if ( faction_reward_data.imperial_weapons_armor[strItem].type == faction_reward_type.armor ) then
			return true
		end
	end
	
	return false
end


function imperial_recruiter_handler:isUniform(strItem)
	if ( faction_reward_data.imperial_uniforms[strItem] ~= nil ) then
		return true
	end

	return false
end

function imperial_recruiter_handler:isFurniture(strItem)
	if ( faction_reward_data.imperial_furniture[strItem] ~= nil ) then
		return true
	end
	
	return false
end

function imperial_recruiter_handler:isContainer(strItem)
	if ( faction_reward_data.imperial_furniture[strItem] ~= nil and faction_reward_data.imperial_furniture[strItem].type == faction_reward_type.container) then
		return true
	end
	
	return false
end

function imperial_recruiter_handler:isTerminal(strItem)
	if(faction_reward_data.imperial_furniture[strItem] ~= nil and faction_reward_data.imperial_furniture[strItem].type == faction_reward_type.terminal) then
		return true
	end
	
	return false
end

function imperial_recruiter_handler:isInstallation(strItem)
	--print("isinstallatoin called for " .. strItem)
	if(faction_reward_data.imperial_installations[strItem] ~= nil and faction_reward_data.imperial_installations[strItem].type == faction_reward_type.installation) then
		return true
	else
		--print("not an installation")
	end
	
	return false
end
function imperial_recruiter_handler:addUniforms(screen) 
	for k,v in pairs(faction_reward_data.imperial_uniform_list) do
		if ( faction_reward_data.imperial_uniforms[v] ~= nil and faction_reward_data.imperial_uniforms[v].display ~= nil and faction_reward_data.imperial_uniforms[v].cost ~= nil ) then
			screen:addOption(faction_reward_data.imperial_uniforms[v].display .. " - " .. faction_reward_data.imperial_uniforms[v].cost, v)
		end
	end
end


function imperial_recruiter_handler:addWeaponsArmor(screen)
	for k,v in pairs(faction_reward_data.imperial_weapons_armor_list) do
		if ( faction_reward_data.imperial_weapons_armor[v] ~= nill and 	faction_reward_data.imperial_weapons_armor[v].display ~= nil and faction_reward_data.imperial_weapons_armor[v].cost ~= nil ) then
				screen:addOption(faction_reward_data.imperial_weapons_armor[v].display .. " - " .. faction_reward_data.imperial_weapons_armor[v].cost, v)
		end
	end
end

function imperial_recruiter_handler:addFurniture(screen) 
	for k,v in pairs(faction_reward_data.imperial_furniture_list) do
		if ( faction_reward_data.imperial_furniture[v] ~= nil and faction_reward_data.imperial_furniture[v].display ~= nil and faction_reward_data.imperial_furniture[v].cost ~= nil ) then
			screen:addOption(faction_reward_data.imperial_furniture[v].display .. " - " .. faction_reward_data.imperial_furniture[v].cost, v)
		end
	end
end

function imperial_recruiter_handler:addInstallations(screen)
		--print("addInstallations()")
		for k,v in pairs(faction_reward_data.imperial_installations_list) do
		if ( faction_reward_data.imperial_installations[v] ~= nil and faction_reward_data.imperial_installations[v].display ~= nil and faction_reward_data.imperial_installations[v].cost ~= nil ) then
			screen:addOption(faction_reward_data.imperial_installations[v].display .. " - " .. faction_reward_data.imperial_installations[v].cost, v)
		else
			--print("not in table")
		end
	end
end

function imperial_recruiter_handler:getItemCost(itemstring)
	local itemcost = nil
	
	if ( self:isWeapon(itemstring) or self:isArmor(itemstring)  and faction_reward_data.imperial_weapons_armor[itemstring] ~= nil ) then
		if ( faction_reward_data.imperial_weapons_armor[itemstring].cost ~= nil ) then
			return faction_reward_data.imperial_weapons_armor[itemstring].cost
		end
	elseif (self:isUniform(itemstring) ) then
		if ( faction_reward_data.imperial_uniforms[itemstring].cost ~= nil ) then
			return faction_reward_data.imperial_uniforms[itemstring].cost
		end
	elseif ( self:isFurniture(itemstring) ) then
		if(faction_reward_data.imperial_furniture[itemstring].cost ~= nil) then
			return faction_reward_data.imperial_furniture[itemstring].cost
		end
	elseif (self:isInstallation(itemstring)) then
		if(faction_reward_data.imperial_installations[itemstring].cost ~= nil) then
			return faction_reward_data.imperial_installations[itemstring].cost
		end
	end

	return itemcost
end

function imperial_recruiter_handler:getTemplatePath(itemstring)
	if ( self:isWeapon(itemstring) or self:isArmor(itemstring) ) then
			return faction_reward_data.imperial_weapons_armor[itemstring].item
	elseif ( self:isUniform(itemstring) ) then
		return faction_reward_data.imperial_uniforms[itemstring].item
	elseif ( self:isFurniture(itemstring) ) then
		return faction_reward_data.imperial_furniture[itemstring].item
	elseif (self:isInstallation(itemstring)) then
		return faction_reward_data.imperial_installations[itemstring].item
	end
	return nil
end


function imperial_recruiter_handler:getGeneratedObjectTemplate(itemstring)
  	if( self:isInstallation(itemstring)) then
 		if ( faction_reward_data.imperial_installations[itemstring].generatedObjectTemplate ~= nil ) then
 			return faction_reward_data.imperial_installations[itemstring].generatedObjectTemplate
 		end
 		
 	end
 	return nil
end
