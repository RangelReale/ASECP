#include <ASECP/GlobalProperty.h>
#include <ASECP/Exceptions.h>
#include <ASECP/Engine.h>

namespace ASECP {

GlobalProperty::GlobalProperty(Poco::AutoPtr<Engine> engine, asUINT index) : _engine(engine), _index(index)
{
	load();
}

GlobalProperty::~GlobalProperty()
{

}

Poco::AutoPtr<Engine> GlobalProperty::engine() const
{
	return _engine;
}

void GlobalProperty::load()
{
	const char* name, *nameSpace, *configgroup;
	throwOnError(_engine->engine()->GetGlobalPropertyByIndex(_index, &name, &nameSpace, &_typeid, &_isconst, &configgroup, &_pointer, &_accessmask));
	if (name)
		_name = std::string(name);
	if (nameSpace)
		_namespace = std::string(nameSpace);
	if (configgroup)
		_configgroup = std::string(configgroup);
}

}
