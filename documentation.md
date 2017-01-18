__This documentation assumes relative familiarity with ReactJS.__

## JSX
[Reason has JSX](http://facebook.github.io/reason/#diving-deeper-jsx)! There's a paragraph about the `[@JSX]` attribute there. These bindings take advantage of it.

The macro we provide currently resides [in the Reason repo itself](https://github.com/facebook/reason/blob/77ede651424fa6d238d98a13142a888765537978/src/reactjs_jsx_ppx.ml). This transforms the agnostic JSX calls into something that works with the current ReactJS bindings.

### Uncapitalized JSX

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
div children::[] () [@JSX] /* with JSX: <div /> */
```
becomes
```reason
ReactDOMRe.createElement "div" [|child1, child2|];
```
Which compiles to
```js
React.createElement('div', undefined, child1, child2)
```

### Capitalized JSX

```reason
MyReasonComponent.createElement foo::bar [child1, child2][@JSX]
/* with JSX: <MyReasonComponent foo=bar>child1 child2</MyReasonComponent> */
```

Stays the same, with the `[@JSX]` part stripped.

## Bindings Usage

### "component bag"

Rehydrate's uses idiomatic Reason/OCaml modules to get rid of ReactJS' `this`, a common pain point for ReactJS newcomers. To fulfill the same role, relevant functions (they're not methods; just regular functions!) accept as argument a `componentBag` record of shape `{props, state, updater, refSetter, instanceVars, setState}`. A render would look like:

```reason
/* normal record destructuring. Pick what you need! */
let render {props, state} => <div className=props.className>(ReactRe.stringToElement state.message)</div>
```

#### `props`, `state`
Same as ReactJS'.

#### `updater`
The secret sauce function that wraps every callback handler. The ReactJS `<div onClick={this.handleClick} />` becomes `<div onClick=(updater handleClick) />`. `updater` takes in your familiar callback and returns a new (memoized) callback that'll give you the up-to-date props, state and other values when it's called. Example:

```reason
/* `props` is up-to-date here, even though onClick is asynchronously triggered */
let handleClick {props} event => {Js.log "clicked!"; None};
let render {props, updater} => <div onClick=(updater handleClick) />;
```

The return type is `option state`, where you indicate whether the handler needs to trigger a state update or not.

#### `refSetter`
Like `updater` but for ref:

```reason
/* this type will be explained later */
type instanceVars = {mutable divRef: option ReactRe.reactRef};
let getInstanceVars () => {divRef: None};
let getRef componentBag theRef => componentBag.instanceVars.divRef = Some theRef;
let render {props, refSetter} => <div ref=(refSetter getRef) />;
```

Rehydrate ref only accept callbacks. The string `ref` from ReactJS is a deprecated feature, which couldn't be easily removed due to the lack of types in JS.

TODO: ref-related helpers (in another section. Refer to that section here).

#### `instanceVars`
Occasionally, ReactJS components are used to store instance properties, e.g. `timeoutID`, `subscriptions`, `isMounted`. We support this pattern.

```reason
type instanceVars = {mutable intervalID: option int};
/* this method & the life cycle methods will be explained below */
let getInstanceVars () => {intervalID: None};
let componentDidMount {instanceVars} => {
  instanceVars.intervalID = Some (someBindingsToSetInterval (fun () => Js.log "testing!") 1000);
  None
};
let componentWillUnmount {instanceVars} =>
  switch instanceVars.intervalID {
  | None => ()
  | Some id => someBindingsToClearInterval id
  };
```

See also the use-case with the previous `refSetter`.

#### `setState`
Different use-cases than ReactJS' `setState`! Since lifecycle events (below) and handlers return an `option state`, this `setState` API is rarely used and only serves as an escape hatch when you know what you're doing.

### Lifecycle events
All lifecycle hooks from ReactJS exist, apart from `componentWillMount` (`componentDidMount` is [recommended](https://facebook.github.io/react/docs/react-component.html#componentwillmount)) and `shouldComponentUpdate` (not implemented yet), e.g.

```reason
/* typical use-case: compare current & next props, then optionally set the state. */
let componentWillReceiveProps {props, state} ::nextProps => nextProps.toggle === props.toggle ? None : Some {count: state.count + 1};
```

(A common nit of ReactJS' lifecycle events is that folks can never remember prevState/prevProps/nextProps and their position in a lifecycle event. Note how we've used types and function labels to solve this.)

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
- `render`, your render function! It takes in the `componentBag` record, described earlier. In the case of the simple `React.Component`, only `props` and `updater` are relevant.

#### Stateful
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
Add:
- `instanceVars` (documented earlier), the type that's usually of the following form:

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

### Interop With Existing JavaScript Components
While it's nice to marvel at OCaml's great type system, Rehydrate's slick API, BuckleScript's great perf after static analysis, our toolchain's great editor integration, etc., it's unpragmatic to suddenly convert over all existing JS components to Reason. We've exposed great hooks to make talking with the JS components easier.

#### Reason -> JS
TODO

#### JS -> Reason
TODO

#### Converting a Component Over
TODO

#### Bind to a Component Without Convert It Over
TODO

### Miscellaneous

- No context (yet).
- No mixins/yes mixins =). OCaml's `include` is actually a form of mixin! With the bindings, you're essentially mixing in functionalities. There are several differences:
- For us, the runtime metaprogramming of mixing in declarations from other modules is statically analyzed and compiled away (see the output), saving us code initiation cost.
- Mixins are statically typed and prevent funny (ab)uses-cases. They're constrained to be easy to understand.
- Since the mixins aren't provided by Rehydrate proper, there's no library-specific learning overhead/magic mixin behavior (e.g. React.createClass's mixin will merge/override/warn in certain mixin properties).
