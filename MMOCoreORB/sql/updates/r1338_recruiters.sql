/*
MySQL Data Transfer
Source Host: swgemu
Source Database: swgemu
Target Host: swgemu
Target Database: swgemu
Date: 2/24/2009 10:05:13 AM
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for recruiters
-- ----------------------------
DROP TABLE IF EXISTS `recruiters`;
CREATE TABLE `recruiters` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `planet_id` tinyint(1) unsigned NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `oY` float NOT NULL,
  `oW` float NOT NULL,
  `cell_id` bigint(20) unsigned NOT NULL default '0',
  `type` tinyint(1) unsigned NOT NULL COMMENT '1 = imperial 2= rebel',
  PRIMARY KEY  (`id`),
  KEY `SECONDARY` (`planet_id`)
) ENGINE=MyISAM AUTO_INCREMENT=19 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records 
-- ----------------------------
INSERT INTO `recruiters` VALUES ('2', '5', '-4928', '4231', '0', '1', '0.053', '0', '1');
INSERT INTO `recruiters` VALUES ('1', '5', '-4936', '4231', '0', '1', '0.053', '0', '1');
INSERT INTO `recruiters` VALUES ('3', '5', '5307', '-1584', '0', '0.6', '0.8', '0', '1');
INSERT INTO `recruiters` VALUES ('4', '5', '-29', '-1.2', '-0.89', '0.6', '0.8', '119', '2');
INSERT INTO `recruiters` VALUES ('5', '0', '6719', '-5804', '315', '1', '0.037', '0', '1');
INSERT INTO `recruiters` VALUES ('6', '0', '-29', '0.5', '-0.89', '0.6', '0.8', '8105504', '2');
INSERT INTO `recruiters` VALUES ('7', '0', '-29', '0.5', '-0.89', '0.6', '0.8', '2625363', '2');
INSERT INTO `recruiters` VALUES ('8', '8', '-6.7', '-6.9', '-3.9', '0.45', '0.89', '1213349', '2');
INSERT INTO `recruiters` VALUES ('9', '8', '-1275', '-3594', '0', '-0.6', '0.8', '0', '1');
INSERT INTO `recruiters` VALUES ('10', '8', '-1138', '-3897', '98', '0', '1', '0', '1');
INSERT INTO `recruiters` VALUES ('11', '8', '-0.86', '-8', '0.4', '0.45', '0.89', '1280131', '1');
INSERT INTO `recruiters` VALUES ('12', '6', '3683', '-6460', '0', '0.77', '-0.63', '0', '2');
INSERT INTO `recruiters` VALUES ('13', '7', '-2192', '2269', '0', '-0.42', '0.9', '0', '1');
INSERT INTO `recruiters` VALUES ('14', '7', '-28.4145', '-1.7825', '-0.89', '0.66', '0.74', '3175399', '2');
INSERT INTO `recruiters` VALUES ('15', '1', '-4196.99', '-2411.57', '3', '-0.65', '0.75', '0', '1');
INSERT INTO `recruiters` VALUES ('16', '6', '5348', '5616', '80', '-0.6', '1', '0', '1');
INSERT INTO `recruiters` VALUES ('17', '5', '4826', '-4696', '0', '0.72', '-0.69', '0', '2');
INSERT INTO `recruiters` VALUES ('18', '4', '-1843.79', '-3069.92', '12', '0.880756', '0.47357', '0', '1');
