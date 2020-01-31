/*------------------------------------------------------------------------
	Project     : SMRT
	Description : Env Define

	Writer      : 
	Date        : 2018. 10.
	Copyright   : Piranti

	[Revision History ]
	1. 2018. 10. : Created

------------------------------------------------------------------------*/

//========================================================================
// Header
#include "envMgr.h"
#include "envValue.h"


//========================================================================
// User Define

#include "SMRTEnv.h"		//	Library Env 가 앞에  있어야함.
#include "MCBEnv.h"			//	Include 순서 고정

#include "SMRTProto.h"		//	SMRT Protocol
#include "SMRTProtoTcms2Avc.h"


//========================================================================
// Function Define


#define		IS_THISFILE_CPP	1

#include "envValue_func.h"			// 외부 정의 선언.


//========================================================================


//CMCBEnv* CMCBEnv::m_pInstance = NULL;


/// @brief			객체 생성 시 필요한 초기화 수행(변수 초기화, 동적생성 메모리 할당)
/// @remarks		
//=============================================================================
CMCBEnv::CMCBEnv( ISMRTDev *_pDev, const TCHAR *sIniFile /*= NULL*/)
//=============================================================================
	:	CSMRTEnv( _pDev, sIniFile )
{
	
}

/// @brief			객체 소멸시 필요한 작업 수행(동적 생성 메모리 해제)
/// @remarks		
//=============================================================================
CMCBEnv::~CMCBEnv()
//=============================================================================
{

}



/// @brief			인스턴스 생성
/// @remarks		
/*
//===========================================================================
CMCBEnv* CMCBEnv::Instance()
//===========================================================================
{
	if (NULL == m_pInstance) {
		m_pInstance = new CMCBEnv;
		m_pInstance->Initialize();
	}

	

	return m_pInstance;
}
*/

/// @brief			객체 소멸시 필요한 작업 수행(동적 생성 메모리 해제)
/// @remarks		
//=============================================================================
int CMCBEnv::Destroy()
//=============================================================================
{
	if (NULL != m_pInstance) {
		delete m_pInstance;
		m_pInstance = NULL;
	}
	return 0;
}

