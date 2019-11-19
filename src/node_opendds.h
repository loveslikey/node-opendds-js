#ifndef NODE_OPENDDS_H
#define NODE_OPENDDS_H

#include <dds/DCPS/Service_Participant.h>
#include <dds/DCPS/V8TypeConverter.h>

#include <iostream>

#include <node_api.h>

class OpenDDSJS
{
private:
    std::vector<DDS::DomainParticipant_var> participants_;
    std::string cft_name;
    void increment(std::string &name);
    OpenDDSJS();
    ~OpenDDSJS();

public:
    static napi_ref constructor;
    napi_env env_;
    napi_ref wrapper_;
    static napi_value initialize(napi_env env, napi_callback_info info);
    static napi_value create_participant(napi_env env, napi_callback_info info);
    static napi_value delete_participant(napi_env env, napi_callback_info info);
    static napi_value subscribe(napi_env env, napi_callback_info info);
    static napi_value unsubscribe(napi_env env, napi_callback_info info);
    static napi_value create_datawriter(napi_env env, napi_callback_info info);
    static napi_value register_instance(napi_env env, napi_callback_info info);
    static napi_value write(napi_env env, napi_callback_info info);
    static napi_value unregister_instance(napi_env env, napi_callback_info info);
    static napi_value dispose(napi_env env, napi_callback_info info);
    static napi_value create_addon(napi_env env);
};

napi_value init_opendds(napi_env env, napi_value exports);

#endif