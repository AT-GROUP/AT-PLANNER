#ifndef ATEnvironment_EDFDDocument_h
#define ATEnvironment_EDFDDocument_h

#include <vector>
#include <memory>
#include "../config.h"
#include "../ADocument.h"
#include "DFDElement.h"
#include "DFDConnection.h"
#include "DFDAnchor.h"

struct _xmlNode;

class AT_CORE_API EDFDDocument : public ADocument
{
public:
	EDFDDocument();
	virtual Type type() const override final;

	void addElement(const std::shared_ptr<DFDElement> & new_element);
	void addConnection(const std::shared_ptr<DFDConnection> & new_connection);

	void deleteElement(const std::shared_ptr<DFDElement> & element);
	void deleteConnection(const std::shared_ptr<DFDConnection> & connection);

	std::vector<std::shared_ptr<DFDElement>> getElements() const;
	const std::vector<std::shared_ptr<DFDElement>> & elements() const;
	const std::vector<std::shared_ptr<DFDConnection>> & connections() const;

	virtual void serialize(_xmlNode * document_node) const override;
	virtual AError deserialize(_xmlNode * document_node) override;

	bool isDetalized() const;
	bool isDetalizedWith(const std::shared_ptr<EDFDDocument> & detail_doc) const;
	AError buildDetalizationLinks(std::vector<std::shared_ptr<EDFDDocument>> & edfd_docs);

	void mergeWith(const std::shared_ptr<EDFDDocument> & detail_doc);
	void mergeElements(int index1, int index2);

private:
	std::vector<std::shared_ptr<DFDElement>> mElements;
	std::vector<std::shared_ptr<DFDConnection>> mConnections;
	std::shared_ptr<DFDAnchor> mAnchor;
};

#endif
