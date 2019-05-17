const testAddon = require('./build/Release/testaddon.node');

const exporter = new testAddon.Exporter();
console.log(exporter.registerProtocol('GIBI','haplgpdmjgcjpmjkmfdpabennaajapdj','pegasus'));

module.exports = testAddon;