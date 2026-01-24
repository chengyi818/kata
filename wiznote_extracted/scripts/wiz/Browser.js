'use strict';
var Wiz = Wiz || {};
Wiz.Browser = {
    onRequest : function(){
        try {
            // chrome.extension.onRequest is deprecated. Use runtime.onMessage.
            return (chrome.runtime.onMessage);
        } catch (err) {
            console.log('Wiz.Browser onRequest() Error : ' + err);
        }
    },
    sendRequest : function (tabId, params, callback) {
        try {
            // Ensure callback to avoid returning a Promise in MV3 which causes "Uncaught (in promise)" if rejected.
            // Also checking runtime.lastError in callback prevents "Unchecked runtime.lastError".
            var safeCallback = callback || function(response) {
                if (chrome.runtime.lastError) {
                    // console.log("Wiz.Browser.sendRequest error: " + chrome.runtime.lastError.message);
                }
            };

            if (chrome.tabs.sendMessage) {
                try {
                    chrome.tabs.sendMessage(tabId, params, {frameId: 0}, safeCallback);
                } catch(e) {
                    chrome.tabs.sendMessage(tabId, params, safeCallback);
                }
            } else {
                // Fallback for very old chrome, unlikely needed
                chrome.tabs.sendMessage(tabId, params, safeCallback);
            }
        } catch (err) {
            console.log('Wiz.Browser sendRequest() Error : ' + err);
        }
    }
};