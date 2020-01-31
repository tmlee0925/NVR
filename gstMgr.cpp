
//#include "StdQt.h"		//	Pre-compiled Header

//#include "typedef.h"		//	Sleep()
#include "gstMgr.h"
//#include "ctrlPrint.h"

#ifdef WIN32
/*
typedef struct timeval {
	long tv_sec;
	long tv_usec;
} timeval;

int gettimeofday(struct timeval* tp, int* tz)
{
	LARGE_INTEGER tickNow;
	static LARGE_INTEGER tickFrequency;
	static BOOL tickFrequencySet = FALSE;
	if (tickFrequencySet == FALSE) {
		QueryPerformanceFrequency(&tickFrequency);
		tickFrequencySet = TRUE;
	}
	QueryPerformanceCounter(&tickNow);
	tp->tv_sec = (long)(tickNow.QuadPart / tickFrequency.QuadPart);
	tp->tv_usec = (long)(((tickNow.QuadPart % tickFrequency.QuadPart) * 1000000L) / tickFrequency.QuadPart);

	return 0;
}
*/

#else

#include <sys/time.h>
#include <unistd.h>

#endif


#ifdef GST_USE
gstMgr::gstMgr()
: m_pPipeline( NULL )
, m_pVolume( NULL )
, m_pBus(NULL)
, m_bTerminate( false )
, m_bRMS(true)
{
	printf( "%s\n", __FUNCTION__ );

	/* Initialize GStreamer */
	gst_init( NULL, NULL );
	GMainLoop *&loop = m_pLoop;
	loop = g_main_loop_new(NULL, FALSE);

	connect(this, SIGNAL(testSig(int)), this, SLOT(testSlot(int)));

}

#else
gstMgr::gstMgr()
:	m_bTerminate( false )
{
	printf( "%s\n", __FUNCTION__ );
}
#endif

gstMgr::~gstMgr()
{
#ifdef GST_USE
	GstBus * &bus = m_pBus;
	GstElement *pipeline = m_pPipeline;
	gst_object_unref (bus);
    gst_element_set_state (pipeline, GST_STATE_NULL);
    gst_object_unref (pipeline);
#endif// GST_USE
}


void gstMgr::stop()
{
#ifdef GST_USE

	GstElement * &pipeline = m_pPipeline;
	GstBus *&bus = m_pBus;

	//printf( "%s this 0x%08p\n", __FUNCTION__, this );
	m_bTerminate = true;
//	gst_element_set_state( GST_ELEMENT( m_pPipeline), GST_STATE_NULL );	// 여기서 이것을 사용하면 gst_bus_timed_pop_filtered에서 메세지가 발생하지 않음

	gst_object_unref( GST_OBJECT( bus ) );
	gst_element_set_state( GST_ELEMENT ( pipeline ), GST_STATE_NULL );
	gst_object_unref( GST_OBJECT( pipeline ) );

#endif//GST_USE
}

void gstMgr::startPa( const char* script )
{
	printf("%s %s\n", __FUNCTION__, script);
#ifdef GST_USE
	GstElement * &pipeline = m_pPipeline;
	GstElement * &volume = m_pVolume;
	GstBus *&bus = m_pBus;

	pipeline = gst_parse_launch( script, NULL );
	g_assert ( pipeline );

	volume = gst_bin_get_by_name ( GST_BIN( pipeline ), "volume" );
	g_assert( volume );
	printf( "%s volume 0x%08p m_pVolume 0x%08p\n", __FUNCTION__, volume, m_pVolume );
	/* make sure we'll get messages */
	g_object_set ( G_OBJECT ( volume ), "mute", TRUE, NULL );

	bus = gst_pipeline_get_bus ( GST_PIPELINE ( pipeline ) );
	g_assert( bus );

	/* go to playing and wait in a mainloop. */
	gst_element_set_state ( pipeline, GST_STATE_PLAYING );

	//#endif

	if ( !isRunning() )
		start();
#endif//GST_USE
}

void gstMgr::setMute( bool ok )
{
	printf("%s mute %d\n", __FUNCTION__, ok);
#ifdef GST_USE
	GstElement *&pipeline = m_pPipeline;
	GstElement *&volume = m_pVolume;


	gboolean mute_status;
	g_object_get( G_OBJECT ( volume ), "mute", &mute_status, NULL );

	if ( volume == NULL ) return;

	if ( ok ) {
		if ( mute_status == (gboolean)FALSE ) {
			g_object_set ( G_OBJECT ( volume ), "mute", TRUE, NULL );
			gst_element_set_state ( pipeline, GST_STATE_NULL );
		}
	}
	else {
		if ( mute_status == (gboolean)TRUE ) {
			g_object_set ( G_OBJECT ( volume ), "mute", FALSE, NULL );
			gst_element_set_state ( pipeline, GST_STATE_PLAYING );
		}
	}
#endif//GST_USE
}


void gstMgr::getRMS(GstMessage *msg)
{
	const GstStructure *s = gst_message_get_structure(msg);
	const gchar *name = gst_structure_get_name(s);
	//static struct timeval tvStartTime;
	//struct timeval tvEndTime;
	if (strcmp(name, "level") == 0)
	{
		gint channels;
		gdouble rms_dB;

		const GValue *array_val;
		const GValue *value;
		GValueArray *rms_arr;
		gint i;

		array_val = gst_structure_get_value(s, "rms");
		rms_arr = (GValueArray *)g_value_get_boxed(array_val);
		// we can get the number of channels as the length of any of the value arrays 
		channels = rms_arr->n_values;
		for (i = 0; i < 1; ++i)
		{
			
			value = g_value_array_get_nth(rms_arr, i);
			rms_dB = g_value_get_double(value);
			
			
			if (m_dList.size() > 10)
			{
				m_dList.pop_front();
			}

			m_dList.push_back(rms_dB);
			
			/*double dTime;
			gettimeofday(&tvEndTime, NULL);
			dTime = (double)(tvEndTime.tv_sec - tvStartTime.tv_sec) + (tvEndTime.tv_usec - tvStartTime.tv_usec) / 1000000.;
			//if (dTime > 10.)
			{
				printf("\tdt %.2lf %.2lf dBV\n", dTime, rms_dB);
				tvStartTime = tvEndTime;
			}
			*/
			
			printf("%s NS level %.2lf dBV\n", __FUNCTION__,rms_dB);
		}
	}
	
}

static gboolean
my_bus_callback(GstBus     *bus,
	GstMessage *message,
	gpointer    data)
{
	printf("Got %s message\n", GST_MESSAGE_TYPE_NAME(message));

	/* we want to be notified again the next time there is a message
	 * on the bus, so returning TRUE (FALSE means we want to stop watching
	 * for messages on the bus and our callback should not be called again)
	 */
	return TRUE;
}


/**
 * @brief GstManualPa::run
 */
void gstMgr::run()
{
#ifdef GST_USE
	GstElement * &pipeline = m_pPipeline;
	GstBus * &bus = m_pBus;
	GstMessage *msg;
	m_bTerminate = false;

	/* Wait until error or EOS */
	bus = gst_element_get_bus( pipeline );

	do {
		msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, (GstMessageType)(GST_MESSAGE_APPLICATION | GST_MESSAGE_ERROR | GST_MESSAGE_EOS | GST_MESSAGE_STATE_CHANGED | GST_MESSAGE_ELEMENT));
		//msg = gst_bus_timed_pop_filtered( bus, GST_CLOCK_TIME_NONE, (GstMessageType)(GST_MESSAGE_ERROR | GST_MESSAGE_EOS | GST_MESSAGE_STATE_CHANGED) );
		/*msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, (GstMessageType)(GST_MESSAGE_ERROR |
																			GST_MESSAGE_STATE_CHANGED |
																			GST_MESSAGE_INFO |
																			GST_MESSAGE_NEW_CLOCK |
																			GST_MESSAGE_EOS |
																			GST_MESSAGE_STREAM_START |
																			GST_MESSAGE_ELEMENT));
		*/

		/* Parse message */
		if (msg != NULL) {
			GError *err;
			gchar *debug_info;
			//printf("this 0x%08X msg 0x%08X\n", this, msg->type);

			switch (GST_MESSAGE_TYPE(msg)) {

			case GST_MESSAGE_APPLICATION:
			{
				printf("gst message application.");
				break;
			}
			case GST_MESSAGE_ERROR:
				gst_message_parse_error(msg, &err, &debug_info);
				printf("Error received from element %s: %s\n", GST_OBJECT_NAME(msg->src), err->message);
				printf("Debugging information: %s\n", debug_info ? debug_info : "none");
				g_clear_error(&err);
				g_free(debug_info);
				emit endStream(1);
				break;

			case GST_MESSAGE_EOS:
				printf("End-Of-Stream reached.\n");
				//stop();
				emit endStream(1);
				//emit testSig(1);
				break;

			case GST_MESSAGE_STATE_CHANGED:
				// We are only interested in state-changed messages from the pipeline 
				if (GST_MESSAGE_SRC(msg) == GST_OBJECT(pipeline)) {
					GstState old_state, new_state, pending_state;
					gst_message_parse_state_changed(msg,
						&old_state,
						&new_state,
						&pending_state);
					printf("GST_MESSAGE_STATE_CHANGE %d %d %d\n", old_state, new_state, pending_state);
				}
				break;

			case GST_MESSAGE_NEW_CLOCK:
				printf("GST_MESSAGE_NEW_CLOCK\n");
				break;

			case GST_MESSAGE_STREAM_START:
				printf("GST_MESSAGE_STREAM_START\n");
				break;

			case GST_MESSAGE_ELEMENT:
				
				//printf("GST_MESSAGE_ELEMENT\n");
				if (m_bRMS)
				{
					getRMS(msg);
				}
				{
					const GstStructure *structure = gst_message_get_structure(msg);
					const gchar *filename;
					
					if (gst_structure_has_name(structure, "GstMultiFileSink")) {
						g_object_set(m_pSink, "location", "d:\\ssd1\\new_%05d.mkv", NULL);

						filename = gst_structure_get_string(structure, "filename");
						printf("Got file save message from multifilesink, "
							"image %s has been saved", filename);
						//gst_element_set_state(pipeline, GST_STATE_NULL);
						if (filename) {
							//gst_image_capture_bin_post_image_done(GST_CAMERA_BIN2_CAST(bin),	filename);
							//gst_element_set_state(pipeline, GST_STATE_NULL);
							//gst_element_set_state(pipeline, GST_STATE_PLAYING);
						}
						//dec_counter = TRUE;
					}
					

				}
				
				break;
			default:
				/* We should not reach here because we only asked for ERRORs and EOS */
				printf( "Unexpected message received.\n" );
				emit endStream(1);
				break;
			}
			gst_message_unref( msg );
		}
		//sleep(1);
	} while ( !m_bTerminate );

	/* Free resources */
	gst_object_unref( GST_OBJECT( bus) );
	gst_element_set_state( GST_ELEMENT ( pipeline), GST_STATE_NULL );
	gst_object_unref( GST_OBJECT(pipeline ));

	printf( "%s - thread stop ------------------------------------------------------\n", __func__ );
#endif//GST_USE
}



void gstMgr::test()
{
#ifdef GST_USE
	GstElement * &pipeline = m_pPipeline;

	/* Build the pipeline */
	pipeline = gst_parse_launch( "playbin uri=https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm", NULL );

	/* Start playing */
	gst_element_set_state( pipeline, GST_STATE_PLAYING );

	if ( !isRunning() )
		start();
#endif//GST_USE
}


int gstMgr::videotest()
{
#ifdef GST_USE
	GstElement * &pipeline = m_pPipeline;
	GstElement *source, *sink;
	GstStateChangeReturn ret;

	/* Initialize GStreamer */
	//gst_init(NULL, NULL);

	/* Create the elements */
	source = gst_element_factory_make( "videotestsrc", "source" );
	sink = gst_element_factory_make( "autovideosink", "sink" );

	/* Create the empty pipeline */
	pipeline = gst_pipeline_new( "test-pipeline" );

	if ( !pipeline || !source || !sink ) {
		g_printerr( "Not all elements could be created.\n" );
		return -1;
	}

	/* Build the pipeline */
	gst_bin_add_many( GST_BIN( pipeline ), source, sink, NULL );
	if ( gst_element_link( source, sink ) != (gboolean)TRUE ) {
		g_printerr( "Elements could not be linked.\n" );
		gst_object_unref( pipeline );
		return -1;
	}

	/* Modify the source's properties */
	g_object_set( source, "pattern", 0, NULL );

	/* Start playing */
	ret = gst_element_set_state( pipeline, GST_STATE_PLAYING );
	if ( ret == GST_STATE_CHANGE_FAILURE ) {
		g_printerr( "Unable to set the pipeline to the playing state.\n" );
		gst_object_unref( pipeline );
		return -1;
	}

	if ( !isRunning() )
		start();
#endif//GST_USE
	return 0;
}


int gstMgr::audio_1kHz()
{
#ifdef GST_USE
	GstElement * &pipeline = m_pPipeline;
	GstElement * &source = m_pSource;
	GstElement * &sink = m_pSink;
	GstStateChangeReturn ret;

	/* Create the elements */
	source = gst_element_factory_make( "audiotestsrc", "source" );
	sink = gst_element_factory_make( "autoaudiosink", "sink" );

	/* Create the empty pipeline */
	pipeline = gst_pipeline_new( "test-pipeline" );

	if ( !pipeline || !source || !sink ) {
		g_printerr( "Not all elements could be created.\n" );
		return -1;
	}

	/* Build the pipeline */
	gst_bin_add_many( GST_BIN( pipeline ), source, sink, NULL );
	if ( gst_element_link( source, sink ) != (gboolean)TRUE ) {
		g_printerr( "Elements could not be linked.\n" );
		gst_object_unref( pipeline );
		return -1;
	}

	/* Modify the source's properties */
	g_object_set( source, "pattern", 0, NULL );

	/* Start playing */
	ret = gst_element_set_state( pipeline, GST_STATE_PLAYING );
	if ( ret == GST_STATE_CHANGE_FAILURE ) {
		g_printerr( "Unable to set the pipeline to the playing state.\n" );
		gst_object_unref( pipeline );
		return -1;
	}

	if ( !isRunning() )
		start();

#endif//GST_USE	
	return 0;
}

int gstMgr::audio_loopback()
{
#ifdef GST_USE
	GstElement * &pipeline = m_pPipeline;
	GstElement *source, *sink;
	GstStateChangeReturn ret;

	/* Initialize GStreamer */
	//gst_init(NULL, NULL);

	/* Create the elements */
	source = gst_element_factory_make( "directsoundsrc", "source" );
	sink = gst_element_factory_make( "directsoundsink", "sink" );

	/* Create the empty pipeline */
	pipeline = gst_pipeline_new( "test-pipeline" );

	if ( !pipeline || !source || !sink ) {
		g_printerr( "Not all elements could be created.\n" );
		return -1;
	}

	/* Build the pipeline */
	gst_bin_add_many( GST_BIN( pipeline ), source, sink, NULL );
	if ( gst_element_link( source, sink ) != (gboolean)TRUE ) {
		g_printerr( "Elements could not be linked.\n" );
		gst_object_unref( pipeline );
		return -1;
	}

	/* Modify the source's properties */
	g_object_set( source, "pattern", 0, NULL );

	/* Start playing */
	ret = gst_element_set_state( pipeline, GST_STATE_PLAYING );
	if ( ret == GST_STATE_CHANGE_FAILURE ) {
		g_printerr( "Unable to set the pipeline to the playing state.\n" );
		gst_object_unref( pipeline );
		return -1;
	}

	if ( !isRunning() )
		start();
#endif//GST_USE
	return 0;
}



int gstMgr::audio_mp3()
{
#ifdef GST_USE
	GstElement * &pipeline = m_pPipeline;

	/* Build the pipeline */
	pipeline = gst_parse_launch( "playbin uri=file:///d:/test.mp3", NULL );

	/* Start playing */
	gst_element_set_state( pipeline, GST_STATE_PLAYING );

	if ( !isRunning() )
		start();
#endif//GST_USE
	return 0;
}

int gstMgr::play( const char* script )
{
	printf("%s %s\n", __FUNCTION__, script);
#ifdef GST_USE

	GstElement * &pipeline = m_pPipeline;
	
	if (isRunning())
	{
		stop();		//	Play전에 항상 stop을 해줌.

		Sleep(10);
	}
	
	/* Build the pipeline */
	pipeline = gst_parse_launch( script, NULL );

	/* Start playing */
	gst_element_set_state( pipeline, GST_STATE_PLAYING );

	if ( !isRunning() )
		start();
#endif//ifdef GST_USE	
	return 0;
}


int gstMgr::launch()
{
#ifdef GST_USE
#if 0
	GstElement * &pipeline = m_pPipeline;
	GstElement *source, *sink;
	GstStateChangeReturn ret;

	/* Initialize GStreamer */
	//gst_init(NULL, NULL);

	/* Create the elements */
	source = gst_element_factory_make( "videotestsrc", "source" );
	sink = gst_element_factory_make( "autovideosink", "sink" );

	/* Create the empty pipeline */
	pipeline = gst_pipeline_new( "test-pipeline" );

	if ( !pipeline || !source || !sink ) {
		g_printerr( "Not all elements could be created.\n" );
		return -1;
	}

	/* Build the pipeline */
	gst_bin_add_many( GST_BIN( pipeline ), source, sink, NULL );
	if ( gst_element_link( source, sink ) != (gboolean)TRUE ) {
		g_printerr( "Elements could not be linked.\n" );
		gst_object_unref( pipeline );
		return -1;
	}

	/* Modify the source's properties */
	g_object_set( source, "pattern", 0, NULL );

	/* Start playing */
	ret = gst_element_set_state( pipeline, GST_STATE_PLAYING );
	if ( ret == GST_STATE_CHANGE_FAILURE ) {
		g_printerr( "Unable to set the pipeline to the playing state.\n" );
		gst_object_unref( pipeline );
		return -1;
	}

	if ( !isRunning() )
		start();
#endif
#endif//GST_USE
	return 0;
}



void gstMgr::testSlot(int value)
{
	printf("%s : %d\n", __FUNCTION__, value);
}

void gstMgr::startRMS()
{
	m_bRMS = 1;
}

void gstMgr::stopRMS()
{
	m_bRMS = 0;
}


double	gstMgr::getNS_dBV()
{
	double avg = 0;
	
	std::list<double>::iterator it;
	for (it = m_dList.begin(); it != m_dList.end(); it++)
	{
		avg += *it;
	}
	avg /= m_dList.size();

	return avg;
}

//static GMainLoop *loop;


static gboolean
bus_call(GstBus     *bus,
	GstMessage *msg,
	gpointer    data)
{
	GMainLoop *loop = (GMainLoop *)data;

	switch (GST_MESSAGE_TYPE(msg)) {

	case GST_MESSAGE_EOS:
		g_print("End of stream\n");
		g_main_loop_quit(loop);
		break;

	case GST_MESSAGE_ERROR: {
		gchar  *debug;
		GError *error;

		gst_message_parse_error(msg, &error, &debug);
		g_free(debug);

		g_printerr("Error: %s\n", error->message);
		g_error_free(error);

		g_main_loop_quit(loop);
		break;

	
	}
	case GST_MESSAGE_ELEMENT:


	{
		const GstStructure *structure = gst_message_get_structure(msg);
		const gchar *filename;

		if (gst_structure_has_name(structure, "GstMultiFileSink")) {
			//g_object_set(m_pSink, "location", "d:\\ssd1\\new_%05d.mkv", NULL);

			filename = gst_structure_get_string(structure, "filename");
			printf("Got file save message from multifilesink, "
				"image %s has been saved", filename);
			if (filename) {

			}

		}


	}

	break;
	default:
		break;
	}

	return TRUE;
}


static void
on_pad_added(GstElement *element,
	GstPad     *pad,
	gpointer    data)
{
	GstPad *sinkpad;
	GstElement *decoder = (GstElement *)data;

	/* We can now link this pad with the vorbis-decoder sink pad */
	g_print("Dynamic pad created, linking demuxer/decoder\n");
	sinkpad = gst_element_get_static_pad(decoder, "sink");
	gst_pad_link(pad, sinkpad);
	gst_object_unref(sinkpad);
}

static gboolean callback(gpointer data)
{
	static guint16 i = 0;
	printf("Iter=%d\n", i++);
	if (i % 5 == 0) {
		g_print("try to stop loop1\n");
		g_main_loop_quit((GMainLoop*)data);
	}
	return TRUE;
}


void gstMgr::startNVR(const char* script)
{
	printf("%s %s\n", __FUNCTION__, script);
#ifdef GST_USE
	GstElement * &pipeline = m_pPipeline;
	GstElement * &src = m_pSource;
	GstElement * &sink = m_pSink;
	GMainLoop * &loop = m_pLoop;
	GstBus *&bus = m_pBus;
	GstStateChangeReturn ret;
	
	guint bus_watch_id;
	

	//GstElement *pipeline = gst_pipeline_new("looper-pipeline");
	pipeline = gst_pipeline_new("looper-pipeline");
	//GstElement *src = gst_element_factory_make("rtspsrc", "rtspsrc0");
	src = gst_element_factory_make("rtspsrc", "rtspsrc0");
	GstElement *depay = gst_element_factory_make("rtph265depay", "rtph265depay0");
	GstElement *parse = gst_element_factory_make("h265parse", "h265parse0");
	GstElement *muxer = gst_element_factory_make("matroskamux", "matroskamux0");
	//GstElement *sink = gst_element_factory_make("multifilesink", "multifilesink0");
	sink = gst_element_factory_make("multifilesink", "multifilesink0");


	if (!pipeline || !src || !depay || !parse || !muxer || !sink) {
		g_error("Failed to create elements");
		return;
	}

	g_object_set(src, "location", "rtsp://10.128.0.225:554/cam/realmonitor?channel=1&subtype=0&unicast=true&proto=Onvif", NULL);


	g_object_set(sink, "next-file", 5, NULL);
	g_object_set(sink, "location", "d:\\ssd1\\min_%05d.mkv", NULL);
	g_object_set(sink, "post-messages", TRUE, NULL);
	g_object_set(sink, "max-file-duration", 50000000000, NULL);

	
	/* we add a message handler */
	bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
	bus_watch_id = gst_bus_add_watch(bus, bus_call, loop);
	gst_object_unref(bus);

	

	gst_bin_add_many(GST_BIN(pipeline), src, depay, parse, muxer, sink, NULL);
		
	gboolean success;
	success = gst_element_link_many(depay, parse, muxer, sink, NULL);
	
	if (!success) {
		g_printerr("Elements could not be linked.\n");
	}

	// Dynamic Pad Creation
	g_signal_connect(src, "pad-added", G_CALLBACK(on_pad_added), depay);
	
	g_timeout_add_seconds(1, callback, loop);
#if 1	
	printf("Running\n");
	gst_element_set_state(pipeline, GST_STATE_PLAYING);
	/* Set the pipeline to "playing" state*/

	/* Iterate */
	g_main_loop_run(loop);

	printf("STOPPING\n");

	/* Out of the main loop, clean up nicely */
	g_print("Returned, stopping playback\n");
	gst_element_set_state(pipeline, GST_STATE_NULL);

	g_print("Deleting pipeline\n");
	gst_object_unref(GST_OBJECT(pipeline));
	g_source_remove(bus_watch_id);
	g_main_loop_unref(loop);

#else
	
	ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
	if (ret == GST_STATE_CHANGE_FAILURE) {
		g_printerr("Unable to set the pipeline to the playing state.\n");
		gst_object_unref(pipeline);
		return;
	}

	if (!isRunning())
		start();
		
#endif
#endif//GST_USE
}