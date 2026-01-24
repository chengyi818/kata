// Shim for jQuery's $.ajax using fetch, specifically for Service Worker context.
// This implements a minimal subset of jQuery.ajax required by Wiz.Remote.js

(function() {
    var $ = {};

    function param(data) {
        if (typeof data === 'string') {
            return data;
        }
        // Use URLSearchParams for serialization
        return new URLSearchParams(data).toString();
    }

    $.ajax = function(options) {
        var url = options.url;
        var method = (options.type || 'GET').toUpperCase();
        var data = options.data;
        var headers = {};

        // Default content type like jQuery
        var contentType = options.contentType || 'application/x-www-form-urlencoded; charset=UTF-8';
        if (options.contentType !== false) {
             headers['Content-Type'] = contentType;
        }

        var fetchOptions = {
            method: method,
            headers: headers,
            credentials: 'include'
        };

        if (method === 'GET' || method === 'HEAD') {
            if (data) {
                var queryString = param(data);
                if (queryString) {
                    url += (url.indexOf('?') === -1 ? '?' : '&') + queryString;
                }
            }
        } else {
            // POST, PUT, DELETE etc.
            if (data) {
                // If contentType is json, data should already be stringified by caller (Remote.js does this)
                // If contentType is urlencoded, we need to serialize if it's an object
                if (contentType.indexOf('application/json') !== -1) {
                    fetchOptions.body = typeof data === 'string' ? data : JSON.stringify(data);
                } else {
                    fetchOptions.body = typeof data === 'string' ? data : param(data);
                }
            }
        }

        // Handle cache: false (jQuery adds _={timestamp})
        if (options.cache === false) {
            var antiCache = '_=' + Date.now();
            url += (url.indexOf('?') === -1 ? '?' : '&') + antiCache;
        }

        fetch(url, fetchOptions)
            .then(function(response) {
                // Prepare jqXHR-like object
                var jqXHR = {
                    status: response.status,
                    statusText: response.statusText
                };

                if (response.ok) {
                    return response.text().then(function(text) {
                        var result = text;
                        if (options.dataType === 'json') {
                            try {
                                result = JSON.parse(text);
                            } catch (e) {
                                // Parse error
                                if (options.error) {
                                    options.error(jqXHR, 'parsererror', e);
                                }
                                return;
                            }
                        }
                        if (options.success) {
                            options.success(result, 'success', jqXHR);
                        }
                    });
                } else {
                    response.text().then(function(text) {
                        jqXHR.responseText = text;
                        if (options.error) {
                            options.error(jqXHR, 'error', response.statusText);
                        }
                    }).catch(function() {
                        if (options.error) {
                            options.error(jqXHR, 'error', response.statusText);
                        }
                    });
                }
            })
            .catch(function(error) {
                if (options.error) {
                    var jqXHR = {
                        status: 0,
                        statusText: error.message
                    };
                    options.error(jqXHR, 'error', error.message);
                }
            });
    };

    // Expose to global scope (self in SW)
    self.$ = $;
    self.jQuery = $;
})();

