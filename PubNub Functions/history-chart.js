// Converts events to status complete for an EON chart.
export default (request) => { 
    const pubnub = require('pubnub');
    const kvstore = require('kvstore');
    const xhr = require('xhr');
    if (request.message == "off") {
        pubnub.publish({
            channel: "tp-status",
            message: {"eon":{"Status":"0"}}
        });
    } else if (request.message == "l1") {
        pubnub.publish({
            channel: "tp-status",
            message: {"eon":{"Status":"30"}}
        });
    } else if (request.message == "l2") {
        pubnub.publish({
            channel: "tp-status",
            message: {"eon":{"Status":"50"}}
        });
    } else if (request.message == "l3") {
        pubnub.publish({
            channel: "tp-status",
            message: {"eon":{"Status":"80"}}
        });
    } else if (request.message == "app") {
        pubnub.publish({
            channel: "tp-status",
            message: {"eon":{"Status":"99"}}
        });
    } else if (request.message == "release") {
        pubnub.publish({
            channel: "tp-status",
            message: {"eon":{"Status":"100"}}
        });
    }
    console.log('request',request.message); // Log the request envelope passed 
    return request.ok(); // Return a promise when you're done 
}