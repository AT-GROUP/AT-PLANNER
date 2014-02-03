
#ifndef ATEnvironment_APluginManager_h
#define ATEnvironment_APluginManager_h

#include <QtWidgets/QApplication>
#include <ATCore/plugin/APluginManager.h>
#include <ATCore/ACommandExecutor.h>
#include <ATPlanner/ATPlanner.h>

class ATPlanner;

class ATApplication : public QApplication, public ACommandExecutor, public AIPlannerDelegate
{
	Q_OBJECT
public:
	ATApplication(int argc, char *argv[]);
	void searchAndLoadPlugins();

	/*
	Primitive command execution. Checks, if command is addressed to core, if
	not - calss parent plugin executor.
	*/
	virtual AError executeCommand(const std::string & cmd_text, std::string & answer);

	//AIPlannerDelegate implementation
	virtual void planRebuilt(ATPlanner * planner, APlan * plan);
	
	//Simple accessor
	ATPlanner * planner() const;
private:
	ATPlanner * m_pPlanner;
};

#endif
