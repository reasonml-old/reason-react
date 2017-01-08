/**
 * ReactRe.
 * vim: set ft=rust:
 * vim: set ft=reason:
 */
/* ============================================ some types */
type reactClass;

type reactElement;

/* TODO: (chenglou) type event better */
type event =
  Js.t {
    .
    charCode : int,
    keyCode : int,
    which : int,
    stopPropagation : (unit => unit) [@bs.meth],
    preventDefault : (unit => unit) [@bs.meth],
    currentTarget : ReasonJs.Document.element,
    relatedTarget : ReasonJs.Document.element,
    target : ReasonJs.Document.element
  };

type reactRef;

type reactChildren;

external createElement : reactClass => props::Js.t {..}? => array reactElement => reactElement = "createElement" [@@bs.splice] [@@bs.val] [@@bs.module
                                                                    "react"
                                                                    ];

external createClassInternalHack : Js.t 'classSpec => reactClass = "createClass" [@@bs.val] [@@bs.module
                                                                    "react"
                                                                    ];

external createCompositeElementInternalHack : reactClass =>
                                              Js.t {.. reasonProps : 'props} =>
                                              array reactElement =>
                                              reactElement = "createElement" [@@bs.val] [@@bs.module
                                                                    "react"
                                                                    ] [@@bs.splice];

external nullElement : reactElement = "null" [@@bs.val];

external stringToElement : string => reactElement = "%identity";

external arrayToElement : array reactElement => reactElement = "%identity";

external refToJsObj : reactRef => Js.t {..} = "%identity";

external classToJsObj : reactClass => Js.t {..} = "%identity";

/* We wrap the props for reason->reason components, as a marker that "these props were passed from another
   reason component" */
let wrapPropsInternal
    comp
    props
    wrapPropsHow
    ::children
    ref::(ref: option (reactRef => unit))=?
    key::(key: option string)=?
    () => {
  let ref =
    switch ref {
    | None => Js.Undefined.empty
    | Some ref => Js.Undefined.return ref
    };
  let key =
    switch key {
    | None => Js.Undefined.empty
    | Some key => Js.Undefined.return key
    };
  let props = wrapPropsHow ::props ::ref ::key;
  switch children {
  | [] => createCompositeElementInternalHack comp props [||]
  | [a] => createCompositeElementInternalHack comp props [|a|]
  | [a, b] => createCompositeElementInternalHack comp props [|a, b|]
  | [a, b, c] => createCompositeElementInternalHack comp props [|a, b, c|]
  | [a, b, c, d] => createCompositeElementInternalHack comp props [|a, b, c, d|]
  | [a, b, c, d, e] => createCompositeElementInternalHack comp props [|a, b, c, d, e|]
  | [a, b, c, d, e, f] => createCompositeElementInternalHack comp props [|a, b, c, d, e, f|]
  | [a, b, c, d, e, f, g] => createCompositeElementInternalHack comp props [|a, b, c, d, e, f, g|]
  | [a, b, c, d, e, f, g, h] =>
    createCompositeElementInternalHack comp props [|a, b, c, d, e, f, g, h|]
  | [a, b, c, d, e, f, g, h, i] =>
    createCompositeElementInternalHack comp props [|a, b, c, d, e, f, g, h, i|]
  | [a, b, c, d, e, f, g, h, i, j] =>
    createCompositeElementInternalHack comp props [|a, b, c, d, e, f, g, h, i, j|]
  | [a, b, c, d, e, f, g, h, i, j, k] =>
    createCompositeElementInternalHack comp props [|a, b, c, d, e, f, g, h, i, j, k|]
  | [a, b, c, d, e, f, g, h, i, j, k, l] =>
    createCompositeElementInternalHack comp props [|a, b, c, d, e, f, g, h, i, j, k, l|]
  | [a, b, c, d, e, f, g, h, i, j, k, l, m] =>
    createCompositeElementInternalHack comp props [|a, b, c, d, e, f, g, h, i, j, k, l, m|]
  | [a, b, c, d, e, f, g, h, i, j, k, l, m, n] =>
    createCompositeElementInternalHack comp props [|a, b, c, d, e, f, g, h, i, j, k, l, m, n|]
  | _ =>
    raise (
      Invalid_argument "Reason allows up to 14 static children (dynamic children can be unlimited in size); If you have more, please put them in an array and assign key to the elements. Sorry for the inconvenience!"
    )
  }
};

let wrapPropsAndPutIndicatorThatItComesFromReason =
  (fun ::props ::ref ::key => {"reasonProps": props, "ref": ref, "key": key}) [@bs];

external object_ : _ = "Object" [@@bs.val];

let wrapPropsAndPutRefAndKey =
  (fun ::props ::ref ::key => object_##assign [%bs.raw "{}"] props {"ref": ref, "key": key}) [@bs];

/* Array.isArray is es2015 */
let isArrayPolyfill: (Obj.t => Js.boolean) [@bs] = [%bs.raw
  "function(a) {return Object.prototype.toString.call(a) === '[object Array]'}"
];

let jsToReasonChildren (children: Js.null_undefined reactChildren) :list reactElement =>
  switch (Js.Null_undefined.to_opt children) {
  | None => []
  | Some children =>
    if (Js.to_bool (isArrayPolyfill (Obj.magic children) [@bs])) {
      Array.to_list (Obj.magic children)
    } else {
      [Obj.magic children]
    }
  };

let rec findFirstCallback callbacks callback =>
  switch callbacks {
  | [(cb, memorized), ...rest] when cb === callback => Some memorized
  | [_, ...rest] => findFirstCallback rest callback
  | [] => None
  };

type jsState 'state = Js.t {. mlState : 'state};

module CommonLifecycle = {
  let componentDidMount _ => None;
  let componentDidUpdate _ _ _ => None;
  let componentWillReceiveProps _ _ => None;
  let componentWillUnmount _ => ();
};

module ComponentBase = {
  type componentBag 'state 'props 'instanceVars = {
    state: 'state,
    props: 'props,
    updater:
      'dataPassedToHandler .
      ('dataPassedToHandler => componentBag 'state 'props 'instanceVars => option 'state) =>
      'dataPassedToHandler =>
      unit,

    refSetter: (reactRef => componentBag 'state 'props 'instanceVars => unit) => reactRef => unit,
    instanceVars: 'instanceVars,
    /**
     * Work in progress / prototype API for setState. This isn't sufficient for
     * every use case and there is some overlap with updater. In a world
     * without `this`, it is even more important that `setState` accept a
     * callback. With `ReactJS`, absence of the callback form often relies on
     * trapping `this` in scope, and relies on the fact that
     * `this.state`/`this.props` will be mutated to have the new
     * `state`/`props` on `this`. Still, this `setState` API doesn't do
     * everything we wish so it will likely change.
     */
    setState: (componentBag 'state 'props 'instanceVars => 'state) => unit
  };
  type jsComponentThis 'state 'props 'instanceVars =
    Js.t {
      .
      state : jsState 'state,
      props : Obj.t,
      setState : ((jsState 'state => 'props => jsState 'state) => unit) [@bs.meth]
    };
  include CommonLifecycle;
};

module Component = {
  include ComponentBase;
  type jsProps = unit;
  type instanceVars = unit;
  type state = unit;
  let getInstanceVars () => ();
  let jsPropsToReasonProps = None;
  let getInitialState _ => ();
  module Stateful = {
    include ComponentBase;
    type jsProps = unit;
    type instanceVars = unit;
    let getInstanceVars () => ();
    let jsPropsToReasonProps = None;
    module JsProps = {
      include ComponentBase;
      type instanceVars = unit;
      let getInstanceVars () => ();
      let jsPropsToReasonProps = None;
    };
    module InstanceVars = {
      include ComponentBase;
      type jsProps = unit;
      let jsPropsToReasonProps = None;
      module JsProps = {
        include ComponentBase;
      };
    };
  };
  module JsProps = {
    include ComponentBase;
    type instanceVars = unit;
    type state = unit;
    let getInstanceVars () => ();
    let getInitialState _ => ();
  };
  module InstanceVars = {
    include ComponentBase;
    type jsProps = unit;
    type state = unit;
    let getInitialState _ => ();
    let jsPropsToReasonProps = None;
    module JsProps = {
      include ComponentBase;
      type state = unit;
      let getInitialState _ => ();
    };
  };
};

module type CompleteComponentSpec = {
  let name: string;
  type props;
  type state;
  type instanceVars;
  type jsProps;
  let getInstanceVars: unit => instanceVars;
  let getInitialState: props => state;

  /**
   * TODO: Preallocate a "returnNone", and then at runtime check for reference
   * equality to this function and avoid even invoking it.
   */
  let componentDidMount: Component.componentBag state props instanceVars => option state;
  let componentWillReceiveProps:
    props => Component.componentBag state props instanceVars => option state;
  let componentDidUpdate:
    props => state => Component.componentBag state props instanceVars => option state;
  let componentWillUnmount: Component.componentBag state props instanceVars => unit;
  let jsPropsToReasonProps: option (jsProps => props);
  let render: Component.componentBag state props instanceVars => reactElement;
};

module type ReactComponent = {
  type props_;
  let comp: reactClass;
  let wrapProps:
    props_ =>
    children::list reactElement =>
    ref::(reactRef => unit)? =>
    key::string? =>
    unit =>
    reactElement;
};

module CreateComponent
       (CompleteComponentSpec: CompleteComponentSpec)
       :(ReactComponent with type props_ = CompleteComponentSpec.props) => {
  type props_ = CompleteComponentSpec.props;
  /* This part is the secret sauce that briges to Reactjs. It's a bit verbose (but consistentt) right now; We'll
     find a way to make it shorter in the future. */
  let convertPropsIfTheyreFromJs props => {
    let props = Obj.magic props;
    switch (Js.Undefined.to_opt props##reasonProps, CompleteComponentSpec.jsPropsToReasonProps) {
    | (Some props, _) => props
    /* TODO: annotate with BS to avoid curry overhead */
    | (None, Some toReasonProps) => toReasonProps props
    | (None, None) =>
      raise (
        Invalid_argument (
          "A JS component called the Reason component " ^
          CompleteComponentSpec.name ^ " which didn't implement the JS->Reason React props conversion"
        )
      )
    }
  };
  type jsComponentThis_ =
    ComponentBase.jsComponentThis
      CompleteComponentSpec.state CompleteComponentSpec.props CompleteComponentSpec.instanceVars;
  let comp =
    createClassInternalHack (
      {
        val displayName = CompleteComponentSpec.name;
        val mutable instanceVars = None;
        val mutable memoizedUpdaterCallbacks = [];
        val mutable memoizedRefCallbacks = [];
        pub getInitialState () :jsState CompleteComponentSpec.state => {
          let that: jsComponentThis_ = [%bs.raw "this"];
          let props = convertPropsIfTheyreFromJs that##props;
          let state = CompleteComponentSpec.getInitialState props;
          this##instanceVars#=(Some (CompleteComponentSpec.getInstanceVars ()));
          {"mlState": state}
        };
        pub componentDidMount () => {
          let that: jsComponentThis_ = [%bs.raw "this"];
          let instanceVars =
            switch this##instanceVars {
            | None =>
              raise (Invalid_argument "ReactRe component: instanceVars somehow isn't initialized.")
            | Some s => s
            };
          let currState = that##state##mlState;
          let newState =
            CompleteComponentSpec.componentDidMount {
              props: convertPropsIfTheyreFromJs that##props,
              state: currState,
              instanceVars,
              updater: Obj.magic this##updaterMethod,
              refSetter: Js_unsafe.js_method_run1 this##refSetterMethod,
              setState: Js_unsafe.js_method_run1 this##setStateMethod
            };
          switch newState {
          | None => ()
          | Some state => that##setState (fun _ _ => {"mlState": state})
          }
        };
        pub componentDidUpdate prevProps prevState => {
          let that: jsComponentThis_ = [%bs.raw "this"];
          let instanceVars =
            switch this##instanceVars {
            | None =>
              raise (Invalid_argument "ReactRe component: instanceVars somehow isn't initialized.")
            | Some s => s
            };
          let currState = that##state##mlState;
          let newState =
            CompleteComponentSpec.componentDidUpdate
              (convertPropsIfTheyreFromJs prevProps)
              prevState##mlState
              {
                props: convertPropsIfTheyreFromJs that##props,
                state: currState,
                instanceVars,
                updater: Obj.magic this##updaterMethod,
                refSetter: Js_unsafe.js_method_run1 this##refSetterMethod,
                setState: Js_unsafe.js_method_run1 this##setStateMethod
              };
          switch newState {
          | None => ()
          | Some state => that##setState (fun _ _ => {"mlState": state})
          }
        };
        pub componentWillReceiveProps nextProps => {
          let that: jsComponentThis_ = [%bs.raw "this"];
          let instanceVars =
            switch this##instanceVars {
            | None =>
              raise (Invalid_argument "ReactRe component: instanceVars somehow isn't initialized.")
            | Some s => s
            };
          let currState = that##state##mlState;
          let newState =
            CompleteComponentSpec.componentWillReceiveProps
              (convertPropsIfTheyreFromJs nextProps)
              {
                props: convertPropsIfTheyreFromJs that##props,
                state: currState,
                instanceVars,
                updater: Obj.magic this##updaterMethod,
                refSetter: Js_unsafe.js_method_run1 this##refSetterMethod,
                setState: Js_unsafe.js_method_run1 this##setStateMethod
              };
          switch newState {
          | None => ()
          | Some state => that##setState (fun _ _ => {"mlState": state})
          }
        };
        pub componentWillUnmount () => {
          let that: jsComponentThis_ = [%bs.raw "this"];
          let instanceVars =
            switch this##instanceVars {
            | None =>
              raise (Invalid_argument "ReactRe component: instanceVars somehow isn't initialized.")
            | Some s => s
            };
          let currState = that##state##mlState;
          CompleteComponentSpec.componentWillUnmount {
            props: convertPropsIfTheyreFromJs that##props,
            state: currState,
            instanceVars,
            updater: Obj.magic this##updaterMethod,
            refSetter: Js_unsafe.js_method_run1 this##refSetterMethod,
            setState: Js_unsafe.js_method_run1 this##setStateMethod
          }
        };
        pub refSetterMethod callback =>
          switch (findFirstCallback this##memoizedRefCallbacks callback) {
          | Some memoized => memoized
          | None =>
            let that: jsComponentThis_ = [%bs.raw "this"];
            let memoizedCallback (theRef: reactRef) => {
              let instanceVars =
                switch this##instanceVars {
                | None =>
                  raise (
                    Invalid_argument "ReactRe component: instanceVars somehow isn't initialized."
                  )
                | Some s => s
                };
              let currState = that##state##mlState;
              callback
                theRef
                {
                  Component.props: convertPropsIfTheyreFromJs that##props,
                  state: currState,
                  instanceVars,
                  updater: Obj.magic this##updaterMethod,
                  refSetter: Js_unsafe.js_method_run1 this##refSetterMethod,
                  setState: Js_unsafe.js_method_run1 this##setStateMethod
                }
            };
            this##memoizedRefCallbacks#=[
                                          (callback, memoizedCallback),
                                          ...this##memoizedRefCallbacks
                                        ];
            memoizedCallback
          };
        pub setStateMethod cb => {
          let that: jsComponentThis_ = [%bs.raw "this"];

          /**
           * Makes sense to adapt the API to the Reason API where you are often
           * passed the entire bag for every lifecycle/callback.
           */
          that##setState (
            fun prevState props => {
              let instanceVars =
                switch this##instanceVars {
                | None =>
                  raise (
                    Invalid_argument "ReactRe component: instanceVars somehow isn't initialized."
                  )
                | Some s => s
                };
              let bag = {
                Component.props: convertPropsIfTheyreFromJs props,
                state: prevState##mlState,
                instanceVars,
                updater: Obj.magic this##updaterMethod,
                refSetter: Js_unsafe.js_method_run1 this##refSetterMethod,
                setState: Js_unsafe.js_method_run1 this##setStateMethod
              };
              {"mlState": cb bag}
            }
          )
        };
        pub updaterMethod callback =>
          switch (findFirstCallback this##memoizedUpdaterCallbacks callback) {
          | Some memoized => memoized
          | None =>
            let that: jsComponentThis_ = [%bs.raw "this"];
            let memoizedCallback event => {
              let instanceVars =
                switch this##instanceVars {
                | None =>
                  raise (
                    Invalid_argument "ReactRe component: instanceVars somehow isn't initialized."
                  )
                | Some s => s
                };
              let currState = that##state##mlState;
              let newState =
                callback
                  event
                  {
                    Component.props: convertPropsIfTheyreFromJs that##props,
                    state: currState,
                    instanceVars,
                    updater: Obj.magic this##updaterMethod,
                    refSetter: Js_unsafe.js_method_run1 this##refSetterMethod,
                    setState: Js_unsafe.js_method_run1 this##setStateMethod
                  };
              switch newState {
              | None => ()
              | Some state => that##setState (fun _ _ => {"mlState": state})
              }
            };
            this##memoizedUpdaterCallbacks#=[
                                              (callback, memoizedCallback),
                                              ...this##memoizedUpdaterCallbacks
                                            ];
            memoizedCallback
          };
        pub render () => {
          let that: jsComponentThis_ = [%bs.raw "this"];
          let instanceVars =
            switch this##instanceVars {
            | None =>
              raise (Invalid_argument "ReactRe component: instanceVars somehow isn't initialized.")
            | Some s => s
            };
          CompleteComponentSpec.render {
            props: convertPropsIfTheyreFromJs that##props,
            state: that##state##mlState,
            instanceVars,
            updater: Obj.magic this##updaterMethod,
            refSetter: Js_unsafe.js_method_run1 this##refSetterMethod,
            setState: Js_unsafe.js_method_run1 this##setStateMethod
          }
        }
      }
      [@bs]
    );
  /* fully apply this to avoid currying overhead */
  let wrapProps (props: props_) ::children ::ref=? ::key=? () =>
    wrapPropsInternal
      comp props wrapPropsAndPutIndicatorThatItComesFromReason ::children ::?key ::?ref ();
};

/* fully apply this to avoid currying overhead */
let wrapPropsShamelessly comp (props: Js.t {..}) ::children ::ref=? ::key=? () =>
  wrapPropsInternal comp props wrapPropsAndPutRefAndKey ::children ::?ref ::?key ();
