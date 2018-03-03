// Server.cpp: Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <aws/core/Aws.h>

int main(int argc, char** argv)
{
	Aws::SDKOptions options;
	options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Info;
	Aws::InitAPI(options);
	{
		// make your SDK calls here.
	}
	Aws::ShutdownAPI(options);
	return 0;
}

