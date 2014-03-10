#include "DFDAnchor.h"
#include "DFDConnection.h"


void DFDAnchor::addConnection(const std::shared_ptr<DFDConnection> & conn)
{
    connectionList.push_back(conn);
}

std::vector<std::shared_ptr<DFDConnection>> DFDAnchor::connections() const
{
    return connectionList;
}

void DFDAnchor::deleteConnection(const std::shared_ptr<DFDConnection> & conn)
{
	int el = find(connectionList.begin(), connectionList.end(), conn) - connectionList.begin();
	if (el <connectionList.size())
		connectionList.erase(connectionList.begin() + el);
}