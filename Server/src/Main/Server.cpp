// Server.cpp: Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include <aws/core/Aws.h>
#include <iostream>

int main(int argc, char** argv)
{
	Aws::SDKOptions options;
	options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Info;
	Aws::InitAPI(options);
	{
		// make your SDK calls here.
	}
	Aws::ShutdownAPI(options);
	while (true)
	{
		std::cout << "running" << std::endl;
	}
	return 0;
}

