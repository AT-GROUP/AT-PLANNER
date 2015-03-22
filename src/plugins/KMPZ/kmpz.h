#ifndef KMPZ_H
#define KMPZ_H

#include "kmpz_global.h"
#include <ATCore/plugin/APlugin.h>

class KMPZ_EXPORT ATKMPZPlugin : public AUtilityPlugin
{
public:
	ATKMPZPlugin();
	~ATKMPZPlugin();

	virtual const std::vector<std::string> getCommands();
	virtual AError executeCommand(const std::string & script, std::string & answer);
private:

};

#endif // KMPZ_H
