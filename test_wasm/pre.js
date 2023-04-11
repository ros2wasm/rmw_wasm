function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
  }
  
  let lastMessage = "data: empty";
  let receivedNewMessage = false;
  let topic = "";
  
  self.onmessage = function(event) {
    // When a new message is received from main
    lastMessage = event.data;
    receivedNewMessage = true;
  }
  
  Module["registerParticipant"] = function registerParticipant(topic_name, role)
  {
    topic = topic_name;
    let gid = Math.random().toString(16).slice(2)
  
    // Register new participant with main
    self.postMessage({
      command: "register",
      topic:   topic_name,
      role:    role,
      gid:     gid
    });
  
    return gid;
  }
  
  Module["deregisterParticipant"] = function deregisterParticipant(gid)
  {
    // Deregister participant from main
    self.postMessage({
      command: "deregister",
      topic:   topic,
      gid:     gid
    });
  
    return;
  }
  
  Module["publishMessage"] = function publishMessage(message, topic_name)
  {
    // Send message to main
    if (message.startsWith("data:")) {
      self.postMessage({
        command: "publish",
        topic:    topic_name,
        message: message
      });
    }
  
    // Assume it gets published
    return true;
  }
  
  Module["retrieveMessage"] = async function retrieveMessage(topic_name)
  {
    receivedNewMessage = false;
    // Trigger main to send new message
    self.postMessage({
      command: "retrieve",
      topic:    topic_name
    });
  
    await sleep(100);
  
    return ( receivedNewMessage ? lastMessage : "" );
  }