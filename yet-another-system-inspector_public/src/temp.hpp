#include <vector>
#include <fstream>
#include <filesystem>

#include <ftxui/dom/elements.hpp>

#include "cpu.hpp"

using namespace ftxui;
namespace fs = std::filesystem;

class Temp {
private:
	static Elements tempInfo2(const CpuInfo& cpu)
	{
		size_t i = 0;
		std::vector<Element> ret;
		bool virt = cpu.isVirtual();

		for (auto& dir : fs::directory_iterator("/sys/class/thermal"))
		{
			if (dir.is_directory() && dir.path().string().find("thermal_zone" + std::to_string(i)) != std::string::npos)
			{
				bool ok = true;
				std::fstream io;
				float val = 0.0f;

				for (auto& dirIn : fs::directory_iterator(dir))
				{
					if (!dirIn.is_directory() && !dirIn.is_symlink() && dirIn.path().stem().string() == "temp")
					{
						std::string s;
						io.open(dirIn.path().string());

						if (!io.is_open())
						{
							ok = false;
							break;
						}

						std::getline(io, s);
						val = std::stof(s);
						break;
					}
				}

				ret.push_back(vbox({
					gaugeUp(val) | flex | border | color(!ok ? Color::Red1 : Color::Palette256(197 + i)),
					text(" cpu" + std::to_string(i) + " ") | flex | inverted | borderLight | center | color(!ok ? Color::Red1 : Color::Palette256(197 + i)),
				}) | flex);

				++i;
			}

			if (i > cpu.coresOffln())
				break;
		}

		Util::updateLog("CPU temperatures extracted.");

		return {
			hbox({
				ret,
			}) | flex,
			text("temperatures (°C)") | bold | center | color(Color::Palette256(129)),
		};
	}
public:
	static Elements tempInfo(const CpuInfo& cpu)
	{
		std::vector<Element> ret;
		bool virt = cpu.isVirtual();

		if (!virt)
			return tempInfo2(cpu);

		for (size_t i = 0; i < cpu.coresOffln(); ++i)
		{
			if (cpu.isVirtual())
			{
				ret.push_back(vbox({
					gaugeUp(0.5f) | flex | border | color(Color::Red1),
					text(" cpu" + std::to_string(i) + " ") | flex | inverted | borderLight | center | color(Color::Red1),
				}) | flex);
			}
		}

		Util::updateLog("Running on a hypervisor, CPU temperatures unavailable.");

		return {
			hbox({
				ret,
			}) | flex,
			text("[x] cpu temps unavailable on VMs") | bold | color(Color::Red1),
			text("FATAL: ../../../thermal_zone*") | bold | color(Color::Red1),
		};
	}
};
