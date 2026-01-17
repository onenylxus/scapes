////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2026 MIT License
////////////////////////////////////////////////////////////////

#include "./core/Application.h"
#include "./util/Logger.h"

// Application values
const char *title = "Scapes";
const char *version = "v0.1.0";
const int width = 1280;
const int height = 720;

// Main function
int main(int argc, char *argv[])
{
	// Default values
	std::string priority = "debug";
	bool enableWrite = false;

	// Parse arguments
	for (int i = 1; i < argc; ++i)
	{
		std::string arg(argv[i]);
		if (arg.rfind("--priority=", 0) == 0)
		{
			priority = arg.substr(11);
		}
		else if (arg.rfind("--write=", 0) == 0)
		{
			std::string val = arg.substr(8);
			enableWrite = (val == "true" || val == "1");
		}
	}

	// Check enable write
	char buffer[80];
	if (enableWrite)
	{
		time_t t = time(0);
		struct tm *now = std::localtime(&t);
		strftime(buffer, 80, "log/%Y%m%d_%H%M%S.txt", now);
		Logger::EnableWrite(buffer);
	}
	else
	{
		Logger::DisableWrite();
	}

	// Check priority level
	if (!priority.empty())
	{
		if (priority == "trace")
		{
			Logger::SetPriority(Logger::Priority::TRACE);
		}
		else if (priority == "debug")
		{
			Logger::SetPriority(Logger::Priority::DEBUG);
		}
		else if (priority == "info")
		{
			Logger::SetPriority(Logger::Priority::INFO);
		}
		else if (priority == "warn")
		{
			Logger::SetPriority(Logger::Priority::WARN);
		}
		else if (priority == "error")
		{
			Logger::SetPriority(Logger::Priority::ERROR);
		}
	}

	// Create application
	Application *app = new Application();
	if (app->Create(title, version, width, height))
	{
		app->Start();
	}

	// Disable logger file write
	Logger::DisableWrite();

	// Return
	return 0;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
