const { subsetFont } = require('./subset-font');
const { convertToCFile } = require('./convert-to-c-file');

subsetFont('PingFang Medium');
convertToCFile(
  './misc/fonts/Font Awesome Solid 900.ttf',
  './include/fonts/font_awesome.h'
);
