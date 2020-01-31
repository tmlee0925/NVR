/*------------------------------------------------------------------------------------------
	File Name		: $Id: version.cpp 992 2015-11-19 05:40:31Z zlkit $
	Project			: SMRT Info 
	Description		: SMRTApp Version Information

	Writer			: $Author: zlkit $
	Revision		: $Rev: 992 $
	Date			: 2018. 08.
	Copyright		: Piranti Corp.
	 
	Revision History 
	1. 2018. 08.	: Created
-------------------------------------------------------------------------------------------*/

//========================================================================
// Header

#include <stdio.h>

#include "VerInfo.h"						// g_Version	선언.
#include "Version.h"						// FILEVER		SW 버전정보.

//========================================================================
// Define

// g_Version 정의.
VER_INFO g_Version		= VER_INFO(	FILEVER	);	//	#define FILEVER 1,	0,	0,	0

//===========================================================================
void version_History()					// Print Version History
//===========================================================================
{
	_tprintf( _T( VERSION_HISTORY ) );
}
