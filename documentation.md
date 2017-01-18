## JSX
[Reason has JSX](http://facebook.github.io/reason/#diving-deeper-jsx)! There's a paragraph about the `[@JSX]` attribute there. These bindings take advantage of it.

The macro we provide currently resides [in the Reason repo itself](https://github.com/facebook/reason/blob/77ede651424fa6d238d98a13142a888765537978/src/reactjs_jsx_ppx.ml). This transforms the agnostic JSX calls into something that works with the current ReactJS bindings.

1.
```reason
div foo::bar children::[child1, child2] () [@JSX]
/* with JSX: <div foo=bar>child1 child2</div> */
```
becomes
```reason
ReactDOMRe.createElement "div" props::(ReactDOMRe.props foo::bar ()) [|child1, child2|];
```
Which compiles to the JS code:
```js
React.createElement('div', {foo: bar}, child1, child2)
```
and
```reason
div children::[] () [@JSX]
/* with JSX: <div /> */
```
becomes
```reason
ReactDOMRe.createElement "div" [|child1, child2|];
```
Which compiles to
```js
React.createElement('div', undefined, child1, child2)
```

2. `MyReasonComponent.createElement foo::bar [child1, child2][@JSX]` stays the same, with the `[@JSX]` part stripped.

## Bindings Usage

### "component bag"

This concept occurs several times later, so we'll explain it here. Rehydrate's bindings uses idiomatic Reason/OCaml modules and gets rid of Reactjs' `this`, a common pain point for newcomers. To fulfill the same role, relevant functions (they're not methods; just regular functions!) accept as argument a `componentBag` record, containing of shape `{props, state, updater, refSetter, instanceVars, setState}`. So a render would look like:

```reason
/* normal record destructuring. Pick what you need! */
let render {props, state} => <div className=props.className>(ReactRe.stringToElement state.message)</div>
```

- `props`, `state`: same as Reactjs'.
- `updater`: a secret sauce function that wraps every callback handler. TODO: more info
- `refSetter`: like `updater` but for ref. TODO: more info.
- `instanceVars`: TODO more info.
- `setState`: different use-cases than Reactjs' `setState`! Since lifecycle events and handlers return an `option state`, this `setState` API is rarely used and only serves as an escape hatch when you know what you're doing.

### Lifecycle events
All lifecycle hooks from Reactjs exist, apart from `componentWillMount` (`componentDidMount` is [recommended](https://facebook.github.io/react/docs/react-component.html#componentwillmount)) and `shouldComponentUpdate` (not implemented yet), e.g.

```reason
/* typical use-case: compare current & next props, then optionally set the state. */
let componentWillReceiveProps {props, state} ::nextProps => nextProps.toggle === props.toggle ? None : Some {count: state.count + 1};
```

(A common nit of Reactjs' lifecycle events is that folks can never remember prevState/prevProps/nextProps and their position in a lifecycle event. Note how we've used types and function labels to solve this.)

Instead of imperatively calling `setState`, the lifecycle functions look for potential state update from their return value. `None` means no state update needed, `Some whateverNewState` means setting the state and trigger a re-render.

- `componentDidMount`: `componentBag => option state`
- `componentWillReceiveProps`: `componentBag => nextProps::props => option state`
- `componentWillUpdate`: `componentBag => nextProps::props => nextState::state => option state`
- `componentDidUpdate`: `prevProps::props => prevState::state => componentBag => option state`
- `componentWillUnmount`: `componentBag => unit`

### The Module API

See the `examples/` folder. The components declaration structure should look quite familiar to those who've worked with ReactJS. To declare a React component class, you'd create a normal OCaml module and include some pre-declared module definitions, like so:

```reason
module MyComponent = {
  include ReactRe.Component.Stateful;
  let name = "MyComponent";
  /*...*/
};
```

There are a few pre-declared definitions under `ReactRe.Component`. You can include them by chaining them like so:

```reason
module MyComponent = {
  include ReactRe.Component.Stateful.InstanceVars.JsProps;
  let name = "MyComponent";
  /*...*/
};
```

Including each of these definitions will allow you to provide the associated functions & types. Compiling without these mandatory definitions lets the type system tell you exactly which things you need to define, but we'll document them here anyway:

(You need to chain them in that order; though you can omit anything in-between, e.g. if you don't need `Stateful`, use `include ReactRe.Component.InstanceVars.JsProps`).

#### Nothing (just `ReactRe.Component`)
The default. Stateless component. You need to provide:
- `name`, the string name of your component, for tooling purposes, e.g. [React devtools](https://github.com/facebook/react-devtools).
- `props`, the type of the component's props, preferably a record, or `unit` if no props.
- `render`, your render function! It takes in the `componentBag` record, of shape `{props, state, updater, refSetter, instanceVars, setState}`. In the case of the simple `React.Component`, only `props` and `updater` are relevant.
  - `props`: the record you've defined, accessible through a parameter rather than through `this.props` like in Reactjs (we don't need `this` in our bindings!).
  - `updater`: your callback handlers' wrapper! Instead of Reactjs' `<div onClick={handleClick} />`, we have `<div onClick=(updater handleClick) />`. Example:

    ```reason
    let handleClick componentBag event => {
      Js.log componentBag.props.message;
      None
    };
    let render {updater} => <div onClick=(updater handleClick) />;
    ```

    the callback receives the fresh `componentBag` (the whole point of `updater`) and the familiar onClick `event`, and needs to return `option state`. Since we're in the default stateless component, the return value is always `None`;

#### Stateful (`ReactRe.Component.Stateful`)
In addition to the default component definitions, this one asks you to also provide:
- `state`, the type of your state, preferably a record.
- `getInitialState`, a function that takes the initial `props` (which you can of course ignore) and returns the initial `state`.

#### JsProps
In addition to the default component definitions, add:
- `jsProps`, the type of the props passed to you from the JS side. The type should be `Js.t {. whatever: here}`, like so:

  ```reason
  type jsProps = Js.t {.
    message: string,
    count: Js.null_undefined int /* optional arg. Read below to see how all of this wires up */
  };
  ```

- `jsPropsToReasonProps`, of the type `option (jsProps => props)`, which translates the JS props into the more idiomatic `props` type you've defined, like so:

  ```reason
  let jsPropsToReasonProps = Some (fun jsProps => {message: jsProps##message, count: Js.Null_undefined.to_opt jsProps##count});
  ```

On the JS side, you'd need to require your component like so:

```js
var ReasonComponent = require('reasonComponent').comp;
<ReasonComponent message="helli" />
```

#### InstanceVars

Allows allows you to attach arbitrary instance properties, e.g. `timeoutID`, `subscriptions`, `isMounted`, etc. Note that there's no (aka no need for) instance methods; We only need regular functions. Add:
- `instanceVars`, the type that's usually of the following form:

  ```reason
  type instanceVars = {
    mutable timeoutID: option int,
    mutable subscription1: option whateverSubscriptionType
  };
  ```

  The fields of the record don't have to be mutable, but in the context of the usages of instanceVars, e.g. setting up a timeOut in `componentDidMount`, your record's likely populated with mostly mutable fields.
- `getInstanceVars`, a function of the type `unit => instanceVars`, which initiates your `instanceVars`:

  ```reason
  let getInstanceVars () => {foo: timeoutID, subscription1: None};
  ```

### Departure From Reactjs

Apart from the idiomatic OCaml-style module API described above, there are several Reactjs features that the bindings explicitly don't support:

- No string `ref`. This is a deprecated feature of Reactjs, which can't be easily removed due to the lack of types. Rehydrate refs all use the callback style previously described.
- No `componentWillMount`. `componentDidMount` is [recommended](https://facebook.github.io/react/docs/react-component.html#componentwillmount) over this method.
- No context (yet).
- No mixins/yes mixins =). OCaml's `include` is actually a form of mixin! With the bindings, you're essentially mixing in functionalities. There are several differences:
  - For us, the runtime metaprogramming of mixing in declarations from other modules is statically analyzed and compiled away (see the output), saving us code initiation cost.
  - Mixins are statically typed and prevent funny (ab)uses-cases. They're constrained to be easy to understand.
  - Since the mixins aren't provided by Rehydrate proper, there's no library-specific learning overhead/magic mixin behavior (e.g. React.createClass's mixin will merge/override/warn in certain mixin properties).


TODO: doc on bind to js without converting
