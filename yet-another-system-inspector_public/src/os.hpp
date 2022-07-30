/*
 * Authored by Rudra Pratap Singh (2022)
 * email: rudrasingh900@gmail.com
 * gh: pseudorandom-x
 * 
*/
#pragma once // _OS_HPP_

#include <string>
#include <errno.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>

namespace KernInfo {

#define PUT_ERR(x) std::cerr << (x) << '\n'
	const size_t HOSTNAME_LEN = 256;

	struct OsInfo {
		bool        isNull_;

		/* uname() */
		std::string sysname_;
		std::string release_;
		std::string version_;
		std::string machine_;
		std::string hostname_;

		/* sysinfo() */
		long long   uptime_;
		long long   nbprocs_;
	};

	OsInfo refresh()
	{
		bool err = false;
		struct utsname un;
		struct sysinfo si;
		static bool initUn = true;
		static bool initSi = true;
		static bool initHn = true;
		char hostname[HOSTNAME_LEN];
		hostname[HOSTNAME_LEN - 1] = '\0';

		if (uname(&un) < 0)
		{
			err = true;
			if (initUn)
			{
				PUT_ERR("[uname() failed]");
				initUn = false;
			}
			return {
				.isNull_ = true
			};
		}

		if (sysinfo(&si) < 0)
		{
			err = true;
			if (initSi)
			{
				PUT_ERR("[sysconf() failed]");
				initSi = false;
			}
			return {
				.isNull_ = true
			};
		}

		if (gethostname(hostname, HOSTNAME_LEN) < 0)
		{
			err = true;
			if (initHn)
			{
				PUT_ERR("[gethostname() failed]");
				initHn = false;
			}
			return {
				.isNull_ = true
			};
		}

		return {
			.isNull_ = false,
			.sysname_ = std::string(un.sysname),
			.release_ = std::string(un.release),
			.version_ = std::string(un.version),
			.machine_ = std::string(un.machine),
			.hostname_ = std::string(hostname),
			.uptime_ = si.uptime,
			.nbprocs_ = si.procs
		};
	}

}