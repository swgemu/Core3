/*
MySQL Data Transfer
Source Host: www.sunrecycler.com
Source Database: swgemuOR
Target Host: www.sunrecycler.com
Target Database: swgemuOR
Date: 6/15/2010 9:04:52 PM
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for badge_areas
-- ----------------------------
DROP TABLE IF EXISTS `badge_areas`;
CREATE TABLE `badge_areas` (
  `uid` tinyint(1) unsigned NOT NULL AUTO_INCREMENT,
  `planet_id` tinyint(1) unsigned NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL DEFAULT '0',
  `badge_id` tinyint(1) unsigned NOT NULL,
  PRIMARY KEY (`uid`),
  KEY `SECONDARY` (`planet_id`)
) ENGINE=MyISAM AUTO_INCREMENT=46 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records 
-- ----------------------------
INSERT INTO `badge_areas` VALUES ('1', '0', '5291', '1494', '1', '79');
INSERT INTO `badge_areas` VALUES ('2', '0', '-5418', '-6248', '24', '80');
INSERT INTO `badge_areas` VALUES ('3', '0', '6767', '-5617', '314', '81');
INSERT INTO `badge_areas` VALUES ('4', '0', '1084', '4176', '18', '20');
INSERT INTO `badge_areas` VALUES ('5', '0', '-6530', '5967', '398', '78');
INSERT INTO `badge_areas` VALUES ('6', '1', '-3862', '-5706', '2', '84');
INSERT INTO `badge_areas` VALUES ('7', '1', '-7156', '-883', '3', '85');
INSERT INTO `badge_areas` VALUES ('8', '1', '-6836', '5520', '53', '31');
INSERT INTO `badge_areas` VALUES ('9', '1', '4195', '5203', '9', '30');
INSERT INTO `badge_areas` VALUES ('10', '2', '-6304', '753', '128', '83');
INSERT INTO `badge_areas` VALUES ('11', '2', '652', '-4888', '77', '25');
INSERT INTO `badge_areas` VALUES ('12', '2', '-2101', '3165', '22', '26');
INSERT INTO `badge_areas` VALUES ('13', '2', '-4427', '586', '22', '27');
INSERT INTO `badge_areas` VALUES ('14', '2', '3558', '1554', '48', '28');
INSERT INTO `badge_areas` VALUES ('15', '2', '5585', '1903', '125', '82');
INSERT INTO `badge_areas` VALUES ('16', '2', '3021', '1289', '96', '29');
INSERT INTO `badge_areas` VALUES ('17', '3', '4596', '-2423', '10', '86');
INSERT INTO `badge_areas` VALUES ('18', '3', '6051', '-2477', '261', '88');
INSERT INTO `badge_areas` VALUES ('19', '3', '1454', '-3272', '1', '87');
INSERT INTO `badge_areas` VALUES ('20', '3', '-4628', '-2273', '90', '89');
INSERT INTO `badge_areas` VALUES ('21', '4', '-1814', '-3086', '12', '98');
INSERT INTO `badge_areas` VALUES ('22', '4', '3091', '-4638', '12', '24');
INSERT INTO `badge_areas` VALUES ('23', '4', '4562', '-1156', '13', '99');
INSERT INTO `badge_areas` VALUES ('24', '5', '-4614', '4261', '0', '75');
INSERT INTO `badge_areas` VALUES ('25', '5', '5157', '-1646', '390', '76');
INSERT INTO `badge_areas` VALUES ('26', '5', '-5828', '-93', '0', '77');
INSERT INTO `badge_areas` VALUES ('27', '5', '-2066', '-5423', '5', '19');
INSERT INTO `badge_areas` VALUES ('28', '6', '-1130', '4544', '77', '97');
INSERT INTO `badge_areas` VALUES ('29', '6', '-5633', '-5661', '75', '96');
INSERT INTO `badge_areas` VALUES ('30', '6', '3664', '-6501', '96', '95');
INSERT INTO `badge_areas` VALUES ('31', '6', '7371', '169', '97', '94');
INSERT INTO `badge_areas` VALUES ('32', '7', '4133', '962', '6', '90');
INSERT INTO `badge_areas` VALUES ('33', '7', '-2184', '2405', '20', '91');
INSERT INTO `badge_areas` VALUES ('34', '7', '-2452', '3846', '39', '92');
INSERT INTO `badge_areas` VALUES ('35', '7', '-4425', '-1414', '61', '93');
INSERT INTO `badge_areas` VALUES ('36', '8', '-2579', '-5500', '0', '17');
INSERT INTO `badge_areas` VALUES ('37', '8', '-4512', '-2270', '35', '12');
INSERT INTO `badge_areas` VALUES ('38', '8', '-6176', '-3372', '19', '16');
INSERT INTO `badge_areas` VALUES ('39', '8', '-3930', '-4425', '33', '15');
INSERT INTO `badge_areas` VALUES ('40', '8', '-4650', '-4363', '55', '14');
INSERT INTO `badge_areas` VALUES ('41', '8', '7428', '4563', '6', '18');
INSERT INTO `badge_areas` VALUES ('42', '8', '-3969', '6267', '60', '13');
INSERT INTO `badge_areas` VALUES ('43', '9', '5076', '5537', '73', '23');
INSERT INTO `badge_areas` VALUES ('44', '9', '-875', '-2047', '84', '22');
INSERT INTO `badge_areas` VALUES ('45', '9', '519', '-646', '81', '21');
