type reactClass;

type reactElement;

type syntheticEvent_like 'a;
type syntheticEvent = syntheticEvent_like unit;
type clipboardEvent_tag;
type clipboardEvent = syntheticEvent_like clipboardEvent_tag;
type compositionEvent_tag;
type compositionEvent = syntheticEvent_like compositionEvent_tag;
type keyboardEvent_tag;
type keyboardEvent = syntheticEvent_like keyboardEvent_tag;
type focusEvent_tag;
type focusEvent = syntheticEvent_like focusEvent_tag;
type formEvent_tag;
type formEvent = syntheticEvent_like formEvent_tag;
type mouseEvent_tag;
type mouseEvent = syntheticEvent_like mouseEvent_tag;
type selectionEvent_tag;
type selectionEvent = syntheticEvent_like selectionEvent_tag;
type touchEvent_tag;
type touchEvent = syntheticEvent_like touchEvent_tag;
type uiEvent_tag;
type uiEvent = syntheticEvent_like uiEvent_tag;
type wheelEvent_tag;
type wheelEvent = syntheticEvent_like wheelEvent_tag;
type mediaEvent_tag;
type mediaEvent = syntheticEvent_like mediaEvent_tag;
type imageEvent_tag;
type imageEvent = syntheticEvent_like imageEvent_tag;
type animationEvent_tag;
type animationEvent = syntheticEvent_like animationEvent_tag;
type transitionEvent_tag;
type transitionEvent = syntheticEvent_like transitionEvent_tag;

module SyntheticEvent: {
  type t_syntheticEvent = syntheticEvent;

  external bubbles : t_syntheticEvent => bool = "" [@@bs.get];
  external cancelable : t_syntheticEvent => bool = "" [@@bs.get];
  external currentTarget : t_syntheticEvent => ReasonJs.Document.element = "" [@@bs.get];
  external defaultPrevented : t_syntheticEvent => bool = "" [@@bs.get];
  external eventPhase : t_syntheticEvent => int = "" [@@bs.get];
  external isTrusted : t_syntheticEvent => bool = "" [@@bs.get];
  external nativeEvent : t_syntheticEvent => Js.t {..} = "" [@@bs.get];
  
  external preventDefault : unit = "" [@@bs.send.pipe: t_syntheticEvent];
  external isDefaultPrevented : bool = "" [@@bs.send.pipe: t_syntheticEvent];
  external stopPropagation : unit = "" [@@bs.send.pipe: t_syntheticEvent];
  external isPropagationStopped : bool = "" [@@bs.send.pipe: t_syntheticEvent];
  external target : t_syntheticEvent => ReasonJs.Document.element = "" [@@bs.get];

  external timeStamp : t_syntheticEvent => float = "" [@@bs.get];
  external type_ : t_syntheticEvent => string = "type" [@@bs.get];

  external persist : unit = "" [@@bs.send.pipe: t_syntheticEvent];
};

module ClipboardEvent: {
  type t = clipboardEvent;
  type t_syntheticEvent = t;

  external bubbles : t_syntheticEvent => bool = "" [@@bs.get];
  external cancelable : t_syntheticEvent => bool = "" [@@bs.get];
  external currentTarget : t_syntheticEvent => ReasonJs.Document.element = "" [@@bs.get];
  external defaultPrevented : t_syntheticEvent => bool = "" [@@bs.get];
  external eventPhase : t_syntheticEvent => int = "" [@@bs.get];
  external isTrusted : t_syntheticEvent => bool = "" [@@bs.get];
  external nativeEvent : t_syntheticEvent => Js.t {..} = "" [@@bs.get];
  
  external preventDefault : unit = "" [@@bs.send.pipe: t_syntheticEvent];
  external isDefaultPrevented : bool = "" [@@bs.send.pipe: t_syntheticEvent];
  external stopPropagation : unit = "" [@@bs.send.pipe: t_syntheticEvent];
  external isPropagationStopped : bool = "" [@@bs.send.pipe: t_syntheticEvent];
  external target : t_syntheticEvent => ReasonJs.Document.element = "" [@@bs.get];

  external timeStamp : t_syntheticEvent => float = "" [@@bs.get];
  external type_ : t_syntheticEvent => string = "type" [@@bs.get];

  external persist : unit = "" [@@bs.send.pipe: t_syntheticEvent];

  external clipboardData : t => Js.t {..} = "" [@@bs.get]; /* Should return Dom.dataTransfer */
};

module CompositionEvent: {
  type t = compositionEvent;
  type t_syntheticEvent = t;

  external bubbles : t_syntheticEvent => bool = "" [@@bs.get];
  external cancelable : t_syntheticEvent => bool = "" [@@bs.get];
  external currentTarget : t_syntheticEvent => ReasonJs.Document.element = "" [@@bs.get];
  external defaultPrevented : t_syntheticEvent => bool = "" [@@bs.get];
  external eventPhase : t_syntheticEvent => int = "" [@@bs.get];
  external isTrusted : t_syntheticEvent => bool = "" [@@bs.get];
  external nativeEvent : t_syntheticEvent => Js.t {..} = "" [@@bs.get];
  
  external preventDefault : unit = "" [@@bs.send.pipe: t_syntheticEvent];
  external isDefaultPrevented : bool = "" [@@bs.send.pipe: t_syntheticEvent];
  external stopPropagation : unit = "" [@@bs.send.pipe: t_syntheticEvent];
  external isPropagationStopped : bool = "" [@@bs.send.pipe: t_syntheticEvent];
  external target : t_syntheticEvent => ReasonJs.Document.element = "" [@@bs.get];

  external timeStamp : t_syntheticEvent => float = "" [@@bs.get];
  external type_ : t_syntheticEvent => string = "type" [@@bs.get];

  external persist : unit = "" [@@bs.send.pipe: t_syntheticEvent];

  external data : t => string = "" [@@bs.get];
};

module KeyboardEvent: {
  type t = keyboardEvent;
  type t_syntheticEvent = t;

  external bubbles : t_syntheticEvent => bool = "" [@@bs.get];
  external cancelable : t_syntheticEvent => bool = "" [@@bs.get];
  external currentTarget : t_syntheticEvent => ReasonJs.Document.element = "" [@@bs.get];
  external defaultPrevented : t_syntheticEvent => bool = "" [@@bs.get];
  external eventPhase : t_syntheticEvent => int = "" [@@bs.get];
  external isTrusted : t_syntheticEvent => bool = "" [@@bs.get];
  external nativeEvent : t_syntheticEvent => Js.t {..} = "" [@@bs.get];
  
  external preventDefault : unit = "" [@@bs.send.pipe: t_syntheticEvent];
  external isDefaultPrevented : bool = "" [@@bs.send.pipe: t_syntheticEvent];
  external stopPropagation : unit = "" [@@bs.send.pipe: t_syntheticEvent];
  external isPropagationStopped : bool = "" [@@bs.send.pipe: t_syntheticEvent];
  external target : t_syntheticEvent => ReasonJs.Document.element = "" [@@bs.get];

  external timeStamp : t_syntheticEvent => float = "" [@@bs.get];
  external type_ : t_syntheticEvent => string = "type" [@@bs.get];

  external persist : unit = "" [@@bs.send.pipe: t_syntheticEvent];

  external altKey : t => bool = "" [@@bs.get];
  external charCode : t => int = "" [@@bs.get];
  external ctrlKey : t => bool = "" [@@bs.get];
  external getModifierState : string => bool = "" [@@bs.send.pipe: t];
  external key : t => string = "" [@@bs.get];
  external keyCode : t => int = "" [@@bs.get];
  external locale : t => string = "" [@@bs.get];
  external location : t => int = "" [@@bs.get];
  external metaKey : t => bool = "" [@@bs.get];
  external repeat : t => bool = "" [@@bs.get];
  external shiftKey : t => bool = "" [@@bs.get];
  external which : t => int = "" [@@bs.get];
};

module FocusEvent: {
  type t = focusEvent;
  type t_syntheticEvent = t;

  external bubbles : t_syntheticEvent => bool = "" [@@bs.get];
  external cancelable : t_syntheticEvent => bool = "" [@@bs.get];
  external currentTarget : t_syntheticEvent => ReasonJs.Document.element = "" [@@bs.get];
  external defaultPrevented : t_syntheticEvent => bool = "" [@@bs.get];
  external eventPhase : t_syntheticEvent => int = "" [@@bs.get];
  external isTrusted : t_syntheticEvent => bool = "" [@@bs.get];
  external nativeEvent : t_syntheticEvent => Js.t {..} = "" [@@bs.get];
  
  external preventDefault : unit = "" [@@bs.send.pipe: t_syntheticEvent];
  external isDefaultPrevented : bool = "" [@@bs.send.pipe: t_syntheticEvent];
  external stopPropagation : unit = "" [@@bs.send.pipe: t_syntheticEvent];
  external isPropagationStopped : bool = "" [@@bs.send.pipe: t_syntheticEvent];
  external target : t_syntheticEvent => ReasonJs.Document.element = "" [@@bs.get];

  external timeStamp : t_syntheticEvent => float = "" [@@bs.get];
  external type_ : t_syntheticEvent => string = "type" [@@bs.get];

  external persist : unit = "" [@@bs.send.pipe: t_syntheticEvent];

  external relatedTarget : t => ReasonJs.Document.element = "" [@@bs.get]; /* Should return Dom.eventTarget */
};

module FormEvent: {
  type t = formEvent;
  type t_syntheticEvent = t;

  external bubbles : t_syntheticEvent => bool = "" [@@bs.get];
  external cancelable : t_syntheticEvent => bool = "" [@@bs.get];
  external currentTarget : t_syntheticEvent => ReasonJs.Document.element = "" [@@bs.get];
  external defaultPrevented : t_syntheticEvent => bool = "" [@@bs.get];
  external eventPhase : t_syntheticEvent => int = "" [@@bs.get];
  external isTrusted : t_syntheticEvent => bool = "" [@@bs.get];
  external nativeEvent : t_syntheticEvent => Js.t {..} = "" [@@bs.get];
  
  external preventDefault : unit = "" [@@bs.send.pipe: t_syntheticEvent];
  external isDefaultPrevented : bool = "" [@@bs.send.pipe: t_syntheticEvent];
  external stopPropagation : unit = "" [@@bs.send.pipe: t_syntheticEvent];
  external isPropagationStopped : bool = "" [@@bs.send.pipe: t_syntheticEvent];
  external target : t_syntheticEvent => ReasonJs.Document.element = "" [@@bs.get];

  external timeStamp : t_syntheticEvent => float = "" [@@bs.get];
  external type_ : t_syntheticEvent => string = "type" [@@bs.get];

  external persist : unit = "" [@@bs.send.pipe: t_syntheticEvent];
};

module MouseEvent: {
  type t = mouseEvent;
  type t_syntheticEvent = t;

  external bubbles : t_syntheticEvent => bool = "" [@@bs.get];
  external cancelable : t_syntheticEvent => bool = "" [@@bs.get];
  external currentTarget : t_syntheticEvent => ReasonJs.Document.element = "" [@@bs.get];
  external defaultPrevented : t_syntheticEvent => bool = "" [@@bs.get];
  external eventPhase : t_syntheticEvent => int = "" [@@bs.get];
  external isTrusted : t_syntheticEvent => bool = "" [@@bs.get];
  external nativeEvent : t_syntheticEvent => Js.t {..} = "" [@@bs.get];
  
  external preventDefault : unit = "" [@@bs.send.pipe: t_syntheticEvent];
  external isDefaultPrevented : bool = "" [@@bs.send.pipe: t_syntheticEvent];
  external stopPropagation : unit = "" [@@bs.send.pipe: t_syntheticEvent];
  external isPropagationStopped : bool = "" [@@bs.send.pipe: t_syntheticEvent];
  external target : t_syntheticEvent => ReasonJs.Document.element = "" [@@bs.get];

  external timeStamp : t_syntheticEvent => float = "" [@@bs.get];
  external type_ : t_syntheticEvent => string = "type" [@@bs.get];

  external persist : unit = "" [@@bs.send.pipe: t_syntheticEvent];

  external altKey : t => bool = "" [@@bs.get];
  external button : t => int = "" [@@bs.get];
  external buttons : t => int = "" [@@bs.get];
  external clientX : t => int = "" [@@bs.get];
  external clientY : t => int = "" [@@bs.get];
  external ctrlKey : t => bool = "" [@@bs.get];
  external getModifierState : string => bool = "" [@@bs.send.pipe: t];
  external metaKey : t => bool = "" [@@bs.get];
  external pageX : t => int = "" [@@bs.get];
  external pageY : t => int = "" [@@bs.get];
  external relatedTarget : t => ReasonJs.Document.element = "" [@@bs.get]; /* Should return Dom.eventTarget */
  external screenX : t => int = "" [@@bs.get];
  external screenY : t => int = "" [@@bs.get];
  external shiftKey : t => bool = "" [@@bs.get];
};

module SelectionEvent: {
  type t = selectionEvent;
  type t_syntheticEvent = t;

  external bubbles : t_syntheticEvent => bool = "" [@@bs.get];
  external cancelable : t_syntheticEvent => bool = "" [@@bs.get];
  external currentTarget : t_syntheticEvent => ReasonJs.Document.element = "" [@@bs.get];
  external defaultPrevented : t_syntheticEvent => bool = "" [@@bs.get];
  external eventPhase : t_syntheticEvent => int = "" [@@bs.get];
  external isTrusted : t_syntheticEvent => bool = "" [@@bs.get];
  external nativeEvent : t_syntheticEvent => Js.t {..} = "" [@@bs.get];
  
  external preventDefault : unit = "" [@@bs.send.pipe: t_syntheticEvent];
  external isDefaultPrevented : bool = "" [@@bs.send.pipe: t_syntheticEvent];
  external stopPropagation : unit = "" [@@bs.send.pipe: t_syntheticEvent];
  external isPropagationStopped : bool = "" [@@bs.send.pipe: t_syntheticEvent];
  external target : t_syntheticEvent => ReasonJs.Document.element = "" [@@bs.get];

  external timeStamp : t_syntheticEvent => float = "" [@@bs.get];
  external type_ : t_syntheticEvent => string = "type" [@@bs.get];

  external persist : unit = "" [@@bs.send.pipe: t_syntheticEvent];
};

module TouchEvent: {
  type t = touchEvent;
  type t_syntheticEvent = t;

  external bubbles : t_syntheticEvent => bool = "" [@@bs.get];
  external cancelable : t_syntheticEvent => bool = "" [@@bs.get];
  external currentTarget : t_syntheticEvent => ReasonJs.Document.element = "" [@@bs.get];
  external defaultPrevented : t_syntheticEvent => bool = "" [@@bs.get];
  external eventPhase : t_syntheticEvent => int = "" [@@bs.get];
  external isTrusted : t_syntheticEvent => bool = "" [@@bs.get];
  external nativeEvent : t_syntheticEvent => Js.t {..} = "" [@@bs.get];
  
  external preventDefault : unit = "" [@@bs.send.pipe: t_syntheticEvent];
  external isDefaultPrevented : bool = "" [@@bs.send.pipe: t_syntheticEvent];
  external stopPropagation : unit = "" [@@bs.send.pipe: t_syntheticEvent];
  external isPropagationStopped : bool = "" [@@bs.send.pipe: t_syntheticEvent];
  external target : t_syntheticEvent => ReasonJs.Document.element = "" [@@bs.get];

  external timeStamp : t_syntheticEvent => float = "" [@@bs.get];
  external type_ : t_syntheticEvent => string = "type" [@@bs.get];

  external persist : unit = "" [@@bs.send.pipe: t_syntheticEvent];

  external altKey : t => bool = "" [@@bs.get];
  external changedTouches : t => Js.t {..} = "" [@@bs.get]; /* Should return Dom.touchList */
  external ctrlKey : t => bool = "" [@@bs.get];
  external getModifierState : string => bool = "" [@@bs.send.pipe: t];
  external metaKey : t => bool = "" [@@bs.get];
  external shiftKey : t => bool = "" [@@bs.get];
  external targetTouches : t => Js.t {..} = "" [@@bs.get]; /* Should return Dom.touchList */
  external touches : t => Js.t {..} = "" [@@bs.get]; /* Should return Dom.touchList */
};

module UIEvent: {
  type t = uiEvent;
  type t_syntheticEvent = t;

  external bubbles : t_syntheticEvent => bool = "" [@@bs.get];
  external cancelable : t_syntheticEvent => bool = "" [@@bs.get];
  external currentTarget : t_syntheticEvent => ReasonJs.Document.element = "" [@@bs.get];
  external defaultPrevented : t_syntheticEvent => bool = "" [@@bs.get];
  external eventPhase : t_syntheticEvent => int = "" [@@bs.get];
  external isTrusted : t_syntheticEvent => bool = "" [@@bs.get];
  external nativeEvent : t_syntheticEvent => Js.t {..} = "" [@@bs.get];
  
  external preventDefault : unit = "" [@@bs.send.pipe: t_syntheticEvent];
  external isDefaultPrevented : bool = "" [@@bs.send.pipe: t_syntheticEvent];
  external stopPropagation : unit = "" [@@bs.send.pipe: t_syntheticEvent];
  external isPropagationStopped : bool = "" [@@bs.send.pipe: t_syntheticEvent];
  external target : t_syntheticEvent => ReasonJs.Document.element = "" [@@bs.get];

  external timeStamp : t_syntheticEvent => float = "" [@@bs.get];
  external type_ : t_syntheticEvent => string = "type" [@@bs.get];

  external persist : unit = "" [@@bs.send.pipe: t_syntheticEvent];

  external detail : t => int = "" [@@bs.get];
  external view : t => ReasonJs.Window.t = "" [@@bs.get]; /* Should return DOMAbstractView/WindowProxy */
};

module WheelEvent: {
  type t = wheelEvent;
  type t_syntheticEvent = t;

  external bubbles : t_syntheticEvent => bool = "" [@@bs.get];
  external cancelable : t_syntheticEvent => bool = "" [@@bs.get];
  external currentTarget : t_syntheticEvent => ReasonJs.Document.element = "" [@@bs.get];
  external defaultPrevented : t_syntheticEvent => bool = "" [@@bs.get];
  external eventPhase : t_syntheticEvent => int = "" [@@bs.get];
  external isTrusted : t_syntheticEvent => bool = "" [@@bs.get];
  external nativeEvent : t_syntheticEvent => Js.t {..} = "" [@@bs.get];
  
  external preventDefault : unit = "" [@@bs.send.pipe: t_syntheticEvent];
  external isDefaultPrevented : bool = "" [@@bs.send.pipe: t_syntheticEvent];
  external stopPropagation : unit = "" [@@bs.send.pipe: t_syntheticEvent];
  external isPropagationStopped : bool = "" [@@bs.send.pipe: t_syntheticEvent];
  external target : t_syntheticEvent => ReasonJs.Document.element = "" [@@bs.get];

  external timeStamp : t_syntheticEvent => float = "" [@@bs.get];
  external type_ : t_syntheticEvent => string = "type" [@@bs.get];

  external persist : unit = "" [@@bs.send.pipe: t_syntheticEvent];

  external deltaMode : t => int = "" [@@bs.get];
  external deltaX : t => float = "" [@@bs.get];
  external deltaY : t => float = "" [@@bs.get];
  external deltaZ : t => float = "" [@@bs.get];
};

module MediaEvent: {
  type t = mediaEvent;
  type t_syntheticEvent = t;

  external bubbles : t_syntheticEvent => bool = "" [@@bs.get];
  external cancelable : t_syntheticEvent => bool = "" [@@bs.get];
  external currentTarget : t_syntheticEvent => ReasonJs.Document.element = "" [@@bs.get];
  external defaultPrevented : t_syntheticEvent => bool = "" [@@bs.get];
  external eventPhase : t_syntheticEvent => int = "" [@@bs.get];
  external isTrusted : t_syntheticEvent => bool = "" [@@bs.get];
  external nativeEvent : t_syntheticEvent => Js.t {..} = "" [@@bs.get];
  
  external preventDefault : unit = "" [@@bs.send.pipe: t_syntheticEvent];
  external isDefaultPrevented : bool = "" [@@bs.send.pipe: t_syntheticEvent];
  external stopPropagation : unit = "" [@@bs.send.pipe: t_syntheticEvent];
  external isPropagationStopped : bool = "" [@@bs.send.pipe: t_syntheticEvent];
  external target : t_syntheticEvent => ReasonJs.Document.element = "" [@@bs.get];

  external timeStamp : t_syntheticEvent => float = "" [@@bs.get];
  external type_ : t_syntheticEvent => string = "type" [@@bs.get];

  external persist : unit = "" [@@bs.send.pipe: t_syntheticEvent];
};

module ImageEvent: {
  type t = imageEvent;
  type t_syntheticEvent = t;

  external bubbles : t_syntheticEvent => bool = "" [@@bs.get];
  external cancelable : t_syntheticEvent => bool = "" [@@bs.get];
  external currentTarget : t_syntheticEvent => ReasonJs.Document.element = "" [@@bs.get];
  external defaultPrevented : t_syntheticEvent => bool = "" [@@bs.get];
  external eventPhase : t_syntheticEvent => int = "" [@@bs.get];
  external isTrusted : t_syntheticEvent => bool = "" [@@bs.get];
  external nativeEvent : t_syntheticEvent => Js.t {..} = "" [@@bs.get];
  
  external preventDefault : unit = "" [@@bs.send.pipe: t_syntheticEvent];
  external isDefaultPrevented : bool = "" [@@bs.send.pipe: t_syntheticEvent];
  external stopPropagation : unit = "" [@@bs.send.pipe: t_syntheticEvent];
  external isPropagationStopped : bool = "" [@@bs.send.pipe: t_syntheticEvent];
  external target : t_syntheticEvent => ReasonJs.Document.element = "" [@@bs.get];

  external timeStamp : t_syntheticEvent => float = "" [@@bs.get];
  external type_ : t_syntheticEvent => string = "type" [@@bs.get];

  external persist : unit = "" [@@bs.send.pipe: t_syntheticEvent];
};

module AnimationEvent: {
  type t = animationEvent;
  type t_syntheticEvent = t;

  external bubbles : t_syntheticEvent => bool = "" [@@bs.get];
  external cancelable : t_syntheticEvent => bool = "" [@@bs.get];
  external currentTarget : t_syntheticEvent => ReasonJs.Document.element = "" [@@bs.get];
  external defaultPrevented : t_syntheticEvent => bool = "" [@@bs.get];
  external eventPhase : t_syntheticEvent => int = "" [@@bs.get];
  external isTrusted : t_syntheticEvent => bool = "" [@@bs.get];
  external nativeEvent : t_syntheticEvent => Js.t {..} = "" [@@bs.get];
  
  external preventDefault : unit = "" [@@bs.send.pipe: t_syntheticEvent];
  external isDefaultPrevented : bool = "" [@@bs.send.pipe: t_syntheticEvent];
  external stopPropagation : unit = "" [@@bs.send.pipe: t_syntheticEvent];
  external isPropagationStopped : bool = "" [@@bs.send.pipe: t_syntheticEvent];
  external target : t_syntheticEvent => ReasonJs.Document.element = "" [@@bs.get];

  external timeStamp : t_syntheticEvent => float = "" [@@bs.get];
  external type_ : t_syntheticEvent => string = "type" [@@bs.get];

  external persist : unit = "" [@@bs.send.pipe: t_syntheticEvent];

  external animationName : t => string = "" [@@bs.get];
  external pseudoElement : t => string = "" [@@bs.get];
  external elapsedTime : t => float = "" [@@bs.get];
};

module TransitionEvent: {
  type t = transitionEvent;
  type t_syntheticEvent = t;

  external bubbles : t_syntheticEvent => bool = "" [@@bs.get];
  external cancelable : t_syntheticEvent => bool = "" [@@bs.get];
  external currentTarget : t_syntheticEvent => ReasonJs.Document.element = "" [@@bs.get];
  external defaultPrevented : t_syntheticEvent => bool = "" [@@bs.get];
  external eventPhase : t_syntheticEvent => int = "" [@@bs.get];
  external isTrusted : t_syntheticEvent => bool = "" [@@bs.get];
  external nativeEvent : t_syntheticEvent => Js.t {..} = "" [@@bs.get];
  
  external preventDefault : unit = "" [@@bs.send.pipe: t_syntheticEvent];
  external isDefaultPrevented : bool = "" [@@bs.send.pipe: t_syntheticEvent];
  external stopPropagation : unit = "" [@@bs.send.pipe: t_syntheticEvent];
  external isPropagationStopped : bool = "" [@@bs.send.pipe: t_syntheticEvent];
  external target : t_syntheticEvent => ReasonJs.Document.element = "" [@@bs.get];

  external timeStamp : t_syntheticEvent => float = "" [@@bs.get];
  external type_ : t_syntheticEvent => string = "type" [@@bs.get];

  external persist : unit = "" [@@bs.send.pipe: t_syntheticEvent];

  external propertyName : t => string = "" [@@bs.get];
  external pseudoElement : t => string = "" [@@bs.get];
  external elapsedTime : t => float = "" [@@bs.get];
};

type reactRef;

type reactJsChildren;

external createElement : reactClass => props::Js.t {..}? => array reactElement => reactElement =
  "createElement" [@@bs.splice] [@@bs.val] [@@bs.module "react"];

external nullElement : reactElement = "null" [@@bs.val];

external stringToElement : string => reactElement = "%identity";

external arrayToElement : array reactElement => reactElement = "%identity";

external refToJsObj : reactRef => Js.t {..} = "%identity";

let jsChildrenToReason: Js.null_undefined reactJsChildren => list reactElement;

module ComponentBase: {
  type componentBag 'state 'props 'instanceVars = {
    state: 'state,
    props: 'props,
    updater:
      'dataPassedToHandler .
      (componentBag 'state 'props 'instanceVars => 'dataPassedToHandler => option 'state) =>
      'dataPassedToHandler =>
      unit,

    refSetter: (componentBag 'state 'props 'instanceVars => reactRef => unit) => reactRef => unit,
    instanceVars: 'instanceVars,
    setState: (componentBag 'state 'props 'instanceVars => 'state) => unit
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
  let componentDidMount: ComponentBase.componentBag state props instanceVars => option state;
  let componentWillReceiveProps:
    ComponentBase.componentBag state props instanceVars => nextProps::props => option state;
  let componentWillUpdate:
    ComponentBase.componentBag state props instanceVars =>
    nextProps::props =>
    nextState::state =>
    option state;
  let componentDidUpdate:
    prevProps::props =>
    prevState::state =>
    ComponentBase.componentBag state props instanceVars =>
    option state;
  let componentWillUnmount: ComponentBase.componentBag state props instanceVars => unit;
  let jsPropsToReasonProps: option (jsProps => props);
  let render: ComponentBase.componentBag state props instanceVars => reactElement;
};

module CreateComponent:
  (CompleteComponentSpec: CompleteComponentSpec) =>
  {
    let comp: reactClass;
    let wrapProps:
      CompleteComponentSpec.props =>
      children::list reactElement =>
      ref::(reactRef => unit)? =>
      key::string? =>
      unit =>
      reactElement;
  };

let wrapPropsShamelessly:
  reactClass =>
  Js.t {..} =>
  children::list reactElement =>
  ref::(reactRef => unit)? =>
  key::string? =>
  unit =>
  reactElement;

/* Don't be scared off by this signature's size! Notice that you will only ever use one of the modules or
submodule in a component. */
module Component: {
  type componentBag 'state 'props 'instanceVars =
    ComponentBase.componentBag 'state 'props 'instanceVars =
      {
        state: 'state,
        props: 'props,
        updater:
          'dataPassedToHandler .
          (componentBag 'state 'props 'instanceVars => 'dataPassedToHandler => option 'state) =>
          'dataPassedToHandler =>
          unit,

        refSetter:
          (componentBag 'state 'props 'instanceVars => reactRef => unit) => reactRef => unit,
        instanceVars: 'instanceVars,
        setState: (componentBag 'state 'props 'instanceVars => 'state) => unit
      };
  let componentDidMount: 'a => option 'b;
  let componentWillUpdate: 'a => nextProps::'b => nextState::'c => option 'd;
  let componentDidUpdate: prevProps::'a => prevState::'b => 'c => option 'd;
  let componentWillReceiveProps: 'a => nextProps::'b => option 'c;
  let componentWillUnmount: 'a => unit;
  type jsProps = unit;
  type instanceVars = unit;
  type state = unit;
  let getInstanceVars: unit => unit;
  let jsPropsToReasonProps: option 'a;
  let getInitialState: 'a => unit;
  module Stateful: {
    type componentBag 'state 'props 'instanceVars =
      ComponentBase.componentBag 'state 'props 'instanceVars =
        {
          state: 'state,
          props: 'props,
          updater:
            'dataPassedToHandler .
            (componentBag 'state 'props 'instanceVars => 'dataPassedToHandler => option 'state) =>
            'dataPassedToHandler =>
            unit,

          refSetter:
            (componentBag 'state 'props 'instanceVars => reactRef => unit) => reactRef => unit,
          instanceVars: 'instanceVars,
          setState: (componentBag 'state 'props 'instanceVars => 'state) => unit
        };
    let componentDidMount: 'a => option 'b;
    let componentWillUpdate: 'a => nextProps::'b => nextState::'c => option 'd;
    let componentDidUpdate: prevProps::'a => prevState::'b => 'c => option 'd;
    let componentWillReceiveProps: 'a => nextProps::'b => option 'c;
    let componentWillUnmount: 'a => unit;
    type jsProps = unit;
    type instanceVars = unit;
    let getInstanceVars: unit => unit;
    let jsPropsToReasonProps: option 'a;
    module JsProps: {
      type componentBag 'state 'props 'instanceVars =
        ComponentBase.componentBag 'state 'props 'instanceVars =
          {
            state: 'state,
            props: 'props,
            updater:
              'dataPassedToHandler .
              (
                componentBag 'state 'props 'instanceVars => 'dataPassedToHandler => option 'state
              ) =>
              'dataPassedToHandler =>
              unit,

            refSetter:
              (componentBag 'state 'props 'instanceVars => reactRef => unit) => reactRef => unit,
            instanceVars: 'instanceVars,
            setState: (componentBag 'state 'props 'instanceVars => 'state) => unit
          };
      let componentDidMount: 'a => option 'b;
      let componentWillUpdate: 'a => nextProps::'b => nextState::'c => option 'd;
      let componentDidUpdate: prevProps::'a => prevState::'b => 'c => option 'd;
      let componentWillReceiveProps: 'a => nextProps::'b => option 'c;
      let componentWillUnmount: 'a => unit;
      type instanceVars = unit;
      let getInstanceVars: unit => unit;
      let jsPropsToReasonProps: option 'a;
    };
    module InstanceVars: {
      type componentBag 'state 'props 'instanceVars =
        ComponentBase.componentBag 'state 'props 'instanceVars =
          {
            state: 'state,
            props: 'props,
            updater:
              'dataPassedToHandler .
              (
                componentBag 'state 'props 'instanceVars => 'dataPassedToHandler => option 'state
              ) =>
              'dataPassedToHandler =>
              unit,

            refSetter:
              (componentBag 'state 'props 'instanceVars => reactRef => unit) => reactRef => unit,
            instanceVars: 'instanceVars,
            setState: (componentBag 'state 'props 'instanceVars => 'state) => unit
          };
      let componentDidMount: 'a => option 'b;
      let componentWillUpdate: 'a => nextProps::'b => nextState::'c => option 'd;
      let componentDidUpdate: prevProps::'a => prevState::'b => 'c => option 'd;
      let componentWillReceiveProps: 'a => nextProps::'b => option 'c;
      let componentWillUnmount: 'a => unit;
      type jsProps = unit;
      let jsPropsToReasonProps: option 'a;
      module JsProps: {
        type componentBag 'state 'props 'instanceVars =
          ComponentBase.componentBag 'state 'props 'instanceVars =
            {
              state: 'state,
              props: 'props,
              updater:
                'dataPassedToHandler .
                (
                  componentBag 'state 'props 'instanceVars => 'dataPassedToHandler => option 'state
                ) =>
                'dataPassedToHandler =>
                unit,

              refSetter:
                (componentBag 'state 'props 'instanceVars => reactRef => unit) => reactRef => unit,
              instanceVars: 'instanceVars,
              setState: (componentBag 'state 'props 'instanceVars => 'state) => unit
            };
        let componentDidMount: 'a => option 'b;
        let componentWillUpdate: 'a => nextProps::'b => nextState::'c => option 'd;
        let componentDidUpdate: prevProps::'a => prevState::'b => 'c => option 'd;
        let componentWillReceiveProps: 'a => nextProps::'b => option 'c;
        let componentWillUnmount: 'a => unit;
      };
    };
  };
  module JsProps: {
    type componentBag 'state 'props 'instanceVars =
      ComponentBase.componentBag 'state 'props 'instanceVars =
        {
          state: 'state,
          props: 'props,
          updater:
            'dataPassedToHandler .
            (componentBag 'state 'props 'instanceVars => 'dataPassedToHandler => option 'state) =>
            'dataPassedToHandler =>
            unit,

          refSetter:
            (componentBag 'state 'props 'instanceVars => reactRef => unit) => reactRef => unit,
          instanceVars: 'instanceVars,
          setState: (componentBag 'state 'props 'instanceVars => 'state) => unit
        };
    let componentDidMount: 'a => option 'b;
    let componentWillUpdate: 'a => nextProps::'b => nextState::'c => option 'd;
    let componentDidUpdate: prevProps::'a => prevState::'b => 'c => option 'd;
    let componentWillReceiveProps: 'a => nextProps::'b => option 'c;
    let componentWillUnmount: 'a => unit;
    type instanceVars = unit;
    type state = unit;
    let getInstanceVars: unit => unit;
    let getInitialState: 'a => unit;
  };
  module InstanceVars: {
    type componentBag 'state 'props 'instanceVars =
      ComponentBase.componentBag 'state 'props 'instanceVars =
        {
          state: 'state,
          props: 'props,
          updater:
            'dataPassedToHandler .
            (componentBag 'state 'props 'instanceVars => 'dataPassedToHandler => option 'state) =>
            'dataPassedToHandler =>
            unit,

          refSetter:
            (componentBag 'state 'props 'instanceVars => reactRef => unit) => reactRef => unit,
          instanceVars: 'instanceVars,
          setState: (componentBag 'state 'props 'instanceVars => 'state) => unit
        };
    let componentDidMount: 'a => option 'b;
    let componentWillUpdate: 'a => nextProps::'b => nextState::'c => option 'd;
    let componentDidUpdate: prevProps::'a => prevState::'b => 'c => option 'd;
    let componentWillReceiveProps: 'a => nextProps::'b => option 'c;
    let componentWillUnmount: 'a => unit;
    type jsProps = unit;
    type state = unit;
    let getInitialState: 'a => unit;
    let jsPropsToReasonProps: option 'a;
    module JsProps: {
      type componentBag 'state 'props 'instanceVars =
        ComponentBase.componentBag 'state 'props 'instanceVars =
          {
            state: 'state,
            props: 'props,
            updater:
              'dataPassedToHandler .
              (
                componentBag 'state 'props 'instanceVars => 'dataPassedToHandler => option 'state
              ) =>
              'dataPassedToHandler =>
              unit,

            refSetter:
              (componentBag 'state 'props 'instanceVars => reactRef => unit) => reactRef => unit,
            instanceVars: 'instanceVars,
            setState: (componentBag 'state 'props 'instanceVars => 'state) => unit
          };
      let componentDidMount: 'a => option 'b;
      let componentWillUpdate: 'a => nextProps::'b => nextState::'c => option 'd;
      let componentDidUpdate: prevProps::'a => prevState::'b => 'c => option 'd;
      let componentWillReceiveProps: 'a => nextProps::'b => option 'c;
      let componentWillUnmount: 'a => unit;
      type state = unit;
      let getInitialState: 'a => unit;
    };
  };
};
