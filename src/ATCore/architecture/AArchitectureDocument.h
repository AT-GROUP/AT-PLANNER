
#ifndef ATCore_AArchitectureDocument_h
#define ATCore_AArchitectureDocument_h

#include "../config.h"
#include "../ADocument.h"

class AT_CORE_API AArchitectureDocument : public ADocument
{
public:
	AArchitectureDocument();
	virtual Type type() const override;

	virtual void serialize(_xmlNode * document_node) const override;
	virtual AError deserialize(_xmlNode * document_node) override;
};

#endif