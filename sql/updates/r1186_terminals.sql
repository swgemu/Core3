/*
MySQL Data Transfer
Source Host: 192.168.1.153
Source Database: swgemu
Target Host: 192.168.1.153
Target Database: swgemu
Date: 21/01/2009 4:11:16 PM
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for terminals
-- ----------------------------
DROP TABLE IF EXISTS `terminals`;
CREATE TABLE `terminals` (
  `id` int(11) NOT NULL auto_increment,
  `parentid` bigint(20) NOT NULL default '0',
  `type` tinyint(4) NOT NULL default '0',
  `oX` float NOT NULL default '0',
  `oZ` float NOT NULL default '0',
  `oY` float NOT NULL default '0',
  `oW` float NOT NULL default '0',
  `X` float NOT NULL default '0',
  `Z` float NOT NULL default '0',
  `Y` float NOT NULL,
  `zoneid` tinyint(4) NOT NULL default '0',
  `attributes` text NOT NULL,
  PRIMARY KEY  USING BTREE (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=100 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records 
-- ----------------------------
INSERT INTO `terminals` VALUES ('1', '1106502', '5', '0', '0', '1', '0', '1', '-0.05', '-1', '8', '');
INSERT INTO `terminals` VALUES ('2', '1106502', '5', '0', '0', '0', '1', '1', '-0.05', '2', '8', '');
INSERT INTO `terminals` VALUES ('3', '1590893', '5', '0', '0', '-1', '0', '0', '-0.378', '-0.5', '8', '');
INSERT INTO `terminals` VALUES ('5', '1105881', '5', '0', '0', '0', '1', '1', '-0.05', '2', '8', '');
INSERT INTO `terminals` VALUES ('6', '1105881', '5', '0', '0', '1', '0', '1', '-0.05', '-1', '8', '');
INSERT INTO `terminals` VALUES ('7', '3565796', '5', '0', '0', '0', '1', '1', '-0.05', '2', '8', '');
INSERT INTO `terminals` VALUES ('8', '3565796', '5', '0', '0', '1', '0', '1', '-0.05', '-1', '8', '');
INSERT INTO `terminals` VALUES ('9', '1254763', '5', '0', '0', '0', '1', '1', '-0.05', '2', '8', '');
INSERT INTO `terminals` VALUES ('10', '1254763', '5', '0', '0', '1', '0', '1', '-0.05', '-1', '8', '');
INSERT INTO `terminals` VALUES ('11', '1233040', '5', '0', '0', '0', '1', '1', '-0.05', '2', '8', '');
INSERT INTO `terminals` VALUES ('12', '1233040', '5', '0', '0', '1', '0', '1', '-0.05', '-1', '8', '');
INSERT INTO `terminals` VALUES ('13', '1528389', '5', '0', '0', '-1', '0', '0', '-0.378', '-0.5', '8', '');
INSERT INTO `terminals` VALUES ('14', '1400866', '5', '0', '0', '-1', '0', '0', '-0.378', '-0.5', '8', '');
INSERT INTO `terminals` VALUES ('15', '1697352', '5', '0', '0', '0', '1', '1', '-0.05', '2', '5', '');
INSERT INTO `terminals` VALUES ('16', '1697352', '5', '0', '0', '1', '0', '1', '-0.05', '-1', '5', '');
INSERT INTO `terminals` VALUES ('17', '474325', '5', '0', '0', '0', '1', '1', '-0.05', '2', '5', '');
INSERT INTO `terminals` VALUES ('18', '474325', '5', '0', '0', '1', '0', '1', '-0.05', '-1', '5', '');
INSERT INTO `terminals` VALUES ('19', '1717560', '5', '0', '0', '0', '1', '1', '-0.05', '2', '5', '');
INSERT INTO `terminals` VALUES ('20', '1717560', '5', '0', '0', '1', '0', '1', '-0.05', '-1', '5', '');
INSERT INTO `terminals` VALUES ('21', '1650613', '5', '0', '0', '0', '1', '1', '-0.05', '2', '5', '');
INSERT INTO `terminals` VALUES ('22', '1650613', '5', '0', '0', '1', '0', '1', '-0.05', '-1', '5', '');
INSERT INTO `terminals` VALUES ('23', '1741514', '5', '0', '0', '0', '1', '1', '-0.05', '2', '5', '');
INSERT INTO `terminals` VALUES ('24', '1741514', '5', '0', '0', '1', '0', '1', '-0.05', '-1', '5', '');
INSERT INTO `terminals` VALUES ('25', '3605960', '5', '0', '0', '0', '1', '-4', '0.125', '-6', '3', '');
INSERT INTO `terminals` VALUES ('26', '4635543', '5', '0', '0', '1', '0', '1', '-0.05', '-1', '6', '');
INSERT INTO `terminals` VALUES ('32', '8615441', '5', '0', '0', '0', '1', '0', '0.125', '-6.5', '4', '');
INSERT INTO `terminals` VALUES ('27', '4635543', '5', '0', '0', '0', '1', '1', '-0.05', '2', '6', '');
INSERT INTO `terminals` VALUES ('28', '4695369', '5', '0', '0', '0', '1', '1', '-0.05', '2', '6', '');
INSERT INTO `terminals` VALUES ('29', '4695369', '5', '0', '0', '1', '0', '1', '-0.05', '-1', '6', '');
INSERT INTO `terminals` VALUES ('30', '2745625', '5', '0', '0', '-1', '0', '0', '-0.378', '-0.5', '4', '');
INSERT INTO `terminals` VALUES ('31', '6705357', '5', '0', '0', '0', '1', '0', '0.125', '-6.5', '3', '');
INSERT INTO `terminals` VALUES ('33', '4505608', '5', '0', '0', '0', '1', '0', '0.125', '-6.5', '6', '');
INSERT INTO `terminals` VALUES ('34', '4885426', '5', '0', '0', '0', '1', '0', '0.125', '-6.5', '1', '');
INSERT INTO `terminals` VALUES ('35', '1366006', '5', '0', '0', '0', '1', '0', '0.125', '-6.5', '1', '');
INSERT INTO `terminals` VALUES ('36', '1365995', '5', '0', '0', '0', '1', '0', '0.125', '-6.5', '1', '');
INSERT INTO `terminals` VALUES ('37', '3175406', '5', '0', '0', '0', '1', '1', '-0.05', '2', '7', '');
INSERT INTO `terminals` VALUES ('38', '3175406', '5', '0', '0', '1', '0', '1', '-0.05', '-1', '7', '');
INSERT INTO `terminals` VALUES ('54', '4345392', '5', '0', '0', '0', '1', '1', '-0.05', '2', '0', '');
INSERT INTO `terminals` VALUES ('41', '4965412', '5', '0', '0', '0', '1', '0', '0.125', '-6.5', '7', '');
INSERT INTO `terminals` VALUES ('42', '7925459', '5', '0', '0', '0', '1', '-4', '0.125', '-6', '9', '');
INSERT INTO `terminals` VALUES ('43', '3035596', '5', '0', '0', '0', '1', '0', '0.125', '-6.5', '9', '');
INSERT INTO `terminals` VALUES ('44', '1392860', '5', '0', '0', '0', '1', '-4', '0.125', '-6', '2', '');
INSERT INTO `terminals` VALUES ('45', '1392892', '5', '0', '0', '0', '1', '0', '0.125', '-6.5', '2', '');
INSERT INTO `terminals` VALUES ('46', '1855493', '5', '0', '0', '1', '0', '1', '-0.05', '-1', '0', '');
INSERT INTO `terminals` VALUES ('47', '1855493', '5', '0', '0', '0', '1', '1', '-0.05', '2', '0', '');
INSERT INTO `terminals` VALUES ('48', '1935515', '5', '0', '0', '1', '0', '1', '-0.05', '-1', '0', '');
INSERT INTO `terminals` VALUES ('49', '1935515', '5', '0', '0', '0', '1', '1', '-0.05', '2', '0', '');
INSERT INTO `terminals` VALUES ('65', '1935515', '6', '0', '0', '-0.7', '0.7', '8', '0.08', '3', '0', '');
INSERT INTO `terminals` VALUES ('56', '4265614', '5', '0', '0', '0', '1', '1', '-0.05', '2', '7', '');
INSERT INTO `terminals` VALUES ('55', '4345392', '5', '0', '0', '1', '0', '1', '-0.05', '-1', '0', '');
INSERT INTO `terminals` VALUES ('57', '4265614', '5', '0', '0', '1', '0', '1', '-0.05', '-1', '7', '');
INSERT INTO `terminals` VALUES ('64', '1855493', '6', '0', '0', '-0.7', '0.7', '8', '0.08', '3', '0', '');
INSERT INTO `terminals` VALUES ('60', '3005428', '5', '0', '0', '0', '1', '1', '-0.05', '2', '0', '');
INSERT INTO `terminals` VALUES ('61', '3005428', '5', '0', '0', '1', '0', '1', '-0.05', '-1', '0', '');
INSERT INTO `terminals` VALUES ('62', '2365903', '5', '0', '0', '1', '0', '1', '-0.05', '-1', '0', '');
INSERT INTO `terminals` VALUES ('63', '2365903', '5', '0', '0', '0', '1', '1', '-0.05', '2', '0', '');
INSERT INTO `terminals` VALUES ('66', '2365903', '6', '0', '0', '-0.7', '0.7', '8', '0.08', '3', '0', '');
INSERT INTO `terminals` VALUES ('67', '3005428', '6', '0', '0', '-0.7', '0.7', '8', '0.08', '3', '0', '');
INSERT INTO `terminals` VALUES ('68', '4345392', '6', '0', '0', '-0.7', '0.7', '8', '0.08', '3', '0', '');
INSERT INTO `terminals` VALUES ('69', '474325', '6', '0', '0', '-0.7', '0.7', '8', '0.08', '3', '5', '');
INSERT INTO `terminals` VALUES ('70', '1650613', '6', '0', '0', '-0.7', '0.7', '8', '0.08', '3', '5', '');
INSERT INTO `terminals` VALUES ('71', '1697352', '6', '0', '0', '-0.7', '0.7', '8', '0.08', '3', '5', '');
INSERT INTO `terminals` VALUES ('72', '1717560', '6', '0', '0', '-0.7', '0.7', '8', '0.08', '3', '5', '');
INSERT INTO `terminals` VALUES ('73', '1741514', '6', '0', '0', '-0.7', '0.7', '8', '0.08', '3', '5', '');
INSERT INTO `terminals` VALUES ('74', '4635543', '6', '0', '0', '-0.7', '0.7', '8', '0.08', '3', '6', '');
INSERT INTO `terminals` VALUES ('75', '4695369', '6', '0', '0', '-0.7', '0.7', '8', '0.08', '3', '6', '');
INSERT INTO `terminals` VALUES ('76', '3175406', '6', '0', '0', '-0.7', '0.7', '8', '0.08', '3', '7', '');
INSERT INTO `terminals` VALUES ('77', '4265614', '6', '0', '0', '-0.7', '0.7', '8', '0.08', '3', '7', '');
INSERT INTO `terminals` VALUES ('78', '1105881', '6', '0', '0', '-0.7', '0.7', '8', '0.08', '3', '8', '');
INSERT INTO `terminals` VALUES ('79', '1106504', '6', '0', '0', '0', '1', '8', '0.08', '3', '8', '');
INSERT INTO `terminals` VALUES ('80', '1233040', '6', '0', '0', '-0.7', '0.7', '8', '0.08', '3', '8', '');
INSERT INTO `terminals` VALUES ('81', '1254763', '6', '0', '0', '-0.7', '0.7', '8', '0.08', '3', '8', '');
INSERT INTO `terminals` VALUES ('82', '3565796', '6', '0', '0', '-0.7', '0.7', '8', '0.08', '3', '8', '');
INSERT INTO `terminals` VALUES ('83', '2745616', '6', '0', '0', '-0.7', '0.7', '5', '0.25', '4.7', '4', '');
INSERT INTO `terminals` VALUES ('84', '1400857', '6', '0', '0', '-0.7', '0.7', '5', '0.25', '4.7', '8', '');
INSERT INTO `terminals` VALUES ('85', '1400846', '6', '0', '0', '-0.7', '0.7', '5', '0.25', '4.7', '8', '');
INSERT INTO `terminals` VALUES ('86', '1495846', '6', '0', '0', '-0.7', '0.7', '5', '0.25', '4.7', '8', '');
INSERT INTO `terminals` VALUES ('87', '1365998', '6', '0', '0', '0.7', '0.7', '-5.5', '0.125', '-3.75', '1', '');
INSERT INTO `terminals` VALUES ('88', '1366009', '6', '0', '0', '0.7', '0.7', '-5.5', '0.125', '-3.75', '1', '');
INSERT INTO `terminals` VALUES ('89', '4885429', '6', '0', '0', '0.7', '0.7', '-5.5', '0.125', '-3.75', '1', '');
INSERT INTO `terminals` VALUES ('90', '1392895', '6', '0', '0', '0.7', '0.7', '-5.5', '0.125', '-3.75', '2', '');
INSERT INTO `terminals` VALUES ('91', '6705360', '6', '0', '0', '0.7', '0.7', '-5.5', '0.125', '-3.75', '3', '');
INSERT INTO `terminals` VALUES ('92', '8615444', '6', '0', '0', '0.7', '0.7', '-5.5', '0.125', '-3.75', '4', '');
INSERT INTO `terminals` VALUES ('93', '4505611', '6', '0', '0', '0.7', '0.7', '-5.5', '0.125', '-3.75', '6', '');
INSERT INTO `terminals` VALUES ('94', '4965415', '6', '0', '0', '0.7', '0.7', '-5.5', '0.125', '-3.75', '7', '');
INSERT INTO `terminals` VALUES ('95', '3035599', '6', '0', '0', '0.7', '0.7', '-5.5', '0.125', '-3.75', '9', '');
INSERT INTO `terminals` VALUES ('96', '1392858', '6', '0', '0', '1', '0', '4', '0.125', '4.5', '2', '');
INSERT INTO `terminals` VALUES ('97', '3605958', '6', '0', '0', '1', '0', '4', '0.125', '4.5', '3', '');
INSERT INTO `terminals` VALUES ('98', '7925457', '6', '0', '0', '1', '0', '4', '0.125', '4.5', '9', '');
INSERT INTO `terminals` VALUES ('99', '2203318222975', '8', '0', '0', '0', '1', '27.4', '-3.5', '-170.7', '42', '');
