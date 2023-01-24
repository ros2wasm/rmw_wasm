Module["js_talker"] = function js_talker(message)
{
    console.log("  [JS] Received " + message);
    return 0;
}

Module["js_listener"] = function js_listener()
{
    console.log("  [JS] Listening for messages");
    let js_message = "FAKE JS MESSAGE";
    return js_message;
}