//
//  USColor.h
//  UltraSimpleEngine
//
//  Created by Yuri Blokhin on 05.03.12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef ATEnvironment_ADelegatedObject_h
#define ATEnvironment_ADelegatedObject_h

#define DELEGATE() if(delegate())delegate()

//Single-delegateble object
template<class T> class ADelegatedObject
{
public:
	void setDelegate(T * del)
	{
		m_pDelegate = del;
	}
	T * delegate()
	{
		return m_pDelegate;
	}
private:
	T * m_pDelegate;
};

#endif
