#include "smrtmcb.h"

#include "SMRTProto.h"
#include "SMRTNet.h"
#include "Env/MCBEnv.h"
#include "dbgMgr.h"
#include "ISMRTDev.h"

#include "SMRTPingMgr.h"

void main_usage(void)
{
        printf("SMRTMCB\n");
        printf("SMRTMCB -v  : Print Version Information\n");
}

int main(int argc, char *argv[])
{
	if (argc > 1)
	{
        printf("argv %s\n", argv[0]);
        main_usage();
		return 0;
	}

#ifdef	WIN32
	TCHAR sDir[1024];
	GetCurrentDirectory(1024, sDir);
	_tprintf(_T("%s - current dir : %s\n"), _T(__FUNCTION__), sDir);
#else


#endif

    printf("SMRTMCB start\n");

    // Dev 생성 및 초기화
    SMRTMCB *pMCBDev = new SMRTMCB();

	uint32_t devid = DEVID_MCB;
	CMCBEnv	*pAppEnv = new CMCBEnv( pMCBDev, _T( "SMRTMCB.ini" ) );

	// Dev 생성 전에 ENV 생성 및 초기화.
	pAppEnv->Init( devid );


//#define OM_MONITORING_USE
#ifdef OM_MONITORING_USE
    pMCBDev->setOperMode(ISMRTDev::OM_MONITORING);
    pMCBDev->setMonIP(inet_addr( "10.128.0.33" )); //
#elif defined OM_EMULATING_USE
    pMCBDev->setOperMode(ISMRTDev::OM_EMULATING);
else
    pMCBDev->setOperMode(ISMRTDev::OM_NORMAL);
#endif

    pMCBDev->InitDev(devid, pAppEnv, (ISMRTDev *)NULL);

	//===========================================================================
	//	Init Ping Manager
	pSMRTPingMgr->InitPingMgr( devid );		//	Manager 생성은 App에서.
	//===========================================================================	


	std::vector< CDevice * > *pDevList = CDevice::GetInstance()->GetDevList();
	int nCam = 0;
	if (pDevList->size() > 0)
	{
		std::vector< CDevice * >::const_iterator iter_dev;

		for (iter_dev = pDevList->begin(); iter_dev != pDevList->end(); ++iter_dev)
		{
			if ((*iter_dev)->GetDevID() == DEVID_CAM)
			{
				pMCBDev->startNVR((*iter_dev)->GetIP());

				nCam++;
				break;
			}
		}
	}


    pMCBDev->Run();		// for QT App

    printf("SMRTMCB end\n");
    delete pMCBDev;

}
