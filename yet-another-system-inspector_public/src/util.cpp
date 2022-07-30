#include "util.hpp"

namespace Util {

	void updateLog(const std::string& s)
	{
		std::fstream io;
		io.open(LOG_PATH + LOG_FILE, std::ios_base::app);

		if (!io.is_open())
		{
			std::cerr << "Failed to update log.\n";
			return;
		}

		io << "-> " << s << '\n';
		io.close();
	}

	void eraseLog()
	{
		std::fstream io;
		io.open(LOG_PATH + LOG_FILE, std::ofstream::out | std::ofstream::trunc);
		io.close();
	}

	Element title(const std::string& s)
	{
		return bold(text(std::string("[ ") + s + std::string(" ]")));    
	}

}