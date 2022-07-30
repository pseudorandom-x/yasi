/*
 * Authored by Rudra Pratap Singh (2022)
 * email: rudrasingh900@gmail.com
 * gh: pseudorandom-x
 * 
*/
#pragma once // _CPU_HPP_

#include <string>
#include <vector>
#include <fstream>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <unordered_map>

#include "util.hpp"

class CpuInfo {
private:
	bool                        hwVirt_; // 'flags' contains 'svm'/'vmx'
	bool                        isVirtual_;
	size_t                      freq_;
	size_t                      cacheSz_;
	std::string                 mnf_;
	std::string                 modelName_;
	std::string                 arch_; // 'flags' contains 'lm' = 64bit
	std::fstream                cpuInfoReader_;

	/* sysconf() : sys/sysinfo.h */
	size_t                      cpuOnln_;
	size_t                      cpuOffln_;

	const std::string ARCH_32   = "x86";
	const std::string ARCH_64   = "x86_64/amd64";
	const std::string CPU_FILE  = "/proc/cpuinfo";
	std::unordered_map<std::string, std::string>
	vendors = {
		{ "GenuineIntel", "Intel"                  },
		{ "AuthenticAMD", "AMD"                    },
		{ "CyrixInstead", "Cyrix"                  },
		{ "NexGenDriven", "NexGen"                 },
		{ "GenuineTMx86", "Transmeta"              },
		{ "UMC UMC UMC ", "UMC"                    },
		{ "CentaurHauls", "Centaur"                },
		{ "RiseRiseRise", "Rise"                   },
		{ "SiS SiS SiS ", "SiS"                    },
		{ "Geode by NSC", "National Semiconductor" },
	};

private: // member funcs
	size_t getStringStart(const std::string& line) const;
	std::string processAttr(const std::string& line) const;
	bool processArch(const std::string& line) const;
	bool processHwVirt(const std::string& line) const;
	bool processVirt(const std::string& line) const;

public:
	CpuInfo();

	inline bool isVirtual() const { return isVirtual_; }
	inline bool hardwareVirt() const { return hwVirt_; }
	inline size_t frequency() const { return freq_; }
	inline size_t cacheSize() const { return cacheSz_; }

	inline std::string vendor() const { return mnf_; }
	inline std::string modelName() const { return modelName_; }
	inline std::string architecture() const { return arch_; }

	inline size_t coresOnl() const { return cpuOnln_; }
	inline size_t coresOffln() const { return cpuOffln_; }

	double calcUsage();
};