
#include "NVR.h"

//#include "Version.h"			//	Version

#ifdef QT_UI_USE
#include "mainwindow.h"
#include <QApplication>
#include <QWidget>
#else
#include <QCoreApplication>
#endif

#ifdef __linux__
#define IT_DECL_EXPORT     __attribute__((visibility("default")))
#define IT_DECL_IMPORT     __attribute__((visibility("default")))
#else
#define IT_DECL_EXPORT     __declspec(dllexport)
#define IT_DECL_IMPORT     __declspec(dllimport)
#endif

#ifdef NVR_LIBRARY
#define NVR_SHARED_EXPORT extern "C" IT_DECL_EXPORT
#else
#define NVR_SHARED_EXPORT
#endif


NVR_SHARED_EXPORT int NVR_init(unsigned int *pDev/*= NULL*/, unsigned int uiOperMode/*= ISMRTDev::eOperMode*/);

//===========================================================================
NVR_SHARED_EXPORT int NVR_init(unsigned int *pDev/*= NULL*/, unsigned int uiOperMode/*= ISMRTDev::eOperMode*/)
//===========================================================================
{
	printf("%s %p %d\n", __FUNCTION__, pDev, uiOperMode);
	
/*	NVR *pMcbDev = new NVR();

	uint32_t devid = DEVID_MCB;
	CMCBEnv	*pAppEnv = new CMCBEnv( pMcbDev, _T( "NVR.ini" ) );

	// Dev 생성 전에 ENV 생성 및 초기화.
	pAppEnv->Init( devid );

	pMcbDev->InitDev(devid, pAppEnv, (ISMRTDev *)pDev);

	//===========================================================================
	//	Init Ping Manager
	pSMRTPingMgr->InitPingMgr( devid );		//	Manager 생성은 App에서.
	//===========================================================================	
	
	

	pMcbDev->Run(uiOperMode);		// for App Loop
	*/

	return 0;
}

//===========================================================================
NVR::NVR()
//===========================================================================
//	: INVR()
{
	printf("[%s]\n", __FUNCTION__);
/*
	memset(&m_sDIO1, 0, sizeof(m_sDIO1));
	memset(&m_sDIO2, 0, sizeof(m_sDIO2));

	//	Application Version설정.
	SetAppVer( VER_INFO( FILEVER ) );

	//connect(&m_gstMgrMic, SIGNAL(endStream(int)), this, SLOT(gstMgrMicEnded(int)));
	//connect(&m_gstMgrSpk, SIGNAL(endStream(int)), this, SLOT(gstMgrSpkEnded(int)));
	connect(&m_gstMgrFile, SIGNAL(endStream(int)), this, SLOT(gstMgrFileEnded(int)));
	connect(this, SIGNAL(testSig(int)), this, SLOT(testSlot(int)));
	printf("testSig(1)\n");
	testSig(1);
	*/
}

//===========================================================================
NVR::~NVR()
//===========================================================================
{
	printf("[%s]\n", __FUNCTION__);
}

