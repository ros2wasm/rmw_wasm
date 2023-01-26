#include <iostream> // REMOVE
#include <string>

#include <emscripten/emscripten.h>
#include <emscripten/val.h>

#include "wasm_cpp/subscriber.hpp"

// EM_JS(int, do_fetch, (), {
//   return Asyncify.handleAsync(function () {
//     out("waiting for a fetch");
//     return fetch("a.html").then(function (response) {
//       out("got the fetch response");
//       // (normally you would do something with the fetch here)
//       return 42;
//     });
//   });
// });

namespace wasm_cpp
{

    Subscriber::Subscriber(const std::string & topic_name)
    {
        // TODO: create subscriber
        std::cout << "[WASM] Subscriber created\n"; // REMOVE
        std::cout << " [SUB] topic out of this world: " << topic_name << '\n';
    }

    Subscriber::~Subscriber()
    {
        // TODO: destroy subscriber
        std::cout << "[WASM] Subscriber destroyed\n"; // REMOVE
    }

    std::string Subscriber::get_message()
    {
        std::string message{ "data: empty message" };

        std::cout << "[SUB] GET MESSAGE\n";

        emscripten::val js_listener = emscripten::val::module_property("js_listener");
        emscripten::val js_response = js_listener().await();

        try {
            auto js_message = js_response.as<std::string>();
            message = js_message;
        }
        catch (...) {
            std::cout << "[SUB] could not convert js_message\n";
            return nullptr;
        }

        std::cout << "[SUB] After trying to convert\n";

        return message;
    }

    // TODO: register subscriber

} // namespace wasm_cpp