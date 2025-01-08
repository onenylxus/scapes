////////////////////////////////////////////////////////////////
// Scapes v0.1.0
// Voxel-based role-playing game
// Nicholas Ng, 2022-2025 MIT License
////////////////////////////////////////////////////////////////

// Include
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
	// Check argument flags
	char *logFlag;
	if (argc > 0)
	{
		char *flag = argv[0];
		while (*argv[0])
		{
			*argv[0] = tolower(*argv[0]);
			argv[0]++;
		}
		logFlag = flag;
	}

	// Enable logger file write
	time_t t = time(0);
	struct tm *now = std::localtime(&t);
	char buffer[80];
	strftime(buffer, 80, "log/%Y%m%d_%H%M%S.txt", now);
	Logger::EnableWrite(buffer);

	// Check log level
	if (logFlag == "trace")
	{
		Logger::SetPriority(Logger::Priority::TRACE);
	}
	else if (logFlag == "debug")
	{
		Logger::SetPriority(Logger::Priority::DEBUG);
	}
	else if (logFlag == "info")
	{
		Logger::SetPriority(Logger::Priority::INFO);
	}
	else if (logFlag == "warn")
	{
		Logger::SetPriority(Logger::Priority::WARN);
	}
	else if (logFlag == "error")
	{
		Logger::SetPriority(Logger::Priority::ERROR);
	}
	else
	{
		Logger::DisableWrite();
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
