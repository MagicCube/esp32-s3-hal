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
    const outputFontFileName = `./data/${fileName}`;
    const command = `fonttools subset "${inputFontFileName}" --text-file="${basePath}/characters${
      characterSet ? `_${characterSet}` : ''
    }.txt" --output-file="${outputFontFileName}" --recommended-glyphs`;
    execCommand(command, (error) => {
      if (error) {
        console.error(`Error executing command: ${error.message}`);
        return;
      }
      console.info(
        `Subset font ${fontName} successfully: ${resolve(outputFontFileName)}`
      );
    });
  },

  subsetFontAwesome(unicodes) {
    const basePath = './misc/fonts';
    const fileName = `Font Awesome Solid 900.ttf`;
    const inputFontFileName = `${basePath}/${fileName}`;
    const outputFontFileName = `./data/font_awesome.ttf`;
    const command = `fonttools subset "${inputFontFileName}" --unicodes="${unicodes.join(
      ','
    )}" --output-file="${outputFontFileName}" --recommended-glyphs`;
    execCommand(command, (error) => {
      if (error) {
        console.error(`Error executing command: ${error.message}`);
        return;
      }
      console.info(`Icon font successfully: ${resolve(outputFontFileName)}`);
    });
  },
};
