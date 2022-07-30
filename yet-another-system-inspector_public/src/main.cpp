#include <string>

/* FTXUI lib: https://github.com/ArthurSonzogni/FTXUI */
#include <ftxui/screen/box.hpp>
#include <ftxui/dom/canvas.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/terminal.hpp>
#include <ftxui/component/screen_interactive.hpp>

/* customs */
#include "cpu.hpp"
#include "temp.hpp"
#include "util.hpp"

int main()
{
using namespace ftxui;

	Util::eraseLog();
	// get system info
	CpuInfo cpu;
	Elements tempInfo = Temp::tempInfo(cpu);

	// set the layout

	ftxui::Element mainDoc = ftxui::borderEmpty(vbox({
		flex(window(Util::title("cpu"), hbox({
			flex(vbox({
				separatorEmpty(),
				vbox({
					text(Util::PADDING + " _   _  __ _ ___ (_)") | color(Color::Palette256(53)),
					text(Util::PADDING + "| | | |/ _  |/ __| |") | color(Color::Palette256(53)),
					text(Util::PADDING + "| |_| | (_| |\\__ \\ |  github.com/pseudorandom-x") | color(Color::Palette256(54)),
					text(Util::PADDING + " \\__, |\\__,_|____/_|") | color(Color::Palette256(55)),
					text(Util::PADDING + " |___/             ") | color(Color::Palette256(56)),
				}) | flex,
				vbox({
					text(Util::PADDING + "vendor:        " + cpu.vendor()) | color(Color::Palette256(197)),
					text(Util::PADDING + "µp:            " + cpu.modelName()) | color(Color::Palette256(198)),
					text(Util::PADDING + "arch:          " + cpu.architecture()) | color(Color::Palette256(199)),
					text(Util::PADDING + "cores (live):  " + std::to_string(cpu.coresOnl())) | color(Color::Palette256(200)),
					text(Util::PADDING + "cores (total): " + std::to_string(cpu.coresOffln())) | color(Color::Palette256(201)),
					text(Util::PADDING + "freq (MHz):    " + std::to_string(cpu.frequency())) | color(Color::Palette256(202)),
					text(Util::PADDING + "cache (KiB):   " + std::to_string(cpu.cacheSize())) | color(Color::Palette256(203)),
				}) | flex,
			})),

			window(text(" temps ") | bold, vbox({
				tempInfo,
			}) | borderEmpty | flex | color(Color::Red1)),

			flex(border(vbox({
				text(Util::PADDING + "vendor:        " + cpu.vendor()),
				text(Util::PADDING + "µp:            " + cpu.modelName()),
				text(Util::PADDING + "arch:          " + cpu.architecture()),
				text(Util::PADDING + "cores (live):  " + std::to_string(cpu.coresOnl())),
				text(Util::PADDING + "cores (total): " + std::to_string(cpu.coresOffln())),
				text(Util::PADDING + "freq (MHz):    " + std::to_string(cpu.frequency())),
				text(Util::PADDING + "cache (KiB):   " + std::to_string(cpu.cacheSize())),
			}))),
		}))),
		flex(window(Util::title("mem"), center(text("Normal window\ncontent")))),
		flex(window(Util::title("tasks"), center(text("Normal window\ncontent")))),
	}));

	// grab the whole screen
	ftxui::Screen scr = ftxui::Screen::Create(Dimension::Full());

	// render layout on terminal
	ftxui::Render(scr, mainDoc);
	scr.Print();

	return EXIT_SUCCESS;
}
