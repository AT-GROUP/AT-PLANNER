#ifndef ATEnvironment_AScheme_h
#define ATEnvironment_AScheme_h

#include "../core/ANamedObject.h"
#include <vector>

namespace BlockScheme
{
	struct Point2d
	{
		double x, y;
	};

	class ABlock;

	class ASlot : public ANamedObject
	{
	public:
		typedef enum {Input, Output} IOType;

		ASlot(const char * slot_name, int io_type, ABlock * parent);
		const int type() const;
	private:
		int mType;
		ABlock * m_pParent;
	};

	class ALink
	{
	public:
		ALink(ASlot * start_slot, ASlot * end_slot);
	private:
		ASlot * m_pStartSlot, *m_pEndSlot;
	};

	class ABlock : public ANamedObject
	{
	public:
		ABlock(const char * block_name);
	private:
		//Coordinates
		Point2d mPosition;

		//Input slots
		std::vector<ASlot*> mInputSlots;

		//Output slots
		std::vector<ASlot*> mOuputSlots;
	};

	class AScheme
	{
		friend class AQSchemesEditor;
	public:
		AScheme();
	private:
		std::vector<ABlock*> mBlocks;
		std::vector<ALink*> mLinks;
	};

};

#endif
