run(
  require('blessed'),
  require('child_process'),
  require('fs'),
  require('path'),
  require('split'),
  process.argv.slice(3),
  {}
);

// wrapping this so that internal and open-source requires can both work
function run(blessed, child_process, fs, path, split, args, processOptions) {
  if (args.length === 0) {
    console.error('Please pass in the bsb command, like so: node foo.js -- bsb -w');
    process.exit(1);
  }

  const proc = child_process.spawn(args[0], args.slice(1), processOptions);
  process.on('exit', () => {
    proc.kill();
  });

  const tipsEntries = [
    'Our Discord channel: discord.gg/reasonml',
    'Wanna know how Reason compilation works under the hood? https://github.com/chenglou/intro-to-reason-compilation',
    'The original Reactjs implementation was written in SML (cousin of OCaml). Writing in OCaml/Reason gives you such inspirations!',
    'Ideas for Reason projects: https://github.com/chenglou/reason-project-ideas',
    'bsb (the build system running under-the-hood) is just the Ninja build system (used by Chrome & Android) + bsc',
    // bad PR move?
    'Coding in Reason/OCaml reveals to you more errors, not less. Think about it!',
    'Blocked by Adblock Plus',
  ];

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

  proc.stdout.pipe(split()).on('data', (data) => {
    if (data.startsWith('>>>> Start compiling')) {
      lastCompileTime = Date.now();
      modulesData = '';
      errorData = '';
      hasError = false;
      waitingForMoreErrors = false;

      operations.setContent('Started compiling.');
      modules.setContent(modulesData);
      error.setContent(errorData);
      status.setContent('{yellow-fg}Compiling...{/yellow-fg}')
      tips.setContent(tipsEntries[Math.floor(Math.random() * tipsEntries.length)]);
      progress.setContent('bsb too fast to display progress bar.');
    } else if (data.startsWith('[')) {
      // this one has to come first
      waitingForMoreErrors = false;
      const match = data.match(/\[(\d+)\/(\d+)\] Building (.+)/);
      if (match) {
        const paths = match[3].trim().split(' ');
        let display = paths.map(p => {
          return `${prettifyPath(p)}`
        }).join('\n');
        modulesData += '\n' + display;
        modules.setContent(modulesData);
      }
    } else if (data.startsWith('>>>> Finish compiling')) {
      waitingForMoreErrors = false;
      // console timestamp highly inaccurate; in reality the build time is much smaller.
      const duration = Math.round((Date.now() - lastCompileTime) / 10) / 100;
      operations.setContent('Waiting for new changes.');
      if (hasError) {
        // previously set already
        // status.setContent('{red-fg}Error{/red-fg}')
      } else {
        status.setContent(`{green-fg}Done!{/green-fg} (${duration}s)`)
        error.setContent(`{green-fg}¯\_(ツ)_/¯{/green-fg}`)
      }
    } else if (data.startsWith('FAILED: ')) {
      waitingForMoreErrors = true;
      hasError = true;
      // let display = data
      //   .slice('FAILED: '.length)
      //   .trim()
      //   .split(' ')
      //   .map(prettifyPath)
      //   .join('\n');
      // errorData += '\n' + display;
      // error.setContent(errorData);
      status.setContent('{red-fg}Error{/red-fg}')
    } else if (data.startsWith('ninja: Entering directory ')) {
      waitingForMoreErrors = false;
    } else if (data.startsWith('ninja: build stopped: ')) {
      waitingForMoreErrors = false;
    } else if (data === 'Event change') {
      waitingForMoreErrors = false;
    } else if (data === 'ninja: no work to do.') {
      waitingForMoreErrors = false;
    } else if (data === 'Rebuilding since []') {
      waitingForMoreErrors = false;
    } else if (data.startsWith('Rebuilding since [')) {
      waitingForMoreErrors = false;
      const match = data.match(/Rebuilding since \[(.+)?\]/);
      if (match) {
        logText.log('Detected: ' + match[1].trim());
      } else {
        logText.log(data);
      }

    } else if (waitingForMoreErrors) {
      let test = data.split(' ');
      if (test.length > 0 && test[0].endsWith('bsc.exe')) {
        // TODO: the whole command that failed. A bit noisy.
      } else {
        errorData += '\n' + data;
        error.setContent(errorData);
        status.setContent('{red-fg}Error{/red-fg}')
      }
    } else {
      logText.log(data);
    }

    screen.render();
  });


  const minimal = false;
  const color = 'green';

  // Create a screen object.
  const screen = blessed.screen({
    smartCSR: true,
    fullUnicode: true,
  });

  const error = blessed.box({
    scrollable: true,
    input: true,
    alwaysScroll: true,
    scrollbar: {
      ch: " ",
      inverse: true
    },
    keys: true,
    vi: true,
    mouse: true,

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

  const modules = blessed.box({
    scrollable: true,
    input: true,
    alwaysScroll: true,
    scrollbar: {
      ch: " ",
      inverse: true
    },
    keys: true,
    vi: true,
    mouse: true,

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

  const wrapperLowerRight = blessed.layout({
    width: "50%",
    height: "58%",
    left: "50%",
    top: "42%",
    layout: "grid"
  });

  const log = blessed.box({
    parent: wrapperLowerRight,
    label: "Miscellaneous Log",
    tags: true,
    padding: 1,
    width: "100%",
    height: "50%",
    // left: "50%",
    // top: "42%",
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

  const tips = blessed.box({
    scrollable: true,
    input: true,
    alwaysScroll: true,
    scrollbar: {
      ch: " ",
      inverse: true
    },
    keys: true,
    vi: true,
    mouse: true,

    parent: wrapperLowerRight,
    label: "Tip!",
    tags: true,
    padding: 1,
    width: "100%",
    height: "50%",
    // left: "50%",
    // top: "42%",
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

  const wrapper = blessed.layout({
    width: minimal ? "100%" : "25%",
    height: minimal ? "30%" : "42%",
    top: minimal ? "70%" : "0%",
    left: minimal ? "0%" : "75%",
    layout: "grid"
  });

  const status = blessed.box({
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

  const operations = blessed.box({
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

  const progress = blessed.box({
    parent: wrapper,
    label: "Progress",
    tags: true,
    padding: minimal ? {
      left: 1,
    } : 1,
    width: minimal ? "33%" : "100%",
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

  // const progressbar = blessed.ProgressBar({
  //   parent: progress,
  //   height: 1,
  //   width: "90%",
  //   top: "center",
  //   left: "center",
  //   hidden: minimal,
  //   orientation: "horizontal",
  //   style: {
  //     bar: {
  //       bg: color,
  //     },
  //   }
  // });

  // Quit on Escape, q, or Control-C.
  screen.key(['escape', 'q', 'C-c'], function(ch, key) {
    return process.exit(0);
  });

  screen.title = 'BuckleScript Build (bsb) Battle Station';
  screen.append(modules);
  screen.append(error);
  screen.append(wrapperLowerRight);
  screen.append(wrapper);
  screen.render();
}
