/*
 * Authored by Rudra Pratap Singh (2022)
 * email: rudrasingh900@gmail.com
 * gh: pseudorandom-x
 * 
*/
#ifndef _UTIL_HPP_
#define _UTIL_HPP_

#include <fstream>

#include <ftxui/screen/box.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/terminal.hpp>
#include <ftxui/component/screen_interactive.hpp>

namespace Util {

using namespace ftxui;

	const std::string PADDING = "  ";
	const std::string LOG_FILE = "yasi.log";
	const std::string LOG_PATH = "../src/resources/";

	void updateLog(const std::string& s);
	void eraseLog();

	Element title(const std::string& s);

}

#endif