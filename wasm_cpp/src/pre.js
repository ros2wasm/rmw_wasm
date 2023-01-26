let lastMessage = "data: pre-js empty message";

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

Module["js_talker"] = function js_talker(message)
{
    console.log("  [JS] Received " + message);
    return 0;
}

Module["js_listener"] = async function js_listener()
{
    console.log("  [JS] Listening for messages");
    // let js_message = "FAKE JS MESSAGE";
    await sleep(10);
    return lastMessage;
}

globalThis.js_listener = js_listener;