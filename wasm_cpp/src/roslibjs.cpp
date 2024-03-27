#include "wasm_cpp/roslibjs.hpp"
#include "rcutils/logging_macros.h"
#include "wasm_cpp/tojson/tojson.hpp"

#include <map>
#include <emscripten/bind.h>

// EM_JS(emscripten::EM_VAL, wasmcpp_roslib_init, (), {
//     console.log('entered wasmcpp_roslib_init');
//     const ros = new ROSLIB.Ros();
//     ros.on('error', function(error) { console.error( error ); });
//     ros.on('connection', function() { console.log('Connection made!'); });
//     return Emval.toHandle(ros);
// });
// 
// EM_JS(void, wasmcpp_roslib_connect, (emscripten::EM_VAL ros_handle, const char * url), {
//     console.log('enetered wasmcpp_roslib_connect');
//     const ros = Emval.fromHandle(ros_handle);
// 
//     ros.connect(url);
// });

namespace wasm_cpp
{

namespace detail {
    template<typename... Args> emscripten::val call(const char * name, Args&&... args) {
        auto func = emscripten::val::module_property(name);
        if (!func) {
            RCUTILS_LOG_ERROR_NAMED("wasm_cpp", "%s is null", name);
            return emscripten::val::null();
        }

        return func(std::forward<Args>(args)...);
    }

    // Hacky workaround for calling std::function from JS.
    // Can't find a good example of how to do this and looks liek it will be a pain.
    // Just store them here and pass an int handle instead.
    static int s_nextCBHandle = 0;
    static std::map<int, int> s_subToCb;
    static std::map<int, std::function<void(const std::string &)>> s_callbacks;

    static void invoke_callback(int handle, const std::string & msg)
    {
        std::string yml = tojson::emitters::toyaml(nlohmann::json::parse(msg));

        auto it = s_callbacks.find(handle);

        if (it != s_callbacks.end())
            it->second(yml);
    }

    EMSCRIPTEN_BINDINGS(wasm_cpp) {
        emscripten::function("wasmcpp_invoke_subscriber_callback", &invoke_callback);
    }
}

RosLibJS::RosLibJS()
{
    detail::call("wasmcpp_roslib_init");
}

RosLibJS::~RosLibJS()
{
    detail::call("wasmcpp_roslib_shutdown");
}

void RosLibJS::connect(const std::string & url)
{
    detail::call("wasmcpp_roslib_connect", url);
}

void RosLibJS::disconnect() {}

int RosLibJS::create_subscriber(
    const std::string & topic,
    const std::string & msg_type,
    const std::function<void(const std::string &)> & onMessage)
{
    int cbHandle = detail::s_nextCBHandle++;
    detail::s_callbacks[cbHandle] = onMessage;
    emscripten::val cb = emscripten::val::module_property("wasmcpp_invoke_subscriber_callback");

    emscripten::val result = detail::call(
        "wasmcpp_roslib_create_subscriber",
        topic,
        msg_type,
        cb,
        cbHandle
    );

    int id = result.as<int>();

    detail::s_subToCb[id] = cbHandle;

    return id;
}

bool RosLibJS::destroy_subscriber(int subscriber_id)
{
    auto it = detail::s_subToCb.find(subscriber_id);
    if (it != detail::s_subToCb.end())
    {
        detail::s_callbacks.erase(it->second);
        detail::s_subToCb.erase(it);
    }

    return detail::call("wasmcpp_roslib_destroy_subscriber", subscriber_id).as<bool>();
}

int RosLibJS::create_publisher(const std::string & topic, const std::string & msg_type)
{
    return detail::call("wasmcpp_roslib_create_publisher", topic, msg_type).as<int>();
}

bool RosLibJS::publish(int publisher, const std::string & yamlMessage)
{
    const std::string jsonMessage = tojson::yaml2json(yamlMessage).dump();

    return detail::call("wasmcpp_roslib_publish_json", publisher, jsonMessage).as<bool>();
}

bool RosLibJS::destroy_publisher(int publisher_id)
{
    return detail::call("wasmcpp_roslib_destroy_publisher", publisher_id).as<bool>();
}

} // namespace wasm_cpp
