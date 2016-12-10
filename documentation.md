## JSX
Reason has JSX! With a few (arguably) welcomed tweaks:

1. No need for curly braces: `<MyComponent className="foo" count=(add 1 2) />`.
2. Automatic label punning: `let className = "foo"; let count = add 1 2; <MyComponent className count />`.
3. Fragments! `<>foo bar baz</>`. More on this another time =).

Under the hood, Reason JSX desugars to some agnostic, pluggable OCaml macros; we provide a default one that works with the current ReactJS bindings. There are 3 categories:

- `<div foo=bar/>`
- TODO it's late.
- TODO wow it's late.

## Idioms
