
#ifndef ATEnvironment_ADocument_h
#define ATEnvironment_ADocument_h

#include "config.h"
#include "AError.h"

class _xmlNode;

class AT_CORE_API ADocument
{
public:
	enum class Type {EDFD, ArchitectureMaket, NotSystem};

	const std::string & fileName() const;

	AError save();
	AError saveToFile(const std::string & file_name);
	AError loadFromFile(const std::string & file_name);

	virtual void serialize(_xmlNode * document_node) const = 0;
	virtual AError deserialize(_xmlNode * document_node) = 0;
	virtual Type type() const;
private:
	std::string mFileName, mDirectory;
};

#endif
