type reactClass;

type reactElement;

/* TODO: (chenglou) type event */
type event;

type reactRef;

type reactChildren;

external createClass : Js.t 'classSpec => reactClass = "createClass" [@@bs.val] [@@bs.module
                                                                    "react"
                                                                    ];

external createDOMElement : string => Js.null (Js.t {..}) => array reactElement => reactElement = "createElement" [@@bs.splice] [@@bs.val] [@@bs.module
                                                                    "react"
                                                                    ];

external createCompositeElement : reactClass =>
                                  Js.null (Js.t {..}) =>
                                  array reactElement =>
                                  reactElement = "createElement" [@@bs.splice] [@@bs.val] [@@bs.module
                                                                    "react"
                                                                    ];

/* ================================================== old api, don't use */
external getProps : 'this => 'reactJsProps = "props" [@@bs.get];

external getState : 'this => 'reactJsState = "state" [@@bs.get];

external setState : 'this => 'state => unit = "setState" [@@bs.send];

external getRefs : 'this => 'refs = "refs" [@@bs.get];

/* ================================================== old api, don't use */
external toElement : _ => reactElement = "%identity";

external nullElement : reactElement = "null" [@@bs.val];

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

external createCompositeElementInternalHack : reactClass =>
                                              Js.t {.. reasonProps : 'props} =>
                                              array reactElement =>
                                              reactElement = "createElement" [@@bs.val] [@@bs.module
                                                                    "react"
                                                                    ] [@@bs.splice];

external refToJsObj : reactRef => Js.t {..} = "%identity";

external reactClassToJsObj : reactClass => Js.t {..} = "%identity";

/* We wrap the props for reason->reason components, as a marker that "these props were passed from another
   reason component" */
let wrapPropsInternal
    ::comp
    ref::(ref: option (reactRef => unit))
    key::(key: option string)
    ::children
    props => {
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

module StatelessComponent = {
  type componentBag 'props 'instanceVariables = {
    props: 'props,
    updater:
      'dataPassedToHandler .
      ('dataPassedToHandler => componentBag 'props 'instanceVariables => unit) =>
      'dataPassedToHandler =>
      unit,

    refSetter: (reactRef => componentBag 'props 'instanceVariables => unit) => reactRef => unit,
    instanceVariables: 'instanceVariables
  };
  type jsComponentThis 'props = Js.t {. props : Obj.t};
  let getInstanceVariables () => ();
  let componentDidMount _ => ();
  /* let shouldComponentUpdate _ _ => true; */
  let componentDidUpdate _ _ => ();
  let componentWillReceiveProps _ _ => ();
  let componentWillUnmount _ => ();
  let createClass
      (type props)
      (type jsPropsType)
      (type instanceVariables)
      ::name
      getInstanceVariables::(getInstanceVariables: unit => instanceVariables)
      componentDidMount::(componentDidMount: componentBag props instanceVariables => unit)
      componentWillReceiveProps::(
        componentWillReceiveProps: props => componentBag props instanceVariables => unit
      )
      componentDidUpdate::(
        componentDidUpdate: props => componentBag props instanceVariables => unit
      )
      componentWillUnmount::(componentWillUnmount: componentBag props instanceVariables => unit)
      jsPropsToReasonProps::(jsPropsToReasonProps: option (jsPropsType => props))=?
      (render: componentBag props instanceVariables => reactElement) => {
    let convertPropsIfTheyreFromJs props => {
      let props = Obj.magic props;
      switch (Js.Undefined.to_opt props##reasonProps, jsPropsToReasonProps) {
      | (Some props, _) => props
      /* TODO: annotate with BS to avoid curry overhead */
      | (None, Some toReasonProps) => toReasonProps props
      | (None, None) =>
        raise (
          Invalid_argument (
            "A JS component called the Reason component " ^
            name ^ " which didn't implement the JS->Reason React props conversion"
          )
        )
      }
    };
    let comp =
      createClass (
        {
          val displayName = name;
          val mutable instanceVariables = None;
          val mutable memoizedUpdaterCallbacks = [];
          val mutable memoizedRefCallbacks = [];
          pri componentWillMount () => this##instanceVariables#=(Some (getInstanceVariables ()));
          pri componentDidMount () => {
            let that: jsComponentThis props = [%bs.raw "this"];
            let instanceVariables =
              switch this##instanceVariables {
              | None =>
                raise (
                  Invalid_argument "ReactRe stateless component: instanceVariables somehow isn't initialized."
                )
              | Some s => s
              };
            componentDidMount {
              props: convertPropsIfTheyreFromJs that##props,
              instanceVariables,
              updater: Obj.magic this##updaterMethod,
              refSetter: Obj.magic this##refSetterMethod
            }
          };
          pri componentDidUpdate prevProps _ => {
            let that: jsComponentThis props = [%bs.raw "this"];
            let instanceVariables =
              switch this##instanceVariables {
              | None =>
                raise (
                  Invalid_argument "ReactRe stateless component: instanceVariables somehow isn't initialized."
                )
              | Some s => s
              };
            componentDidUpdate
              (convertPropsIfTheyreFromJs prevProps)
              {
                props: convertPropsIfTheyreFromJs that##props,
                instanceVariables,
                updater: Obj.magic this##updaterMethod,
                refSetter: Obj.magic this##refSetterMethod
              }
          };
          pri componentWillReceiveProps nextProps => {
            let that: jsComponentThis props = [%bs.raw "this"];
            let instanceVariables =
              switch this##instanceVariables {
              | None =>
                raise (
                  Invalid_argument "ReactRe stateless component: instanceVariables somehow isn't initialized."
                )
              | Some s => s
              };
            componentWillReceiveProps
              (convertPropsIfTheyreFromJs nextProps)
              {
                props: convertPropsIfTheyreFromJs that##props,
                instanceVariables,
                updater: Obj.magic this##updaterMethod,
                refSetter: Obj.magic this##refSetterMethod
              }
          };
          pri componentWillUnmount () => {
            let that: jsComponentThis props = [%bs.raw "this"];
            let instanceVariables =
              switch this##instanceVariables {
              | None =>
                raise (
                  Invalid_argument "ReactRe stateless component: instanceVariables somehow isn't initialized."
                )
              | Some s => s
              };
            componentWillUnmount {
              props: convertPropsIfTheyreFromJs that##props,
              instanceVariables,
              updater: Obj.magic this##updaterMethod,
              refSetter: Obj.magic this##refSetterMethod
            }
          };
          pri updaterMethod callback =>
            switch (findFirstCallback this##memoizedUpdaterCallbacks callback) {
            | Some memoized => memoized
            | None =>
              let that: jsComponentThis props = [%bs.raw "this"];
              let memoizedCallback event => {
                let instanceVariables =
                  switch this##instanceVariables {
                  | None =>
                    raise (
                      Invalid_argument "ReactRe stateless component: instanceVariables somehow isn't initialized."
                    )
                  | Some s => s
                  };
                callback
                  event
                  {
                    props: convertPropsIfTheyreFromJs that##props,
                    instanceVariables,
                    updater: Obj.magic this##updaterMethod,
                    refSetter: Obj.magic this##refSetterMethod
                  }
              };
              this##memoizedUpdaterCallbacks#=[
                                                (callback, memoizedCallback),
                                                ...this##memoizedUpdaterCallbacks
                                              ];
              memoizedCallback
            };
          pri refSetterMethod callback =>
            switch (findFirstCallback this##memoizedRefCallbacks callback) {
            | Some memoized => memoized
            | None =>
              let that: jsComponentThis props = [%bs.raw "this"];
              let memoizedCallback (theRef: reactRef) => {
                let instanceVariables =
                  switch this##instanceVariables {
                  | None =>
                    raise (
                      Invalid_argument "ReactRe stateless component: instanceVariables somehow isn't initialized."
                    )
                  | Some s => s
                  };
                callback
                  theRef
                  {
                    props: convertPropsIfTheyreFromJs that##props,
                    instanceVariables,
                    updater: Obj.magic this##updaterMethod,
                    refSetter: Obj.magic this##refSetterMethod
                  }
              };
              this##memoizedRefCallbacks#=[
                                            (callback, memoizedCallback),
                                            ...this##memoizedRefCallbacks
                                          ];
              memoizedCallback
            };
          pri render () => {
            let that: jsComponentThis props = [%bs.raw "this"];
            let instanceVariables =
              switch this##instanceVariables {
              | None =>
                raise (
                  Invalid_argument "ReactRe stateless component: instanceVariables somehow isn't initialized."
                )
              | Some s => s
              };
            render {
              props: convertPropsIfTheyreFromJs that##props,
              instanceVariables,
              updater: Obj.magic this##updaterMethod,
              refSetter: Obj.magic this##refSetterMethod
            }
          }
        }
        [@bs]
      );
    /* We wrap the props for reason->reason components, as a marker that "these props were passed from another
       reason component" */
    (comp, wrapPropsInternal ::comp)
  };
};

module Component = {
  type componentBag 'state 'props 'instanceVariables = {
    state: 'state,
    props: 'props,
    updater:
      'dataPassedToHandler .
      ('dataPassedToHandler => componentBag 'state 'props 'instanceVariables => option 'state) =>
      'dataPassedToHandler =>
      unit,

    refSetter:
      (reactRef => componentBag 'state 'props 'instanceVariables => unit) => reactRef => unit,
    instanceVariables: 'instanceVariables
  };
  type jsState 'state = Js.t {. mlState : 'state};
  type jsComponentThis 'state 'props =
    Js.t {. state : jsState 'state, props : Obj.t, setState : (jsState 'state => unit) [@bs.meth]};
  let getInstanceVariables () => ();
  let componentDidMount _ => None;
  /* let shouldComponentUpdate _ _ => true; */
  let componentDidUpdate _ _ _ => None;
  let componentWillReceiveProps _ _ => None;
  let componentWillUnmount _ => ();
  let createClass
      (type state)
      (type props)
      (type jsPropsType)
      (type instanceVariables)
      ::name
      getInstanceVariables::(getInstanceVariables: unit => instanceVariables)
      getInitialState::(getInitialState: props => state)
      componentDidMount::(
        componentDidMount: componentBag state props instanceVariables => option state
      )
      componentWillReceiveProps::(
        componentWillReceiveProps:
          props => componentBag state props instanceVariables => option state
      )
      componentDidUpdate::(
        componentDidUpdate:
          props => state => componentBag state props instanceVariables => option state
      )
      componentWillUnmount::(
        componentWillUnmount: componentBag state props instanceVariables => unit
      )
      jsPropsToReasonProps::(jsPropsToReasonProps: option (jsPropsType => props))=?
      (render: componentBag state props instanceVariables => reactElement) => {
    let convertPropsIfTheyreFromJs props => {
      let props = Obj.magic props;
      switch (Js.Undefined.to_opt props##reasonProps, jsPropsToReasonProps) {
      | (Some props, _) => props
      /* TODO: annotate with BS to avoid curry overhead */
      | (None, Some toReasonProps) => toReasonProps props
      | (None, None) =>
        raise (
          Invalid_argument (
            "A JS component called the Reason component " ^
            name ^ " which didn't implement the JS->Reason React props conversion"
          )
        )
      }
    };
    let comp =
      createClass (
        {
          val displayName = name;
          val mutable instanceVariables = None;
          val mutable memoizedUpdaterCallbacks = [];
          val mutable memoizedRefCallbacks = [];
          pri getInitialState () :jsState state => {
            let that: jsComponentThis state props = [%bs.raw "this"];
            let props = convertPropsIfTheyreFromJs that##props;
            let state = getInitialState props;
            this##instanceVariables#=(Some (getInstanceVariables ()));
            {"mlState": state}
          };
          pri componentDidMount () => {
            let that: jsComponentThis state props = [%bs.raw "this"];
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
              componentDidMount {
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
          pri componentDidUpdate prevProps prevState => {
            let that: jsComponentThis state props = [%bs.raw "this"];
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
              componentDidUpdate
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
          pri componentWillReceiveProps nextProps => {
            let that: jsComponentThis state props = [%bs.raw "this"];
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
              componentWillReceiveProps
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
          pri componentWillUnmount () => {
            let that: jsComponentThis state props = [%bs.raw "this"];
            let instanceVariables =
              switch this##instanceVariables {
              | None =>
                raise (
                  Invalid_argument "ReactRe stateful component: instanceVariables somehow isn't initialized."
                )
              | Some s => s
              };
            let currState = that##state##mlState;
            componentWillUnmount {
              props: convertPropsIfTheyreFromJs that##props,
              state: currState,
              instanceVariables,
              updater: Obj.magic this##updaterMethod,
              refSetter: Obj.magic this##refSetterMethod
            }
          };
          pri refSetterMethod callback =>
            switch (findFirstCallback this##memoizedRefCallbacks callback) {
            | Some memoized => memoized
            | None =>
              let that: jsComponentThis state props = [%bs.raw "this"];
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
                    props: convertPropsIfTheyreFromJs that##props,
                    state: currState,
                    instanceVariables,
                    updater: Obj.magic this##updaterMethod,
                    refSetter: Obj.magic this##refSetterMethod
                  }
              };
              this##memoizedRefCallbacks#=[
                                            (callback, memoizedCallback),
                                            ...this##memoizedRefCallbacks
                                          ];
              memoizedCallback
            };
          pri updaterMethod callback =>
            switch (findFirstCallback this##memoizedUpdaterCallbacks callback) {
            | Some memoized => memoized
            | None =>
              let that: jsComponentThis state props = [%bs.raw "this"];
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
              this##memoizedUpdaterCallbacks#=[
                                                (callback, memoizedCallback),
                                                ...this##memoizedUpdaterCallbacks
                                              ];
              memoizedCallback
            };
          pri render () => {
            let that: jsComponentThis state props = [%bs.raw "this"];
            let instanceVariables =
              switch this##instanceVariables {
              | None =>
                raise (
                  Invalid_argument "ReactRe stateful component: instanceVariables somehow isn't initialized."
                )
              | Some s => s
              };
            render {
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
    (comp, wrapPropsInternal ::comp)
  };
};
