# extensionized-register-protocol

## In development

extensionized-register-protocol allows to register a Google Chrome extension as possible handlers for particular protocols.
At the moment the functionality is only available on windows.

## Usage

```js
    const appName = 'app name';
    const extensionId = 'extension id';
    const protocolName = 'protocol name';
    registerProtocol(protocolName , extensionId ,appName);

    //handle requests
    const port = chrome.runtime.connectNative('com.' + appName + '.protocol.handler');
    port.onMessage.addListener(function(req) {
        console.log(req);
    });
}
```