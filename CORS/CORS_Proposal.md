# Title:
Making sense of CORS using web.py

# Audience Level:
Intermediate

# Brief Outline: (1 Paragraph, 400 chars max)
Cross-Origin Resource Sharing is the bane of Javascript API clients
existence. It is possible to easily implement CORS support in your
Python server code with just a few simple request headers. Once your
API is talking CORS, you are free from the tyranny of browsers'
same-origin security policies. This talk will explain what CORS is,
why should care, and work through an example using web.py.


# Detailed Abstract (Detailed Description and outline)

## What is CORS?

* Cross-Origin Resource Sharing
* A way to side-step/relax Same-Origin Policy

## Why is CORS useful?

* AJAX calls (notably JS)
* web fonts

## How CORS works?

* extra/special headers in both request and response

### Simple Request

* ` Origin` HTTP header in request
* `Access-Control-Allow-Origin` header in response

### Everything Else

### Preflight Request

1. `Options` HTTP request

    * `Origin` HTTP header in request
    * `Access-Control-Allow-Origin` HTTP header in response
    * `Access-Control-Allow-Methods` HTTP header in response

2. Actual `PUT`, `POST`, `DELETE`, etc. request

### Worked Example in web.py

* Show simple REST API in Python using web.py

    * Show `OPTIONS` request handler
    * Show extra headers being sent

* Show JS AJAX requests working and not working if CORS is
enabled/disabled
* Show example of using `Access-Control-Allow-Origin` to whitelist
domains
* Show example of using `Access-Control-Allow-Methods` to whitelist
actions

## Best Practices

* `Access-Control-Allow-Origin: '*'` is really scary/wide open
