#ifndef __API_FOR_REST__
#define __API_FOR_REST__

#include <map>
#include <string>
#include <set>
#include "servercontroller.hpp"
#include "ArmAL5D.hpp"
using std::map;
using std::string;
using std::set;

class RestHttp
{
public:

    /** @brief This method allow to declare variable api
    * @param none
    */
    RestHttp();

    /** @brief This method to analyze url and call api correspondent 
     * @param:  const string& url : endpoint
     *          const map<string, string>& argval : key-value of parameters in url
     *          string& response : response returned to client
     *          Server& server : server
     */
    bool response_rest_request(const string& url, const map<string, string>& argval, 
                    string& response, ServerController& server);
private:
    /** @brief This method to open connection between local machine with robotic arm 
     * @param:  const string& url : endpoint
     *          const map<string, string>& argval : key-value of parameters in url
     *          string& response : response returned to client
     *          Server& server : server
     */
    bool _open_arm_rest(const string& url, const map<string, string>& argval, string& response, ServerController& server);

    /** @brief This method to call api close connection
     * @param:  as above
     */
    bool _close_arm_rest(const string& url, const map<string, string>& argval, string& response, ServerController& server);

    /** @brief This method to call api initialize la position of robotic arm
     * @param:  as above
     */
    bool _init_position_arm_rest(const string& url, const map<string, string>& argval, string& response, ServerController& server);

    /** @brief This method to call api control the shoulder
     * @param:  as above
     */
    bool _control_shoulder_rest(const string& url, const map<string, string>& argval, string& response, ServerController& server);

    /** @brief This method to call api control elbow
     * @param:  as above
     */
    bool _control_elbow_rest(const string& url, const map<string, string>& argval, string& response, ServerController& server);

    /** @brief This method to call api control the base
     * @param:  as above
     */
    bool _control_base_rest(const string& url, const map<string, string>& argval, string& response, ServerController& server);
        
    /** @brief This method to call api control the gripper
     * @param:  as above
     */
    bool _control_gripper_rest(const string& url, const map<string, string>& argval, string& response, ServerController& server);
    
    /** @brief This method to call api control wrist
     * @param:  as above
     */
    bool _control_wrist_rest(const string& url, const map<string, string>& argval, string& response, ServerController& server);
    
    /** @brief This method to convert pair key-value to string format json
     * @param:  data : response type ptree
     *          output: string format json
     */
    void _generate_json_output(void *data, string& output);

    /** @brief This method to verify type of motion in case wrist
     * @param:  data : endpoint and parameter recieved 
     */
    bool _validate(const void *data);

    
    void _get_invalid_response(string &response);
    map<string, set<string> > _apiparams;
};

#endif