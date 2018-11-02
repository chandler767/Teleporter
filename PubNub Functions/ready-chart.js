// Updates EON chart when users ready up and unready. 
export default (request) => { 
    const pubnub = require('pubnub');
    const kvstore = require('kvstore');
    const xhr = require('xhr');
    kvstore.get("ready_count").then((value) => {
        var ready_count = value;
        if (request.message == "ready") {
            ready_count++;
        } else if (request.message == "unready") {
            if (ready_count > 0) {
                ready_count--;
            }
        } else if (request.message == "reset") {
            ready_count = 0;
        }
        kvstore.set("ready_count", ready_count);
        pubnub.publish({
            channel: "tp-ready",
            message: {"eon":{"Ready":ready_count}}
        });
    });
    console.log('request',request); // Log the request envelope passed 
    return request.ok(); // Return a promise when you're done 
}