const { exec } = require('child_process');
const { unlinkSync } = require('fs');
const { resolve } = require('path');

const { convertToCFile } = require('./convert-to-c-file');

function execCommand(command, callback) {
  exec(command, (error, stdout, stderr) => {
    if (error) {
      callback(error);
      return;
    }
    callback();
  });
}

module.exports = {
  subsetFont(fontName, characterSet) {
    const basePath = './misc/fonts';
    const fileName = fontName.toLowerCase().replace(/\s+/g, '_') + '.ttf';
    const inputFontFileName = `${basePath}/${fontName}.ttf`;
    const outputFontFileName = `${basePath}/${fileName}`;
    const command = `fonttools subset "${inputFontFileName}" --text-file="${basePath}/characters${
      characterSet ? `_${characterSet}` : ''
    }.txt" --output-file="${outputFontFileName}" --recommended-glyphs`;
    execCommand(command, (error) => {
      if (error) {
        console.error(`Error executing command: ${error.message}`);
        return;
      }
      const outputCFileName = `include/fonts/${fileName.replace('.ttf', '.h')}`;
      convertToCFile(outputFontFileName, outputCFileName);
      // Delete the font file
      unlinkSync(outputFontFileName);
      console.info(
        `Subset font ${fontName} successfully: ${resolve(outputCFileName)}`
      );
    });
  },

  subsetFontAwesome(unicodes) {
    const basePath = './misc/fonts';
    const fileName = `Font Awesome Solid 900.ttf`;
    const inputFontFileName = `${basePath}/${fileName}`;
    const outputFontFileName = `${basePath}/font_awesome.ttf`;
    const command = `fonttools subset "${inputFontFileName}" --unicodes="${unicodes.join(
      ','
    )}" --output-file="${outputFontFileName}" --recommended-glyphs`;
    execCommand(command, (error) => {
      if (error) {
        console.error(`Error executing command: ${error.message}`);
        return;
      }
      const outputCFileName = `include/fonts/font_awesome.h`;
      convertToCFile(outputFontFileName, outputCFileName);
      // Delete the font file
      unlinkSync(outputFontFileName);
      console.info(`Icon font successfully: ${resolve(outputCFileName)}`);
    });
  },
};
