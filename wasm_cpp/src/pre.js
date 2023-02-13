
function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

Module["registerParticipant"] = function registerParticipant(name, role)
{

    return gid;
}

Module["deregisterParticipant"] = function deregisterParticipant(gid)
{
    return;
}

Module["publishMessage"] = function publishMessage(message, topic_name)
{
    console.log("  [JS] Received " + message);
    return 0;
}

Module["retrieveMessage"] = async function retrieveMessage(topic_name)
{
    console.log("  [JS] Listening for messages");
    await sleep(10);
    return "lastMessage";
}

