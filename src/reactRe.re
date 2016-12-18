/* ============================================ some types */
type reactClass;

type reactElement;

/* TODO: (chenglou) type event */
type event;

type reactRef;

type reactChildren;

external createDOMElement : string => Js.null (Js.t {..}) => array reactElement => reactElement = "createElement" [@@bs.splice] [@@bs.val] [@@bs.module
                                                                    "react"
                                                                    ];

external createCompositeElement : reactClass => Js.null (Js.t {..}) => array reactElement => reactElement = "createElement" [@@bs.splice] [@@bs.val] [@@bs.module
                                                                    "react"
                                                                    ];

/* ================================================== old api, don't use */
external createClass : Js.t 'classSpec => reactClass = "createClass" [@@bs.val] [@@bs.module "react"];

external getProps : 'this => 'reactJsProps = "props" [@@bs.get];

external getState : 'this => 'reactJsState = "state" [@@bs.get];

external setState : 'this => 'state => unit = "setState" [@@bs.send];

external getRefs : 'this => 'refs = "refs" [@@bs.get];

module PropTypes = {
  type propType;
  external isRequired : propType => propType = "isRequired" [@@bs.get];
  external string : propType = "React.PropTypes.string" [@@bs.val];
  external bool : propType = "React.PropTypes.bool" [@@bs.val];
  external number : propType = "React.PropTypes.number" [@@bs.val];
  external object_ : propType = "React.PropTypes.object" [@@bs.val];
  external symbol : propType = "React.PropTypes.symbol" [@@bs.val];
  external any : propType = "React.PropTypes.any" [@@bs.val];
  external node : propType = "React.PropTypes.node" [@@bs.val];
  external oneOfType : array propType => propType = "React.PropTypes.oneOfType" [@@bs.val];
  external oneOf : array string => propType = "React.PropTypes.oneOf" [@@bs.val];
  external element : propType = "React.PropTypes.element" [@@bs.val];
  external func : propType = "React.PropTypes.func" [@@bs.val];
  external objectOf : propType => propType = "React.PropTypes.objectOf" [@@bs.val];
  external arrayOf : propType => propType = "React.PropTypes.arrayOf" [@@bs.val];
  external instanceOf : propType => propType = "React.PropTypes.instanceOf" [@@bs.val];
  external shape : Js.t 'shape => propType = "React.PropTypes.shape" [@@bs.val];
};

/* ================================================== old api, don't use */
external createCompositeElementInternalHack : reactClass =>
                                              Js.t {.. reasonProps : 'props} =>
                                              array reactElement =>
                                              reactElement = "createElement" [@@bs.val] [@@bs.module "react"] [@@bs.splice];

external nullElement : reactElement = "null" [@@bs.val];

external toElement : _ => reactElement = "%identity";

external refToJsObj : reactRef => Js.t {..} = "%identity";

external classToJsObj : reactClass => Js.t {..} = "%identity";

/* We wrap the props for reason->reason components, as a marker that "these props were passed from another
   reason component" */
let wrapPropsInternal
    ::comp
    props
    children
    ref::(ref: option (reactRef => unit))=?
    key::(key: option string)=?
    () => {
  let refValue =
    switch ref {
    | None => Js.Undefined.empty
    | Some ref => Js.Undefined.return ref
    };
  let keyValue =
    switch key {
    | None => Js.Undefined.empty
    | Some key => Js.Undefined.return key
    };
  let props = {"reasonProps": props, "ref": refValue, "key": keyValue};
  switch children {
  | [] => createCompositeElementInternalHack comp props [||]
  | [a] => createCompositeElementInternalHack comp props [|a|]
  | [a, b] => createCompositeElementInternalHack comp props [|a, b|]
  | [a, b, c] => createCompositeElementInternalHack comp props [|a, b, c|]
  | [a, b, c, d] => createCompositeElementInternalHack comp props [|a, b, c, d|]
  | [a, b, c, d, e] => createCompositeElementInternalHack comp props [|a, b, c, d, e|]
  | [a, b, c, d, e, f] => createCompositeElementInternalHack comp props [|a, b, c, d, e, f|]
  | [a, b, c, d, e, f, g] => createCompositeElementInternalHack comp props [|a, b, c, d, e, f, g|]
  | [a, b, c, d, e, f, g, h] => createCompositeElementInternalHack comp props [|a, b, c, d, e, f, g, h|]
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

type jsComponentThis 'state 'props =
  Js.t {. state : jsState 'state, props : Obj.t, setState : (jsState 'state => unit) [@bs.meth]};

module ComponentBase = {
  type componentBag 'state 'props 'instanceVariables = {
    state: 'state,
    props: 'props,
    updater:
      'dataPassedToHandler .
      ('dataPassedToHandler => componentBag 'state 'props 'instanceVariables => option 'state) =>
      'dataPassedToHandler =>
      unit,

    refSetter: (reactRef => componentBag 'state 'props 'instanceVariables => unit) => reactRef => unit,
    instanceVariables: 'instanceVariables
  };
};

module Component = {
  include ComponentBase;
  type jsPropTypes = unit;
  type instanceVariables = unit;
  type nonrec jsComponentThis 'props = jsComponentThis unit 'props;
  let getInstanceVariables () => ();
  let componentDidMount _ => None;
  /* let shouldComponentUpdate _ _ => true; */
  let componentDidUpdate _ _ _ => None;
  let componentWillReceiveProps _ _ => None;
  let componentWillUnmount _ => ();
  let jsPropsToReasonProps = None;
};

module ComponentJs = {
  include ComponentBase;
  type instanceVariables = unit;
  type nonrec jsComponentThis 'props = jsComponentThis unit 'props;
  let getInstanceVariables () => ();
  let componentDidMount _ => None;
  /* let shouldComponentUpdate _ _ => true; */
  let componentDidUpdate _ _ _ => None;
  let componentWillReceiveProps _ _ => None;
  let componentWillUnmount _ => ();
  let jsPropsToReasonProps = None;
};

module StatelessComponent = {
  include ComponentBase;
  type jsPropTypes = unit;
  type state = unit;
  type instanceVariables = unit;
  type jsComponentThis 'props = Js.t {. props : Obj.t};
  let getInstanceVariables () => ();
  let getInitialState _ => ();
  let componentDidMount _ => None;
  /* let shouldComponentUpdate _ _ => true; */
  let componentDidUpdate _ _ _ => None;
  let componentWillReceiveProps _ _ => None;
  let componentWillUnmount _ => ();
  let jsPropsToReasonProps = None;
};

module StatelessComponentJs = {
  include ComponentBase;
  type state = unit;
  type instanceVariables = unit;
  type jsComponentThis 'props = Js.t {. props : Obj.t};
  let getInstanceVariables () => ();
  let getInitialState _ => ();
  let componentDidMount _ => None;
  /* let shouldComponentUpdate _ _ => true; */
  let componentDidUpdate _ _ _ => None;
  let componentWillReceiveProps _ _ => None;
  let componentWillUnmount _ => ();
  let jsPropsToReasonProps = None;
};


/**
 * Ironically, this mixin doesn't include type instanceVariables.
 */
module ComponentWithInstanceVariable = {
  type nonrec jsComponentThis 'props = jsComponentThis unit 'props;
  let getInstanceVariables () => ();
  let componentDidMount _ => None;
  /* let shouldComponentUpdate _ _ => true; */
  let componentDidUpdate _ _ _ => None;
  let componentWillReceiveProps _ _ => None;
  let componentWillUnmount _ => ();
  let jsPropsToReasonProps = None;
};

module type CompleteComponentSpec = {
  let name: string;
  type props;
  type state;
  type instanceVariables;
  type jsPropTypes;
  let getInstanceVariables: unit => instanceVariables;
  let getInitialState: props => state;

  /**
   * TODO: Preallocate a "returnNone", and then at runtime check for reference
   * equality to this function and avoid even invoking it.
   */
  let componentDidMount: Component.componentBag state props instanceVariables => option state;
  let componentWillReceiveProps:
    props => Component.componentBag state props instanceVariables => option state;
  let componentDidUpdate:
    props => state => Component.componentBag state props instanceVariables => option state;
  let componentWillUnmount: Component.componentBag state props instanceVariables => unit;
  let jsPropsToReasonProps: option (jsPropTypes => props);
  let render: Component.componentBag state props instanceVariables => reactElement;
};

module type ReactComponent = {
  type props_;
  let comp: reactClass;
  let wrapProps:
    props_ => list reactElement => ref::(reactRef => unit)? => key::string? => unit => reactElement;
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
  let comp =
    createClass (
      {
        val displayName = CompleteComponentSpec.name;
        val mutable instanceVariables = None;
        val mutable memoizedUpdaterCallbacks = [];
        val mutable memoizedRefCallbacks = [];
        pub getInitialState () :jsState CompleteComponentSpec.state => {
          let that: jsComponentThis CompleteComponentSpec.state CompleteComponentSpec.props = [%bs.raw
            "this"
          ];
          let props = convertPropsIfTheyreFromJs that##props;
          let state = CompleteComponentSpec.getInitialState props;
          this##instanceVariables#=(Some (CompleteComponentSpec.getInstanceVariables ()));
          {"mlState": state}
        };
        pub componentDidMount () => {
          let that: jsComponentThis CompleteComponentSpec.state CompleteComponentSpec.props = [%bs.raw
            "this"
          ];
          let instanceVariables =
            switch this##instanceVariables {
            | None =>
              raise (
                Invalid_argument "ReactRe stateful component: instanceVariables somehow isn't initialized."
              )
            | Some s => s
            };
          let currState = that##state##mlState;
          let newState =
            CompleteComponentSpec.componentDidMount {
              props: convertPropsIfTheyreFromJs that##props,
              state: currState,
              instanceVariables,
              updater: Obj.magic this##updaterMethod,
              refSetter: Obj.magic this##refSetterMethod
            };
          switch newState {
          | None => ()
          | Some state => that##setState {"mlState": state}
          }
        };
        pub componentDidUpdate prevProps prevState => {
          let that: jsComponentThis CompleteComponentSpec.state CompleteComponentSpec.props = [%bs.raw
            "this"
          ];
          let instanceVariables =
            switch this##instanceVariables {
            | None =>
              raise (
                Invalid_argument "ReactRe stateful component: instanceVariables somehow isn't initialized."
              )
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
                instanceVariables,
                updater: Obj.magic this##updaterMethod,
                refSetter: Obj.magic this##refSetterMethod
              };
          switch newState {
          | None => ()
          | Some state => that##setState {"mlState": state}
          }
        };
        pub componentWillReceiveProps nextProps => {
          let that: jsComponentThis CompleteComponentSpec.state CompleteComponentSpec.props = [%bs.raw
            "this"
          ];
          let instanceVariables =
            switch this##instanceVariables {
            | None =>
              raise (
                Invalid_argument "ReactRe stateful component: instanceVariables somehow isn't initialized."
              )
            | Some s => s
            };
          let currState = that##state##mlState;
          let newState =
            CompleteComponentSpec.componentWillReceiveProps
              (convertPropsIfTheyreFromJs nextProps)
              {
                props: convertPropsIfTheyreFromJs that##props,
                state: currState,
                instanceVariables,
                updater: Obj.magic this##updaterMethod,
                refSetter: Obj.magic this##refSetterMethod
              };
          switch newState {
          | None => ()
          | Some state => that##setState {"mlState": state}
          }
        };
        pub componentWillUnmount () => {
          let that: jsComponentThis CompleteComponentSpec.state CompleteComponentSpec.props = [%bs.raw
            "this"
          ];
          let instanceVariables =
            switch this##instanceVariables {
            | None =>
              raise (
                Invalid_argument "ReactRe stateful component: instanceVariables somehow isn't initialized."
              )
            | Some s => s
            };
          let currState = that##state##mlState;
          CompleteComponentSpec.componentWillUnmount {
            props: convertPropsIfTheyreFromJs that##props,
            state: currState,
            instanceVariables,
            updater: Obj.magic this##updaterMethod,
            refSetter: Obj.magic this##refSetterMethod
          }
        };
        pub refSetterMethod callback =>
          switch (findFirstCallback this##memoizedRefCallbacks callback) {
          | Some memoized => memoized
          | None =>
            let that: jsComponentThis CompleteComponentSpec.state CompleteComponentSpec.props = [%bs.raw
              "this"
            ];
            let memoizedCallback (theRef: reactRef) => {
              let instanceVariables =
                switch this##instanceVariables {
                | None =>
                  raise (
                    Invalid_argument "ReactRe stateless component: instanceVariables somehow isn't initialized."
                  )
                | Some s => s
                };
              let currState = that##state##mlState;
              callback
                theRef
                {
                  Component.props: convertPropsIfTheyreFromJs that##props,
                  state: currState,
                  instanceVariables,
                  updater: Obj.magic this##updaterMethod,
                  refSetter: Obj.magic this##refSetterMethod
                }
            };
            this##memoizedRefCallbacks#=[(callback, memoizedCallback), ...this##memoizedRefCallbacks];
            memoizedCallback
          };
        pub updaterMethod callback =>
          switch (findFirstCallback this##memoizedUpdaterCallbacks callback) {
          | Some memoized => memoized
          | None =>
            let that: jsComponentThis CompleteComponentSpec.state CompleteComponentSpec.props = [%bs.raw
              "this"
            ];
            let memoizedCallback event => {
              let instanceVariables =
                switch this##instanceVariables {
                | None =>
                  raise (
                    Invalid_argument "ReactRe stateful component: instanceVariables somehow isn't initialized."
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
                    instanceVariables,
                    updater: Obj.magic this##updaterMethod,
                    refSetter: Obj.magic this##refSetterMethod
                  };
              switch newState {
              | None => ()
              | Some state => that##setState {"mlState": state}
              }
            };
            this##memoizedUpdaterCallbacks#=[
                                              (callback, memoizedCallback),
                                              ...this##memoizedUpdaterCallbacks
                                            ];
            memoizedCallback
          };
        pub render () => {
          let that: jsComponentThis CompleteComponentSpec.state CompleteComponentSpec.props = [%bs.raw
            "this"
          ];
          let instanceVariables =
            switch this##instanceVariables {
            | None =>
              raise (
                Invalid_argument "ReactRe stateful component: instanceVariables somehow isn't initialized."
              )
            | Some s => s
            };
          CompleteComponentSpec.render {
            props: convertPropsIfTheyreFromJs that##props,
            state: that##state##mlState,
            instanceVariables,
            updater: Obj.magic this##updaterMethod,
            refSetter: Obj.magic this##refSetterMethod
          }
        }
      }
      [@bs]
    );
  let wrapProps (props: props_) children ::ref=? ::key=? () =>
    wrapPropsInternal ::comp props children ::?key ::?ref ();
};
