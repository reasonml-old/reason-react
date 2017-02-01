var ReactDOM = require('react-dom');
var React = require('react');
var PageReason = require('../../lib/js/examples/interop/pageReason').comp;

ReactDOM.render(React.createElement(PageReason, {message: 'Hello!'}), document.getElementById('index'));
