NabooMoeniaScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "NabooMoeniaScreenPlay"
}

registerScreenPlay("NabooMoeniaScreenPlay", true)

function NabooMoeniaScreenPlay:start()
	if (isZoneEnabled("naboo")) then
		self:spawnMobiles()
	end
end

function NabooMoeniaScreenPlay:spawnMobiles()

	--Anything dashed out will need to be added here and removed from spawn manager once the spawnMobiles command is extended.

	--Outside
	spawnMobile("naboo", "informant_npc_lvl_1",0,4652,3.8,-4749,0,0)
	spawnMobile("naboo", "informant_npc_lvl_1",0,4744,3.8,-4847,0,0)
	spawnMobile("naboo", "informant_npc_lvl_1",0,4825,3.8,-4829,0,0)
	spawnMobile("naboo", "informant_npc_lvl_1",0,4958,3.8,-4854,0,0)
	spawnMobile("naboo", "informant_npc_lvl_1",0,4976,3.8,-4920,0,0)
	spawnMobile("naboo", "informant_npc_lvl_1",0,4971,3.8,-4941,0,0)
	spawnMobile("naboo", "informant_npc_lvl_1",0,4909,3.8,-4975,0,0)
	spawnMobile("naboo", "informant_npc_lvl_1",0,4679,3.8,-4923,0,0)
	spawnMobile("naboo", "informant_npc_lvl_1",0,4838,4.4,-4877,0,0)
	spawnMobile("naboo", "informant_npc_lvl_1",0,4810,4.2,-4627,0,0)
	spawnMobile("naboo", "informant_npc_lvl_1",0,4773,4.4,-4937,0,0)
	spawnMobile("naboo", "informant_npc_lvl_2",0,4638,4.4,-4643,270,0)
	spawnMobile("naboo", "informant_npc_lvl_3",0,4721,4.2,-4614,180,0)
	spawnMobile("naboo", "rebel_recruiter",0,4826,4.2,-4696,-93,0)
	spawnMobile("naboo", "trainer_architect",0,4779,3.75,-4973,0,0)
	spawnMobile("naboo", "trainer_artisan",0,4823.13,4.17,-4705.34,81,0)
	spawnMobile("naboo", "trainer_brawler",0,4800,4.17,-4734,151,0)
	spawnMobile("naboo", "trainer_brawler",0,4999,3.8,-4926,-12,0)
	spawnMobile("naboo", "trainer_chef",0,4942,3.8,-4837,180,0)
	spawnMobile("naboo", "trainer_dancer",0,4730,3.75,-4872,44,0)
	spawnMobile("naboo", "trainer_doctor",0,4887,3.8,-4899,180,0)
	spawnMobile("naboo", "trainer_droidengineer",0,4654,4.3,-4692,0,0)
	spawnMobile("naboo", "trainer_entertainer",0,4846,4.17,-4658,258,0)
	spawnMobile("naboo", "trainer_marksman",0,4794,4.17,-4730,0,0)
	spawnMobile("naboo", "trainer_medic",0,4808,4.17,-4724,0,0)
	spawnMobile("naboo", "trainer_medic",0,4772,3.7,-4814,164,0)
	spawnMobile("naboo", "trainer_merchant",0,4819,4.17,-4704,81,0)
	spawnMobile("naboo", "trainer_musician",0,4740,3.8,-4886,0,0)
	spawnMobile("naboo", "trainer_scout",0,4836.08,4.17,-4703.96,94,0)
	--{"trainer_shipwright",0,4727,4.3,-4649,0,0, "", "a shipwright trainer"},
	spawnMobile("naboo", "trainer_squadleader",0,4701,3.75,-4939,0,0)
	spawnMobile("naboo", "trainer_tailor",0,4858,3.8,-4799,180,0)

	--Cantina
	spawnMobile("naboo", "rebel_recruiter",0,-29,-0.89,-1.2,74,119)
	spawnMobile("naboo", "informant_npc_lvl_2",0,-2.2226,-0.894992,5.90785,90,111)

	--Guild Hall 4923 -4783
	spawnMobile("naboo", "trainer_artisan",0,-0.0177415,1.13306,-13.3088,0,1717546)

	--Guild Hall 4721 -4966
	spawnMobile("naboo", "trainer_brawler",0,-11.0386,1.13306,-13.0273,0,1717535)
	spawnMobile("naboo", "trainer_marksman",0,0,1.13306,-13,0,1717534)
	spawnMobile("naboo", "trainer_scout",0,-11.303,1.13306,4.63738,199,1717532)

	--Guild Hall 4805 -4980
	spawnMobile("naboo", "trainer_architect",0,11,1.133,-14.5,0,1717555)
	spawnMobile("naboo", "trainer_armorsmith",0,-15,1.113,0,88,1717554)
	spawnMobile("naboo", "trainer_droidengineer",0,-11.5102,1.13306,-13.7835,2,1717557)
	spawnMobile("naboo", "trainer_merchant",0,12,1.13306,6,180,1717553)
	spawnMobile("naboo", "trainer_weaponsmith",0,-2.5,1.13306,-8.4,91,1717556)

	--Med Center
	spawnMobile("naboo", "trainer_combatmedic",0,27.0188,0.26,5.47931,82,1717502)
	spawnMobile("naboo", "trainer_combatmedic",0,-16.404,0.26,10.6808,172,1717506)
	spawnMobile("naboo", "trainer_doctor",0,19.6344,0.26,-4.81265,37,1717502)
	spawnMobile("naboo", "trainer_doctor",0,-25,0.26,-4,180,1717506)
	spawnMobile("naboo", "trainer_medic",0,-17.2255,0.26,-1.2311,150,1717506)
	spawnMobile("naboo", "trainer_medic",0,16.6671,0.26,5.91467,177,1717502)

end
