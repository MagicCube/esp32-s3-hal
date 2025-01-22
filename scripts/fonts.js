const { subsetFont, subsetFontAwesome } = require('./subset-font');
const { convertToCFile } = require('./convert-to-c-file');

subsetFont('PingFang Medium');
subsetFontAwesome(['f095']);
