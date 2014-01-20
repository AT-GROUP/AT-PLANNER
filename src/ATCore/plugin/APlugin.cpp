#include "APlugin.h"

const APlugin::Type AUtilityPlugin::type() const
{
	return APlugin::Type::Utility;
}

const APlugin::Type AEditorPlugin::type() const
{
	return APlugin::Type::Editor;
}
