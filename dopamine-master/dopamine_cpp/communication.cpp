#include "communication.h"
#include "functions.h"
#include <fstream>
#include <sstream>

std::vector<std::string> split_string(const std::string& str, const std::string& delimiter) // stackoverflow
{
	std::vector<std::string> strings;

	std::string::size_type pos = 0;
	std::string::size_type prev = 0;
	while ((pos = str.find(delimiter, prev)) != std::string::npos)
	{
		strings.push_back(str.substr(prev, pos - prev));
		prev = pos + 1;
	}

	// To get the last substring (or only, if delimiter is not found)
	strings.push_back(str.substr(prev));

	return strings;
}

std::string get_file_contents(std::string filename)
{
	std::ifstream file(filename);
	return std::string(static_cast<std::stringstream const&>(std::stringstream() << file.rdbuf()).str());
}

void communication::init(std::string config)
{
	config += "/";
	std::string old_content = "";

	while (true)
	{
		std::string content = get_file_contents(config + "comm.txt");

		if (content != old_content && content != "")
		{
			std::ofstream write_file(config + "out.txt", std::ios::trunc);
			auto actions = split_string(content, "\n");

			for (auto action : actions)
			{
				if (action == "ping")
				{
					write_file << "pong";
				}
				else
				{
					auto action_data = split_string(content, " ");

					std::string id = action_data[0];
					std::string func = action_data[1];
					json args(content.substr(id.length() + func.length() + 3));

					auto response = function_list[func](args);
					write_file << id << " " << response;
				}
			}

			write_file.close();
		}

		old_content = content;	
		Sleep(90);
	}
}
