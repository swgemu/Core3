-- phpMyAdmin SQL Dump
-- version 3.3.5
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Aug 28, 2010 at 07:08 PM
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
-- Table structure for table `mission_manager_recon_locs`
--

USE swgemu;

DROP TABLE IF EXISTS `mission_manager_recon_locs`;
CREATE TABLE IF NOT EXISTS `mission_manager_recon_locs` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `zoneid` tinyint(4) NOT NULL,
  `template_file` varchar(200) NOT NULL,
  `template_type` int(255) NOT NULL,
  `oX` float NOT NULL,
  `oY` float NOT NULL,
  `oZ` float NOT NULL,
  `oW` float NOT NULL,
  `X` float NOT NULL,
  `Z` float NOT NULL,
  `Y` float NOT NULL,
  PRIMARY KEY (`id`),
  KEY `zone_id` (`zoneid`),
  FULLTEXT KEY `file_ix` (`template_file`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Dumping data for table `mission_manager_recon_locs`
--

INSERT INTO `mission_manager_recon_locs` (`id`, `zoneid`, `template_file`, `template_type`, `oX`, `oY`, `oZ`, `oW`, `X`, `Z`, `Y`) VALUES
(1, 5, 'object/tangible/lair/cu_pa/lair_cu_pa.iff', 8203, 0, -0.401868, 0, 0.915698, -4934, 6, 4114);
