#include <string>

#include "rcutils/logging_macros.h"

#include <emscripten/emscripten.h>
#include <emscripten/val.h>

#include "wasm_cpp/publisher.hpp"
#include "wasm_cpp/subscriber.hpp"
#include "wasm_cpp/context.hpp"
#include "wasm_cpp/modes.hpp"


namespace wasm_cpp
{
    std::mutex g_topicsLock;
    std::map<std::string, std::vector<Subscriber*>> g_topics;

    Publisher::Publisher(const std::string & topic_name)
        : Participant(topic_name, "publisher")
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace Publisher::Publisher()");
    }

    Publisher::Publisher(const std::string & topic_name, const std::string &msg_type, const std::string & msg_namespace)
        : Participant(topic_name, "publisher")
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace Publisher::Publisher()");
        if (roslibjs_enable()){
            std::string module_name = msg_namespace.substr(0, msg_namespace.find("__"));
            std::string full_interface_name = msg_type;
            if (module_name.length() > 0)
                full_interface_name = module_name + "/" + full_interface_name;

            m_roslib_handle = get_global_context()->get_roslib_js().create_publisher(
                topic_name,
                full_interface_name);
        }
    }

    Publisher::~Publisher()
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace Publisher::~Publisher()");

        if(roslibjs_enable()){
            get_global_context()->get_roslib_js().destroy_publisher(m_roslib_handle);
        }
    }

    void Publisher::publish(const std::string & message)
    {
        RCUTILS_LOG_DEBUG_NAMED("wasm_cpp", "trace Publisher::publish()");
        if(roslibjs_enable()){
            get_global_context()->get_roslib_js().publish(m_roslib_handle, message);
        }
        else{
            get_global_context()->push_message_to_subscribers(get_name(), message);
        }

    }

} // namespace wasm_cpp
