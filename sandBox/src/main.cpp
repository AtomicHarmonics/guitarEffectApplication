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
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include <iostream>
#include <iomanip>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>
#include <json.hpp>
#include "readerwriterqueue.h"

using json = nlohmann::json;

void *myThreadFun(void *vargp)
{
    moodycamel::ReaderWriterQueue<audioEffectsConfig> *configQueue2 = (moodycamel::ReaderWriterQueue<audioEffectsConfig> *)vargp;
    audioEffectsConfig config2 = {};
    while(1){
    while(configQueue2->size_approx() == 0)
    {
        usleep(10000);
    }
    if(!configQueue2->try_dequeue(config2))
    {
        throw std::invalid_argument("FAILED TO POP QUEUE!");
    }
    
    printf("Overdrive A value: %lf \n", config2.overDriveA);
    }
    return NULL;
}
   

int
main ( int argc, char *argv[] )
{

    moodycamel::ReaderWriterQueue<audioEffectsConfig> *configQueue;
    configQueue = new moodycamel::ReaderWriterQueue<audioEffectsConfig> (1);

    pthread_t thread_id;
    printf("Before Thread\n");
    pthread_create(&thread_id, NULL, myThreadFun, configQueue);
    
    audioEffects a;
    a.recieveConfig();
    while(1)
    {
        
    }
    httplib::Client cli("http://localhost:4996");
    
    


    while (1)
    {
        auto res = cli.Get("/effectsProfile/selectedProfile/");
    std::cout << res->body << std::endl;
    std::cout << "now onto parse json " << std::endl;
    json j_complete = json::parse(res->body);
    std::cout << std::setw(4) << j_complete << "\n\n";
    std::cout << j_complete["author"] << "\n\n";

    audioEffectsConfig config = {};
    config.overDriveEnabled = j_complete["overDriveEnabled"];
    config.overDriveOrderNumber = j_complete["overDriveOrderNumber"];
    config.overDriveA = j_complete["overDriveThresh"];
    config.tremoloDepth = j_complete["tremoloDepth"];
    config.tremoloEnabled = j_complete["tremoloEnabled"];
    config.tremoloFreq = j_complete["tremoloFreq"];
    config.tremoloOrderNumber = j_complete["tremoloOrderNumber"];
    
    if (configQueue->size_approx() != 1)
    {
        if(!configQueue->try_enqueue(config))
        {
            throw std::invalid_argument("FAILED TO PUSH FULL FRAME!");
        }
    }



#ifdef WIN32
        Sleep ( 1000 );
#else
        sleep ( 2 );
#endif
    }
    exit ( 0 );
}

