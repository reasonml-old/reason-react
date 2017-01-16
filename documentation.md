**Note** that you don't really need to know this part in order to work with React bindings, but it's interesting knowledge if you're curious how we achieved framework-agnostic JSX in Reason.

## JSX
[Reason has JSX](http://facebook.github.io/reason/#diving-deeper-jsx)! There's a paragraph about the `[@JSX]` attribute there. These bindings take advantage of it.

The macro we provide currently resides [in the Reason repo itself](https://github.com/facebook/reason/blob/77ede651424fa6d238d98a13142a888765537978/src/reactjs_jsx_ppx.ml). This transforms the agnostic JSX calls into something that works with the current ReactJS bindings.

1.
  ```re
  div foo::bar children::[child1, child2] () [@JSX]
  ```
  becomes
  ```re
  ReactDOMRe.createElement "div" props::(ReactDOMRe.props foo::bar ()) [|child1, child2|];
  ```
  Which compiles to the JS code
  ```js
  React.createElement('div', {foo: bar}, child1, child2)
  ```

2. `MyReasonComponent.createElement foo::bar [child1, child2][@JSX]` stays the same, with the `[@JSX]` part stripped too.

## Bindings Usage

See the `examples/` folder. The components declaration structure should look quite familiar to those who've worked with ReactJS. To declare a React component class, you'd create a normal OCaml module and include some pre-declared module definitions, like so:

```reason
module MyComponent = {
  include ReactRe.Component.Stateful;
  let name = "MyComponent";
  /*...*/
};
```

There are a few pre-declared definitions under `ReactRe.Component`:

- nothing: the default. Stateless component.
- Stateful: stateful component.
- JsProps: component that can be called by existing JS components through the normal JS JSX: `<Foo myProp1="hi" />`.
- InstanceVars: component that allows you to attach arbitrary instance properties, e.g. `timeoutID`, `subscriptions`, `isMounted`, etc. Note that there's no (aka no need for) instance methods; We only need regular functions.

You can chain these like so:

```reason
module MyComponent = {
  include ReactRe.Component.Stateful.InstanceVars.JsProps;
  let name = "MyComponent";
  /*...*/
};
```

TODO: more docs.


*This was the original React API envisioned three years ago; back then we had many other social challenged that prompted us to make tradeoffs in terms of API for the sake of familiarity; Now that React's commonplace, we can finally go back to the original plan =).
