#ifndef NVR_H
#define NVR_H

//#include "INVR.h"

//#include "gstMgr.h"
#include <QObject>

class NVR : public QObject//, public INVR
{
	//==========================================================================
	// Constructor & Destructor
	Q_OBJECT
public:
	NVR();

	~NVR();
	
	//==========================================================================
	// Attributes
protected:
#ifdef GST_USE
/*	gstMgr			m_gstMgrFile;		//	���� ��Ʈ������.

	std::map	<	uint32_t,		//	multicast or unicast addr
		uint32_t *		//	pgstMgr
	> m_mapGstMgr;		// ���� �� ��ȭ

	*/
#endif// GST_USE

	//==========================================================================
	// Interfaces
public:
	//virtual void Run(unsigned int uiOperMode = ISMRTDev::OM_NORMAL);

	//==========================================================================
	// Interfaces - Callback / Virtual
public:



//signals:


//public slots:


};

#endif//NVR_H
