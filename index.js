const testAddon = require('./build/Release/testaddon.node');

const exporter = new testAddon.Exporter();
console.log(exporter.registerProtocol('GIBI','12345','prova'));

module.exports = testAddon;