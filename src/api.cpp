#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "../includes/api.hpp"
#include <vector>

using boost::property_tree::ptree;
using std::make_pair;
using std::vector;
using std::to_string;
using namespace myapi;

namespace pt = boost::property_tree;

struct validate_data
{
    string api;
    set <string>* params;
};

api::api(){
    string wristparams[] = {"rotate", "move"};

    _apiparams["/wrist"] = set<string>(wristparams,wristparams+2);
}

bool api::executeAPI(const string& url, const map<string, string>& argval, 
                    string& response, Server& server)
{
    bool ret = false;
    if(url == "/initposition")
    {
        ret = _initAPI(url, argval,response, server);
    }
    else if(url == "/shoulder")
    {
        ret = _shoulderAPI(url, argval, response , server);
    }
    else if(url == "/elbow")
    {
        ret = _elbowAPI(url, argval,response, server);
    }
    else if(url == "/base")
    {
        ret = _baseAPI(url, argval,response, server);
    }
    else if(url == "/gripper")
    {
        ret = _gripperAPI(url, argval,response, server);
    }
    else if(url == "/wrist")
    {
        ret = _wristAPI(url, argval,response, server);
    }
    else if(url == "/open")
    {
        ret = _openAPI(url, argval,response, server);
    }
    else if(url == "/close")
    {
        ret = _closeAPI(url, argval,response, server);
    }
    else
    {
        ptree executeroot;
        ptree execute;
        ptree::iterator ptit = executeroot.push_back(make_pair("url", execute ));
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));
        ptit->second.push_back(make_pair("error",pt::ptree(string("can't recognize url"))));
        _generateOutput(&executeroot,response);
        return false; 
    }
    
    return ret;
}

bool api::_openAPI(const string& url, const map<string, string>& argval, string& response, Server& server)
{
    int ret;
    ptree openroot;
    ptree open;
    ptree::iterator ptit = openroot.push_back(make_pair("open", open ));
    if(!(ret = server.Open()))
    {
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));
        ptit->second.push_back(make_pair("error",pt::ptree(string("try with sudo to run server"))));          
        _generateOutput(&openroot,response);
        return false;
    }
    else
    {
        ptit->second.push_back(make_pair("status",pt::ptree(string("OK"))));
    }
    _generateOutput(&openroot,response);
    return true;
}

bool api::_closeAPI(const string& url, const map<string, string>& argval, string& response, Server& server)
{
    int ret;
    ptree closeroot;
    ptree close;
    ptree::iterator ptit = closeroot.push_back(make_pair("open", close ));
    if(!(ret = server.Close()))
    {
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));
        _generateOutput(&closeroot,response);
        return false;
    }
    else
    {
        ptit->second.push_back(make_pair("status",pt::ptree(string("OK"))));
    }
    _generateOutput(&closeroot,response);
    return true;
}

bool api::_initAPI(const string& url, const map<string, string>& argval, string& response, Server& server)
{
    int ret;
    ptree initroot;
    ptree init;
    ptree::iterator ptit = initroot.push_back(make_pair("initialisation", init ));
    if(!(ret = server.MoveToInitialPosition()))
    {
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));            
        _generateOutput(&initroot,response);
        return false;
    }
    else
    {
        ptit->second.push_back(make_pair("shoulder", pt::ptree(to_string(server.getjoint(SHOULDER).actualPosition))));
        ptit->second.push_back(make_pair("elbow", pt::ptree(to_string(server.getjoint(ELBOW).actualPosition))));
        ptit->second.push_back(make_pair("base", pt::ptree(to_string(server.getjoint(BASE).actualPosition))));
        ptit->second.push_back(make_pair("gripper", pt::ptree(to_string(server.getjoint(GRIPPER).actualPosition))));
        ptit->second.push_back(make_pair("wrist", pt::ptree(to_string(server.getjoint(WRIST).actualPosition))));
        ptit->second.push_back(make_pair("wrist rotation", pt::ptree(to_string(server.getjoint(WRIST_ROT).actualPosition))));
        ptit->second.push_back(make_pair("status",pt::ptree(string("OK"))));
    }
    _generateOutput(&initroot,response);
    return true;
}

bool api::_shoulderAPI(const string& url, const map<string, string>& argval, string& response, Server& server)
{
    map<string, string>::const_iterator it;
    int ret;
    ptree shoulderroot;
    ptree shoulder;
    ptree::iterator ptit;

    ptit = shoulderroot.push_back(make_pair("shoulder", shoulder ));

    it = argval.find("direction");
    if( it == argval.end())
    {
        ptit->second.push_back(make_pair("status",pt::ptree(string("OK"))));
        ptit->second.push_back(make_pair("error",pt::ptree(string("can not get direction parameters"))));            
        _generateOutput(&shoulderroot,response);
        return false;
    }
    else if(strcmp(it->second.c_str(),"0") !=0 && strcmp(it->second.c_str(),"1") != 0)
    {
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));
        ptit->second.push_back(make_pair("error",pt::ptree(string("value of direction is wrong"))));            
        _generateOutput(&shoulderroot,response);
        return false;
    }
    if(!(ret = server.MoveShoulder(atoi(it->second.c_str()))))
    {
        ptit->second.push_back(make_pair("positionCurrent", pt::ptree(to_string(server.getjoint(SHOULDER).actualPosition))));
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));            
        _generateOutput(&shoulderroot,response);
        return false;
    }
    else
    {
        ptit->second.push_back(make_pair("positionCurrent", pt::ptree(to_string(server.getjoint(SHOULDER).actualPosition))));
        ptit->second.push_back(make_pair("positionInit",pt::ptree(to_string(server.getjoint(SHOULDER).initPosition))));
        ptit->second.push_back(make_pair("hightLimit",pt::ptree(to_string(server.getjoint(SHOULDER).limitHight))));
        ptit->second.push_back(make_pair("lowLimit",pt::ptree(to_string(server.getjoint(SHOULDER).limitLow))));
        ptit->second.push_back(make_pair("status",pt::ptree(string("OK"))));
    }
    _generateOutput(&shoulderroot,response);
    return true;
}

bool api::_elbowAPI(const string& url, const map<string, string>& argval, string& response, Server& server)
{
    map<string, string>::const_iterator it;
    int ret;
    ptree elbowroot;
    ptree elbow;
    ptree::iterator ptit;

    ptit = elbowroot.push_back(make_pair("elbow", elbow ));

    it = argval.find("direction");
    if( it == argval.end())
    {
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));
        ptit->second.push_back(make_pair("error",pt::ptree(string("can not get direction parameters"))));            
        _generateOutput(&elbowroot,response);
        return false;
    }
    else if(strcmp(it->second.c_str(),"0") !=0 && strcmp(it->second.c_str(),"1") != 0)
    {
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));
        ptit->second.push_back(make_pair("error",pt::ptree(string("value of direction is wrong"))));            
        _generateOutput(&elbowroot,response);
        return false;
    }

    ptit = elbowroot.push_back(make_pair("elbow", elbow ));
    if(!(ret = server.MoveElbow(atoi(it->second.c_str()))))
    {
        ptit->second.push_back(make_pair("positionCurrent", pt::ptree(to_string(server.getjoint(ELBOW).actualPosition))));
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));            
        _generateOutput(&elbowroot,response);
        return false;
    }
    else
    {
        ptit->second.push_back(make_pair("positionCurrent", pt::ptree(to_string(server.getjoint(ELBOW).actualPosition))));
        ptit->second.push_back(make_pair("positionInit",pt::ptree(to_string(server.getjoint(ELBOW).initPosition))));
        ptit->second.push_back(make_pair("hightLimit",pt::ptree(to_string(server.getjoint(ELBOW).limitHight))));
        ptit->second.push_back(make_pair("lowLimit",pt::ptree(to_string(server.getjoint(ELBOW).limitLow))));
        ptit->second.push_back(make_pair("status",pt::ptree(string("OK"))));
    }
    _generateOutput(&elbowroot,response);
    return true;
}

bool api::_baseAPI(const string& url, const map<string, string>& argval, string& response, Server& server)
{
    map<string, string>::const_iterator it;
    int ret;
    ptree baseroot;
    ptree base;
    ptree::iterator ptit;

    ptit = baseroot.push_back(make_pair("base", base ));

    it = argval.find("direction");
    if( it == argval.end())
    {
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));
        ptit->second.push_back(make_pair("error",pt::ptree(string("can not get direction parameters"))));            
        _generateOutput(&baseroot,response);
        return false;
    }
    else if(strcmp(it->second.c_str(),"0") !=0 && strcmp(it->second.c_str(),"1") != 0)
    {
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));
        ptit->second.push_back(make_pair("error",pt::ptree(string("value of direction is wrong"))));            
        _generateOutput(&baseroot,response);
        return false;
    }

    if(!(ret = server.RotateBase(atoi(it->second.c_str()))))
    {
        ptit->second.push_back(make_pair("positionCurrent", pt::ptree(to_string(server.getjoint(BASE).actualPosition))));
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));            
        _generateOutput(&baseroot,response);
        return false;
    }
    else
    {
        ptit->second.push_back(make_pair("positionCurrent", pt::ptree(to_string(server.getjoint(BASE).actualPosition))));
        ptit->second.push_back(make_pair("positionInit",pt::ptree(to_string(server.getjoint(BASE).initPosition))));
        ptit->second.push_back(make_pair("hightLimit",pt::ptree(to_string(server.getjoint(BASE).limitHight))));
        ptit->second.push_back(make_pair("lowLimit",pt::ptree(to_string(server.getjoint(BASE).limitLow))));
        ptit->second.push_back(make_pair("status",pt::ptree(string("OK"))));
    }
    _generateOutput(&baseroot,response);
    return true;
}

bool api::_gripperAPI(const string& url, const map<string, string>& argval, string& response, Server& server)
{
    map<string, string>::const_iterator it;
    ptree::iterator ptit;
    int ret;
    ptree gripperroot;
    ptree gripper;

    ptit = gripperroot.push_back(make_pair("gripper", gripper ));

    it = argval.find("direction");
    if( it == argval.end())
    {
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));
        ptit->second.push_back(make_pair("error",pt::ptree(string("can not get direction parameters"))));            
        _generateOutput(&gripperroot,response);
        return false;
    }
    else if(strcmp(it->second.c_str(),"0") !=0 && strcmp(it->second.c_str(),"1") != 0)
    {
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));
        ptit->second.push_back(make_pair("error",pt::ptree(string("value of direction is wrong"))));            
        _generateOutput(&gripperroot,response);
        return false;
    }

    if(!(ret = server.MoveGripper(atoi(it->second.c_str()))))
    {
        ptit->second.push_back(make_pair("positionCurrent", pt::ptree(to_string(server.getjoint(GRIPPER).actualPosition))));
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));            
        _generateOutput(&gripperroot,response);
        return false;
    }
    else
    {
        ptit->second.push_back(make_pair("positionCurrent", pt::ptree(to_string(server.getjoint(GRIPPER).actualPosition))));
        ptit->second.push_back(make_pair("positionInit",pt::ptree(to_string(server.getjoint(GRIPPER).initPosition))));
        ptit->second.push_back(make_pair("hightLimit",pt::ptree(to_string(server.getjoint(GRIPPER).limitHight))));
        ptit->second.push_back(make_pair("lowLimit",pt::ptree(to_string(server.getjoint(GRIPPER).limitLow))));
        ptit->second.push_back(make_pair("status",pt::ptree(string("OK"))));
    }
    _generateOutput(&gripperroot,response);
    return true;
}

bool api::_wristAPI(const string& url, const map<string, string>& argval, string& response, Server& server)
{
    map<string, string>::const_iterator it;
    ptree::iterator ptit;
    int ret;
    ptree wristroot;
    ptree wrist;
    validate_data vdata;
    vdata.api = url;
    set<string> params;

    ptit = wristroot.push_back(make_pair("wristMove", wrist ));

    it = argval.find("direction");
    if( it == argval.end())
    {
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));
        ptit->second.push_back(make_pair("error",pt::ptree(string("can not get direction parameters"))));            
        _generateOutput(&wristroot,response);
        return false;
    }
    else if(strcmp(it->second.c_str(),"0") !=0 && strcmp(it->second.c_str(),"1") != 0)
    {
        ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));
        ptit->second.push_back(make_pair("error",pt::ptree(string("value of direction is wrong"))));            
        _generateOutput(&wristroot,response);
        return false;
    }

    map<string, string>::const_iterator it2 = argval.find("type");

    if(it2== argval.end())
    {
        _getInvalidResponse(response);
        return false;
    }
    params.insert(it2->second);
    vdata.params = &params;
    if(!_validate(&vdata))
    {
        _getInvalidResponse(response);
        return false;
    }

    if(it2->second == "move")
    {
        if(!(ret = server.MoveWrist(atoi(it->second.c_str()))))
        {
            ptit->second.push_back(make_pair("positionCurrent", pt::ptree(to_string(server.getjoint(WRIST).actualPosition))));
            ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));            
            _generateOutput(&wristroot,response);
            return false;
        }
        else
        {
            ptit->second.push_back(make_pair("positionCurrent", pt::ptree(to_string(server.getjoint(WRIST).actualPosition))));
            ptit->second.push_back(make_pair("positionInit",pt::ptree(to_string(server.getjoint(WRIST).initPosition))));
            ptit->second.push_back(make_pair("hightLimit",pt::ptree(to_string(server.getjoint(WRIST).limitHight))));
            ptit->second.push_back(make_pair("lowLimit",pt::ptree(to_string(server.getjoint(WRIST).limitLow))));
            ptit->second.push_back(make_pair("status",pt::ptree(string("OK"))));
        }
        _generateOutput(&wristroot,response);
    }
    if(it2->second == "rotate")
    {
        if(!(ret = server.RotateWrist(atoi(it->second.c_str()))))
        {
            ptit->second.push_back(make_pair("positionCurrent", pt::ptree(to_string(server.getjoint(WRIST_ROT).actualPosition))));
            ptit->second.push_back(make_pair("status",pt::ptree(string("Failed"))));            
            _generateOutput(&wristroot,response);
            return false;
        }
        else
        {
            ptit->second.push_back(make_pair("positionCurrent", pt::ptree(to_string(server.getjoint(WRIST_ROT).actualPosition))));
            ptit->second.push_back(make_pair("positionInit",pt::ptree(to_string(server.getjoint(WRIST_ROT).initPosition))));
            ptit->second.push_back(make_pair("hightLimit",pt::ptree(to_string(server.getjoint(WRIST_ROT).limitHight))));
            ptit->second.push_back(make_pair("lowLimit",pt::ptree(to_string(server.getjoint(WRIST_ROT).limitLow))));
            ptit->second.push_back(make_pair("status",pt::ptree(string("OK"))));
        }
        _generateOutput(&wristroot,response);
    }
    return true;
}

void api::_generateOutput(void *data, string& output)
{
    std::ostringstream ostr;
    ptree *pt = (ptree *) data;
    write_json(ostr, *pt);

    output = ostr.str();
}

bool api::_validate(const void *data)
{
    const validate_data *vdata = static_cast<const validate_data *>(data);
    map<string, set<string>>::const_iterator it = _apiparams.find(vdata->api);

    if(it == _apiparams.end())
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

void api::_getInvalidResponse(string &response)
{
    response = "Some error in your data";
}