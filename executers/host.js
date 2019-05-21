
const sendMessage = require('./messaging')(handleMessage);
const ipc = require('node-ipc');


function handleMessage (req) {
    sendMessage({message: req})
}


ipc.config.id = 'host';
ipc.config.retry= 1500;
ipc.config.silent = true; //console.log generate an exception in the chrome.runtime

ipc.serve(
    function(){
        ipc.server.on(
            'app.message',
            function(data,socket){
                if ( data.message === 'openExtension'){
                    sendMessage({command:'open' , message:'url'});
                }
            }
        );
    }
);


ipc.server.start();