
class WasmCppCtx {
    constructor() {
        console.log('entered wasmcpp_roslib_init');

        this.ros = new ROSLIB.Ros();
        this.ros.on('error', function(error) { console.error( error ); });
        this.ros.on('connection', function() { console.log('Connection made!'); });

        this.subscribers = new Map();
        this.publishers  = new Map();
        this.nextHandle  = 1;
    }

    destroy() {
        this.subscribers.forEach((_, listener) => {
            listener.unsubscribe();
        });
        this.subscribers.clear();
        this.publishers.forEach((_, listener) => {
            listener.unadvertise();
        });
        this.publishers.clear();
    }

    connect(url) {
        this.ros.connect(url);
    }

    addSubscriber(topic, msgType, callback, cb_handle) {
        console.log(`Creating subscriber {topic: ${topic}, msg: ${msgType}}`);

        const handle = this.nextHandle++;
        const listener = new ROSLIB.Topic({
            ros: this.ros,
            name: topic,
            messageType: msgType
        });

        this.subscribers.set(handle, listener);

        listener.subscribe(function(message) {
          callback(cb_handle, JSON.stringify(message));
        });

        return handle;
    }

    removeSubscribe(handle) {
        const listener = this.subscribers.get(handle);
        if (listener === undefined)
            return false;
        this.subscribers.delete(handle);
        listener.unsubscribe();
        return true;
    }

    addPublisher(topic, msgType) {
        console.log(`Creating publisher {topic: ${topic}, msg: ${msgType}}`);

        const handle = this.nextHandle++;
        const listener = new ROSLIB.Topic({
            ros: this.ros,
            name: topic,
            messageType: msgType
        });

        this.publishers.set(handle, listener);
        listener.advertise();

        return handle;
    }

    removePublisher(handle) {
        const listener = this.publishers.get(handle);
        if (listener === undefined)
            return false;
        this.publishers.delete(handle);
        listener.unadvertise();
        return true;
    }

    // Publish a ROSLIB.Message
    publish(handle, message) {
        const listener = this.publishers.get(handle);
        if (listener === undefined)
            return false;
        listener.publish(message);
        return true;
    }

    // Convert a JSON string to a ROSLIB.Message and publish it.
    publishJSON(handle, msgJson) {
        return this.publish(handle, new ROSLIB.Message(JSON.parse(msgJson)));
    }
}

let wasmcpp = null;

Module["wasmcpp_roslib_init"] = function ()
{
    console.log('entered wasmcpp_roslib_init');
    wasmcpp = new WasmCppCtx();
}

Module["wasmcpp_roslib_shutdown"] = function ()
{
    console.log('entered wasmcpp_roslib_shutdown');

    wasmcpp.destroy();
    wasmcpp = null;
}

Module["wasmcpp_roslib_connect"] = function (url)
{
    console.log('entered wasmcpp_roslib_connect');
    wasmcpp.connect(url);
}

Module["wasmcpp_roslib_create_subscriber"] = function (topic, message_type, callback, cb_handle)
{
    console.log('entered wasmcpp_roslib_create_subscriber');
    return wasmcpp.addSubscriber(topic, message_type, callback, cb_handle);
}

Module["wasmcpp_roslib_destroy_subscriber"] = function (handle)
{
    console.log('entered wasmcpp_roslib_destroy_subscriber');
    return wasmcpp.removeSubscribe(handle);
}

Module["wasmcpp_roslib_create_publisher"] = function (topic, message_type)
{
    console.log('entered wasmcpp_roslib_create_publisher');
    return wasmcpp.addPublisher(topic, message_type);
}

Module["wasmcpp_roslib_publish_json"] = function (handle, message)
{
    console.log('entered wasmcpp_roslib_publish_json');
    return wasmcpp.publishJSON(handle, message);
}

Module["wasmcpp_roslib_destroy_publisher"] = function (handle)
{
    console.log('entered wasmcpp_roslib_destroy_publisher');
    return wasmcpp.removePublisher(handle);
}
