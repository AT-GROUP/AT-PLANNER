
#ifndef ATEnvironment_AKBDocument_h
#define ATEnvironment_AKBDocument_h

#include "../config.h"
#include "../ADocument.h"

class AT_CORE_API AKBDocument : public ADocument
{
public:
	AKBDocument();
	~AKBDocument();

	virtual void serialize(_xmlNode * document_node) const override;
	virtual AError deserialize(_xmlNode * document_node)  override;
};

#endif
