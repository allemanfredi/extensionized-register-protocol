{
    "targets": [{
        "target_name": "testaddon",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "src/main.cc",
            "src/exporter/exporter.cc",
        ],
        "conditions":[
            ["OS=='linux'", {
            "sources": [ "src/handlers/handler_linux.cc" ]
            }],
            ["OS=='mac'", {
            "sources": [ "src/handlers/handler_mac.cc" ]
            }],
            ["OS=='win'", {
            "sources": [ "src/handlers/handler_win.cc" ]
            }]
        ], 
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'libraries': [],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }]
}

