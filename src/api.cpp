#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "../includes/api.hpp"
#include <vector>

using boost::property_tree::ptree;
using std::make_pair;
using boost::lexical_cast;
using boost::bad_lexical_cast;
using boost::format;
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
}

bool api::executeAPI(const string& url, const map<string, string>& argval, 
                    string& response, Server& server, const string& direction)
{
    bool ret = false;
    if(url == "/shoulder")
    {
        LOG_I("Catch shoulder");
        ret = _shoulderAPI(response , server, direction);
    }
    if(url == "/elbow")
    {
        ret = _elbowAPI(response, server, direction);
    }
    return ret;
}

bool api::_shoulderAPI(string& response, Server& server, const string& direction)
{
    int ret;
    ptree shoulderroot;
    ptree shoulder;
    string::const_iterator start,end;
    ptree::iterator ptit = shoulderroot.push_back(make_pair("shoulder", shoulder ));
    if(!(ret = server.MoveShoulder(atoi(direction.c_str()))))
    {
        return EXIT_FAILURE;
    }
    else
    {
        ptit->second.push_back(make_pair("positionCurruent", pt::ptree(to_string(server.getjoint(SHOULDER).actualPosition))));
        ptit->second.push_back(make_pair("positionInit",pt::ptree(to_string(server.getjoint(SHOULDER).initPosition))));
        ptit->second.push_back(make_pair("hightLimit",pt::ptree(to_string(server.getjoint(SHOULDER).limitHight))));
        ptit->second.push_back(make_pair("lowLimit",pt::ptree(to_string(server.getjoint(SHOULDER).limitLow))));
        ptit->second.push_back(make_pair("status",pt::ptree(string("OK"))));
    }
    _generateOutput(&shoulderroot,response);
    return true;
}

bool api::_elbowAPI(string& response, Server& server, const string& direction)
{
    int ret;
    ptree elbowroot;
    ptree elbow;
    string::const_iterator start,end;
    ptree::iterator ptit = elbowroot.push_back(make_pair("elbow", elbow ));
    if(!(ret = server.MoveElbow(atoi(direction.c_str()))))
    {
        return EXIT_FAILURE;
    }
    else
    {
        ptit->second.push_back(make_pair("positionCurruent", pt::ptree(to_string(server.getjoint(ELBOW).actualPosition))));
        ptit->second.push_back(make_pair("positionInit",pt::ptree(to_string(server.getjoint(ELBOW).initPosition))));
        ptit->second.push_back(make_pair("hightLimit",pt::ptree(to_string(server.getjoint(ELBOW).limitHight))));
        ptit->second.push_back(make_pair("lowLimit",pt::ptree(to_string(server.getjoint(ELBOW).limitLow))));
        ptit->second.push_back(make_pair("status",pt::ptree(string("OK"))));
    }
    _generateOutput(&elbowroot,response);
    return true;
}

void api::_generateOutput(void *data, string& output)
{
    std::ostringstream ostr;
    ptree *pt = (ptree *) data;
    write_json(ostr, *pt);

    output = ostr.str();
}