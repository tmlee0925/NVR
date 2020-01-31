#ifndef GSTMGR_H
#define GSTMGR_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QTimer>
//#include "typedef.h"		//	Sleep()
//#ifdef __linux__
#ifdef GST_USE
#include <gst/gst.h>
//#include <sys/asoundlib.h>
#endif//GST_USE

#include "gstDefine.h"



class gstMgr : public QThread
{
	Q_OBJECT
public: 
	gstMgr();
	~gstMgr();


public:
	void	startPa			( const char* script );
	int		play			( const char* script );
	void	stop			( void );

	void	setMute			( bool ok );
	void	test			( void );
	int		videotest		( void );
	int		audio_1kHz		( void );
	int		audio_loopback	( void );
	int		audio_mp3		( void );
	int		launch			( void );
	void	startRMS(void);
	void	stopRMS(void);
	double	getNS_dBV();
	void	startNVR(const char* script);


	
public Q_SLOTS:
	void	run				( void );
	void	testSlot(int value);

private:

#ifdef GST_USE

	GstBus		*m_pBus;
	GMainLoop *m_pLoop;

	GstElement	*m_pLevel;
	GstElement	*m_pVolume;
	GstElement	*m_pUdpsrc;
	GstElement	*m_pPipeline, *m_pSource, *m_pSink;
	
	void	getRMS			(GstMessage *msg);
	

	std::list<double> m_dList;

#endif//GST_USE

	bool		m_bTerminate;
	bool		m_bRMS;

signals:
	void endStream(int value);
	void testSig(int value);
};

#endif // GSTMGR_H
