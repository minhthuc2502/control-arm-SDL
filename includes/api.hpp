#ifndef __API_FOR_REST__
#define __API_FOR_REST__

#include <map>
#include <string>
#include <set>
#include "Server.hpp"
#include "ArmAL5D.hpp"
using std::map;
using std::string;
using std::set;

namespace myapi
{

class api
{
public:

    /** @brief This method allow to declare variable api
    * @param none
    */
    api();

    /** @brief This method to analyze url and call api correspondent 
     * @param:  const string& url : endpoint
     *          const map<string, string>& argval : key-value of parameters in url
     *          string& response : response returned to client
     *          Server& server : server
     */
    bool executeAPI(const string& url, const map<string, string>& argval, 
                    string& response, Server& server);
private:
    /** @brief This method to open connection between local machine with robotic arm 
     * @param:  const string& url : endpoint
     *          const map<string, string>& argval : key-value of parameters in url
     *          string& response : response returned to client
     *          Server& server : server
     */
    bool _openAPI(const string& url, const map<string, string>& argval, string& response, Server& server);

    /** @brief This method to call api close connection
     * @param:  as above
     */
    bool _closeAPI(const string& url, const map<string, string>& argval, string& response, Server& server);

    /** @brief This method to call api initialize la position of robotic arm
     * @param:  as above
     */
    bool _initAPI(const string& url, const map<string, string>& argval, string& response, Server& server);

    /** @brief This method to call api control the shoulder
     * @param:  as above
     */
    bool _shoulderAPI(const string& url, const map<string, string>& argval, string& response, Server& server);

    /** @brief This method to call api control elbow
     * @param:  as above
     */
    bool _elbowAPI(const string& url, const map<string, string>& argval, string& response, Server& server);

    /** @brief This method to call api control the base
     * @param:  as above
     */
    bool _baseAPI(const string& url, const map<string, string>& argval, string& response, Server& server);
        
    /** @brief This method to call api control the gripper
     * @param:  as above
     */
    bool _gripperAPI(const string& url, const map<string, string>& argval, string& response, Server& server);
    
    /** @brief This method to call api control wrist
     * @param:  as above
     */
    bool _wristAPI(const string& url, const map<string, string>& argval, string& response, Server& server);
    
    /** @brief This method to convert pair key-value to string format json
     * @param:  data : response type ptree
     *          output: string format json
     */
    void _generateOutput(void *data, string& output);

    /** @brief This method to verify type of motion in case wrist
     * @param:  data : endpoint and parameter recieved 
     */
    bool _validate(const void *data);

    
    void _getInvalidResponse(string &response);
    map<string, set<string> > _apiparams;
};
}

#endif