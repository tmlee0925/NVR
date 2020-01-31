/*------------------------------------------------------------------------
	Project     : SMRT
	Description : Env Define

	Writer      : 
	Date        : 2018. 10.
	Copyright   : Piranti

	[Revision History ]
	1. 2018. 10. : Created

------------------------------------------------------------------------*/

#ifndef MCB_ENV_H
#define MCB_ENV_H

//========================================================================
// Header
#include "typedef.h"		//	int32_t
#include "envValue.h"

#include "SMRTEnv.h"

#include <queue>
#include <iostream>
using namespace std;


//========================================================================
#define		ENV_ITEM_CSTR_EX( param, name, key, value 	)	extern	CString	param;
#define		ENV_ITEM_DWORD_EX( param, name, key, value 	)	extern	DWORD		param;
//========================================================================

#include "ProtocolData.h"
//========================================================================
// User Define

// ENV_ITEM_STR(	name,	key,	defaultValue	)

#define		ENV_LIST	\

#ifdef	WIN32
#define		ENV_LIST_EX	\
	ENV_ITEM_INT_EX( 	m_bPing,				_T("Debug"),		_T("Ping"),				1	)	\
	ENV_ITEM_INT_EX( 	m_nDelayOutOfService,	_T("Timeout"),		_T("OutOfService"),		60	)	\
	
#else	//	Linux	
#define		ENV_LIST_EX	\
	ENV_ITEM_INT_EX( 	m_bPing,				_T("Debug"),		_T("Ping"),				1	)	\
	ENV_ITEM_INT_EX( 	m_nDelayOutOfService,	_T("Timeout"),		_T("OutOfService"),		60	)	\
	
#endif

#undef		REDEF_LIB_ENV_LIST_EX	

#ifdef	WIN32
#define		REDEF_LIB_ENV_LIST_EX	\
	ENV_ITEM_STR_EX( 	m_strDevDrv,	_T("Device"),	_T("strDevDrv"),	_T("data/devdrv_mcb.json"))	\
	ENV_ITEM_STR_EX( 	m_strFuncHide,	_T("Debug"),	_T("FuncHide"),		_T("SMRT::CRoute::LoadStation;SMRT::CRoute::LoadRouteXml;STProtocolData::OpenProtocol;SMRT::CSMRTNet::CallbackRecvFunc;SMRT::OnRecvDevStatReq;SMRT::OnRecvDevStatRsp;CEnvMgr::printValueTree;CEnvMgr::printValue;SMRT::OnRecvMDStatDatReq;SMRT::OnRecvMDStatDatRsp;SMRT::CSMRTNet::SendMD;SMRT::OnRecvPDStatDatReq_PA;SMRT::OnRecvPDStatDatRsp_PA;SMRT::OnRecvPDStatDatReq_PIS;SMRT::OnRecvPDStatDatRsp_PIS;SMRT::OnRecvPDStatDatReq_CCTV;SMRT::OnRecvPDStatDatRsp_CCTV;SMRT::CSMRTEnv::LoadDeviceInfoFromIP;SMRT::OnRecvIntfDataSet;SMRT::OnRecvCtrlRsp_Start;SMRT::OnRecvCtrlRsp_Start_PAAuto;SMRT::OnRecvCtrlRsp;SMRT::OnRecvCtrlRsp_Stop;SMRT::OnRecvCtrlRsp_Start_PAFunc;"))	\
	ENV_ITEM_INT_EX(	m_iMicVol,		_T( "Device" ), _T( "MicVol" ),		10 )	\
	ENV_ITEM_INT_EX(	m_iSpkVol,		_T( "Device" ), _T( "SpkVol" ),		7 )		\
	ENV_ITEM_INT_EX(	m_iSpkVol2,		_T( "Device" ), _T( "SpkVol2" ),	7 )		\
	ENV_ITEM_INT_EX(	m_iIndoorVol,	_T( "Device" ), _T( "IndoorVol" ),	7 )		\
	ENV_ITEM_INT_EX(	m_iOutdoorVol,	_T( "Device" ), _T( "OutdoorVol" ), 7 )	

#else	//	Linux	
#define		REDEF_LIB_ENV_LIST_EX	\
	ENV_ITEM_STR_EX( 	m_strDevDrv,	_T("Device"),	_T("strDevDrv"),	_T("data/devdrv_mcb.json"))	\
	ENV_ITEM_STR_EX(	m_strFuncHide,	_T("Debug"),	_T("FuncHide"),		_T("LoadStation;LoadRouteXml;OpenProtocol;CallbackRecvFunc;OnRecvDevStatReq;OnRecvDevStatRsp;printValueTree;printValue;OnRecvMDStatDatReq;OnRecvMDStatDatRsp;OnRecvCtrlReq;SendMD;OnRecvPDStatDatReq_PA;OnRecvPDStatDatRsp_PA;OnRecvPDStatDatReq_PIS;OnRecvPDStatDatRsp_PIS;OnRecvPDStatDatReq_CCTV;OnRecvPDStatDatRsp_CCTV;LoadDeviceInfoFromIP;OnRecvIntfDataSet;OnRecvCtrlRsp;OnRecvCtrlRsp_Stop;OnRecvCtrlRsp_Start;OnRecvCtrlRsp_Start_PAAuto;OnRecvCtrlRsp;OnRecvCtrlRsp_Stop;OnRecvCtrlRsp_Start_PAFunc"))	\
	ENV_ITEM_INT_EX(	m_iMicVol,		_T( "Device" ), _T( "MicVol" ),		10 )	\
	ENV_ITEM_INT_EX(	m_iSpkVol,		_T( "Device" ), _T( "SpkVol" ),		7 )		\
	ENV_ITEM_INT_EX(	m_iSpkVol2,		_T( "Device" ), _T( "SpkVol2" ),	7 )		\
	ENV_ITEM_INT_EX(	m_iIndoorVol,	_T( "Device" ), _T( "IndoorVol" ),	7 )		\
	ENV_ITEM_INT_EX(	m_iOutdoorVol,	_T( "Device" ), _T( "OutdoorVol" ), 7 )	

#endif
//	END ENV_LIST_EX

//========================================================================
// envValue::ENV_LIST_EX
namespace	envValue
{
	ENV_LIST_EX
	REDEF_LIB_ENV_LIST_EX
}


class CMCBEnv : public CSMRTEnv
{
	//=============================================================================
	// Constructor & Destructor
public:
	CMCBEnv( ISMRTDev *_pDev, const TCHAR *sIniFile = NULL);
public:
	virtual ~CMCBEnv();
	//=============================================================================
	// Attributes
private:

protected:
//	static CMCBEnv*			m_pInstance;

public:

	//STProtocolData	m_TcmsSdr;
	//STProtocolData	m_TcmsSd;
	//	std::deque<unsigned char> m_qUartBuf;
	//=============================================================================
	// Implementations
private:

protected:
	//=============================================================================
	// Interfaces
public:
	// Initialization
//	static CMCBEnv*			Instance();
	virtual int				Destroy();

};

//#define		pMCBEnv			(	CMCBEnv::Instance()		)

#endif	//	MCB_ENV_H
