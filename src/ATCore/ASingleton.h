
#ifndef ATCore_ASingleton_h
#define ATCore_ASingleton_h

/*
Singletones can be called from any point of application code.
*/

template <class T> class AAbstractSingleton
{
	/*
	Base for singleton with static variable instance.
	*/
public:
    static T * setSingleton(T* instance)
	{
		m_pInstance = instance;
		return m_pInstance;
	}

protected:
    AAbstractSingleton();
    virtual ~AAbstractSingleton();
protected:
    static T * m_pInstance;
};

template <class T> T* AAbstractSingleton<T>::m_pInstance=0;


template <class T> class ASingleton : public AAbstractSingleton<T>
{
	/*
	Singleton with manual creation. First time you must
	create the instance and call setSingleton().
	*/
public:
    static T* singleton()
    {
        return AAbstractSingleton<T>::m_pInstance;
    }
};

template <class T> class AAutocreateSingleton : public AAbstractSingleton<T>
{
public:
    /*
	Singleton with automatic creation on first call.
	*/
    static T* singleton()
    {
		if(!AAutocreateSingleton<T>::m_pInstance)
			AAutocreateSingleton<T>::m_pInstance = new T;
        return AAutocreateSingleton<T>::m_pInstance;
    }
};

#endif