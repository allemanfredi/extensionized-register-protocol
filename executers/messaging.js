module.exports = (handleMessage) => {

  process.stdin.on('readable', () => {
    let input = [];
    let chunk;
    while (chunk = process.stdin.read()) {
      input.push(chunk)
    }
    input = Buffer.concat(input);

    const msgLen = input.readUInt32LE(0);
    const dataLen = msgLen + 4;

    if (input.length >= dataLen) {
      const content = input.slice(4, dataLen);
      const json = JSON.parse(content.toString());
      handleMessage(json);
    }
  })

  function sendMessage (msg) {
    const buffer = Buffer.from(JSON.stringify(msg));

    const header = Buffer.alloc(4);
    header.writeUInt32LE(buffer.length, 0);

    const data = Buffer.concat([header, buffer]);
    process.stdout.write(data);
  }

  process.on('uncaughtException', (err) => {
    //sendMessage({error: err.toString()})
  })

  return sendMessage

}