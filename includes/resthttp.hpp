/**
 * @file resthttp.hpp
 * @author PHAM Minh Thuc
 * @date 7 april 2020
 * @brief File contain class and function to define the endpoint and provide a REST API for client.
 * This REST API give us services web to control arm ALD5 through browers for example.
 */
#ifndef __REST_HTTP__
#define __REST_HTTP__

#include <map>
#include <string>
#include <set>
#include "servercontroller.hpp"
#include "armAL5D.hpp"
using std::map;
using std::string;
using std::set;

/**
 * @brief RestHttp class for rest api
*/
class RestHttp
{
public:
    /** 
     * @brief constructor 
     * Constructor of class RestHttp
    */
    RestHttp();

    /** 
     * @brief This method to analyze url and call api correspondent 
     * @param   url : endpoint
     * @param   argval : key-value of parameters in url
     * @param   response : response returned to client
     * @param   server : server
     */
    bool ResponseRestRequest(const string& url, const map<string, string>& argval, 
                    string& response, ServerController& server);
private:
    /** 
     * @brief This method to open connection between local machine with robotic arm 
     * @param  url : endpoint
     * @param  argval : key-value of parameters in url
     * @param  response : response returned to client
     * @param  server : server
     */
    bool _open_arm_rest(const string& url, const map<string, string>& argval, string& response, ServerController& server);

    /** 
     * @brief This method to call api close connection
     * @sa _open_arm_rest
     */
    bool _close_arm_rest(const string& url, const map<string, string>& argval, string& response, ServerController& server);

    /** 
     * @brief This method to call api initialize la position of robotic arm
     * @sa _open_arm_rest
     */
    bool _init_position_arm_rest(const string& url, const map<string, string>& argval, string& response, ServerController& server);

    /** 
     * @brief This method to call api control the shoulder
     * @sa _open_arm_rest
     */
    bool _control_shoulder_rest(const string& url, const map<string, string>& argval, string& response, ServerController& server);

    /** 
     * @brief This method to call api control elbow
     * @sa _open_arm_rest
     */
    bool _control_elbow_rest(const string& url, const map<string, string>& argval, string& response, ServerController& server);

    /** 
     * @brief This method to call api control the base
     * @sa _open_arm_rest
     */
    bool _control_base_rest(const string& url, const map<string, string>& argval, string& response, ServerController& server);
        
    /** 
     * @brief This method to call api control the gripper
     * @sa _open_arm_rest
     */
    bool _control_gripper_rest(const string& url, const map<string, string>& argval, string& response, ServerController& server);
    
    /** 
     * @brief This method to call api control wrist
     * @sa _open_arm_rest
     */
    bool _control_wrist_rest(const string& url, const map<string, string>& argval, string& response, ServerController& server);
    
    /** 
     * @brief This method to convert pair key-value to string format json
     * @param data response type ptree
     * @param output string format json
     */
    void _generate_json_output(void *data, string& output);

    /** 
     * @brief This method to verify type of motion in case wrist
     * @param data endpoint and parameter recieved 
     */
    bool _validate(const void *data);

    /** 
     * @brief This method to get invalid response on endpoint
     * @param response bad response 
     */
    void _get_invalid_response(string &response);
    map<string, set<string> > _apiparams;               /*!< map : end point of web service and parameter */
};

#endif