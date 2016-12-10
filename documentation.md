## JSX
Reason has JSX! With a few (arguably) welcomed tweaks:

1. No need for curly braces: `<MyComponent className="foo" count=(add 1 2) />`.
2. Automatic label punning: `let className = "foo"; let count = add 1 2; <MyComponent className count />`.
3. Fragments! `<>foo bar baz</>`. More on this another time =).

Under the hood, Reason JSX desugars to normal, pluggable OCaml calls:

1. Upper-case

  ```jsx
  <MyComponent foo=bar>child1 child2</MyComponent>
  ```

  becomes

  ```re
  MyComponent.createElement foo::bar [child1, child2][@JSX]
  ```

2. Lower-case

  ```jsx
  <div foo=bar>child1 child2</div>
  ```

  becomes

  ```re
  div foo::bar [child1, child2][@JSX]
  ```


And now, we provide a macro (ppx), `reactjs_jsx_ppx`, that transforms the above calls into something that works with the current ReactJS bindings. **Note** that you don't really need to know this part in order to work with React bindings, but it's interesting know nonetheless.

1.
  ```re
  div foo::bar [child1, child2][@JSX]
  ```
  becomes
  ```re
  ReactRe.createElement "div" Js.Null.return {"foo": bar} [|child1, child2|]
  ```
  Which compiles to
  ```js
  React.createElement('div', {foo: bar}, child1, child2)
  ```

2.
  ```re
  slider_ foo::bar [child1, child2][@JSX]
  ```
  becomes
  ```re
  ReactRe.createElement slider_ Js.Null.return {"foo": bar} [|child1, child2|]
  ```
  Note that it's not quoted! This allows you to use ReactJS components inside Reason:

  ```jsx
  external slider_: ReactRe.reactClass = "Slider" [@@bs.module]; /* this is a BuckleScript JS interop call. */

  <slider_ foo=bar> child1 child2 </slider_>
  ```

  Which compiles to

  ```js
  var Slider_ = require("Slider");

  React.createElement(Slider_, {foo: bar}, child1, child2);
  ```

3. Finally, `MyReasonComponent.createElement foo::bar [child1, child2][@JSX]` stays the same, with the `[@JSX]` part stripped.

## Idioms
