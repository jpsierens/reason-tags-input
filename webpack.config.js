const path = require('path');

module.exports = {
  entry: './src/TagsInput.bs.js',
  output: {
    path: path.join(__dirname, "build"),
    filename: 'index.js',
    libraryTarget: 'commonjs2'
  },
  externals: { 'react': 'commonjs react' }
};
