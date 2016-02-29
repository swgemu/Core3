/*
 * CommandLuaTest.cpp
 *
 *  Created on: 20/10/2013
 *      Author: victor
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "server/zone/managers/templates/DataArchiveStore.h"
#include "server/zone/managers/objectcontroller/command/CommandConfigManager.h"
#include "server/zone/managers/objectcontroller/command/CommandList.h"
#include "server/zone/objects/creature/commands/CombatQueueCommand.h"
#include "server/conf/ConfigManager.h"

class CombatAnimTest : public ::testing::Test {

public:
	Vector<uint32> animList;
	WeaponObject* dummyWeapon;
	CreatureObject* dummyCreature;
	CombatAnimTest() {
		loadAnimList();
		dummyWeapon = new WeaponObject();
		dummyWeapon->setMaxDamage(50);
		dummyWeapon->setMinDamage(50);

		dummyCreature->setWeapon(dummyWeapon, false);

		// Perform creation setup here.
		ConfigManager::instance()->loadConfigData();
		DataArchiveStore::instance()->loadTres(ConfigManager::instance()->getTrePath(), ConfigManager::instance()->getTreFiles());
	}

	~CombatAnimTest() {
	}

	void SetUp() {
		// Perform setup of common constructs here.
	}

	void TearDown() {
		// Perform clean up of common constructs here.
	}
	void loadAnimList() {
		animList.add(STRING_HASHCODE("fire_single"));
		animList.add(STRING_HASHCODE("fire_burst"));
		animList.add(STRING_HASHCODE("fire_suppression"));
		animList.add(STRING_HASHCODE("ranged_coup_de_grace"));
		animList.add(STRING_HASHCODE("unarmed_coup_de_grace"));
		animList.add(STRING_HASHCODE("melee_coup_de_grace"));
		animList.add(STRING_HASHCODE("fire_acrobatic"));
		animList.add(STRING_HASHCODE("tumble_facing"));
		animList.add(STRING_HASHCODE("tumble"));
		animList.add(STRING_HASHCODE("warcry"));
		animList.add(STRING_HASHCODE("force_throw_1_arc_particle_level_1_light"));
		animList.add(STRING_HASHCODE("force_throw_1_arc_particle_level_1_medium"));
		animList.add(STRING_HASHCODE("force_throw_1_particle_level_1_light"));
		animList.add(STRING_HASHCODE("force_throw_1_particle_level_1_medium"));
		animList.add(STRING_HASHCODE("force_mind_blast_1_arc_particle_level_1_light"));
		animList.add(STRING_HASHCODE("force_mind_blast_1_arc_particle_level_1_medium"));
		animList.add(STRING_HASHCODE("force_mind_blast_1_particle_level_1_light"));
		animList.add(STRING_HASHCODE("force_mind_blast_1_particle_level_1_medium"));
		animList.add(STRING_HASHCODE("force_knockdown_1_particle_level_1"));
		animList.add(STRING_HASHCODE("force_knockdown_1_arc_particle_level_1"));
		animList.add(STRING_HASHCODE("force_intimidate"));
		animList.add(STRING_HASHCODE("force_intimidate_chain"));
		animList.add(STRING_HASHCODE("force_weaken_1_arc_particle_level_1_light"));
		animList.add(STRING_HASHCODE("force_weaken_1_arc_particle_level_1_medium"));
		animList.add(STRING_HASHCODE("force_weaken_1_particle_level_1_light"));
		animList.add(STRING_HASHCODE("force_weaken_1_particle_level_1_medium"));
		animList.add(STRING_HASHCODE("force_healing_1"));
		animList.add(STRING_HASHCODE("force_drain_1"));
		animList.add(STRING_HASHCODE("force_transfer_1"));
		animList.add(STRING_HASHCODE("mind_trick_1"));
		animList.add(STRING_HASHCODE("force_lightning_1_particle_level_1_light"));
		animList.add(STRING_HASHCODE("force_lightning_1_particle_level_1_medium"));
		animList.add(STRING_HASHCODE("force_lightning_1_particle_level_2_light"));
		animList.add(STRING_HASHCODE("force_lightning_1_particle_level_2_medium"));
		animList.add(STRING_HASHCODE("force_lightning_1_particle_level_3_light"));
		animList.add(STRING_HASHCODE("force_lightning_1_particle_level_3_medium"));
		animList.add(STRING_HASHCODE("force_lightning_1_particle_level_4_light"));
		animList.add(STRING_HASHCODE("force_lightning_1_particle_level_4_medium"));
		animList.add(STRING_HASHCODE("force_lightning_1_particle_level_5_light"));
		animList.add(STRING_HASHCODE("force_lightning_1_particle_level_5_medium"));
		animList.add(STRING_HASHCODE("force_lightning_1_arc_particle_level_1_light"));
		animList.add(STRING_HASHCODE("force_lightning_1_arc_particle_level_1_medium"));
		animList.add(STRING_HASHCODE("force_lightning_1_arc_particle_level_2_light"));
		animList.add(STRING_HASHCODE("force_lightning_1_arc_particle_level_2_medium"));
		animList.add(STRING_HASHCODE("force_lightning_1_arc_particle_level_3_light"));
		animList.add(STRING_HASHCODE("force_lightning_1_arc_particle_level_3_medium"));
		animList.add(STRING_HASHCODE("force_lightning_1_arc_particle_level_4_light"));
		animList.add(STRING_HASHCODE("force_lightning_1_arc_particle_level_4_medium"));
		animList.add(STRING_HASHCODE("force_lightning_1_arc_particle_level_5_light"));
		animList.add(STRING_HASHCODE("force_lightning_1_arc_particle_level_5_medium"));
		animList.add(STRING_HASHCODE("force_choke_1_arc_particle_level_1_light"));
		animList.add(STRING_HASHCODE("force_choke_1_arc_particle_level_1_medium"));
		animList.add(STRING_HASHCODE("force_choke_1_particle_level_1_light"));
		animList.add(STRING_HASHCODE("force_choke_1_particle_level_1_medium"));
		animList.add(STRING_HASHCODE("force_channel_2_particles_light"));
		animList.add(STRING_HASHCODE("force_channel_2_particles_medium"));
		animList.add(STRING_HASHCODE("force_channel_1_particle_light"));
		animList.add(STRING_HASHCODE("force_channel_1_particle_medium"));
		animList.add(STRING_HASHCODE("force_blast_2_particles_light"));
		animList.add(STRING_HASHCODE("force_blast_2_particles_medium"));
		animList.add(STRING_HASHCODE("force_blast_1_particle_light"));
		animList.add(STRING_HASHCODE("force_blast_1_particle_medium"));
		animList.add(STRING_HASHCODE("force_absorb_2_particles_light"));
		animList.add(STRING_HASHCODE("force_absorb_2_particles_medium"));
		animList.add(STRING_HASHCODE("force_absorb_1_particle_light"));
		animList.add(STRING_HASHCODE("force_absorb_1_particle_medium"));
		animList.add(STRING_HASHCODE("point_and_laugh"));
		animList.add(STRING_HASHCODE("intimidate"));
		animList.add(STRING_HASHCODE("rescue"));
		animList.add(STRING_HASHCODE("fire_defender_posture_change_up"));
		animList.add(STRING_HASHCODE("fire_defender_posture_change_down"));
		animList.add(STRING_HASHCODE("fire_area_light"));
		animList.add(STRING_HASHCODE("fire_area_medium"));
		animList.add(STRING_HASHCODE("fire_area_no_trails_light"));
		animList.add(STRING_HASHCODE("fire_area_no_trails_medium"));
		animList.add(STRING_HASHCODE("fire_5_single_medium"));
		animList.add(STRING_HASHCODE("fire_5_single_light"));
		animList.add(STRING_HASHCODE("fire_5_single_medium_face"));
		animList.add(STRING_HASHCODE("fire_5_single_light_face"));
		animList.add(STRING_HASHCODE("fire_7_single_medium"));
		animList.add(STRING_HASHCODE("fire_7_single_light"));
		animList.add(STRING_HASHCODE("fire_7_single_medium_face"));
		animList.add(STRING_HASHCODE("fire_7_single_light_face"));
		animList.add(STRING_HASHCODE("fire_9_single_medium"));
		animList.add(STRING_HASHCODE("fire_9_single_light"));
		animList.add(STRING_HASHCODE("fire_9_single_medium_face"));
		animList.add(STRING_HASHCODE("fire_9_single_light_face"));
		animList.add(STRING_HASHCODE("fire_5_special_single_light"));
		animList.add(STRING_HASHCODE("fire_5_special_single_medium"));
		animList.add(STRING_HASHCODE("fire_5_special_single_light_face"));
		animList.add(STRING_HASHCODE("fire_5_special_single_medium_face"));
		animList.add(STRING_HASHCODE("fire_3_single_light"));
		animList.add(STRING_HASHCODE("fire_3_single_medium"));
		animList.add(STRING_HASHCODE("fire_3_single_light_face"));
		animList.add(STRING_HASHCODE("fire_3_single_medium_face"));
		animList.add(STRING_HASHCODE("fire_3_special_single_light"));
		animList.add(STRING_HASHCODE("fire_3_special_single_medium"));
		animList.add(STRING_HASHCODE("fire_3_special_single_light_face"));
		animList.add(STRING_HASHCODE("fire_3_special_single_medium_face"));
		animList.add(STRING_HASHCODE("fire_1_single_light"));
		animList.add(STRING_HASHCODE("fire_1_single_medium"));
		animList.add(STRING_HASHCODE("fire_1_single_light_face"));
		animList.add(STRING_HASHCODE("fire_1_single_medium_face"));
		animList.add(STRING_HASHCODE("fire_1_special_single_light"));
		animList.add(STRING_HASHCODE("fire_1_special_single_medium"));
		animList.add(STRING_HASHCODE("fire_1_special_single_light_face"));
		animList.add(STRING_HASHCODE("fire_1_special_single_medium_face"));
		animList.add(STRING_HASHCODE("test_swoosh"));
		animList.add(STRING_HASHCODE("test_homing"));
		animList.add(STRING_HASHCODE("test_heavy_weapon"));
		animList.add(STRING_HASHCODE("test_heavy_weapon_particle_system"));
		animList.add(STRING_HASHCODE("test_sword_ricochet"));
		animList.add(STRING_HASHCODE("test_sword_throw"));
		animList.add(STRING_HASHCODE("test_flamethrower_arc"));
		animList.add(STRING_HASHCODE("test_lightning_1"));
		animList.add(STRING_HASHCODE("test_lightning_2"));
		animList.add(STRING_HASHCODE("test_lightning_passive_actors"));
		animList.add(STRING_HASHCODE("fire_flame_thrower_cone_1_light"));
		animList.add(STRING_HASHCODE("fire_flame_thrower_cone_1_medium"));
		animList.add(STRING_HASHCODE("fire_flame_thrower_cone_2_light"));
		animList.add(STRING_HASHCODE("fire_flame_thrower_cone_2_medium"));
		animList.add(STRING_HASHCODE("fire_flame_thrower_single_1_light"));
		animList.add(STRING_HASHCODE("fire_flame_thrower_single_1_medium"));
		animList.add(STRING_HASHCODE("fire_flame_thrower_single_2_light"));
		animList.add(STRING_HASHCODE("fire_flame_thrower_single_2_medium"));
		animList.add(STRING_HASHCODE("fire_lightning_rifle_single_1_light"));
		animList.add(STRING_HASHCODE("fire_lightning_rifle_single_1_medium"));
		animList.add(STRING_HASHCODE("fire_lightning_rifle_single_2_light"));
		animList.add(STRING_HASHCODE("fire_lightning_rifle_single_2_medium"));
		animList.add(STRING_HASHCODE("fire_acid_rifle_single_1_light"));
		animList.add(STRING_HASHCODE("fire_acid_rifle_single_1_medium"));
		animList.add(STRING_HASHCODE("fire_acid_rifle_single_2_light"));
		animList.add(STRING_HASHCODE("fire_acid_rifle_single_2_medium"));
		animList.add(STRING_HASHCODE("test_flamethrower"));
		animList.add(STRING_HASHCODE("saberthrow_posture_change"));
		animList.add(STRING_HASHCODE("saberthrow_light"));
		animList.add(STRING_HASHCODE("saberthrow_medium"));
		animList.add(STRING_HASHCODE("fire_heavy_rocket_launcher_light"));
		animList.add(STRING_HASHCODE("fire_heavy_rocket_launcher_medium"));
		animList.add(STRING_HASHCODE("fire_heavy_particle_beam_light"));
		animList.add(STRING_HASHCODE("fire_heavy_particle_beam_medium"));
		animList.add(STRING_HASHCODE("fire_heavy_lightning_beam_light"));
		animList.add(STRING_HASHCODE("fire_heavy_lightning_beam_medium"));
		animList.add(STRING_HASHCODE("fire_heavy_acid_beam_light"));
		animList.add(STRING_HASHCODE("fire_heavy_acid_beam_medium"));
		animList.add(STRING_HASHCODE("change_posture"));
		animList.add(STRING_HASHCODE("posture_scramble"));
		animList.add(STRING_HASHCODE("dodge"));
		animList.add(STRING_HASHCODE("go_incapacitated"));
		animList.add(STRING_HASHCODE("get_hit_light"));
		animList.add(STRING_HASHCODE("get_hit_medium"));
		animList.add(STRING_HASHCODE("attack_high_left_light_0"));
		animList.add(STRING_HASHCODE("attack_high_center_light_0"));
		animList.add(STRING_HASHCODE("attack_high_right_light_0"));
		animList.add(STRING_HASHCODE("attack_mid_left_light_0"));
		animList.add(STRING_HASHCODE("attack_mid_center_light_0"));
		animList.add(STRING_HASHCODE("attack_mid_right_light_0"));
		animList.add(STRING_HASHCODE("attack_low_left_light_0"));
		animList.add(STRING_HASHCODE("attack_low_center_light_0"));
		animList.add(STRING_HASHCODE("attack_low_right_light_0"));
		animList.add(STRING_HASHCODE("attack_high_left_medium_0"));
		animList.add(STRING_HASHCODE("attack_high_center_medium_0"));
		animList.add(STRING_HASHCODE("attack_high_right_medium_0"));
		animList.add(STRING_HASHCODE("attack_mid_left_medium_0"));
		animList.add(STRING_HASHCODE("attack_mid_center_medium_0"));
		animList.add(STRING_HASHCODE("attack_mid_right_medium_0"));
		animList.add(STRING_HASHCODE("attack_low_left_medium_0"));
		animList.add(STRING_HASHCODE("attack_low_center_medium_0"));
		animList.add(STRING_HASHCODE("attack_low_right_medium_0"));
		animList.add(STRING_HASHCODE("attack_high_left_light_1"));
		animList.add(STRING_HASHCODE("attack_high_center_light_1"));
		animList.add(STRING_HASHCODE("attack_high_right_light_1"));
		animList.add(STRING_HASHCODE("attack_mid_left_light_1"));
		animList.add(STRING_HASHCODE("attack_mid_center_light_1"));
		animList.add(STRING_HASHCODE("attack_mid_right_light_1"));
		animList.add(STRING_HASHCODE("attack_low_left_light_1"));
		animList.add(STRING_HASHCODE("attack_low_center_light_1"));
		animList.add(STRING_HASHCODE("attack_low_right_light_1"));
		animList.add(STRING_HASHCODE("attack_high_left_medium_1"));
		animList.add(STRING_HASHCODE("attack_high_center_medium_1"));
		animList.add(STRING_HASHCODE("attack_high_right_medium_1"));
		animList.add(STRING_HASHCODE("attack_mid_left_medium_1"));
		animList.add(STRING_HASHCODE("attack_mid_center_medium_1"));
		animList.add(STRING_HASHCODE("attack_mid_right_medium_1"));
		animList.add(STRING_HASHCODE("attack_low_left_medium_1"));
		animList.add(STRING_HASHCODE("attack_low_center_medium_1"));
		animList.add(STRING_HASHCODE("attack_low_right_medium_1"));
		animList.add(STRING_HASHCODE("attack_high_left_light_2"));
		animList.add(STRING_HASHCODE("attack_high_center_light_2"));
		animList.add(STRING_HASHCODE("attack_high_right_light_2"));
		animList.add(STRING_HASHCODE("attack_mid_left_light_2"));
		animList.add(STRING_HASHCODE("attack_mid_center_light_2"));
		animList.add(STRING_HASHCODE("attack_mid_right_light_2"));
		animList.add(STRING_HASHCODE("attack_low_left_light_2"));
		animList.add(STRING_HASHCODE("attack_low_center_light_2"));
		animList.add(STRING_HASHCODE("attack_low_right_light_2"));
		animList.add(STRING_HASHCODE("attack_high_left_medium_2"));
		animList.add(STRING_HASHCODE("attack_high_center_medium_2"));
		animList.add(STRING_HASHCODE("attack_high_right_medium_2"));
		animList.add(STRING_HASHCODE("attack_mid_left_medium_2"));
		animList.add(STRING_HASHCODE("attack_mid_center_medium_2"));
		animList.add(STRING_HASHCODE("attack_mid_right_medium_2"));
		animList.add(STRING_HASHCODE("attack_low_left_medium_2"));
		animList.add(STRING_HASHCODE("attack_low_center_medium_2"));
		animList.add(STRING_HASHCODE("attack_low_right_medium_2"));
		animList.add(STRING_HASHCODE("attack_high_left_light_3"));
		animList.add(STRING_HASHCODE("attack_high_center_light_3"));
		animList.add(STRING_HASHCODE("attack_high_right_light_3"));
		animList.add(STRING_HASHCODE("attack_mid_left_light_3"));
		animList.add(STRING_HASHCODE("attack_mid_center_light_3"));
		animList.add(STRING_HASHCODE("attack_mid_right_light_3"));
		animList.add(STRING_HASHCODE("attack_low_left_light_3"));
		animList.add(STRING_HASHCODE("attack_low_center_light_3"));
		animList.add(STRING_HASHCODE("attack_low_right_light_3"));
		animList.add(STRING_HASHCODE("attack_high_left_medium_3"));
		animList.add(STRING_HASHCODE("attack_high_center_medium_3"));
		animList.add(STRING_HASHCODE("attack_high_right_medium_3"));
		animList.add(STRING_HASHCODE("attack_mid_left_medium_3"));
		animList.add(STRING_HASHCODE("attack_mid_center_medium_3"));
		animList.add(STRING_HASHCODE("attack_mid_right_medium_3"));
		animList.add(STRING_HASHCODE("attack_low_left_medium_3"));
		animList.add(STRING_HASHCODE("attack_low_center_medium_3"));
		animList.add(STRING_HASHCODE("attack_low_right_medium_3"));
		animList.add(STRING_HASHCODE("counter_high_left_light"));
		animList.add(STRING_HASHCODE("counter_high_center_light"));
		animList.add(STRING_HASHCODE("counter_high_right_light"));
		animList.add(STRING_HASHCODE("counter_mid_left_light"));
		animList.add(STRING_HASHCODE("counter_mid_center_light"));
		animList.add(STRING_HASHCODE("counter_mid_right_light"));
		animList.add(STRING_HASHCODE("counter_low_left_light"));
		animList.add(STRING_HASHCODE("counter_low_center_light"));
		animList.add(STRING_HASHCODE("counter_low_right_light"));
		animList.add(STRING_HASHCODE("counter_high_left_medium"));
		animList.add(STRING_HASHCODE("counter_high_center_medium"));
		animList.add(STRING_HASHCODE("counter_high_right_medium"));
		animList.add(STRING_HASHCODE("counter_mid_left_medium"));
		animList.add(STRING_HASHCODE("counter_mid_center_medium"));
		animList.add(STRING_HASHCODE("counter_mid_right_medium"));
		animList.add(STRING_HASHCODE("counter_low_left_medium"));
		animList.add(STRING_HASHCODE("counter_low_center_medium"));
		animList.add(STRING_HASHCODE("counter_low_right_medium"));
		animList.add(STRING_HASHCODE("charge"));
		animList.add(STRING_HASHCODE("attack_high_right_2_punch_roundhouse_medium"));
		animList.add(STRING_HASHCODE("attack_special_foot_stomp_medium"));
		animList.add(STRING_HASHCODE("attack_special_shoulder_bash_medium"));
		animList.add(STRING_HASHCODE("attack_special_wookiee_slap_medium"));
		animList.add(STRING_HASHCODE("attack_special_headbutt_medium"));
		animList.add(STRING_HASHCODE("attack_special_knee_strike_medium"));
		animList.add(STRING_HASHCODE("attack_special_elbow_throw_medium"));
		animList.add(STRING_HASHCODE("attack_special_hammerfist_medium"));
		animList.add(STRING_HASHCODE("attack_high_right_0_rear_handhook_medium"));
		animList.add(STRING_HASHCODE("attack_high_right_1_lead_arckick_medium"));
		animList.add(STRING_HASHCODE("attack_high_right_2_rear_roundhouse_kick_medium"));
		animList.add(STRING_HASHCODE("attack_high_center_1_jab_double_medium"));
		animList.add(STRING_HASHCODE("combo_2a_medium"));
		animList.add(STRING_HASHCODE("combo_2b_medium"));
		animList.add(STRING_HASHCODE("combo_2c_medium"));
		animList.add(STRING_HASHCODE("combo_2d_medium"));
		animList.add(STRING_HASHCODE("combo_2e_medium"));
		animList.add(STRING_HASHCODE("attack_high_right_2_punch_roundhouse_light"));
		animList.add(STRING_HASHCODE("attack_special_foot_stomp_light"));
		animList.add(STRING_HASHCODE("attack_special_shoulder_bash_light"));
		animList.add(STRING_HASHCODE("attack_special_wookiee_slap_light"));
		animList.add(STRING_HASHCODE("attack_special_headbutt_light"));
		animList.add(STRING_HASHCODE("attack_special_knee_strike_light"));
		animList.add(STRING_HASHCODE("attack_special_elbow_throw_light"));
		animList.add(STRING_HASHCODE("attack_special_hammerfist_light"));
		animList.add(STRING_HASHCODE("attack_high_right_0_rear_handhook_light"));
		animList.add(STRING_HASHCODE("attack_high_right_1_lead_arckick_light"));
		animList.add(STRING_HASHCODE("attack_high_right_2_rear_roundhouse_kick_light"));
		animList.add(STRING_HASHCODE("attack_high_center_1_jab_double_light"));
		animList.add(STRING_HASHCODE("combo_2a_light"));
		animList.add(STRING_HASHCODE("combo_2b_light"));
		animList.add(STRING_HASHCODE("combo_2c_light"));
		animList.add(STRING_HASHCODE("combo_2d_light"));
		animList.add(STRING_HASHCODE("combo_2e_light"));
		animList.add(STRING_HASHCODE("combo_3a_light"));
		animList.add(STRING_HASHCODE("combo_3a_medium"));
		animList.add(STRING_HASHCODE("combo_3b_light"));
		animList.add(STRING_HASHCODE("combo_3b_medium"));
		animList.add(STRING_HASHCODE("combo_3c_light"));
		animList.add(STRING_HASHCODE("combo_3c_medium"));
		animList.add(STRING_HASHCODE("combo_3d_light"));
		animList.add(STRING_HASHCODE("combo_3d_medium"));
		animList.add(STRING_HASHCODE("combo_3e_light"));
		animList.add(STRING_HASHCODE("combo_3e_medium"));
		animList.add(STRING_HASHCODE("combo_4a_light"));
		animList.add(STRING_HASHCODE("combo_4a_medium"));
		animList.add(STRING_HASHCODE("combo_4b_light"));
		animList.add(STRING_HASHCODE("combo_4b_medium"));
		animList.add(STRING_HASHCODE("combo_4c_light"));
		animList.add(STRING_HASHCODE("combo_4c_medium"));
		animList.add(STRING_HASHCODE("combo_4d_light"));
		animList.add(STRING_HASHCODE("combo_4d_medium"));
		animList.add(STRING_HASHCODE("combo_4e_light"));
		animList.add(STRING_HASHCODE("combo_4e_medium"));
		animList.add(STRING_HASHCODE("combo_5a_light"));
		animList.add(STRING_HASHCODE("combo_5a_medium"));
		animList.add(STRING_HASHCODE("combo_5b_light"));
		animList.add(STRING_HASHCODE("combo_5b_medium"));
		animList.add(STRING_HASHCODE("showoff_1_light"));
		animList.add(STRING_HASHCODE("showoff_1_medium"));
		animList.add(STRING_HASHCODE("showoff_2_light"));
		animList.add(STRING_HASHCODE("showoff_2_medium"));
		animList.add(STRING_HASHCODE("showoff_3_light"));
		animList.add(STRING_HASHCODE("showoff_3_medium"));
		animList.add(STRING_HASHCODE("showoff_4_light"));
		animList.add(STRING_HASHCODE("showoff_4_medium"));
		animList.add(STRING_HASHCODE("combo_jedi_1_light"));
		animList.add(STRING_HASHCODE("combo_jedi_1_medium"));
		animList.add(STRING_HASHCODE("combo_jedi_2_light"));
		animList.add(STRING_HASHCODE("combo_jedi_2_medium"));
		animList.add(STRING_HASHCODE("combo_jedi_3_light"));
		animList.add(STRING_HASHCODE("combo_jedi_3_medium"));
		animList.add(STRING_HASHCODE("combo_jedi_4_light"));
		animList.add(STRING_HASHCODE("combo_jedi_4_medium"));
		animList.add(STRING_HASHCODE("lower_posture_polearm_1"));
		animList.add(STRING_HASHCODE("lower_posture_unarmed_1"));
		animList.add(STRING_HASHCODE("lower_posture_2hmelee_1"));
		animList.add(STRING_HASHCODE("lower_posture_2hmelee_2"));
		animList.add(STRING_HASHCODE("lower_posture_2hmelee_3"));
		animList.add(STRING_HASHCODE("lower_posture_2hmelee_4"));
		animList.add(STRING_HASHCODE("lower_posture_2hmelee_5"));
		animList.add(STRING_HASHCODE("lower_posture_2hmelee_6"));
		animList.add(STRING_HASHCODE("lower_posture_1hmelee_1"));
		animList.add(STRING_HASHCODE("lower_posture_polearm_2"));
		animList.add(STRING_HASHCODE("knockdown_polearm_1"));
		animList.add(STRING_HASHCODE("knockdown_polearm_2"));
		animList.add(STRING_HASHCODE("knockdown_polearm_3"));
		animList.add(STRING_HASHCODE("knockdown_1hmelee_1"));
		animList.add(STRING_HASHCODE("knockdown_2hmelee_1"));
		animList.add(STRING_HASHCODE("knockdown_unarmed_1"));
		animList.add(STRING_HASHCODE("knockdown_unarmed_2"));
		animList.add(STRING_HASHCODE("knockdown_unarmed_3"));
		animList.add(STRING_HASHCODE("ranged_melee_light"));
		animList.add(STRING_HASHCODE("ranged_melee_medium"));
		animList.add(STRING_HASHCODE("throw_grenade"));
		animList.add(STRING_HASHCODE("throw_grenade_near_cryoban"));
		animList.add(STRING_HASHCODE("throw_grenade_medium_cryoban"));
		animList.add(STRING_HASHCODE("throw_grenade_far_cryoban"));
		animList.add(STRING_HASHCODE("throw_grenade_near_bug_bomb"));
		animList.add(STRING_HASHCODE("throw_grenade_medium_bug_bomb"));
		animList.add(STRING_HASHCODE("throw_grenade_far_bug_bomb"));
		animList.add(STRING_HASHCODE("throw_grenade_near_healing"));
		animList.add(STRING_HASHCODE("throw_grenade_medium_healing"));
		animList.add(STRING_HASHCODE("throw_grenade_far_healing"));
		animList.add(STRING_HASHCODE("throw_grenade_near_healing_longrange"));
		animList.add(STRING_HASHCODE("throw_grenade_medium_healing_longrange"));
		animList.add(STRING_HASHCODE("throw_grenade_far_healing_longrange"));
		animList.add(STRING_HASHCODE("throw_grenade_near_poison"));
		animList.add(STRING_HASHCODE("throw_grenade_medium_poison"));
		animList.add(STRING_HASHCODE("throw_grenade_far_poison"));
		animList.add(STRING_HASHCODE("throw_grenade_near_area_poison"));
		animList.add(STRING_HASHCODE("throw_grenade_medium_area_poison"));
		animList.add(STRING_HASHCODE("throw_grenade_far_area_poison"));
		animList.add(STRING_HASHCODE("throw_grenade_near_disease"));
		animList.add(STRING_HASHCODE("throw_grenade_medium_disease"));
		animList.add(STRING_HASHCODE("throw_grenade_far_disease"));
		animList.add(STRING_HASHCODE("throw_grenade_near_area_disease"));
		animList.add(STRING_HASHCODE("throw_grenade_medium_area_disease"));
		animList.add(STRING_HASHCODE("throw_grenade_far_area_disease"));
		animList.add(STRING_HASHCODE("throw_grenade_near_fragmentation"));
		animList.add(STRING_HASHCODE("throw_grenade_medium_fragmentation"));
		animList.add(STRING_HASHCODE("throw_grenade_far_fragmentation"));
		animList.add(STRING_HASHCODE("throw_grenade_near_glop"));
		animList.add(STRING_HASHCODE("throw_grenade_medium_glop"));
		animList.add(STRING_HASHCODE("throw_grenade_far_glop"));
		animList.add(STRING_HASHCODE("throw_grenade_near_imperial_detonator"));
		animList.add(STRING_HASHCODE("throw_grenade_medium_imperial_detonator"));
		animList.add(STRING_HASHCODE("throw_grenade_far_imperial_detonator"));
		animList.add(STRING_HASHCODE("throw_grenade_near_proton"));
		animList.add(STRING_HASHCODE("throw_grenade_medium_proton"));
		animList.add(STRING_HASHCODE("throw_grenade_far_proton"));
		animList.add(STRING_HASHCODE("throw_grenade_near_thermal_detonator"));
		animList.add(STRING_HASHCODE("throw_grenade_medium_thermal_detonator"));
		animList.add(STRING_HASHCODE("throw_grenade_far_thermal_detonator"));
		animList.add(STRING_HASHCODE("get_hit_grenade_near_light"));
		animList.add(STRING_HASHCODE("get_hit_grenade_medium_light"));
		animList.add(STRING_HASHCODE("get_hit_grenade_far_light"));
		animList.add(STRING_HASHCODE("get_hit_grenade_near_medium"));
		animList.add(STRING_HASHCODE("get_hit_grenade_medium_medium"));
		animList.add(STRING_HASHCODE("get_hit_grenade_far_medium"));
		animList.add(STRING_HASHCODE("throw_trap_enraging_spur"));
		animList.add(STRING_HASHCODE("throw_trap_flash_bomb"));
		animList.add(STRING_HASHCODE("throw_trap_noise_maker"));
		animList.add(STRING_HASHCODE("throw_trap_sonic_pulse"));
		animList.add(STRING_HASHCODE("throw_trap_tranq_dart"));
		animList.add(STRING_HASHCODE("throw_trap_drowsy_dart"));
		animList.add(STRING_HASHCODE("throw_trap_webber"));
		animList.add(STRING_HASHCODE("throw_trap_melee_def_1"));
		animList.add(STRING_HASHCODE("throw_trap_melee_ranged_def_1"));
		animList.add(STRING_HASHCODE("throw_trap_ranged_def_1"));
		animList.add(STRING_HASHCODE("throw_trap_state_def_1"));
		animList.add(STRING_HASHCODE("creature_attack_light"));
		animList.add(STRING_HASHCODE("creature_attack_special_1_medium"));
		animList.add(STRING_HASHCODE("creature_attack_special_1_light"));
		animList.add(STRING_HASHCODE("creature_attack_special_2_medium"));
		animList.add(STRING_HASHCODE("creature_attack_special_2_light"));
		animList.add(STRING_HASHCODE("creature_attack_medium"));
		animList.add(STRING_HASHCODE("creature_attack_ranged_light"));
		animList.add(STRING_HASHCODE("creature_attack_ranged_medium"));
		animList.add(STRING_HASHCODE("droid_attack_light"));
		animList.add(STRING_HASHCODE("droid_attack_medium"));
		animList.add(STRING_HASHCODE("fire_turret_light"));
		animList.add(STRING_HASHCODE("fire_turret_medium"));
		animList.add(STRING_HASHCODE("fire_turret"));
	}

};

TEST_F(CombatAnimTest, TestAnimationNames) {
	CommandConfigManager* man = new CommandConfigManager(NULL);
	CommandList* list = new CommandList();

	man->registerSpecialCommands(list);
	man->loadSlashCommandsFile();


	ASSERT_EQ(CommandConfigManager::ERROR_CODE, 0);

	HashTableIterator<uint32, Reference<QueueCommand*> > iter;
	while(iter.hasNext()) {
		Reference<QueueCommand*> command = iter.getNextValue();
		if(command->isCombatCommand()) {
			CombatQueueCommand* combatCommand = command.castTo<CombatQueueCommand*>();
			uint8 animType = combatCommand->getAnimType();
			if (animType == CombatQueueCommand::GENERATE_NONE) {
				String anim = combatCommand->getAnimationString();
				if(!anim.isEmpty()) {
					ASSERT_TRUE(animList.contains(anim.hashCode()));
				}
			} else if (animType == CombatQueueCommand::GENERATE_RANGED) {
				String anim = combatCommand->getAnimation(dummyCreature, dummyWeapon, CombatManager::HIT_HEAD, 25);
				ASSERT_TRUE(animList.contains(anim.hashCode()));
				anim = combatCommand->getAnimation(dummyCreature, dummyWeapon, CombatManager::HIT_HEAD, 200);
				ASSERT_TRUE(animList.contains(anim.hashCode()));
				String anim = combatCommand->getAnimation(dummyCreature, dummyWeapon, CombatManager::HIT_BODY, 25);
				ASSERT_TRUE(animList.contains(anim.hashCode()));
				anim = combatCommand->getAnimation(dummyCreature, dummyWeapon, CombatManager::HIT_BODY, 200);
				ASSERT_TRUE(animList.contains(anim.hashCode()));
			}
		}
	}

	delete man;
}



