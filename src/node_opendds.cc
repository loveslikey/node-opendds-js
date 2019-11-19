//#include "NodeDRListener.h"
//#include "NodeQosConversion.h"

#include "node_opendds.h"

#include <dds/DCPS/Service_Participant.h>
#include <dds/DCPS/Registered_Data_Types.h>
#include <dds/DCPS/Marked_Default_Qos.h>
#include <dds/DCPS/V8TypeConverter.h>

#include <ace/DLL_Manager.h>
#include <ace/Init_ACE.h>

#include <assert.h>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>

#define DECLARE_NAPI_METHOD(name, func)         \
    {                                           \
        name, 0, func, 0, 0, 0, napi_default, 0 \
    }
#define NAPI_CALL(env, call)                                              \
    do                                                                    \
    {                                                                     \
        napi_status status = (call);                                      \
        if (status != napi_ok)                                            \
        {                                                                 \
            const napi_extended_error_info *error_info = NULL;            \
            napi_get_last_error_info((env), &error_info);                 \
            bool is_pending;                                              \
            napi_is_exception_pending((env), &is_pending);                \
            if (!is_pending)                                              \
            {                                                             \
                const char *message = (error_info->error_message == NULL) \
                                          ? "empty error message"         \
                                          : error_info->error_message;    \
                napi_throw_error((env), NULL, message);                   \
                return NULL;                                              \
            }                                                             \
        }                                                                 \
    } while (0)

using OpenDDS::DCPS::Data_Types_Register;
//using NodeOpenDDS::NodeDRListener;
//using NodeOpenDDS::convertQos;

napi_ref constructor;

OpenDDSJS::OpenDDSJS() : cft_name("CFT000001") {

}

void OpenDDSJS::increment(std::string &name)
{
    const size_t i = cft_name.find_first_not_of('0', 3);
    if (name[i] == '9')
    {
        if (i == 3)
        {
            name = "CFT000001";
        }
        else
        {
            name[i] = '0';
            name[i - 1] = '1';
        }
    }
    else
    {
        ++name[i];
    }
}

napi_value OpenDDSJS::initialize(napi_env env, napi_callback_info info)
{
    ACE::init();
    napi_status status;
    napi_deferred deferred;
    napi_value promise;
    napi_value target;
    status = napi_get_new_target(env, info, &target);
    assert(status == napi_ok);
    bool is_constructor = target != nullptr;

    if (is_constructor) {
        // Invoked as constructor
        size_t argc = 1;
        napi_value args[1];
        napi_value jsthis;
        status = napi_get_cb_info(env, info, &argc, args, &jsthis, nullptr);
        assert(status == napi_ok);
    } else {
        // Invoked as plain function

    }
}

napi_value OpenDDSJS::create_participant(napi_env env, napi_callback_info info)
{
}

napi_value OpenDDSJS::delete_participant(napi_env env, napi_callback_info info)
{
}

napi_value OpenDDSJS::subscribe(napi_env env, napi_callback_info info)
{
}

napi_value OpenDDSJS::unsubscribe(napi_env env, napi_callback_info info)
{
}

napi_value OpenDDSJS::create_datawriter(napi_env env, napi_callback_info info)
{
}

napi_value OpenDDSJS::register_instance(napi_env env, napi_callback_info info)
{
}

napi_value OpenDDSJS::write(napi_env env, napi_callback_info info)
{
}

napi_value OpenDDSJS::unregister_instance(napi_env env, napi_callback_info info)
{
}

napi_value OpenDDSJS::dispose(napi_env env, napi_callback_info info)
{
}

napi_value init_opendds(napi_env env, napi_value exports)
{
    napi_status status;
    napi_property_descriptor properties[] = {
        DECLARE_NAPI_METHOD("create_participant", OpenDDSJS::create_participant),
        DECLARE_NAPI_METHOD("delete_participant", OpenDDSJS::delete_participant),
    };

    napi_value cons;
    status =
      napi_define_class(env, "factory", NAPI_AUTO_LENGTH, OpenDDSJS::initialize, nullptr, 1, properties, &cons);
    assert(status == napi_ok);

    status = napi_create_reference(env, cons, 1, &constructor);
    assert(status == napi_ok);
    
    status = napi_set_named_property(env, exports, "factory", cons);
    assert(status == napi_ok);
    
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init_opendds)
