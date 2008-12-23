/*
MySQL Data Transfer
Source Host: localhost
Source Database: swgemu
Target Host: localhost
Target Database: swgemu
Date: 11/6/2008 8:48:35 PM
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for no_build_zones
-- ----------------------------
DROP TABLE IF EXISTS `no_build_zones`;
CREATE TABLE `no_build_zones` (
  `nbz_id` int(11) unsigned NOT NULL auto_increment,
  `planet_id` int(11) NOT NULL default '0',
  `zone_name` char(255) default 'region_name',
  `zone_file` char(255) default 'region_file',
  `zone_type` char(255) default NULL,
  `x` float NOT NULL default '0',
  `z` float NOT NULL default '0',
  `radius` float NOT NULL default '0',
  PRIMARY KEY  (`nbz_id`)
) ENGINE=InnoDB AUTO_INCREMENT=182 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records 
-- ----------------------------
INSERT INTO `no_build_zones` VALUES ('1', '0', 'coronet', 'corellia_region_names', 'city', '-178', '-4504', '1181');
INSERT INTO `no_build_zones` VALUES ('2', '0', 'tyrena', 'corellia_region_names', 'city', '-5140', '-2450', '900');
INSERT INTO `no_build_zones` VALUES ('3', '0', 'bela_vista', 'corellia_region_names', 'city', '6766', '-5692', '970');
INSERT INTO `no_build_zones` VALUES ('4', '0', 'kor_vella', 'corellia_region_names', 'city', '-3420', '3146', '1220');
INSERT INTO `no_build_zones` VALUES ('5', '0', 'doaba_guerfel', 'corellia_region_names', 'city', '3274', '5582', '925');
INSERT INTO `no_build_zones` VALUES ('6', '0', 'vreni_island', 'corellia_region_names', 'city', '-5538', '-6176', '820');
INSERT INTO `no_build_zones` VALUES ('7', '0', 'corellia_badge', 'corsec_base', 'poi_badge', '5291', '1494', '400');
INSERT INTO `no_build_zones` VALUES ('8', '0', 'corellia_badge', 'grand_theater', 'poi_badge', '-5418', '-6248', '350');
INSERT INTO `no_build_zones` VALUES ('9', '0', 'corellia_badge', 'crystal_fountain', 'poi_badge', '6767', '-5617', '360');
INSERT INTO `no_build_zones` VALUES ('10', '0', 'corellia_badge', 'agrilat_swamp', 'poi_badge', '1084', '4176', '350');
INSERT INTO `no_build_zones` VALUES ('11', '0', 'corellia_badge', 'rebel_hideout', 'poi_badge', '-6530', '5967', '400');
INSERT INTO `no_build_zones` VALUES ('12', '0', 'hideout', 'corellia', 'poi', '-6584', '5915', '300');
INSERT INTO `no_build_zones` VALUES ('13', '0', 'corsecbase', 'corellia', 'poi', '5291', '1494', '300');
INSERT INTO `no_build_zones` VALUES ('14', '0', 'grandtheater', 'corellia', 'poi', '-5421', '-6212', '300');
INSERT INTO `no_build_zones` VALUES ('15', '0', 'crystalfountain', 'corellia', 'poi', '6760', '-5617', '300');
INSERT INTO `no_build_zones` VALUES ('16', '0', 'agrilat', 'corellia', 'poi', '1402', '3802', '300');
INSERT INTO `no_build_zones` VALUES ('17', '0', 'drall', 'corellia', 'poi', '1042', '4193', '300');
INSERT INTO `no_build_zones` VALUES ('18', '0', 'nyax', 'corellia', 'poi', '1414', '-317', '300');
INSERT INTO `no_build_zones` VALUES ('19', '0', 'stronghold', 'corellia', 'poi', '4651', '-5617', '1000');
INSERT INTO `no_build_zones` VALUES ('20', '0', 'afarathu', 'corellia', 'poi', '-2483', '2907', '300');
INSERT INTO `no_build_zones` VALUES ('21', '0', 'racingagrilat', 'corellia', 'poi', '1859', '4642', '300');
INSERT INTO `no_build_zones` VALUES ('22', '1', 'an_outpost', 'dantooine_region_names', 'city', '-640', '2486', '735');
INSERT INTO `no_build_zones` VALUES ('23', '1', 'an_outpost', 'dantooine_region_names', 'city', '1588', '-6399', '735');
INSERT INTO `no_build_zones` VALUES ('24', '1', 'an_imperial_outpost', 'dantooine_region_names', 'city', '-4224', '-2400', '850');
INSERT INTO `no_build_zones` VALUES ('25', '1', 'dantooine_badge', 'dantari_village', 'poi_badge', '-3862', '-5706', '350');
INSERT INTO `no_build_zones` VALUES ('26', '1', 'dantooine_badge', 'dantari_rock_village', 'poi_badge', '-7156', '-883', '350');
INSERT INTO `no_build_zones` VALUES ('27', '1', 'dantooine_badge', 'ab_rebel_base', 'poi_badge', '-6836', '5520', '325');
INSERT INTO `no_build_zones` VALUES ('28', '1', 'dantooine_badge', 'jedi_temple', 'poi_badge', '4195', '5203', '325');
INSERT INTO `no_build_zones` VALUES ('29', '1', 'dantari1', 'dantooine', 'poi', '-3929', '-5632', '300');
INSERT INTO `no_build_zones` VALUES ('30', '1', 'dantari2', 'dantooine', 'poi', '-7144', '-1053', '300');
INSERT INTO `no_build_zones` VALUES ('31', '1', 'dantari3', 'dantooine', 'poi', '5655', '-589', '300');
INSERT INTO `no_build_zones` VALUES ('32', '1', 'abandoned', 'dantooine', 'poi', '-6858', '5725', '300');
INSERT INTO `no_build_zones` VALUES ('33', '1', 'jeditemple', 'dantooine', 'poi', '4258', '5374', '300');
INSERT INTO `no_build_zones` VALUES ('34', '1', 'cystalhunter', 'dantooine', 'poi', '-6259', '7336', '300');
INSERT INTO `no_build_zones` VALUES ('35', '1', 'janta', 'dantooine', 'poi', '6994', '-4110', '300');
INSERT INTO `no_build_zones` VALUES ('37', '1', 'mokk', 'dantooine', 'poi', '-7258', '-3320', '300');
INSERT INTO `no_build_zones` VALUES ('38', '1', 'kunga', 'dantooine', 'poi', '-368', '-240', '300');
INSERT INTO `no_build_zones` VALUES ('39', '1', 'warren', 'dantooine', 'poi', '-580', '-3763', '1000');
INSERT INTO `no_build_zones` VALUES ('40', '2', 'trade_outpost', 'dathomir_region_names', 'outpost', '599', '3046', '410');
INSERT INTO `no_build_zones` VALUES ('41', '2', 'science_outpost', 'dathomir_region_names', 'outpost', '-85', '-1600', '425');
INSERT INTO `no_build_zones` VALUES ('42', '2', 'dathomir_badge', 'imp_prison', 'poi_badge', '-6304', '753', '400');
INSERT INTO `no_build_zones` VALUES ('43', '2', 'dathomir_badge', 'tarpits', 'poi_badge', '652', '-4888', '350');
INSERT INTO `no_build_zones` VALUES ('44', '2', 'dathomir_badge', 'lesser_sarlacc', 'poi_badge', '-2101', '3165', '350');
INSERT INTO `no_build_zones` VALUES ('45', '2', 'dathomir_badge', 'escape_pod', 'poi_badge', '-4427', '586', '325');
INSERT INTO `no_build_zones` VALUES ('46', '2', 'dathomir_badge', 'lesser_misty_fall', 'poi_badge', '3558', '1554', '325');
INSERT INTO `no_build_zones` VALUES ('47', '2', 'dathomir_badge', 'downed_ship', 'poi_badge', '5585', '1903', '350');
INSERT INTO `no_build_zones` VALUES ('48', '2', 'dathomir_badge', 'great_misty_fall', 'poi_badge', '3021', '1289', '325');
INSERT INTO `no_build_zones` VALUES ('49', '2', 'a_imperial_outpost', 'dathomir_region_name', 'outpost', '-6090', '1010', '350');
INSERT INTO `no_build_zones` VALUES ('50', '2', 'prison', 'dathomir', 'poi', '-6091', '1010', '1000');
INSERT INTO `no_build_zones` VALUES ('51', '2', 'lessersarlacc', 'dathomir', 'poi', '-2091', '3177', '300');
INSERT INTO `no_build_zones` VALUES ('52', '2', 'dathpod', 'dathomir', 'poi', '-4446', '596', '300');
INSERT INTO `no_build_zones` VALUES ('53', '2', 'mistyfalls', 'dathomir', 'poi', '3566', '1560', '300');
INSERT INTO `no_build_zones` VALUES ('54', '2', 'tarpit', 'dathomir', 'poi', '651', '-4888', '300');
INSERT INTO `no_build_zones` VALUES ('55', '2', 'nightsister', 'dathomir', 'poi', '-3946', '-50', '300');
INSERT INTO `no_build_zones` VALUES ('56', '2', 'singing', 'dathomir', 'poi', '678', '4079', '1000');
INSERT INTO `no_build_zones` VALUES ('57', '2', 'nightvssing', 'dathomir', 'poi', '-2450', '1521', '1000');
INSERT INTO `no_build_zones` VALUES ('58', '2', 'nightspider', 'dathomir', 'poi', '-1219', '6262', '300');
INSERT INTO `no_build_zones` VALUES ('59', '2', 'slavecamp', 'dathomir', 'poi', '2428', '-1701', '300');
INSERT INTO `no_build_zones` VALUES ('60', '3', 'an_outpost', 'endor_region_names', 'outpost', '-905', '1584', '430');
INSERT INTO `no_build_zones` VALUES ('61', '3', 'an_outpost', 'endor_region_names', 'outpost', '3221', '-3471', '400');
INSERT INTO `no_build_zones` VALUES ('62', '3', 'endor_badge', 'ewok_tree_vill', 'poi_badge', '4596', '-2423', '400');
INSERT INTO `no_build_zones` VALUES ('63', '3', 'endor_badge', 'dulok_village', 'poi_badge', '6051', '-2477', '400');
INSERT INTO `no_build_zones` VALUES ('64', '3', 'endor_badge', 'ewok_lake_vill', 'poi_badge', '-650', '-5076', '400');
INSERT INTO `no_build_zones` VALUES ('65', '3', 'endor_badge', 'maruaders_stronghold', 'poi_badge', '-4628', '-2273', '350');
INSERT INTO `no_build_zones` VALUES ('66', '3', 'tree1', 'endor', 'poi', '6', '-5', '300');
INSERT INTO `no_build_zones` VALUES ('67', '3', 'tree2', 'endor', 'poi', '4661', '-2425', '300');
INSERT INTO `no_build_zones` VALUES ('68', '3', 'lake1', 'endor', 'poi', '1578', '-3271', '300');
INSERT INTO `no_build_zones` VALUES ('69', '3', 'lake2', 'endor', 'poi', '-605', '-4940', '300');
INSERT INTO `no_build_zones` VALUES ('70', '3', 'dulok1', 'endor', 'poi', '5921', '-2514', '300');
INSERT INTO `no_build_zones` VALUES ('71', '3', 'dulok2', 'endor', 'poi', '-1287', '2904', '300');
INSERT INTO `no_build_zones` VALUES ('72', '3', 'marauder', 'endor', 'poi', '-4838', '-2339', '300');
INSERT INTO `no_build_zones` VALUES ('73', '3', 'korga', 'endor', 'poi', '2286', '3459', '300');
INSERT INTO `no_build_zones` VALUES ('74', '3', 'orphan', 'endor', 'poi', '-6853', '679', '300');
INSERT INTO `no_build_zones` VALUES ('75', '3', 'jinda', 'endor', 'poi', '-1695', '-56', '300');
INSERT INTO `no_build_zones` VALUES ('76', '4', 'nyms_stronghold', 'lok_region_names', 'city', '440', '5029', '915');
INSERT INTO `no_build_zones` VALUES ('77', '4', 'an_imperial_outpost', 'lok_region_names', 'outpost', '-1920', '-3084', '436');
INSERT INTO `no_build_zones` VALUES ('78', '4', 'lok_badge', 'imp_outpost', 'poi_badge', '-1814', '-3086', '350');
INSERT INTO `no_build_zones` VALUES ('79', '4', 'lok_badge', 'mount_chaolt', 'poi_badge', '3091', '-4638', '350');
INSERT INTO `no_build_zones` VALUES ('80', '4', 'lok_badge', 'kimo_skeleton', 'poi_badge', '4562', '-1156', '325');
INSERT INTO `no_build_zones` VALUES ('81', '4', 'volcano', 'lok', 'poi', '3091', '-4638', '300');
INSERT INTO `no_build_zones` VALUES ('82', '4', 'lokimpoutpost', 'lok', 'poi', '-1785', '-3087', '1000');
INSERT INTO `no_build_zones` VALUES ('84', '4', 'kimogilaskel', 'lok', 'poi', '4572', '-1114', '300');
INSERT INTO `no_build_zones` VALUES ('85', '4', 'kimogilatown', 'lok', 'poi', '-68', '2650', '300');
INSERT INTO `no_build_zones` VALUES ('86', '4', 'canyoncosair', 'lok', 'poi', '-3792', '-3904', '300');
INSERT INTO `no_build_zones` VALUES ('87', '4', 'bloodrazor', 'lok', 'poi', '3703', '2274', '300');
INSERT INTO `no_build_zones` VALUES ('88', '4', 'droidcave', 'lok', 'poi', '3364', '-4923', '300');
INSERT INTO `no_build_zones` VALUES ('89', '4', 'greatmaze', 'lok', 'poi', '3824', '-465', '300');
INSERT INTO `no_build_zones` VALUES ('90', '5', 'theed', 'naboo_region_names', 'city', '-5488', '4380', '1210');
INSERT INTO `no_build_zones` VALUES ('91', '5', 'keren', 'naboo_region_names', 'city', '1888', '2700', '1150');
INSERT INTO `no_build_zones` VALUES ('92', '5', 'moenia', 'naboo_region_names', 'city', '4836', '-4830.5', '877');
INSERT INTO `no_build_zones` VALUES ('93', '5', 'deeja_peak', 'naboo_region_names', 'city', '4686', '-1375', '820');
INSERT INTO `no_build_zones` VALUES ('94', '5', 'kaadara', 'naboo_region_names', 'city', '5288', '6687', '825');
INSERT INTO `no_build_zones` VALUES ('95', '5', 'lake_retreat', 'naboo_region_name', 'city', '-5488', '-6', '625');
INSERT INTO `no_build_zones` VALUES ('96', '5', 'naboo_badge', 'theed_waterfall', 'poi_badge', '-4628', '4207', '325');
INSERT INTO `no_build_zones` VALUES ('97', '5', 'naboo_badge', 'peak_waterfall', 'poi_badge', '5157', '-1646', '325');
INSERT INTO `no_build_zones` VALUES ('98', '5', 'naboo_badge', 'amidala_beach', 'poi_badge', '-5828', '-93', '350');
INSERT INTO `no_build_zones` VALUES ('99', '5', 'naboo_badge', 'gungan_place', 'poi_badge', '-2066', '-5423', '350');
INSERT INTO `no_build_zones` VALUES ('100', '5', 'gungan', 'naboo', 'poi', '-2104', '-5408', '300');
INSERT INTO `no_build_zones` VALUES ('101', '5', 'theedfalls', 'naboo', 'poi', '-4627', '4207', '300');
INSERT INTO `no_build_zones` VALUES ('102', '5', 'deejafalls', 'naboo', 'poi', '5174', '-1550', '300');
INSERT INTO `no_build_zones` VALUES ('103', '5', 'amidalasbeach', 'naboo', 'poi', '-5828', '-93', '300');
INSERT INTO `no_build_zones` VALUES ('104', '5', 'impvsgun', 'naboo', 'poi', '4825', '-3820', '1000');
INSERT INTO `no_build_zones` VALUES ('105', '5', 'mordran', 'naboo', 'poi', '-1952', '-5279', '300');
INSERT INTO `no_build_zones` VALUES ('106', '5', 'weaponfacility', 'naboo', 'poi', '-6456', '-3235', '1000');
INSERT INTO `no_build_zones` VALUES ('107', '5', 'narglatch', 'naboo', 'poi', '5864', '-4681', '300');
INSERT INTO `no_build_zones` VALUES ('108', '5', 'mauler', 'naboo', 'poi', '2963', '1109', '300');
INSERT INTO `no_build_zones` VALUES ('109', '5', 'racingkeren', 'naboo', 'poi', '1396', '2686', '300');
INSERT INTO `no_build_zones` VALUES ('110', '6', 'narmle', 'rori_region_names', 'city', '-5140', '-2368', '850');
INSERT INTO `no_build_zones` VALUES ('111', '6', 'restuss', 'rori_region_names', 'city', '5318', '5680', '925');
INSERT INTO `no_build_zones` VALUES ('112', '6', 'a_rebel_outpost', 'rori_region_names', 'outpost', '3677', '-6447', '380');
INSERT INTO `no_build_zones` VALUES ('113', '6', 'rori_badge', 'hyperdrive_fac', 'poi_badge', '-1130', '4544', '400');
INSERT INTO `no_build_zones` VALUES ('114', '6', 'rori_badge', 'imp_camp', 'poi_badge', '-5633', '-5661', '350');
INSERT INTO `no_build_zones` VALUES ('115', '6', 'rori_badge', 'reb_outpost', 'poi_badge', '3664', '-6501', '400');
INSERT INTO `no_build_zones` VALUES ('116', '6', 'rori_badge', 'spice_mine', 'poi_badge', '7371', '169', '350');
INSERT INTO `no_build_zones` VALUES ('117', '6', 'reboutpost', 'rori', 'poi', '3669', '-6586', '1000');
INSERT INTO `no_build_zones` VALUES ('118', '6', 'kobala', 'rori', 'poi', '7304', '63', '300');
INSERT INTO `no_build_zones` VALUES ('119', '6', 'impencampment', 'rori', 'poi', '-5651', '-5660', '1000');
INSERT INTO `no_build_zones` VALUES ('120', '6', 'hyperdrive', 'rori', 'poi', '-1070', '4542', '300');
INSERT INTO `no_build_zones` VALUES ('121', '6', 'garyn', 'rori', 'poi', '-6004', '-1851', '300');
INSERT INTO `no_build_zones` VALUES ('122', '6', 'borglebat', 'rori', 'poi', '902', '-4933', '300');
INSERT INTO `no_build_zones` VALUES ('123', '6', 'cobral', 'rori', 'poi', '5464', '5045', '300');
INSERT INTO `no_build_zones` VALUES ('124', '6', 'tortoncave', 'rori', 'poi', '-1814', '-4533', '300');
INSERT INTO `no_build_zones` VALUES ('125', '6', 'poacher', 'rori', 'poi', '773', '-2109', '300');
INSERT INTO `no_build_zones` VALUES ('126', '6', 'barkmite', 'rori', 'poi', '3584', '5419', '300');
INSERT INTO `no_build_zones` VALUES ('127', '6', 'swamptown', 'rori', 'poi', '-1986', '3339', '300');
INSERT INTO `no_build_zones` VALUES ('128', '7', 'dearic', 'talus_region_names', 'city', '422', '-3004', '1035');
INSERT INTO `no_build_zones` VALUES ('129', '7', 'nashal', 'talus_region_names', 'city', '4163', '5220', '795');
INSERT INTO `no_build_zones` VALUES ('130', '7', 'an_imperial_outpost', 'talus_region_names', 'outpost', '-2178', '2300', '450');
INSERT INTO `no_build_zones` VALUES ('131', '7', 'talus_badge', 'durbin', 'poi_badge', '4133', '962', '350');
INSERT INTO `no_build_zones` VALUES ('132', '7', 'talus_badge', 'imp_outpost', 'poi_badge', '-2184', '2405', '350');
INSERT INTO `no_build_zones` VALUES ('133', '7', 'talus_badge', 'imp_reb_batle', 'poi_badge', '-2452', '3846', '325');
INSERT INTO `no_build_zones` VALUES ('134', '7', 'talus_badge', 'aquq_cave', 'poi_badge', '-4425', '-1414', '325');
INSERT INTO `no_build_zones` VALUES ('135', '7', 'impoutpost', 'talus', 'poi', '-2193', '2494', '1000');
INSERT INTO `no_build_zones` VALUES ('136', '7', 'creaturevillage', 'talus', 'poi', '4174', '1162', '300');
INSERT INTO `no_build_zones` VALUES ('137', '7', 'impvsreb', 'talus', 'poi', '-2595', '3724', '1000');
INSERT INTO `no_build_zones` VALUES ('138', '7', 'aqualishcave', 'talus', 'poi', '-4268', '-1432', '300');
INSERT INTO `no_build_zones` VALUES ('139', '7', 'weapondepot', 'talus', 'poi', '-4899', '-3137', '1000');
INSERT INTO `no_build_zones` VALUES ('140', '7', 'detainment', 'talus', 'poi', '4963', '-5977', '1000');
INSERT INTO `no_build_zones` VALUES ('141', '7', 'corvsflail', 'talus', 'poi', '2938', '6004', '300');
INSERT INTO `no_build_zones` VALUES ('142', '7', 'flynock', 'talus', 'poi', '1508', '-858', '300');
INSERT INTO `no_build_zones` VALUES ('143', '7', 'erransif', 'talus', 'poi', '2145', '-5576', '300');
INSERT INTO `no_build_zones` VALUES ('144', '7', 'aakuan', 'talus', 'poi', '5939', '4562', '300');
INSERT INTO `no_build_zones` VALUES ('145', '7', 'khamurrabio', 'talus', 'poi', '-4816', '-4752', '300');
INSERT INTO `no_build_zones` VALUES ('146', '7', 'decaymite', 'talus', 'poi', '-5505', '-4680', '300');
INSERT INTO `no_build_zones` VALUES ('147', '7', 'binyare', 'talus', 'poi', '5526', '-4073', '300');
INSERT INTO `no_build_zones` VALUES ('148', '8', 'bestine', 'tatooine_region_names', 'city', '-1204', '-3692', '975');
INSERT INTO `no_build_zones` VALUES ('149', '8', 'mos_espa', 'tatooine_region_names', 'city', '-2878', '2226', '1035');
INSERT INTO `no_build_zones` VALUES ('150', '8', 'mos_eisley', 'tatooine_region_names', 'city', '3569', '-4818', '1000');
INSERT INTO `no_build_zones` VALUES ('151', '8', 'mos_entha', 'tatooine_region_names', 'city', '1470', '3248', '990');
INSERT INTO `no_build_zones` VALUES ('152', '8', 'mos_taike', 'tatooine_region_names', 'city', '3855', '2338', '770');
INSERT INTO `no_build_zones` VALUES ('153', '8', 'anchorhead', 'tatooine_region_names', 'city', '40', '-5348', '930');
INSERT INTO `no_build_zones` VALUES ('154', '8', 'wayfar', 'tatooine_region_names', 'city', '-5157', '-6549', '810');
INSERT INTO `no_build_zones` VALUES ('155', '8', 'tatooine_badge', 'lars_home', 'poi_badge', '-2579', '-5500', '325');
INSERT INTO `no_build_zones` VALUES ('156', '8', 'tatooine_badge', 'bens_hut', 'poi_badge', '-4512', '-2270', '325');
INSERT INTO `no_build_zones` VALUES ('157', '8', 'tatooine_badge', 'sarlacc', 'poi_badge', '-6176', '-3372', '325');
INSERT INTO `no_build_zones` VALUES ('158', '8', 'tatooine_badge', 'escape_pod', 'poi_badge', '-3930', '-4425', '325');
INSERT INTO `no_build_zones` VALUES ('159', '8', 'tatooine_badge', 'krayt_skull', 'poi_badge', '-4650', '-4363', '325');
INSERT INTO `no_build_zones` VALUES ('160', '8', 'tatooine_badge', 'krayt_graveyard', 'poi_badge', '7428', '4563', '350');
INSERT INTO `no_build_zones` VALUES ('161', '8', 'tatooine_badge', 'fort_tusken', 'poi_badge', '-3969', '6267', '350');
INSERT INTO `no_build_zones` VALUES ('162', '8', 'jabbaspalace', 'tatooine', 'poi', '-5856', '-6183', '1000');
INSERT INTO `no_build_zones` VALUES ('163', '8', 'forttusken', 'tatooine', 'poi', '-3980', '6311', '1000');
INSERT INTO `no_build_zones` VALUES ('164', '8', 'jawatraders', 'tatooine', 'poi', '-6141', '1854', '300');
INSERT INTO `no_build_zones` VALUES ('165', '8', 'darklighter', 'tatooine', 'poi', '-718', '-6683', '300');
INSERT INTO `no_build_zones` VALUES ('166', '8', 'kraytgraveyard', 'tatooine', 'poi', '6839', '4320', '300');
INSERT INTO `no_build_zones` VALUES ('167', '8', 'larshomestead', 'tatooine', 'poi', '-2579', '-5500', '300');
INSERT INTO `no_build_zones` VALUES ('168', '8', 'kenobishouse', 'tatooine', 'poi', '-4512', '-2270', '300');
INSERT INTO `no_build_zones` VALUES ('169', '8', 'sarlacc', 'tatooine', 'poi', '-6169', '-3387', '300');
INSERT INTO `no_build_zones` VALUES ('170', '8', 'pod', 'tatooine', 'poi', '-3931', '-4397', '300');
INSERT INTO `no_build_zones` VALUES ('171', '8', 'skeleton', 'tatooine', 'poi', '-4632', '-4346', '300');
INSERT INTO `no_build_zones` VALUES ('172', '8', 'racingmosespa', 'tatooine', 'poi', '2380', '5000', '300');
INSERT INTO `no_build_zones` VALUES ('173', '9', 'an_outpost', 'yavin4_region_names', 'outpost', '-312', '4865', '400');
INSERT INTO `no_build_zones` VALUES ('174', '9', 'an_oupost', 'yavin4_region_names', 'outpost', '-6925', '-5707', '430');
INSERT INTO `no_build_zones` VALUES ('175', '9', 'yavin_badge', 'exar_kun', 'poi_badge', '5076', '5537', '325');
INSERT INTO `no_build_zones` VALUES ('176', '9', 'yavin_badge', 'blueleaf_temple', 'poi_badge', '-875', '-2047', '350');
INSERT INTO `no_build_zones` VALUES ('177', '9', 'yavin_badge', 'woolamander_palace', 'poi_badge', '519', '-646', '325');
INSERT INTO `no_build_zones` VALUES ('178', '9', 'woolamander', 'yavin4', 'poi', '467', '-693', '300');
INSERT INTO `no_build_zones` VALUES ('179', '9', 'blueleaf', 'yavin4', 'poi', '-976', '-2039', '300');
INSERT INTO `no_build_zones` VALUES ('180', '9', 'exarkun', 'yavin4', 'poi', '5163', '5539', '300');
INSERT INTO `no_build_zones` VALUES ('181', '9', 'massassi', 'yavin4', 'poi', '-3226', '-3139', '300');
