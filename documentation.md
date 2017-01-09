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

See the `examples/` folder. The components declaration structure should look quite familiar to those who've worked with ReactJS.

To declare a component, you do the usual React stuff, except now all your functions can be standalone and take in `state`, `props`, and the rest as arguments instead.*

TODO: more docs.






*This was the original React API envisioned three years ago; back then we had many other social challenged that prompted us to make tradeoffs in terms of API for the sake of familiarity; Now that React's commonplace, we can finally go back to the original plan =).
