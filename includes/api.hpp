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
    api();
    bool executeAPI(const string& url, const map<string, string>& argval, 
                    string& response, Server& server, const string& direction);
private:
    bool _shoulderAPI(string& response, Server& server, const string& direction);
    bool _elbowAPI(string& response, Server& server, const string& direction);
    void _getInvalidResponse(string& response, Server& server);
    void _generateOutput(void *data, string& output);

    map<string, set<string> > _apiparams;
};
}

#endif