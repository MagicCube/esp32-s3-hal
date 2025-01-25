const { subsetFont, subsetFontAwesome } = require('./subset-font');
const { convertToCFile } = require('./convert-to-c-file');

subsetFont('PingFang Medium');
subsetFontAwesome([
  'e2ca', // wand-magic-sparkles
  'f001', // music
  'f013', // gear
  'f030', // camera
  'f095', // phone
  'f130', // microphone
  'f1eb', // wifi
  'f4ff', // user-pen
]);
