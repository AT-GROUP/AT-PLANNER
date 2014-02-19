
#include "AArchitectureDocument.h"

AArchitectureDocument::AArchitectureDocument()
	:ADocument()
{

}

ADocument::Type AArchitectureDocument::type() const
{
	return ADocument::Type::ArchitectureMaket;
}

void AArchitectureDocument::serialize(_xmlNode * document_node) const
{

}

AError AArchitectureDocument::deserialize(_xmlNode * document_node)
{
	return AError();
}
