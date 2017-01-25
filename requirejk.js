function normalizeArray(parts, allowAboveRoot) {
  // if the path tries to go above the root, `up` ends up > 0
  var up = 0;
  for (var i = parts.length - 1; i >= 0; i--) {
    var last = parts[i];
    if (last === '.') {
      parts.splice(i, 1);
    } else if (last === '..') {
      parts.splice(i, 1);
      up++;
    } else if (up) {
      parts.splice(i, 1);
      up--;
    }
  }

  // if the path is allowed to go above the root, restore leading ..s
  if (allowAboveRoot) {
    for (; up--; up) {
      parts.unshift('..');
    }
  }

  return parts;
};

function pathNormalize(path) {
  var isAbsolute = path.charAt(0) === '/';
  var trailingSlash = path.substr(-1) === '/';

  // Normalize the path
  path = normalizeArray(path.split('/').filter(function(p) {
    return !!p;
  }), !isAbsolute).join('/');

  if (!path && !isAbsolute) {
    path = '.';
  }
  if (path && trailingSlash) {
    path += '/';
  }

  return (isAbsolute ? '/' : '') + path;
};

var globalEval = eval;
var currentScript = document.currentScript;
var nodeModulesDir = currentScript.dataset.root + '/node_modules/';

var modulesCache = {};
var packageJsonMainCache = {};

function loadScript(scriptPath) {
  var request = new XMLHttpRequest();

  request.open("GET", scriptPath, false); // sync
  request.send();
  var dirSeparatorIndex = scriptPath.lastIndexOf('/');
  var dir = dirSeparatorIndex === -1 ? '.' : scriptPath.slice(0, dirSeparatorIndex);

  var extraHeader = `
    (function(module, exports, modulesCache, packageJsonMainCache, nodeModulesDir) {
      function require(path) {
        var __dirname = "${dir}/";
        var resolvedPath;
        if (path.startsWith('.')) {
          // require('./foo/bar')
          resolvedPath = __dirname + path + '.js';
        } else if (path.indexOf('/') === -1) {
          // require('react')
          var packageJson = pathNormalize(nodeModulesDir + path + '/package.json');
          if (packageJsonMainCache[packageJson] == null) {
            var jsonRequest = new XMLHttpRequest();
            jsonRequest.open("GET", packageJson, false);
            jsonRequest.send();
            if (main == null) {
              main = 'index.js';
            } else if (!main.endsWith('.js')) {
              main = main + '.js';
            }
            packageJsonMainCache[packageJson] = nodeModulesDir + path + '/' + main;
          }
          resolvedPath = packageJsonMainCache[packageJson];
        } else {
          // require('react/bar')
          resolvedPath = nodeModulesDir + path + '.js';
        };
        resolvedPath = pathNormalize(resolvedPath);
        if (modulesCache[resolvedPath] != null) {
          return modulesCache[resolvedPath];
        };
        var result = loadScript(resolvedPath);
        modulesCache[resolvedPath] = result;
        return result;
      };
      var process = {env: {}};
  `;
  var module = {exports: {}};
  return globalEval(extraHeader + request.responseText + 'return module.exports})')(module, module.exports, modulesCache, packageJsonMainCache, nodeModulesDir);
};

loadScript(currentScript.dataset.main)
