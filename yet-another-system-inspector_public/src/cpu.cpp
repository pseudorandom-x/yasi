#include "cpu.hpp"

// ctor
CpuInfo::CpuInfo()
{
    cpuInfoReader_.open(CPU_FILE, std::ios_base::in);

    if (!cpuInfoReader_.is_open())
	{
		Util::updateLog("Unable to open /proc/cpuinfo. Some memory information may be missing...");
		return;
    }

    std::string s;
	std::vector<std::string> lines;

    while (std::getline(cpuInfoReader_, s) && s != "\n")
		lines.push_back(s);

	Util::updateLog("Opened cpuinfo. Processing...");

	for (const auto& line : lines)
	{
		if (line.find("vendor_id") != std::string::npos)
			mnf_ = vendors[processAttr(line)];
		else if (line.find("model name") != std::string::npos)
			modelName_ = processAttr(line);
		else if (line.find("cpu MHz") != std::string::npos)
			freq_ = std::stoi(processAttr(line));
		else if (line.find("cache size") != std::string::npos)
			cacheSz_ = std::stoi(processAttr(line));
		else if (line.find("flags") != std::string::npos)
		{
			arch_ = processArch(line) == 1 ? ARCH_64 : ARCH_32;
			hwVirt_ = processHwVirt(line);
			isVirtual_ = processVirt(line);
		}
	}

	Util::updateLog("Success! CPU information extracted successfully.");

	cpuOnln_ = sysconf(_SC_NPROCESSORS_ONLN);
	cpuOffln_ = sysconf(_SC_NPROCESSORS_CONF);

	cpuInfoReader_.close();
}

size_t
CpuInfo::getStringStart(const std::string& line) const
{
	size_t i = 0;

	while (line[i] != ':') ++i;

	return i;
}

std::string
CpuInfo::processAttr(const std::string& line) const
{
	return line.substr(getStringStart(line) + 2);
}

bool
CpuInfo::processArch(const std::string& line) const
{
	return (line.find(" lm ") != std::string::npos ||
			line.find("tm") == std::string::npos) ? 1 : 0;
}

bool
CpuInfo::processHwVirt(const std::string& line) const
{
	return (line.find("svm") != std::string::npos ||
			line.find("vmx") != std::string::npos) ? 1 : 0;
}

bool
CpuInfo::processVirt(const std::string& line) const
{
	return line.find("hypervisor") != std::string::npos;
}