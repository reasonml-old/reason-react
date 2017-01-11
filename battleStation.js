const readline = require('readline');
const blessed = require('blessed');
const child_process = require('child_process');
const fs = require('fs');
const path = require('path');
var Readable = require('stream').Readable
var Writable = require('stream').Writable

const args = process.argv.slice(3);

if (args.length === 0) {
  console.error('Please pass in the bsb command, like so: node foo.js -- bsb -w');
  process.exit(1);
}

const asd = new Writable();
const asd2 = new Readable();
var readable = fs.createReadStream(null, {fd: 3});
var writable = fs.createWriteStream('./what.txt', {fd: 3});

const proc = child_process.spawn('bsb', ['-w']);

process.on('exit', () => {
  proc.kill();
});

// >>>> Start compiling
// Rebuilding since []
// ninja: Entering directory `lib/bs'
// ninja: no work to do.
//
//
// >>>> Finish compiling
// watching dir examples now
// watching dir examples/todomvc now
// watching dir examples/pure now
// watching dir src now
// Event change
// >>>> Start compiling
// Rebuilding since [ 'change : page.re' ]
// ninja: Entering directory `lib/bs'
// [1/2] Building examples/pure/page.mlast
// [2/2] Building examples/pure/page.mlast.d
// [1/2] Building examples/pure/page.cmj /Users/chenglou/Github/rehydrate/lib/js/examples/pure/page.js examples/pure/page.cmi
// [2/2] Building examples/pure/index.cmj /Users/chenglou/Github/rehydrate/lib/js/examples/pure/index.js examples/pure/index.cmi
//
//
// >>>> Finish compiling

let lastCompileTime = null;
let modulesData = '';
let errorData = '';
let hasError = false;
let waitingForMoreErrors = false;

function prettifyPath(p) {
  const dir = path.dirname(p);
  const file = path.basename(p);
  return `{grey-fg}${dir}/{/grey-fg}${file}`;
};

proc.stdout.pipe(require('split')()).on('data', (data) => {
  if (data.startsWith('[')) {
    // this one has to come first
    waitingForMoreErrors = false;
    const match = data.match(/\[(\d+)\/(\d+)\] Building (.+)/);
    if (match) {
      let [_, curr, total, paths] = match;
      curr = parseInt(curr);
      total = parseInt(total);
      paths = paths.trim().split(' ');
      let display = paths.map(p => {
        return `[${curr}/${total}] ${prettifyPath(p)}`
      }).join('\n');
      modulesData += '\n' + display;
      modules.setContent(modulesData);
    }
  } else if (data.startsWith('>>>> Start compiling')) {
    lastCompileTime = Date.now();
    modulesData = '';
    errorData = '';
    hasError = false;
    waitingForMoreErrors = false;

    operations.setContent('Started compiling');
    modules.setContent(modulesData);
    error.setContent(errorData);
    status.setContent('{yellow-fg}Compiling...{/yellow-fg}')
    // operations.setContent('Building');
  } else if (data.startsWith('>>>> Finish compiling')) {
    waitingForMoreErrors = false;
    const duration = Math.floor((Date.now() - lastCompileTime) / 10) / 100;
    operations.setContent('Finished in ' + duration + 's\nWaiting for new changes');
    if (hasError) {
      // previously set
      // status.setContent('{red-fg}Error{/red-fg}')
    } else {
      status.setContent('{green-fg}Done!{/green-fg}')
    }
    // operations.setContent('Idle, waiting for changes');
  } else if (data.startsWith('FAILED: ')) {
    waitingForMoreErrors = true;
    hasError = true;
    let display = data
      .slice('FAILED: '.length)
      .trim()
      .split(' ')
      .map(prettifyPath)
      .join('\n');
    errorData += '\n' + display;
    error.setContent(errorData);
    status.setContent('{red-fg}Error{/red-fg}')
  } else if (data.startsWith('ninja: Entering directory ')) {
    waitingForMoreErrors = false;
    // do nothing
  } else if (data === 'Event change') {
    waitingForMoreErrors = false;
    // do nothing
  } else if (data === 'ninja: no work to do.') {
    waitingForMoreErrors = false;
    // do nothing
  } else if (waitingForMoreErrors) {
    errorData += '\n' + data;
    error.setContent(errorData);
    status.setContent('{red-fg}Error{/red-fg}')
  } else {
    logText.log(data);
  }

  screen.render();
});

// proc.stdout.pipe(asd2)

const minimal = false;
const color = 'green';

// Create a screen object.
const screen = blessed.screen({
  smartCSR: true
});

screen.title = 'BuckleScript Build (bsb) Battle Station';

const error = blessed.box({
  label: "Error",
  tags: true,
  padding: 1,
  width: minimal ? "100%" : "75%",
  height: minimal ? "70%" : "42%",
  left: "0%",
  top: "0%",
  border: {
    type: "line",
  },
  style: {
    fg: -1,
    border: {
      fg: color,
    },
  },
});

screen.append(error);

const modules = blessed.box({
  label: "Files Being Rebuilt",
  tags: true,
  padding: 1,
  width: "50%",
  height: "58%",
  left: "0%",
  top: "42%",
  border: {
    type: "line",
  },
  style: {
    fg: -1,
    border: {
      fg: color,
    },
  },
});

screen.append(modules);

const log = blessed.box({
  label: "Miscellaneous Log",
  tags: true,
  padding: 1,
  width: "50%",
  height: "58%",
  left: "50%",
  top: "42%",
  border: {
    type: "line",
  },
  style: {
    fg: -1,
    border: {
      fg: color,
    },
  },
});

const logText = blessed.log({
  parent: log,
  tags: true,
  width: "100%-5",
  scrollable: true,
  input: true,
  alwaysScroll: true,
  scrollbar: {
    ch: " ",
    inverse: true
  },
  keys: true,
  vi: true,
  mouse: true
});

screen.append(log);

wrapper = blessed.layout({
  width: minimal ? "100%" : "25%",
  height: minimal ? "30%" : "42%",
  top: minimal ? "70%" : "0%",
  left: minimal ? "0%" : "75%",
  layout: "grid"
});

status = blessed.box({
  parent: wrapper,
  label: "Status",
  tags: true,
  padding: {
    left: 1,
  },
  width: minimal ? "34%" : "100%",
  height: minimal ? "100%" : "34%",
  valign: "middle",
  border: {
    type: "line",
  },
  style: {
    fg: -1,
    border: {
      fg: color,
    },
  },
});

operations = blessed.box({
  parent: wrapper,
  label: "Operation",
  tags: true,
  padding: {
    left: 1,
  },
  width: minimal ? "34%" : "100%",
  height: minimal ? "100%" : "34%",
  valign: "middle",
  border: {
    type: "line",
  },
  style: {
    fg: -1,
    border: {
      fg: color,
    },
  },
});

progress = blessed.box({
  parent: wrapper,
  label: "Progress",
  tags: true,
  padding: minimal ? {
    left: 1,
  } : 1,
  width: minimal ? "33%" : "100%",
  // TODO: why does this need to be 36? webpack-dashboard's 34 doesn't work
  height: minimal ? "100%" : "36%",
  valign: "middle",
  border: {
    type: "line",
  },
  style: {
    fg: -1,
    border: {
      fg: color,
    },
  },
});

progressbar = blessed.ProgressBar({
  parent: progress,
  height: 1,
  width: "90%",
  top: "center",
  left: "center",
  hidden: minimal,
  orientation: "horizontal",
  style: {
    bar: {
      bg: color,
    },
  }
});

screen.append(wrapper);

// Quit on Escape, q, or Control-C.
screen.key(['escape', 'q', 'C-c'], function(ch, key) {
  return process.exit(0);
});

// Focus our element.
// centerBox.focus();





// Render the screen.
screen.render();
