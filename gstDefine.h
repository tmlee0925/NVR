/*
 *
 * Copyright 2011 by Software Development Center, (c)Hunter Technology, Inc.,
 * All rights reserved.
 *
 * This software is the confidential and proprietary information
 * of (C)Hunter Technology, Inc. (“Confidential Information”). You
 * shall not disclose such Confidential Information and shall use
 * it only in accordance with the terms of the license agreement
 * you entered into with (C)Hunter Technology.
 *
 */

#ifndef GST_DEF_H
#define GST_DEF_H

#ifdef GST_USE
#include <gst/gst.h>


struct _App
{
//#ifdef __linux__
 GstElement *pipeline;
 GstElement *appsrc;

 GMainLoop *loop;
 guint sourceid;

 GTimer *timer;
//#endif	//	__linux__

};


typedef struct _App App;

#define COB_PEI_OCC_CALL  "alsasrc device=hw:0,0 do-timestamp=true buffer-time=1 latency-time=1 \
! audioconvert ! audioresample ! tee name=\"cop_mic\" \
alsasrc device=hw:1,0 do-timestamp=true buffer-time=1 latency-time=1 \
! audioconvert ! audioresample ! volume volume=1 ! tee name=\"occ_mic\" \
udpsrc name=\"from_pei_udpsrc\" auto-multicast=true port=5500 caps=\"application/x-rtp\" \
! rtpjitterbuffer ! rtppcmudepay ! mulawdec ! audioconvert ! audioresample ! tee name=\"pei_mic\" \
adder name=\"mix_0\" ! mulawenc ! rtppcmupay ! udpsink name=\"to_pei_udpsink\" port=5500 auto-multicast=true sync=false async=false \
adder name=\"mix_1\" ! alsasink device=hw:0,0 sync=false async=false latency-time=1 buffer-time=1 max-lateness=1 ts-offset=-1000000000 \
adder name=\"mix_2\" ! alsasink device=hw:1,0 sync=false async=false latency-time=1 buffer-time=1 max-lateness=1 ts-offset=-1000000000 \
adder name=\"mix_3\" ! mulawenc ! rtppcmupay ! udpsink name=\"mon_udpsink\" port=5500 auto-multicast=true sync=false async=false \
cop_mic. ! queue flush-on-eos=true max-size-time=100 ! mix_0. \
occ_mic. ! queue flush-on-eos=true max-size-time=100 ! mix_0. \
pei_mic. ! queue flush-on-eos=true max-size-time=100 ! mix_1. \
occ_mic. ! queue flush-on-eos=true max-size-time=100 ! mix_1. \
cop_mic. ! queue flush-on-eos=true max-size-time=100 ! mix_2. \
pei_mic. ! queue flush-on-eos=true max-size-time=100 ! mix_2. \
cop_mic. ! queue flush-on-eos=true max-size-time=100 ! mix_3. \
pei_mic. ! queue flush-on-eos=true max-size-time=100 ! mix_3. \
occ_mic. ! queue flush-on-eos=true max-size-time=100 ! mix_3."

/*
//#define MAN_PA "udpsrc multicast-group=234.1.3.3 auto-multicast=true port=5500 \
//caps=\"application/x-rtp,media=(string)audio,clock-rate=(int)16000,encoding-name=(string)SPEEX\" \
//! rtpjitterbuffer ! queue \
//! rtpspeexdepay ! speexdec \
//! audioconvert ! audioresample \
//! volume name=\"volume\" \
//! alsasink ts-offset=-1000000000 sync=false async=false"

#define MAN_PA "rtpbin name=rtpbin \
udpsrc multicast-group=234.1.3.3 auto-multicast=true port=5500 caps=\"application/x-rtp,media=(string)audio,clock-rate=(int)16000,encoding-name=(string)SPEEX\" ! rtpbin.recv_rtp_sink_0 \
rtpbin. ! rtpspeexdepay ! speexdec ! audioconvert ! audioresample ! volume name=\"volume\" \
! alsasink ts-offset=-1000000000 sync=false async=false \
udpsrc multicast-group=234.1.3.3 auto-multicast=true port=5003 ! rtpbin.recv_rtcp_sink_0 \
rtpbin.send_rtcp_src_0 ! udpsink host=234.1.3.3 auto-multicast=true port=5007 sync=false async=false"
*/

#ifdef WIN32

#define MAN_PA "udpsrc multicast-group=230.0.0.81 auto-multicast=true port=55120 caps=application/x-rtp \
!queue !rtppcmadepay !alawdec !audioconvert !audioresample ! directsoundsink"

#define UDP_SRC_TO_SOUND_SINK "udpsrc multicast-group=%s auto-multicast=true port=%d caps=application/x-rtp \
!queue !rtppcmadepay !alawdec !audioconvert !audioresample ! directsoundsink"

#define FILE_SRC_TO_SOUND_SINK "filesrc location=%s ! wavparse ! audioconvert ! directsoundsink"


#define RTSP_SRC_TO_MP3_FILE_SINK "udpsrc multicast-group=%s auto-multicast=true port=%d caps=\"application/x-rtp\" ! rtppcmadepay ! alawdec ! audioconvert ! audioresample ! queue ! lamemp3enc ! multifilesink location=\"%s\" next-file=max-duration max-file-duration=600000000000"

#define RTSP_SRC2_TO_MP3_FILE_SINK "adder name=mix ! lamemp3enc ! multifilesink location=\"%s\" next-file=max-duration max-file-duration=600000000000 \
udpsrc multicast-group=%s auto-multicast=true port=%d caps=\"application/x-rtp\" ! rtppcmadepay ! alawdec ! audioconvert ! audioresample ! queue ! mix. \
udpsrc multicast-group=%s auto-multicast=true port=%d caps=\"application/x-rtp\" ! rtppcmadepay ! alawdec ! audioconvert ! audioresample ! queue ! mix."


#define RTSP_SRC_TO_MKV_FILE_SINK "rtspsrc location=%s ! rtph265depay ! h265parse ! matroskamux ! multifilesink post-messages=true location=%s next-file=5 max-file-duration=20000000000"





#else	//	linux

#define MAN_PA "udpsrc multicast-group = 230.0.0.81 auto-multicast = true port = 55120 caps = application/x-rtp \
!queue !rtppcmadepay !alawdec !audioconvert !audioresample !alsasink"

#define UDP_SRC_TO_SOUND_SINK "udpsrc multicast-group=%s auto-multicast=true port=%d caps=application/x-rtp \
!queue !rtppcmadepay !alawdec !audioconvert !audioresample !alsasink sync=false latency-time=1 buffer-time=1"

#define FILE_SRC_TO_SOUND_SINK "filesrc location=%s ! wavparse ! audioconvert ! alsasink"

#define RTSP_SRC_TO_MP3_FILE_SINK "adder name=mix ! lamemp3enc ! multifilesink location=\"%s\" next-file=max-duration max-file-duration=600000000000 \
udpsrc multicast-group=%s auto-multicast=true port=%d caps=\"application/x-rtp\" ! rtppcmadepay ! alawdec ! audioconvert ! audioresample ! queue ! mix. \
udpsrc multicast-group=%s auto-multicast=true port=%d caps=\"application/x-rtp\" ! rtppcmadepay ! alawdec ! audioconvert ! audioresample ! queue ! mix."


#define RTSP_SRC_TO_MP3_FILE_SINK "udpsrc multicast-group=%s auto-multicast=true port=%d caps=\"application/x-rtp\" ! rtppcmadepay ! alawdec ! audioconvert ! audioresample ! queue ! lamemp3enc ! multifilesink location=\"%s\" next-file=max-duration max-file-duration=600000000000"

#define RTSP_SRC2_TO_MP3_FILE_SINK "adder name=mix ! lamemp3enc ! multifilesink location=\"%s\" next-file=max-duration max-file-duration=600000000000 \
udpsrc multicast-group=%s auto-multicast=true port=%d caps=\"application/x-rtp\" ! rtppcmadepay ! alawdec ! audioconvert ! audioresample ! queue ! mix. \
udpsrc multicast-group=%s auto-multicast=true port=%d caps=\"application/x-rtp\" ! rtppcmadepay ! alawdec ! audioconvert ! audioresample ! queue ! mix."


#endif


#define AUTO_PA "udpsrc multicast-group=234.1.3.1 auto-multicast=true port=5500 \
caps=\"application/x-rtp, media=(string)audio, clock-rate=(int)90000, encoding-name=(string)MPA, payload=(int)14\" \
! rtpjitterbuffer ! queue \
! rtpmpadepay ! mpegaudioparse ! beepdec \
! audioconvert \
! audioresample \
! volume volume=0.1 name=\"volume\" \
! alsasink"

#define FUNC_PA "udpsrc multicast-group=234.1.3.2 auto-multicast=true port=5500 \
caps=\"application/x-rtp, media=(string)audio, clock-rate=(int)90000, encoding-name=(string)MPA, payload=(int)14\" \
! rtpjitterbuffer ! queue \
! rtpmpadepay ! mpegaudioparse ! beepdec \
! audioconvert \
! audioresample \
! volume volume=0.1 name=\"volume\" \
! alsasink"

#define OCC_PA "udpsrc multicast-group=234.1.3.4 auto-multicast=true port=5500 \
caps=\"application/x-rtp,media=(string)audio,clock-rate=(int)16000,encoding-name=(string)SPEEX\" \
! rtpjitterbuffer ! queue \
! rtpspeexdepay ! speexdec \
! audioconvert ! audioresample \
! volume name=\"volume\" \
! alsasink sync=false async=false"

#define PEI_COB_CALL_R "udpsrc multicast-group=234.10.1.1 auto-multicast=true port=5500 \
caps=\"application/x-rtp,media=(string)audio,clock-rate=(int)16000,encoding-name=(string)SPEEX\" \
! rtpjitterbuffer ! queue ! rtpspeexdepay ! speexdec ! audioconvert ! audioresample \
! volume name=\"volume\" ! alsasink ts-offset=-1000000000 sync=false async=false "

#define PEI_COB_CALL_T "alsasrc ! audio/x-raw, rate=(int)16000 ! audioconvert ! audioresample \
! volume name=\"volume\" ! speexenc ! rtpspeexpay ! udpsink host=234.10.1.2 auto-multicast=true port=5500 sync=false async=false"

#define COB_MAN_PA "alsasrc device=cop \
! audio/x-raw, rate=(int)16000 \
! audioconvert ! audioresample \
! volume name=\"volume\" \
! speexenc ! rtpspeexpay \
! queue ! udpsink host=234.1.3.3 auto-multicast=true port=5500"

#ifdef WIN32
//#define COP_MAN_PA "directsoundsrc ! audio/x-raw, ate=(int)16000 \
//!audioconvert !audioresample \
//!volume name = volume !speexenc !rtpspeexpay \
//!queue !udpsink host = 230.0.0.81 auto-multicast = true port = 55120"
//#define COP_MAN_PA "directsoundsrc ! \"audio/x-raw,rate=16000,channels=2,depth=16\" ! audioconvert ! audioresample !alawenc !rtppcmapay !queue !udpsink host = 230.0.0.81 auto-multicast = true port = 55120"

#define COP_MAN_PA "directsoundsrc \
! audio/x-raw,rate=16000,channels=2,depth=16 \
! audioconvert ! audioresample !alawenc !rtppcmapay \
!queue !udpsink host = 230.0.0.81 auto-multicast = true port = 55120"

#define OCC_MAN_PA "directsoundsrc \
! audio/x-raw,rate=16000,channels=2,depth=16 \
! audioconvert ! audioresample !alawenc !rtppcmapay \
!queue !udpsink host = 230.0.0.81 auto-multicast = true port = 55120"



#define SOUND_SRC_TO_UDP_SINK "directsoundsrc \
! audio/x-raw,rate=16000,channels=2,depth=16 \
! audioconvert ! audioresample !alawenc !rtppcmapay \
!queue !udpsink host=%s auto-multicast=true port=%d"

#define WAV_FILE_SRC_TO_UDP_SINK "filesrc location=%s ! wavparse ! audioconvert ! volume volume=%.1f ! audioresample !alawenc !rtppcmapay \
!queue !udpsink host=%s auto-multicast=true port=%d"

#define MP3_FILE_SRC_TO_UDP_SINK "filesrc location=%s ! mpegaudioparse ! rtppcmapay \
!queue !udpsink host=%s auto-multicast=true port=%d"

/* 이렇게 변경해야 하는데 리눅스에는 mp3 dec 가 없음. 박과장 오면 적용하자.
#ifdef WIN32
#define MP3_FILE_SRC_TO_UDP_SINK "filesrc location=%s ! mpegaudioparse ! mpg123audiodec !audioconvert !audioresample ! alawenc ! rtppcmapay \
!queue !udpsink host=%s auto-multicast=true port=%d"
#else
#define MP3_FILE_SRC_TO_UDP_SINK "filesrc location=%s ! mpegaudioparse ! mpg123audiodec !audioconvert !audioresample ! alawenc ! rtppcmapay \
!queue !udpsink host=%s auto-multicast=true port=%d"
#endif
*/

#else
//#define COP_MAN_PA "alsasrc \
//! audio/x-raw, rate=(int)16000 \
//! audioconvert ! audioresample \
//! volume name=\"volume\" \
//! speexenc ! rtpspeexpay \
//! queue ! udpsink host=230.0.0.81 auto-multicast=true port=55120"

#define COP_MAN_PA "alsasrc buffer-time=1 latency-time=1 \
! audio/x-raw,rate=16000,channels=2,depth=16 \
! audioconvert ! audioresample ! alawenc ! rtppcmapay \
! queue ! udpsink host=230.0.0.81 auto-multicast=true port=55120"

#define SOUND_SRC_TO_UDP_SINK "alsasrc do-timestamp=true buffer-time=1 latency-time=1 blocksize=256 \
! audio/x-raw,rate=16000,channels=2,depth=16 \
! audioconvert ! audioresample ! alawenc ! rtppcmapay \
! queue ! udpsink host=%s auto-multicast=true port=%d"


#define WAV_FILE_SRC_TO_UDP_SINK "filesrc location=%s ! wavparse ! audioconvert ! volume volume=%.1f ! audioresample !alawenc !rtppcmapay \
!queue !udpsink host=%s auto-multicast=true port=%d"

#define MP3_FILE_SRC_TO_UDP_SINK "filesrc location=%s ! mpegaudioparse ! rtppcmapay \
!queue !udpsink host=%s auto-multicast=true port=%d"
#endif

#define SOB_MAN_PA "alsasrc \
! audio/x-raw, rate=(int)16000 \
! audioconvert ! audioresample \
! volume name=\"volume\" \
! speexenc ! rtpspeexpay \
! queue ! udpsink host=234.1.3.3 auto-multicast=true port=5500"

#define COB_MAN_MON "udpsrc multicast-group=234.1.3.3 auto-multicast=true port=5500 \
caps=\"application/x-rtp,media=(string)audio,clock-rate=(int)16000,encoding-name=(string)SPEEX\" \
! queue ! rtpjitterbuffer \
! rtpspeexdepay ! speexdec \
! audioconvert ! audioresample \
! volume name=\"volume\" \
! alsasink device=cop ts-offset=-1000000000 sync=false async=false"

#endif GST_USE

#endif // GST_DEF_H
