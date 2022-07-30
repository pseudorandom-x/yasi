#include <string>
#include <fstream>

#include "util.hpp"

namespace Memory {

using u64 = uint64_t;

	struct MemInfo {
		u64 free_;
		u64 total_;
		u64 swpFree_;
		u64 swpTotal_;
	};

	u64 processAttr(const std::string& s)
	{
		size_t i = 0;
		std::string res;

		while (!std::isdigit(s[i]))
			++i;

		while (std::isdigit(s[i]))
		{
			res.push_back(s[i]);
			++i;
		}

		return u64(std::stoull(res));
	}

	MemInfo memInfo()
	{
		MemInfo mi;
		std::fstream io;
		io.open("/proc/meminfo", std::ios_base::out);

		if (!io.is_open())
		{
			Util::updateLog("Unable to open /proc/meminfo. Some memory information may be missing...");
			return;
		}

		int ftr = 4;

		while (ftr)
		{
			std::string s;
			std::getline(io, s);

			if (s.find("MemTotal") != std::string::npos)
			{
				mi.total_ = processAttr(s);
				--ftr;
			}
			if (s.find("MemFree") != std::string::npos)
			{
				mi.free_ = processAttr(s);
				--ftr;
			}
			if (s.find("SwapTotal") != std::string::npos)
			{
				mi.swpTotal_ = processAttr(s);
				--ftr;
			}
			if (s.find("SwapFree") != std::string::npos)
			{
				mi.swpFree_ = processAttr(s);
				--ftr;
			}
		}

		io.close();

		return mi;
	}

}