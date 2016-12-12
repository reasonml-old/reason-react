# Secret Reason Test

If you got to this place then you know what this is for! Please don't publicize it. We're still polishing it before the official announcement. In the meantime, come join us in [Discord](discord.gg/reasonml)!

## Installation

Prerequisite: having [Ninja](https://ninja-build.org/) installed, e.g. `brew install ninja` if you're on macOS.

```sh
git clone https://github.com/reasonml/rehydrate.git
cd rehydrate
npm install
npm start
# in another window
npm run build
```

## Usage
See the `examples/` folder.


## Known Issues:

`bsb` currently builds a `.merlin` file that doesn't quite work right for some reason.
Comment it out before editing, and it won't fail, but you won't get any type checking by merlin.
To fix the `.merlin` file,  make it look something like this (by hand).


```
####{BSB GENERATED: NO EDIT
S /absolute/path/to/rehydrate/node_modules/bs-platform/bin/../lib/ocaml
B /absolute/path/to/rehydrate/node_modules/bs-platform/bin/../lib/ocaml
FLG -ppx bsppx.exe
FLG -ppx reactjs_jsx_ppx

S examples
B lib/bs/examples

S examples/pure
B lib/bs/examples/pure

S src
B lib/bs/src

####BSB GENERATED: NO EDIT}
```
