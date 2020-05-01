/**
 * @file resthttp.cpp
 * @author PHAM Minh Thuc
 * @date 7 april 2020
 * @brief File contain class and function to define the endpoint and provide a REST API for client.
 * This REST API give us services web to control arm ALD5 through browers for example.
 */
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "../includes/resthttp.hpp"
#include <vector>

using boost::property_tree::ptree;
using std::make_pair;
using std::vector;
using std::to_string;

namespace pt = boost::property_tree;

/**
 * @brief struct of a validate url, check end point and parameters received
*/
struct validate_data
{
    string endpoint;                /*!< end point */
    set <string>* params;           /*!< parameters corresponding to "type" */
};

RestHttp::RestHttp(){
    string wristparams[] = {"rotate", "move"};
    _apiparams["/wrist"] = set<string>(wristparams,wristparams+2);
}

bool RestHttp::ResponseRestRequest(const string& url, const map<string, string>& argval, 
                    string& response, ServerController& server)
{
    bool ret = false;
    if (url == "/initposition") {
        ret = _init_position_arm_rest(url, argval,response, server);
    } else if (url == "/shoulder") {
        ret = _control_shoulder_rest(url, argval, response , server);
    } else if (url == "/elbow") {
        ret = _control_elbow_rest(url, argval,response, server);
    } else if (url == "/base") {
        ret = _control_base_rest(url, argval,response, server);
    } else if (url == "/gripper") {
        ret = _control_gripper_rest(url, argval,response, server);
    } else if (url == "/wrist") {
        ret = _control_wrist_rest(url, argval,response, server);
    } else if (url == "/open") {
        ret = _open_arm_rest(url, argval,response, server);
    } else if(url == "/close") {
        ret = _close_arm_rest(url, argval,response, server);
    } else {
        ptree executeroot;
        ptree execute;
        ptree::iterator ptit = executeroot.push_back(make_pair("url", execute ));
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));
        ptit->second.push_back(make_pair("error",pt::ptree(string("can't recognize url"))));
        _generate_json_output(&executeroot,response);
        return false; 
    }
    return ret;
}

bool RestHttp::_open_arm_rest(const string& url, const map<string, string>& argval, string& response, ServerController& server)
{
    int ret;
    ptree openroot;
    ptree open;
    ptree::iterator ptit = openroot.push_back(make_pair("open", open ));
    if (!(ret = server.Open())) {
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));
        ptit->second.push_back(make_pair("error",pt::ptree(string("try with sudo to run server"))));          
        _generate_json_output(&openroot,response);
        return false;
    } else {
        ptit->second.push_back(make_pair("shoulder", pt::ptree(to_string(server.GetJoint(SHOULDER).actualPosition))));
        ptit->second.push_back(make_pair("elbow", pt::ptree(to_string(server.GetJoint(ELBOW).actualPosition))));
        ptit->second.push_back(make_pair("base", pt::ptree(to_string(server.GetJoint(BASE).actualPosition))));
        ptit->second.push_back(make_pair("gripper", pt::ptree(to_string(server.GetJoint(GRIPPER).actualPosition))));
        ptit->second.push_back(make_pair("wrist", pt::ptree(to_string(server.GetJoint(WRIST).actualPosition))));
        ptit->second.push_back(make_pair("wristrotation", pt::ptree(to_string(server.GetJoint(WRIST_ROT).actualPosition))));
        ptit->second.push_back(make_pair("status",pt::ptree(string("OK"))));
    }
    _generate_json_output(&openroot,response);
    return true;
}

bool RestHttp::_close_arm_rest(const string& url, const map<string, string>& argval, string& response, ServerController& server)
{
    int ret;
    ptree closeroot;
    ptree close;
    ptree::iterator ptit = closeroot.push_back(make_pair("close", close ));
    if (!(ret = server.Close())) {
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));
        _generate_json_output(&closeroot,response);
        return false;
    } else {
        ptit->second.push_back(make_pair("status",pt::ptree(string("OK"))));
    }
    _generate_json_output(&closeroot,response);
    return true;
}

bool RestHttp::_init_position_arm_rest(const string& url, const map<string, string>& argval, string& response, ServerController& server)
{
    int ret;
    ptree initroot;
    ptree init;
    ptree::iterator ptit = initroot.push_back(make_pair("initialisation", init ));
    if(!(ret = server.MoveToInitialPosition())) {
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));            
        _generate_json_output(&initroot,response);
        return false;
    } else {
        ptit->second.push_back(make_pair("shoulder", pt::ptree(to_string(server.GetJoint(SHOULDER).actualPosition))));
        ptit->second.push_back(make_pair("elbow", pt::ptree(to_string(server.GetJoint(ELBOW).actualPosition))));
        ptit->second.push_back(make_pair("base", pt::ptree(to_string(server.GetJoint(BASE).actualPosition))));
        ptit->second.push_back(make_pair("gripper", pt::ptree(to_string(server.GetJoint(GRIPPER).actualPosition))));
        ptit->second.push_back(make_pair("wrist", pt::ptree(to_string(server.GetJoint(WRIST).actualPosition))));
        ptit->second.push_back(make_pair("wristrotation", pt::ptree(to_string(server.GetJoint(WRIST_ROT).actualPosition))));
        ptit->second.push_back(make_pair("status",pt::ptree(string("OK"))));
    }
    _generate_json_output(&initroot,response);
    return true;
}

bool RestHttp::_control_shoulder_rest(const string& url, const map<string, string>& argval, string& response, ServerController& server)
{
    map<string, string>::const_iterator it;
    int ret;
    ptree shoulderroot;
    ptree shoulder;
    ptree::iterator ptit;

    ptit = shoulderroot.push_back(make_pair("shoulder", shoulder ));

    it = argval.find("direction");
    if (it == argval.end()) {
        ptit->second.push_back(make_pair("status",pt::ptree(string("OK"))));
        ptit->second.push_back(make_pair("error",pt::ptree(string("can not get direction parameters"))));            
        _generate_json_output(&shoulderroot,response);
        return false;
    } else if(strcmp(it->second.c_str(),"0") !=0 && strcmp(it->second.c_str(),"1") != 0) {
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));
        ptit->second.push_back(make_pair("error",pt::ptree(string("value of direction is wrong"))));            
        _generate_json_output(&shoulderroot,response);
        return false;
    }
    if (!(ret = server.MoveShoulder(atoi(it->second.c_str())))) {
        ptit->second.push_back(make_pair("positionCurrent", pt::ptree(to_string(server.GetJoint(SHOULDER).actualPosition))));
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));            
        _generate_json_output(&shoulderroot,response);
        return false;
    } else {
        ptit->second.push_back(make_pair("positionCurrent", pt::ptree(to_string(server.GetJoint(SHOULDER).actualPosition))));
        ptit->second.push_back(make_pair("positionInit",pt::ptree(to_string(server.GetJoint(SHOULDER).initPosition))));
        ptit->second.push_back(make_pair("hightLimit",pt::ptree(to_string(server.GetJoint(SHOULDER).limitHight))));
        ptit->second.push_back(make_pair("lowLimit",pt::ptree(to_string(server.GetJoint(SHOULDER).limitLow))));
        ptit->second.push_back(make_pair("status",pt::ptree(string("OK"))));
    }
    _generate_json_output(&shoulderroot,response);
    return true;
}

bool RestHttp::_control_elbow_rest(const string& url, const map<string, string>& argval, string& response, ServerController& server)
{
    map<string, string>::const_iterator it;
    int ret;
    ptree elbowroot;
    ptree elbow;
    ptree::iterator ptit;

    ptit = elbowroot.push_back(make_pair("elbow", elbow ));

    it = argval.find("direction");
    if (it == argval.end()) {
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));
        ptit->second.push_back(make_pair("error",pt::ptree(string("can not get direction parameters"))));            
        _generate_json_output(&elbowroot,response);
        return false;
    } else if (strcmp(it->second.c_str(),"0") !=0 && strcmp(it->second.c_str(),"1") != 0){
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));
        ptit->second.push_back(make_pair("error",pt::ptree(string("value of direction is wrong"))));            
        _generate_json_output(&elbowroot,response);
        return false;
    }

    ptit = elbowroot.push_back(make_pair("elbow", elbow ));
    if (!(ret = server.MoveElbow(atoi(it->second.c_str())))) {
        ptit->second.push_back(make_pair("positionCurrent", pt::ptree(to_string(server.GetJoint(ELBOW).actualPosition))));
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));            
        _generate_json_output(&elbowroot,response);
        return false;
    } else {
        ptit->second.push_back(make_pair("positionCurrent", pt::ptree(to_string(server.GetJoint(ELBOW).actualPosition))));
        ptit->second.push_back(make_pair("positionInit",pt::ptree(to_string(server.GetJoint(ELBOW).initPosition))));
        ptit->second.push_back(make_pair("hightLimit",pt::ptree(to_string(server.GetJoint(ELBOW).limitHight))));
        ptit->second.push_back(make_pair("lowLimit",pt::ptree(to_string(server.GetJoint(ELBOW).limitLow))));
        ptit->second.push_back(make_pair("status",pt::ptree(string("OK"))));
    }
    _generate_json_output(&elbowroot,response);
    return true;
}

bool RestHttp::_control_base_rest(const string& url, const map<string, string>& argval, string& response, ServerController& server)
{
    map<string, string>::const_iterator it;
    int ret;
    ptree baseroot;
    ptree base;
    ptree::iterator ptit;

    ptit = baseroot.push_back(make_pair("base", base ));

    it = argval.find("direction");
    if (it == argval.end()) {
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));
        ptit->second.push_back(make_pair("error",pt::ptree(string("can not get direction parameters"))));            
        _generate_json_output(&baseroot,response);
        return false;
    } else if (strcmp(it->second.c_str(),"0") !=0 && strcmp(it->second.c_str(),"1") != 0) {
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));
        ptit->second.push_back(make_pair("error",pt::ptree(string("value of direction is wrong"))));            
        _generate_json_output(&baseroot,response);
        return false;
    }

    if (!(ret = server.RotateBase(atoi(it->second.c_str())))) {
        ptit->second.push_back(make_pair("positionCurrent", pt::ptree(to_string(server.GetJoint(BASE).actualPosition))));
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));            
        _generate_json_output(&baseroot,response);
        return false;
    } else {
        ptit->second.push_back(make_pair("positionCurrent", pt::ptree(to_string(server.GetJoint(BASE).actualPosition))));
        ptit->second.push_back(make_pair("positionInit",pt::ptree(to_string(server.GetJoint(BASE).initPosition))));
        ptit->second.push_back(make_pair("hightLimit",pt::ptree(to_string(server.GetJoint(BASE).limitHight))));
        ptit->second.push_back(make_pair("lowLimit",pt::ptree(to_string(server.GetJoint(BASE).limitLow))));
        ptit->second.push_back(make_pair("status",pt::ptree(string("OK"))));
    }
    _generate_json_output(&baseroot,response);
    return true;
}

bool RestHttp::_control_gripper_rest(const string& url, const map<string, string>& argval, string& response, ServerController& server)
{
    map<string, string>::const_iterator it;
    ptree::iterator ptit;
    int ret;
    ptree gripperroot;
    ptree gripper;

    ptit = gripperroot.push_back(make_pair("gripper", gripper ));

    it = argval.find("direction");
    if (it == argval.end()) {
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));
        ptit->second.push_back(make_pair("error",pt::ptree(string("can not get direction parameters"))));            
        _generate_json_output(&gripperroot,response);
        return false;
    } else if(strcmp(it->second.c_str(),"0") !=0 && strcmp(it->second.c_str(),"1") != 0) {
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));
        ptit->second.push_back(make_pair("error",pt::ptree(string("value of direction is wrong"))));            
        _generate_json_output(&gripperroot,response);
        return false;
    }
    if (!(ret = server.MoveGripper(atoi(it->second.c_str())))) {
        ptit->second.push_back(make_pair("positionCurrent", pt::ptree(to_string(server.GetJoint(GRIPPER).actualPosition))));
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));            
        _generate_json_output(&gripperroot,response);
        return false;
    } else {
        ptit->second.push_back(make_pair("positionCurrent", pt::ptree(to_string(server.GetJoint(GRIPPER).actualPosition))));
        ptit->second.push_back(make_pair("positionInit",pt::ptree(to_string(server.GetJoint(GRIPPER).initPosition))));
        ptit->second.push_back(make_pair("hightLimit",pt::ptree(to_string(server.GetJoint(GRIPPER).limitHight))));
        ptit->second.push_back(make_pair("lowLimit",pt::ptree(to_string(server.GetJoint(GRIPPER).limitLow))));
        ptit->second.push_back(make_pair("status",pt::ptree(string("OK"))));
    }
    _generate_json_output(&gripperroot,response);
    return true;
}

bool RestHttp::_control_wrist_rest(const string& url, const map<string, string>& argval, string& response, ServerController& server)
{
    map<string, string>::const_iterator it;
    ptree::iterator ptit;
    int ret;
    ptree wristroot;
    ptree wrist;
    validate_data vdata;
    vdata.endpoint = url;
    set<string> params;

    map<string, string>::const_iterator it2 = argval.find("type");

    if (it2== argval.end()) {
        _get_invalid_response(response);
        return false;
    }
    params.insert(it2->second);
    vdata.params = &params;
    if (!_validate(&vdata)) {
        _get_invalid_response(response);
        return false;
    }

    if (it2->second == "move") {
        ptit = wristroot.push_back(make_pair("wrist", wrist ));
    } else {
        ptit = wristroot.push_back(make_pair("wristrotate", wrist ));
    }
    
    it = argval.find("direction");
    if (it == argval.end()) {
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));
        ptit->second.push_back(make_pair("error",pt::ptree(string("can not get direction parameters"))));            
        _generate_json_output(&wristroot,response);
        return false;
    } else if (strcmp(it->second.c_str(),"0") !=0 && strcmp(it->second.c_str(),"1") != 0) {
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));
        ptit->second.push_back(make_pair("error",pt::ptree(string("value of direction is wrong"))));            
        _generate_json_output(&wristroot,response);
        return false;
    }

    if (it2->second == "move") {   
        if (!(ret = server.MoveWrist(atoi(it->second.c_str())))) {
            ptit->second.push_back(make_pair("positionCurrent", pt::ptree(to_string(server.GetJoint(WRIST).actualPosition))));
            ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));            
            _generate_json_output(&wristroot,response);
            return false;
        } else {
            ptit->second.push_back(make_pair("positionCurrent", pt::ptree(to_string(server.GetJoint(WRIST).actualPosition))));
            ptit->second.push_back(make_pair("positionInit",pt::ptree(to_string(server.GetJoint(WRIST).initPosition))));
            ptit->second.push_back(make_pair("hightLimit",pt::ptree(to_string(server.GetJoint(WRIST).limitHight))));
            ptit->second.push_back(make_pair("lowLimit",pt::ptree(to_string(server.GetJoint(WRIST).limitLow))));
            ptit->second.push_back(make_pair("status",pt::ptree(string("OK"))));
        }
    }
    else if (it2->second == "rotate") {
        if (!(ret = server.RotateWrist(atoi(it->second.c_str())))) {
            ptit->second.push_back(make_pair("positionCurrent", pt::ptree(to_string(server.GetJoint(WRIST_ROT).actualPosition))));
            ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));            
            _generate_json_output(&wristroot,response);
            return false;
        } else {
            ptit->second.push_back(make_pair("positionCurrent", pt::ptree(to_string(server.GetJoint(WRIST_ROT).actualPosition))));
            ptit->second.push_back(make_pair("positionInit",pt::ptree(to_string(server.GetJoint(WRIST_ROT).initPosition))));
            ptit->second.push_back(make_pair("hightLimit",pt::ptree(to_string(server.GetJoint(WRIST_ROT).limitHight))));
            ptit->second.push_back(make_pair("lowLimit",pt::ptree(to_string(server.GetJoint(WRIST_ROT).limitLow))));
            ptit->second.push_back(make_pair("status",pt::ptree(string("OK"))));
        }
    }
    _generate_json_output(&wristroot,response);

    return true;
}

void RestHttp::_generate_json_output(void *data, string& output)
{
    std::ostringstream ostr;
    ptree *pt = (ptree *) data;
    write_json(ostr, *pt);

    output = ostr.str();
}

bool RestHttp::_validate(const void *data)
{
    const validate_data *vdata = static_cast<const validate_data *>(data);
    map<string, set<string>>::const_iterator it = _apiparams.find(vdata->endpoint);

    if (it == _apiparams.end())
        return false;
    set<string>::iterator it2 = vdata->params->begin();

    while(it2 != vdata->params->end())
    {
        if(it->second.find(*it2) == it->second.end())
            return false;
        it2++;
    }
    return true;
}

void RestHttp::_get_invalid_response(string &response)
{
    response = "Some error in your data";
}