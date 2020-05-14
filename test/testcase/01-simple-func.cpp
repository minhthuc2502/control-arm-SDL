#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE CONFIG_FILE
#include <boost/test/unit_test.hpp>
#include <fstream>
#include <iostream>
#include "../../includes/joystickPS3.hpp"
bool validinput(int i)
{
    return (i > 16) ? false : true;
}

bool GetConfig(char* fileConfig, PARAM_CONFIG &pconfigJoy)
{
    bool haveHat; 
    std::ifstream cFile (fileConfig);
    if (cFile.is_open()) {
        std::string line;
        while(getline(cFile, line)){
            line.erase(std::remove_if(line.begin(), line.end(), isspace),
                                line.end());
            line.erase(std::remove(line.begin(), line.end(), '\"'),
                                line.end());
            if (line[0] == '#' || line.empty())
                continue;
            auto delimiterPos = line.find("=");
            std::string name = line.substr(0, delimiterPos);
            if (!name.compare("input_b_btn")) {
                pconfigJoy.BSouth = stoi(line.substr(delimiterPos + 1));
                if (!validinput(pconfigJoy.BSouth))
                    return false;
            } else if (!name.compare("input_y_btn")) {
                pconfigJoy.BWest = stoi(line.substr(delimiterPos + 1));
                if (!validinput(pconfigJoy.BWest))
                    return false;
            } else if (!name.compare("input_a_btn")) {
                pconfigJoy.BEast = stoi(line.substr(delimiterPos + 1));
                if (!validinput(pconfigJoy.BEast))
                    return false;
            } else if (!name.compare("input_x_btn")) {
                pconfigJoy.BNorth = stoi(line.substr(delimiterPos + 1));
                if (!validinput(pconfigJoy.BNorth))
                    return false;
            } else if (!name.compare("input_select_btn")) {
                pconfigJoy.BSelect = stoi(line.substr(delimiterPos + 1));
                if (!validinput(pconfigJoy.BSelect))
                    return false;
            } else if (!name.compare("input_start_btn")) {
                pconfigJoy.BStart = stoi(line.substr(delimiterPos + 1));
                if (!validinput(pconfigJoy.BStart))
                    return false;
            } else if (!name.compare("input_up_btn")) {
                if (line.substr(delimiterPos + 1) == "h0up") {
                pconfigJoy.BUp = SDL_HAT_UP_NIN;
                haveHat = true;
                } else {
                pconfigJoy.BUp = stoi(line.substr(delimiterPos + 1));
                if (!validinput(pconfigJoy.BUp))
                    return false;
                }
            } else if (!name.compare("input_down_btn"))
            {
                if (line.substr(delimiterPos + 1) == "h0down")
                {
                pconfigJoy.BDown = SDL_HAT_DOWN_NIN;
                haveHat = true;
                } else {
                pconfigJoy.BDown = stoi(line.substr(delimiterPos + 1));
                if (!validinput(pconfigJoy.BDown))
                    return false;
                }
            } else if (!name.compare("input_left_btn")) {
                if (line.substr(delimiterPos + 1) == "h0left") {
                pconfigJoy.BLeft = SDL_HAT_LEFT_NIN;
                haveHat = true;
                } else {
                pconfigJoy.BLeft = stoi(line.substr(delimiterPos + 1));
                if (!validinput(pconfigJoy.BLeft))
                    return false;
                }
            }
            else if (!name.compare("input_right_btn")) {
                            if (line.substr(delimiterPos + 1) == "h0right")
                {
                pconfigJoy.BRight = SDL_HAT_RIGHT_NIN;
                haveHat = true;
                } else {
                pconfigJoy.BRight = stoi(line.substr(delimiterPos + 1));
                if (!validinput(pconfigJoy.BRight))
                    return false;
                }
            } else if (!name.compare("input_l_btn"))
            {
                pconfigJoy.BTl = stoi(line.substr(delimiterPos + 1));
                if (!validinput(pconfigJoy.BTl))
                    return false;
            } else if (!name.compare("input_r_btn"))
            {
                pconfigJoy.BTr = stoi(line.substr(delimiterPos + 1));
                if (!validinput(pconfigJoy.BTr))
                    return false;
            } else if (!name.compare("input_l2_btn"))
            {
                pconfigJoy.BTl1 = stoi(line.substr(delimiterPos + 1));
                if (!validinput(pconfigJoy.BTl1))
                    return false;
            } else if (!name.compare("input_r2_btn"))
            {
                pconfigJoy.BTr1 = stoi(line.substr(delimiterPos + 1));
                if (!validinput(pconfigJoy.BTr1))
                    return false;
            }
        }
        std::cout << "this joystick have hat: " << (haveHat ? "true":"false") << std::endl;
        return true;
    }
    else {
        std::cerr << "Couldn't open config file for reading.\n";
        return false;
    }
}
 
BOOST_AUTO_TEST_SUITE(interactconfigfile)
// invalid path
BOOST_AUTO_TEST_CASE (test1) 
{
    char const *file = ""; 
    PARAM_CONFIG pconfigJoy = {};
    BOOST_CHECK(GetConfig((char*)file, pconfigJoy) == false);
}
// invalid path
BOOST_AUTO_TEST_CASE (test2)
{
    char const *file = "thueifnsifu";
    PARAM_CONFIG pconfigJoy = {}; 
    BOOST_CHECK(GetConfig((char*)file, pconfigJoy) == false);
}
// test with a config file standard
BOOST_AUTO_TEST_CASE (test3)
{
    char const *file = "../../config/PS3Joystick.cfg";
    PARAM_CONFIG pconfigJoy = {};
    BOOST_CHECK(GetConfig((char*)file, pconfigJoy) == true);
}
// read config file with the lack of quotes
BOOST_AUTO_TEST_CASE (test4)
{
    char const *file = "../testcase/config_incomplet.cfg";
    PARAM_CONFIG pconfigJoy = {};
    pconfigJoy.BEast = 0;
    GetConfig((char*)file, pconfigJoy);
    BOOST_REQUIRE_EQUAL(pconfigJoy.BEast, 2);
}
// test a value invalid (> 16 ~ a joystick have 16 buttons max)
BOOST_AUTO_TEST_CASE (test5)
{
    char const *file = "../testcase/config_invalid_input.cfg";
    PARAM_CONFIG pconfigJoy = {};
    BOOST_CHECK(GetConfig((char*)file, pconfigJoy) == false);
}
// test reading well when update value in config file
BOOST_AUTO_TEST_CASE (test6)
{
    char const *file = "../testcase/config_change_value.cfg";
    PARAM_CONFIG pconfigJoy = {};
    GetConfig((char*)file, pconfigJoy);
    BOOST_REQUIRE_EQUAL(pconfigJoy.BStart, 12);
}
BOOST_AUTO_TEST_SUITE_END()