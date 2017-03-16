__This documentation assumes relative familiarity with ReactJS.__

If reading a linear doc bores you, try this [alternative tutorial](https://github.com/glennsl/reason-react-quick-start/blob/master/quick-start.md)!

## JSX

The JSX ppx transform resides in the Reason repo itself. The documentation is [here](https://github.com/facebook/reason/tree/master/src#jsx-transform-for-reactjs).

## Bindings Usage

### "component bag"

Reason-React's uses idiomatic Reason/OCaml modules to get rid of ReactJS' `this`, a common pain point for ReactJS newcomers. To fulfill the same role, relevant functions (they're not methods; just regular functions!) accept as argument a `componentBag` record of shape `{props, state, updater, refSetter, instanceVars, setState}`. A render would look like:

```reason
/* normal record destructuring. Pick what you need! */
let render {props, state} => <div className=props.className>(ReactRe.stringToElement state.message)</div>
```

#### `props`, `state`
Same as ReactJS'.

#### `updater`
The secret sauce function that wraps every callback handler. The ReactJS `<div onClick={this.handleClick} />` becomes `<div onClick=(updater handleClick) />`. `updater` takes in your familiar callback and returns a new (memoized) callback that'll give you the up-to-date "component bag" (props, state and other values) when the callback is called, and ensures that the component state is appropriately updated after the callback. Example:

```reason
/* `props` is up-to-date here, even though onClick is asynchronously triggered. The same goes for other component bag values */
let handleClick {props} event => {Js.log "clicked!"; None};
let render {props, updater} => <div onClick=(updater handleClick) />;
```

The return type is `option state`, where you indicate whether the handler needs to trigger a state update or not.

##### Note

`updater` memoize up to 30 callbacks.

In Reason-React, and likewise in ReactJS, when you do `<Foo onClick=(fun () => 1) />` inside `render`, you're creating a new, inline function each time and passing it down to `Foo`'s `onClick`. If `Foo` implemented [shouldComponentUpdate](https://facebook.github.io/react/docs/react-component.html#shouldcomponentupdate), you'd accidentally cause its `shouldComponentUpdate` to return `true` every time (since `props.onClick !== nextProps.onClick`). This has been avoided largely because in ReactJS, people did `<Foo onClick={this.handleClick} />`, which keeps pointing to the same reference (thus `props.onClick === nextProps.onClick` in `Foo`).

But in Reason-React, since you need to wrap your handler in `updater`, we need to make sure that for each `myHandlerReference`, we return the same reference if `(updater myHandlerReference)` has been called before (in other words: `updater myHandlerReference === updater myHandlerReference`). We achieve this by storing `myHandlerReference` in a collection internally, and finding it the next time it's passed to us. To avoid memory leaks (in case people mistakenly inline the handler through `updater (fun () => ...)` and the `render`'s called again and again).

#### `refSetter`
Like `updater` but for ref:

```reason
/* this type will be explained later */
type instanceVars = {mutable divRef: option ReactRe.reactRef};
let getInstanceVars () => {divRef: None};
let getRef componentBag theRef => componentBag.instanceVars.divRef = Some theRef;
let render {props, refSetter} => <div ref=(refSetter getRef) />;
```

Reason-React ref only accept callbacks. The string `ref` from ReactJS is a deprecated feature, which couldn't be easily removed due to the lack of types in JS.

We also expose an escape hatch `ReactRe.refToJsObj` (type: `ReactRe.reactRef => Js.t {..}`) which turns your ref into a JS object you can freely use; **this is only used to access ReactJS component class methods**.

```reason
let callSomethingDangerous componentBag =>
  switch componentBag.instanceVars.theRef {
  | None => ()
  | Some r => (ReactRe.refToJsObj r)##someMethod 1 2 3
  };
```

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
**Different use-cases than ReactJS' `setState`**! Since lifecycle events (below) and handlers return an `option state`, this `setState` API is rarely used and only serves as an escape hatch when you know what you're doing.

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

### Component API

The component API uses OCaml's module system rather than our own `createClass`-like API (less APIs!). **All you need to know about modules is [here](http://facebook.github.io/reason/modules.html)**.

See the `examples/` folder. The components declaration structure should look quite familiar to those who've worked with ReactJS. To declare a React component class, you'd create a normal OCaml module and include some pre-declared module definitions. Here's the basic version:

```reason
/* This is like the object declaration part of RaectJS' `React.createClass(theObjectSpec)` */
module MyComponent = {
  include ReactRe.Component.Stateful;
  let name = "MyComponent";
  type props = {
    foo: string,
    bar: option int,
  };
  /*...*/
};

/* This is the equivalent of `React.createClass` */
include ReactRe.CreateComponent MyComponent;

/* The actual call exposed to consumers, via JSX */
let createElement ::foo ::bar=? => wrapProps {foo, bar};
```

#### Last Two Expressions

##### `include ReactRe.CreateComponent MyComponent`

`ReactRe.CreateComponent` takes in the declared MyComponent and returns a new module containing `comp` (for JS interop, described later) and `wrapProps`. You need to expose these two by `include`-ing this returned module, aka "spread" the two definitions into the current file.

##### 'createElement'

`createElement` exposes the call used by the JSX sugar described at the beginning. From another module, you'd be able to call `MyComponent.createElement ...` or use the JSX sugar (remember that Reason JSX desugars `<MyComponent foo="hi" />` to `MyComponent.createElement foo::"hi" children::[] ()`).

`wrapProps` creates the bindings magic; it takes a props record that you've constructed from the arguments, and **curries `children`, `ref` and `key` for you**! So the whole call is actually:

```reason
let createElement ::foo ::bar=? ::children ::ref=? key=? () => wrapProps {foo, bar} ::children ::ref=? key=? ();
```

But since we have currying, this can simply to:

```reason
let createElement ::foo ::bar=? => wrapProps {foo, bar};
```

Now components don't have to worry about declaring `ref` and `key` in `createElement`! If their props actually need to read into `children`, then simply uncurry that (aka, add `::children` to **both** sides of the expression!):

```reason
let createElement ::foo ::bar=? ::children => wrapProps {foo, bar, children} ::children;
```

Note that Reason functions can have default values and be optional. This maps well to ReactJS' defaultProps and optional props. There's no (need for a) special Reason-React API for these use-cases. `::bar=?` means `bar` is an `option whateverTypeBarIs`.

**Tips: if your component doesn't accept any prop**:

```reason
/*...*/
type props = unit;
/*...*/
let createElement = wrapProps ()
```

#### The Module Itself

For the `MyComponent` module, you'd mix in one of the pre-declared definitions under `ReactRe.Component.*`:

```reason
module MyComponent = {
  include ReactRe.Component.Stateful.JsProps;
  let name = "MyComponent";
  /*...*/
};
```

Including such definition allows you to provide the associated functions & types. As of today, the most fully-featured component spec is `Stateful.InstanceVars.JsProps` (a stateful component, that allows attaching instance properties, and that can be called as JSX from JS). You can omit any of the three, but the order should be kept, e.g. `include ReactRe.Component.Stateful.JsProps` works but `include ReactRe.Component.JsProps.Stateful` doesn't.

##### Nothing (just `ReactRe.Component`)
The default. Stateless component. You need to provide:
- `name`, the string name of your component, for tooling purposes, e.g. [React devtools](https://github.com/facebook/react-devtools).
- `props`, the type of the component's props, preferably a record, or `unit` if no props.
- `render`, your render function! It takes in the `componentBag` record, described earlier. In the case of the `React.Component`, only `props` and `updater` are relevant.

##### Stateful
In addition to the default component definitions, this one also asks you to provide:
- `state`, the type of your state, preferably a record.
- `getInitialState`, a function that takes the initial `props` (which you can ignore) and returns the initial `state`.

##### InstanceVars
In addition to the default component definitions, add:
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
  let getInstanceVars () => {timeoutID: None, subscription1: None};
  let componentDidMount componentBag => {componentBag.instanceVars.timeoutID = Some (setIntervalBinding bla); None}; /* lifecycle events need to return `option state` */
  ```

##### JsProps
Add:
- `jsProps`, the type of the props passed to you from the JS side, which should be `Js.t {. whatever: here}`, like so:

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

On the JS side, you can require your component like so:

```js
var ReasonComponent = require('reasonComponent').comp;
// make sure you're passing the correct data types!
<ReasonComponent message="hello" />
```

Every Reason-React component expose a `comp` value, implicitly, when doing `include ReactRe.CreateComponent MyComponentModule;`. This is mentioned [here](#include-reactrecreatecomponent-mycomponent).

### Interop With Existing JavaScript Components
While it's nice to marvel at OCaml's great type system, Reason-React's slick API, BuckleScript's mind-blowing idiomatic output, our toolchain's superb static analysis, etc., it's unpragmatic to suddenly convert over all existing JS components to Reason. We've exposed simple hooks to talk to the JS components.

#### ReactJS Using Reason-React
See [jsProps](#jsprops).

#### Reason-React Using ReactJs
We only need a single hook, `wrapPropsShamelessly` to make calling a JS component work! Assuming we have `Banner.js`, here's how we'd use it in Reason:

```reason
/* bannerRe.re */
external foo : ReactRe.reactClass = "Banner" [@@bs.module];

/* this is the call that takes in Reason data and converts it to JS data. Make sure you get the conversion right! JS won't warn you of type errors... */
let createElement
    className::(className: option string)=?
    show::(show: bool)
    onClick::(onClick: ReactRe.event => unit) =>
  ReactRe.wrapPropsShamelessly
    foo
    {
      /* turn an option string into a js nullable string */
      "className": Js.Null_undefined.from_opt className,
      /* turn a mandatory bool into a js boolean */
      "show": Js.Bool.to_js_boolean show,
      /* this stays the same, in BuckleScript and in JS */
      "onClick": onClick
    };
```

Usage:

```reason
/* myApp.re */
/* ... */
<Foo show=true onClick=(updater handleClick) />
<Foo className="hello" show=true onClick=(updater handleClick) />
```

That's pretty much it!

### Working with Children

ReactJS' children are a bit "loose" and don't type well. Reason-React components `children` are always `list ReactRe.reactElement`. E.g. the JS code `<Foo>hello</Foo>` needs to be `<Foo>(ReactRe.stringToElement "hello")</Foo>` in Reason-React.

What can be a `reactElement`?

- The DOM components from `ReactDOMRe.createElement` (JSX sugar: `<div />`, `<span />` and the rest).
- The components from `ReactRe.createElement` (JSX sugar: `<Foo />`).
- String, but only through `ReactRe.stringToElement myString`.
- The null element, `ReactRe.nullElement` (BuckleScript's `Js.null` won't work).
- `array ReactRe.reactElement`, but only through `ReactRe.arrayToElement myArray`.
- `list ReactRe.reactElement`, a helper implemented as `ReactRe.arrayToElement (Array.of_list myList)`

ReactJS children must be typed as `Js.null_undefined ReactRe.reactJsChildren`. They can be converted into a `list ReactRe.reactElement` with `ReactRe.jsChildrenToReason myJSChildren`;

To pass Reason-React children to the JS side, do a conversion, e.g. `<div> (ReactRe.arrayToElement (Array.of_list props.children)) </div>`

See also the section on [createElement](#createelement).

### Working with Events

React events should be typed as ReactRe.event. The [interface file](https://github.com/reasonml/reason-react/blob/master/src/reactRe.rei) has the event's shape.

```reason
let handleMouseDown componentBag event => {
  event##stopPropagation ();
  doSomethingElse ()
};
```

### Miscellaneous

- Reason-React doesn't support ReactJS context (yet).
- No mixins/yes mixins =). OCaml's `include` is actually a form of mixin! With the bindings, you're essentially mixing in functionalities. There are several differences:
- For us, the runtime metaprogramming of mixing in declarations from other modules is statically analyzed and compiled away (see the output), saving us code initiation cost.
- Mixins are statically typed and prevent funny (ab)uses-cases. They're constrained to be easy to understand.
- Since the mixins aren't provided by Reason-React proper, there's no library-specific learning overhead/magic mixin behavior (e.g. React.createClass's mixin will merge/override/warn in certain mixin properties).
