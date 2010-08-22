-- phpMyAdmin SQL Dump
-- version 3.3.5
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Aug 22, 2010 at 09:43 AM
-- Server version: 5.1.47
-- PHP Version: 5.3.3

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `swgemu`
--

-- --------------------------------------------------------

--
-- Table structure for table `mission_manager_npcs`
--

USE swgemu;

CREATE TABLE IF NOT EXISTS `mission_manager_npcs` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `zoneid` int(11) DEFAULT NULL,
  `parentid` bigint(20) DEFAULT '0',
  `file` varchar(200) DEFAULT NULL,
  `oX` float DEFAULT '0',
  `oY` float DEFAULT '0',
  `oZ` float DEFAULT '0',
  `oW` float DEFAULT '1',
  `x` float DEFAULT NULL,
  `z` float DEFAULT NULL,
  `y` float DEFAULT NULL,
  `level` int(11) DEFAULT '10',
  `mood_animation` varchar(45) DEFAULT NULL,
  `creature_bitmask` int(10) unsigned DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `idworldserverspawns_UNIQUE` (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

--
-- Dumping data for table `mission_manager_npcs`
--

INSERT INTO `mission_manager_npcs` (`id`, `zoneid`, `parentid`, `file`, `oX`, `oY`, `oZ`, `oW`, `x`, `z`, `y`, `level`, `mood_animation`, `creature_bitmask`) VALUES
(1, 5, 0, 'object/mobile/dressed_commoner_fat_human_male_01.iff', 0, 0, 0, 1, -4854, 6, 4131, 15, 'neutral', 264),
(2, 5, 0, 'object/mobile/dressed_commoner_fat_human_male_01.iff', 0, 0, 0, 1, -4858, 6, 4131, 15, 'neutral', 264);
