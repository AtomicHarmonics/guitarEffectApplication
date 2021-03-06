/** @file thru_client.c
 *
 * @brief This simple through client demonstrates the basic features of JACK
 * as they would be used by many applications.
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#ifndef WIN32
#include <unistd.h>
#endif
#include <jack/jack.h>
#include "audioEffects.h"



jack_port_t **input_ports;
jack_port_t **output_ports;
jack_client_t *client;

// #define TABLE_SIZE   (512)
// typedef struct
// {
// 	float sine[TABLE_SIZE];
// 	int left_phase;
// 	int right_phase;
//     int counter;
// }
// paTestData;


static void signal_handler ( int sig )
{
    jack_client_close ( client );
    fprintf ( stderr, "signal received, exiting ...\n" );
    exit ( 0 );
}

/**
 * The process callback for this JACK application is called in a
 * special realtime thread once for each audio cycle.
 *
 * This client follows a simple rule: when the JACK transport is
 * running, copy the input port to the output.  When it stops, exit.
 */

int
process ( jack_nframes_t nframes, void *arg )
{
    int i;
    jack_default_audio_sample_t *in, *out;
    audioEffects *data = (audioEffects*)arg;
    //left channel = 2: clean audio
    //right channel = 1: send audio to tremoloEffect
    for ( i = 1; i < 3; i++ )
    {
        if(i == 2)
        {
            in = (jack_default_audio_sample_t*) jack_port_get_buffer ( input_ports[0], nframes );
            out = (jack_default_audio_sample_t*) jack_port_get_buffer ( output_ports[0], nframes );
        }
        else
        {
            in = (jack_default_audio_sample_t*) jack_port_get_buffer ( input_ports[i], nframes );
            out = (jack_default_audio_sample_t*) jack_port_get_buffer ( output_ports[i], nframes );
        }
        if(i == 2)
        {
            memcpy ( out, in, nframes * sizeof ( jack_default_audio_sample_t ) );
        }
        else
        {
            //data->tremoloEffect(in,out,nframes,4.0, 48000);
            //data->tremoloEffect_2(in,out,nframes,4.0, 100);
            //data->distortEffect(in,out,nframes, 0.3);
            //data->overdriveEffect(in,out,nframes, 3);
//void audioEffects::reverbEffect(const float* inputBuffer, float* outputBuffer, unsigned long frames, unsigned int sampleRate, float reverbWetLevel, float reverbRoomSize, float reverbDryLevel, float reverbDampLevel, float reverbWidth, float reverbMode)
            
            //data->reverbEffect(in, out, nframes, 44100, (1.0f/3.0f), 0.5f, 0.0f, 0.25f, 1.0f, 0.0f);

            //data->reverbEffect_2(in, out, nframes, 44100);
            data->process(in,out,nframes);


        }
    }
    return 0;
}

/**
 * JACK calls this shutdown_callback if the server ever shuts down or
 * decides to disconnect the client.
 */
void
jack_shutdown ( void *arg )
{
    free ( input_ports );
    free ( output_ports );
    exit ( 1 );
}

int
main ( int argc, char *argv[] )
{
    int i;
    const char **ports;
    const char *client_name;
    const char *server_name = NULL;
    jack_options_t options = JackNullOption;
    jack_status_t status;
    audioEffects a;
    volatile int x = a.returnFour();
    if ( argc >= 2 )        /* client name specified? */
    {
        client_name = argv[1];
        if ( argc >= 3 )    /* server name specified? */
        {
            server_name = argv[2];
            int my_option = JackNullOption | JackServerName;
			options = (jack_options_t)my_option;
        }
    }
    else              /* use basename of argv[0] */
    {
        client_name = strrchr ( argv[0], '/' );
        if ( client_name == 0 )
        {
            client_name = argv[0];
        }
        else
        {
            client_name++;
        }
    }

    /* open a client connection to the JACK server */

    client = jack_client_open ( client_name, options, &status, server_name );
    if ( client == NULL )
    {
        fprintf ( stderr, "jack_client_open() failed, "
                  "status = 0x%2.0x\n", status );
        if ( status & JackServerFailed )
        {
            fprintf ( stderr, "Unable to connect to JACK server\n" );
        }
        exit ( 1 );
    }
    if ( status & JackServerStarted )
    {
        fprintf ( stderr, "JACK server started\n" );
    }
    if ( status & JackNameNotUnique )
    {
        client_name = jack_get_client_name ( client );
        fprintf ( stderr, "unique name `%s' assigned\n", client_name );
    }

    /* tell the JACK server to call `process()' whenever
       there is work to be done.
    */

    jack_set_process_callback ( client, process,&a );

    /* tell the JACK server to call `jack_shutdown()' if
       it ever shuts down, either entirely, or if it
       just decides to stop calling us.
    */

    jack_on_shutdown ( client, jack_shutdown, 0 );

    /* create two ports pairs*/
    input_ports = ( jack_port_t** ) calloc ( 2, sizeof ( jack_port_t* ) );
    output_ports = ( jack_port_t** ) calloc ( 2, sizeof ( jack_port_t* ) );

    char port_name[16];
    for ( i = 0; i < 2; i++ )
    {
        sprintf ( port_name, "input_%d", i + 1 );
        input_ports[i] = jack_port_register ( client, port_name, JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0 );
        sprintf ( port_name, "output_%d", i + 1 );
        output_ports[i] = jack_port_register ( client, port_name, JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0 );
        if ( ( input_ports[i] == NULL ) || ( output_ports[i] == NULL ) )
        {
            fprintf ( stderr, "no more JACK ports available\n" );
            exit ( 1 );
        }
    }

    /* Tell the JACK server that we are ready to roll.  Our
     * process() callback will start running now. */

    if ( jack_activate ( client ) )
    {
        fprintf ( stderr, "cannot activate client" );
        exit ( 1 );
    }

    /* Connect the ports.  You can't do this before the client is
     * activated, because we can't make connections to clients
     * that aren't running.  Note the confusing (but necessary)
     * orientation of the driver backend ports: playback ports are
     * "input" to the backend, and capture ports are "output" from
     * it.
     */

    // ports = jack_get_ports ( client, NULL, NULL, JackPortIsOutput );
    // if ( ports == NULL )
    // {
    //     fprintf ( stderr, "no physical capture ports\n" );
    //     exit ( 1 );
    // }

    // for ( i = 0; i < 2; i++ )
	// {
	//     int res = jack_connect ( client, ports[i], jack_port_name ( input_ports[0] ) );
	// 	if (res)
	// 	{
    //         fprintf ( stderr, "cannot connect input ports1: %d %d \n",i, res );
	// 	}
    // }
    // free ( ports );

    // ports = jack_get_ports ( client, NULL, NULL, JackPortIsPhysical|JackPortIsInput );
    // if ( ports == NULL )
    // {
    //     fprintf ( stderr, "no physical playback ports\n" );
    //     exit ( 1 );
    // }

    // for ( i = 0; i < 2; i++ )
    //     if ( jack_connect ( client, jack_port_name ( output_ports[i] ), ports[i] ) )
    //         fprintf ( stderr, "cannot connect input ports2\n" );

    // free ( ports );

    /* install a signal handler to properly quits jack client */
#ifdef WIN32
    signal ( SIGINT, signal_handler );
    signal ( SIGABRT, signal_handler );
    signal ( SIGTERM, signal_handler );
#else
    signal ( SIGQUIT, signal_handler );
    signal ( SIGTERM, signal_handler );
    signal ( SIGHUP, signal_handler );
    signal ( SIGINT, signal_handler );
#endif

    /* keep running until the transport stops */

    while (1)
    {
        a.recieveConfig();
#ifdef WIN32
        Sleep ( 1000 );
#else
        usleep ( 500000 );
#endif
    }

    jack_client_close ( client );
    exit ( 0 );
}

