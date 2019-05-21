    
const ipc = require('node-ipc');

ipc.config.id = 'host';
ipc.config.retry = 1000;
ipc.config.silent = true;

ipc.connectTo(
    'host',
    function(){
        ipc.of.host.on(
            'connect',
            function(){
                ipc.of.host.emit('app.message',
                    {
                        id      : ipc.config.id,
                        message : 'openExtension',
                        url : process.argv[2]
                    }
                );
                ipc.disconnect('host');
            }
        );
    }
);