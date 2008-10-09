/*
MySQL Data Transfer
Source Host: localhost
Source Database: swgemu
Target Host: localhost
Target Database: swgemu
Date: 10/9/2008 3:06:05 PM
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for ticket_terminals
-- ----------------------------
CREATE TABLE `ticket_terminals` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `transport_id` int(11) NOT NULL,
  `parent` bigint(20) unsigned NOT NULL,
  `pos_x` float NOT NULL,
  `pos_y` float NOT NULL,
  `pos_z` float NOT NULL,
  `dir_y` float NOT NULL,
  `dir_w` float NOT NULL,
  PRIMARY KEY  (`id`),
  KEY `SECONDARY` (`transport_id`)
) ENGINE=MyISAM AUTO_INCREMENT=106 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records 
-- ----------------------------
INSERT INTO `ticket_terminals` VALUES ('1', '1', '0', '6935', '-5545', '330.6', '-0.64', '0.8');
INSERT INTO `ticket_terminals` VALUES ('2', '2', '0', '6638', '-5912', '330.6', '0.75', '0.8');
INSERT INTO `ticket_terminals` VALUES ('3', '3', '0', '-319.5', '-4634', '28.6', '1', '0');
INSERT INTO `ticket_terminals` VALUES ('4', '4', '0', '-15', '-4402', '28.6', '1', '0');
INSERT INTO `ticket_terminals` VALUES ('5', '5', '0', '3079.5', '5002.5', '280.6', '0.75', '0.8');
INSERT INTO `ticket_terminals` VALUES ('6', '6', '0', '-3765.5', '3240.5', '86.6', '1', '0');
INSERT INTO `ticket_terminals` VALUES ('7', '7', '0', '-5011', '-2353', '21.6', '0', '0.8');
INSERT INTO `ticket_terminals` VALUES ('8', '8', '0', '-5607', '-2781', '21.6', '0.75', '0.8');
INSERT INTO `ticket_terminals` VALUES ('9', '9', '0', '-5542', '-6053', '16.6', '1', '0');
INSERT INTO `ticket_terminals` VALUES ('10', '10', '8565353', '3.19301', '-17.4439', '0.146595', '0.71', '-0.64');
INSERT INTO `ticket_terminals` VALUES ('11', '11', '7105354', '-3.19301', '-17.4439', '0.146595', '0.71', '-0.64');
INSERT INTO `ticket_terminals` VALUES ('12', '12', '2955586', '-3.19301', '-17.4439', '0.146595', '0.71', '-0.64');
INSERT INTO `ticket_terminals` VALUES ('13', '13', '2835561', '-3.19301', '-17.4439', '0.146595', '0.71', '-0.64');
INSERT INTO `ticket_terminals` VALUES ('14', '14', '6915359', '-3.19301', '17.4439', '0.146595', '0.71', '-0.64');
INSERT INTO `ticket_terminals` VALUES ('15', '15', '9875354', '-3.19301', '-17.4439', '0.146595', '0.71', '-0.64');
INSERT INTO `ticket_terminals` VALUES ('16', '16', '6705353', '-3.19301', '-17.4439', '0.146595', '0.71', '-0.64');
INSERT INTO `ticket_terminals` VALUES ('17', '17', '4705365', '-3.19301', '-17.4439', '0.146595', '0.71', '-0.65');
INSERT INTO `ticket_terminals` VALUES ('18', '18', '0', '5339', '-1585', '327.7', '-0.71', '0.7');
INSERT INTO `ticket_terminals` VALUES ('19', '19', '0', '5122', '6605', '-191.4', '0.42', '-0.83');
INSERT INTO `ticket_terminals` VALUES ('20', '20', '0', '2027.8', '2517', '19.7', '-0.71', '0.7');
INSERT INTO `ticket_terminals` VALUES ('21', '21', '0', '1576', '2845', '25.7', '1', '0');
INSERT INTO `ticket_terminals` VALUES ('22', '22', '0', '-5487', '-30', '-149.4', '-0.71', '0.7');
INSERT INTO `ticket_terminals` VALUES ('23', '23', '0', '4968.6', '-4901', '4.4', '-0.71', '0.7');
INSERT INTO `ticket_terminals` VALUES ('24', '24', '0', '-5863', '4181', '6.8', '0.72', '0.69');
INSERT INTO `ticket_terminals` VALUES ('25', '25', '0', '-5419', '4315', '6.8', '0', '1');
INSERT INTO `ticket_terminals` VALUES ('26', '26', '0', '-4990', '4075', '6.6', '-0.94', '0.38');
INSERT INTO `ticket_terminals` VALUES ('27', '27', '0', '-5244', '-2163.1', '81.3', '0.92', '-0.38');
INSERT INTO `ticket_terminals` VALUES ('28', '28', '0', '3668', '-6412', '96', '1', '0');
INSERT INTO `ticket_terminals` VALUES ('29', '29', '0', '5221', '5797', '80.7', '1', '0');
INSERT INTO `ticket_terminals` VALUES ('30', '30', '0', '689', '-3047', '6.6', '0', '0.8');
INSERT INTO `ticket_terminals` VALUES ('31', '31', '0', '-3.19301', '-17.4439', '0.14', '0.76', '0.64');
INSERT INTO `ticket_terminals` VALUES ('32', '32', '0', '4328', '5439', '10.6', '0.75', '0.8');
INSERT INTO `ticket_terminals` VALUES ('33', '33', '0', '54', '-5332', '52.6', '1', '0');
INSERT INTO `ticket_terminals` VALUES ('34', '34', '0', '-1092', '-3570.9', '12.6', '-0.64', '0.76');
INSERT INTO `ticket_terminals` VALUES ('35', '35', '0', '3418.5', '-4657.5', '5.6', '-0.51', '0.8');
INSERT INTO `ticket_terminals` VALUES ('36', '36', '0', '1738.5', '3191', '7.6', '1', '0');
INSERT INTO `ticket_terminals` VALUES ('37', '37', '0', '-2809.5', '2175', '5.6', '-0.15', '0.8');
INSERT INTO `ticket_terminals` VALUES ('38', '38', '0', '-3121', '2183', '5.6', '0.6', '0.8');
INSERT INTO `ticket_terminals` VALUES ('39', '39', '1512720', '-3.19301', '-17.4439', '0.146595', '0.71', '-0.64');
INSERT INTO `ticket_terminals` VALUES ('40', '40', '3035485', '-3.19301', '-17.4439', '0.146595', '0.71', '-0.64');
INSERT INTO `ticket_terminals` VALUES ('41', '41', '7795549', '-3.19301', '-17.4439', '0.146595', '0.71', '-0.64');
INSERT INTO `ticket_terminals` VALUES ('42', '42', '1692104', '-9.49707', '-45.2359', '7.97928', '-0.71', '1');
INSERT INTO `ticket_terminals` VALUES ('43', '42', '1692104', '9.49707', '-45.2359', '7.97928', '-0.71', '1');
INSERT INTO `ticket_terminals` VALUES ('44', '42', '1692103', '26.9453', '-67.1413', '0.749357', '1', '0');
INSERT INTO `ticket_terminals` VALUES ('45', '42', '1692102', '-26.9453', '-67.1413', '0.749357', '1', '0');
INSERT INTO `ticket_terminals` VALUES ('46', '43', '4215410', '-2.7419', '48.1677', '0.639421', '1', '1');
INSERT INTO `ticket_terminals` VALUES ('47', '43', '4215410', '12.6536', '51.1838', '0.639421', '-0.416129', '0.909306');
INSERT INTO `ticket_terminals` VALUES ('48', '43', '4215410', '2.54505', '48.1693', '0.639421', '-1', '1');
INSERT INTO `ticket_terminals` VALUES ('49', '43', '4215410', '-13.0021', '51.1865', '0.639421', '0.332372', '0.943148');
INSERT INTO `ticket_terminals` VALUES ('50', '45', '1741539', '-2.7419', '48.1677', '0.639421', '1', '1');
INSERT INTO `ticket_terminals` VALUES ('51', '45', '1741539', '12.6536', '51.1838', '0.639421', '-0.416129', '0.909306');
INSERT INTO `ticket_terminals` VALUES ('52', '45', '1741539', '2.54505', '48.1693', '0.639421', '-1', '1');
INSERT INTO `ticket_terminals` VALUES ('53', '45', '1741539', '-13.0021', '51.1865', '0.639421', '0.332372', '0.943148');
INSERT INTO `ticket_terminals` VALUES ('54', '44', '2125382', '-2.7419', '48.1677', '0.639421', '1', '1');
INSERT INTO `ticket_terminals` VALUES ('55', '44', '2125382', '12.6536', '51.1838', '0.639421', '-0.416129', '0.909306');
INSERT INTO `ticket_terminals` VALUES ('56', '44', '2125382', '2.54505', '48.1693', '0.639421', '-1', '1');
INSERT INTO `ticket_terminals` VALUES ('57', '44', '2125382', '-13.0021', '51.1865', '0.639421', '0.332372', '0.943148');
INSERT INTO `ticket_terminals` VALUES ('58', '46', '9665356', '-2.7419', '48.1677', '0.639421', '1', '1');
INSERT INTO `ticket_terminals` VALUES ('59', '46', '9665356', '12.6536', '51.1838', '0.639421', '-0.416129', '0.909306');
INSERT INTO `ticket_terminals` VALUES ('60', '46', '9665356', '2.54505', '48.1693', '0.639421', '-1', '1');
INSERT INTO `ticket_terminals` VALUES ('61', '46', '9665356', '-13.0021', '51.1865', '0.639421', '0.332372', '0.943148');
INSERT INTO `ticket_terminals` VALUES ('62', '47', '4255423', '-2.7419', '48.1677', '0.639421', '1', '1');
INSERT INTO `ticket_terminals` VALUES ('63', '47', '4255423', '12.6536', '51.1838', '0.639421', '-0.416129', '0.909306');
INSERT INTO `ticket_terminals` VALUES ('64', '47', '4255423', '2.54505', '48.1693', '0.639421', '-1', '1');
INSERT INTO `ticket_terminals` VALUES ('65', '47', '4255423', '-13.0021', '51.1865', '0.639421', '0.332372', '0.943148');
INSERT INTO `ticket_terminals` VALUES ('66', '48', '1935687', '-2.7419', '48.1677', '0.639421', '1', '1');
INSERT INTO `ticket_terminals` VALUES ('67', '48', '1935687', '12.6536', '51.1838', '0.639421', '-0.416129', '0.909306');
INSERT INTO `ticket_terminals` VALUES ('68', '48', '1935687', '2.54505', '48.1693', '0.639421', '-1', '1');
INSERT INTO `ticket_terminals` VALUES ('69', '48', '1935687', '-13.0021', '51.1865', '0.639421', '0.332372', '0.943148');
INSERT INTO `ticket_terminals` VALUES ('70', '49', '1855675', '-2.7419', '48.1677', '0.639421', '1', '1');
INSERT INTO `ticket_terminals` VALUES ('71', '49', '1855675', '12.6536', '51.1838', '0.639421', '-0.416129', '0.909306');
INSERT INTO `ticket_terminals` VALUES ('72', '49', '1855675', '2.54505', '48.1693', '0.639421', '-1', '1');
INSERT INTO `ticket_terminals` VALUES ('73', '49', '1855675', '-13.0021', '51.1865', '0.639421', '0.332372', '0.943148');
INSERT INTO `ticket_terminals` VALUES ('74', '50', '4635670', '-2.7419', '48.1677', '0.639421', '1', '1');
INSERT INTO `ticket_terminals` VALUES ('75', '50', '4635670', '12.6536', '51.1838', '0.639421', '-0.416129', '0.909306');
INSERT INTO `ticket_terminals` VALUES ('76', '50', '4635670', '2.54505', '48.1693', '0.639421', '-1', '1');
INSERT INTO `ticket_terminals` VALUES ('77', '50', '4635670', '-13.0021', '51.1865', '0.639421', '0.332372', '0.943148');
INSERT INTO `ticket_terminals` VALUES ('78', '51', '4635437', '-2.7419', '48.1677', '0.639421', '1', '1');
INSERT INTO `ticket_terminals` VALUES ('79', '51', '4635437', '12.6536', '51.1838', '0.639421', '-0.416129', '0.909306');
INSERT INTO `ticket_terminals` VALUES ('80', '51', '4635437', '2.54505', '48.1693', '0.639421', '-1', '1');
INSERT INTO `ticket_terminals` VALUES ('81', '51', '4635437', '-13.0021', '51.1865', '0.639421', '0.332372', '0.943148');
INSERT INTO `ticket_terminals` VALUES ('82', '52', '3175356', '-2.7419', '48.1677', '0.639421', '1', '1');
INSERT INTO `ticket_terminals` VALUES ('83', '52', '3175356', '12.6536', '51.1838', '0.639421', '-0.416129', '0.909306');
INSERT INTO `ticket_terminals` VALUES ('84', '52', '3175356', '2.54505', '48.1693', '0.639421', '-1', '1');
INSERT INTO `ticket_terminals` VALUES ('85', '52', '3175356', '-13.0021', '51.1865', '0.639421', '0.332372', '0.943148');
INSERT INTO `ticket_terminals` VALUES ('86', '53', '4265359', '-2.7419', '48.1677', '0.639421', '1', '1');
INSERT INTO `ticket_terminals` VALUES ('87', '53', '4265359', '12.6536', '51.1838', '0.639421', '-0.416129', '0.909306');
INSERT INTO `ticket_terminals` VALUES ('88', '53', '4265359', '2.54505', '48.1693', '0.639421', '-1', '1');
INSERT INTO `ticket_terminals` VALUES ('89', '53', '4265359', '-13.0021', '51.1865', '0.639421', '0.332372', '0.943148');
INSERT INTO `ticket_terminals` VALUES ('90', '54', '4005520', '-2.7419', '48.1677', '0.639421', '1', '1');
INSERT INTO `ticket_terminals` VALUES ('91', '54', '4005520', '12.6536', '51.1838', '0.639421', '-0.416129', '0.909306');
INSERT INTO `ticket_terminals` VALUES ('92', '54', '4005520', '2.54505', '48.1693', '0.639421', '-1', '1');
INSERT INTO `ticket_terminals` VALUES ('93', '54', '4005520', '-13.0021', '51.1865', '0.639421', '0.332372', '0.943148');
INSERT INTO `ticket_terminals` VALUES ('94', '55', '1261655', '-2.7419', '48.1677', '0.639421', '1', '1');
INSERT INTO `ticket_terminals` VALUES ('95', '55', '1261655', '12.6536', '51.1838', '0.639421', '-0.416129', '0.909306');
INSERT INTO `ticket_terminals` VALUES ('96', '55', '1261655', '2.54505', '48.1693', '0.639421', '-1', '1');
INSERT INTO `ticket_terminals` VALUES ('97', '55', '1261655', '-13.0021', '51.1865', '0.639421', '0.332372', '0.943148');
INSERT INTO `ticket_terminals` VALUES ('98', '56', '1106372', '-2.7419', '48.1677', '0.639421', '1', '1');
INSERT INTO `ticket_terminals` VALUES ('99', '56', '1106372', '12.6536', '51.1838', '0.639421', '-0.416129', '0.909306');
INSERT INTO `ticket_terminals` VALUES ('100', '56', '1106372', '2.54505', '48.1693', '0.639421', '-1', '1');
INSERT INTO `ticket_terminals` VALUES ('101', '56', '1106372', '-13.0021', '51.1865', '0.639421', '0.332372', '0.943148');
INSERT INTO `ticket_terminals` VALUES ('102', '57', '1026828', '-2.7419', '48.1677', '0.639421', '1', '1');
INSERT INTO `ticket_terminals` VALUES ('103', '57', '1026828', '12.6536', '51.1838', '0.639421', '-0.416129', '0.909306');
INSERT INTO `ticket_terminals` VALUES ('104', '57', '1026828', '2.54505', '48.1693', '0.639421', '-1', '1');
INSERT INTO `ticket_terminals` VALUES ('105', '57', '1026828', '-13.0021', '51.1865', '0.639421', '0.332372', '0.943148');
