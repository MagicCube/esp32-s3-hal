const fs = require('fs');

module.exports = {
  convertToCFile(inputFile, outputFile) {
    const inputBuffer = Array.from(fs.readFileSync(inputFile));
    let code = '#pragma once\n\n#include <Arduino.h>\n\n';
    const variableName = outputFile
      .split('/')
      .pop()
      .split('.')
      .shift()
      .replace(/-/g, '_');
    code += `static const uint8_t ${variableName}[] PROGMEM = {${inputBuffer
      .map((byte) => `0x${byte.toString(16)}`)
      .join(', ')}};`;
    code += '\n\n';
    code += `static const size_t ${variableName}_size = ${inputBuffer.length};`;
    fs.writeFileSync(outputFile, code);
  },
};
