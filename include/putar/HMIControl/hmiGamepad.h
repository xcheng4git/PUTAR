#ifndef _HMIGAMEPAD_H_
#define _HMIGAMEPAD_H_

#include "hmi.h"
#include "../Defs/defs.h"
#include "Utilities/observerAR.h"
#include <iostream>
#include <string>
#include "opencvCore.h"


#include "../../3rdParty/tinyXML/tinyxml2.h"
#include <thread>
#include <mutex>



namespace putar {
    Hmi* createMyHmiGamepad(void);
    Hmi* createMyHmiGamepad(std::string configFilename);
}

using namespace putar;


class HmiGamepad : public Hmi {
    public:

        // Pointer
        typedef std::unique_ptr<HmiGamepad> Ptr;
    class Config
    {

      public:
        Config(){
        }

        Config(std::string configFilename){
            load(configFilename);
        }

        void load(std::string configFilename) {
            tinyxml2::XMLDocument config;
            std::string filename = "../../resources/" + configFilename;
            config.LoadFile(filename.c_str());
            if (config.ErrorID())
                std::cout << "unable to load HmiGamepad config file: " + filename << std::endl;
            tinyxml2::XMLElement * model = config.FirstChildElement( "HmiGamepadConfig" );
            devicename = model->FirstChildElement( "parameters" )->Attribute("devicename");
            model->FirstChildElement( "parameters" )->QueryFloatAttribute("delay", &delay);
            model->FirstChildElement( "parameters" )->QueryFloatAttribute("increment", &increment);
            model->FirstChildElement( "parameters" )->QueryFloatAttribute("increment", &angle);
        }

        public:
            /// devicename
            std::string devicename;
            /// delay
            float delay;
            /// increment
            float increment;
            /// angle
            float angle;
    };

        // overloaded constructor
        HmiGamepad(void);

        /// Construction
        HmiGamepad(std::string configFilename);
        
        // Updates pose
        void updatePose(Mat34& pose);
        
        // Virtual descrutor
        ~HmiGamepad();
private:
        ///config
        Config config;

        void gamepadProcess();

        int joy_fd, *axis=NULL, num_of_axis=0, num_of_buttons=0, x;
        char *button=NULL, name_of_joystick[80];

        Mat34 zmienna;
        Mat34 macierz;
        std::unique_ptr<std::thread> gamepadThread;
};

#endif
