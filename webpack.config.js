const path = require('path');

module.exports = {
  entry: {
    pure: './lib/js/examples/pure/index.js',
    todomvc: './lib/js/examples/todomvc/app.js',
  },
  output: {
    path: path.join(__dirname, "finalOutput"),
    filename: '[name].js',
  },
};
