type synthetic 'a;

module Synthetic: {
  type tag;
  type t = synthetic tag ;

  external bubbles : synthetic 'a => bool = "" [@@bs.get];
  external cancelable : synthetic 'a => bool = "" [@@bs.get];
  external currentTarget : synthetic 'a => ReasonJs.Document.element = "" [@@bs.get];
  external defaultPrevented : synthetic 'a => bool = "" [@@bs.get];
  external eventPhase : synthetic 'a => int = "" [@@bs.get];
  external isTrusted : synthetic 'a => bool = "" [@@bs.get];
  external nativeEvent : synthetic 'a => Js.t {..} = "" [@@bs.get];

  external preventDefault : unit = "" [@@bs.send.pipe: synthetic 'a];
  external isDefaultPrevented : bool = "" [@@bs.send.pipe: synthetic 'a];
  external stopPropagation : unit = "" [@@bs.send.pipe: synthetic 'a];
  external isPropagationStopped : bool = "" [@@bs.send.pipe: synthetic 'a];
  external target : synthetic 'a => ReasonJs.Document.element = "" [@@bs.get];

  external timeStamp : synthetic 'a => float = "" [@@bs.get];
  external _type : synthetic 'a => string = "type" [@@bs.get];

  external persist : unit = "" [@@bs.send.pipe: synthetic 'a];
};

module Clipboard: {
  type tag;
  type t = synthetic tag;

  external bubbles : t => bool = "" [@@bs.get];
  external cancelable : t => bool = "" [@@bs.get];
  external currentTarget : t => ReasonJs.Document.element = "" [@@bs.get];
  external defaultPrevented : t => bool = "" [@@bs.get];
  external eventPhase : t => int = "" [@@bs.get];
  external isTrusted : t => bool = "" [@@bs.get];
  external nativeEvent : t => Js.t {..} = "" [@@bs.get];

  external preventDefault : unit = "" [@@bs.send.pipe: t];
  external isDefaultPrevented : bool = "" [@@bs.send.pipe: t];
  external stopPropagation : unit = "" [@@bs.send.pipe: t];
  external isPropagationStopped : bool = "" [@@bs.send.pipe: t];
  external target : t => ReasonJs.Document.element = "" [@@bs.get];

  external timeStamp : t => float = "" [@@bs.get];
  external _type : t => string = "type" [@@bs.get];

  external persist : unit = "" [@@bs.send.pipe: t];

  external clipboardData : t => Js.t {..} = "" [@@bs.get]; /* Should return Dom.dataTransfer */
};

module Composition: {
  type tag;
  type t = synthetic tag;

  external bubbles : t => bool = "" [@@bs.get];
  external cancelable : t => bool = "" [@@bs.get];
  external currentTarget : t => ReasonJs.Document.element = "" [@@bs.get];
  external defaultPrevented : t => bool = "" [@@bs.get];
  external eventPhase : t => int = "" [@@bs.get];
  external isTrusted : t => bool = "" [@@bs.get];
  external nativeEvent : t => Js.t {..} = "" [@@bs.get];

  external preventDefault : unit = "" [@@bs.send.pipe: t];
  external isDefaultPrevented : bool = "" [@@bs.send.pipe: t];
  external stopPropagation : unit = "" [@@bs.send.pipe: t];
  external isPropagationStopped : bool = "" [@@bs.send.pipe: t];
  external target : t => ReasonJs.Document.element = "" [@@bs.get];

  external timeStamp : t => float = "" [@@bs.get];
  external _type : t => string = "type" [@@bs.get];

  external persist : unit = "" [@@bs.send.pipe: t];

  external data : t => string = "" [@@bs.get];
};

module Keyboard: {
  type tag;
  type t = synthetic tag;

  external bubbles : t => bool = "" [@@bs.get];
  external cancelable : t => bool = "" [@@bs.get];
  external currentTarget : t => ReasonJs.Document.element = "" [@@bs.get];
  external defaultPrevented : t => bool = "" [@@bs.get];
  external eventPhase : t => int = "" [@@bs.get];
  external isTrusted : t => bool = "" [@@bs.get];
  external nativeEvent : t => Js.t {..} = "" [@@bs.get];

  external preventDefault : unit = "" [@@bs.send.pipe: t];
  external isDefaultPrevented : bool = "" [@@bs.send.pipe: t];
  external stopPropagation : unit = "" [@@bs.send.pipe: t];
  external isPropagationStopped : bool = "" [@@bs.send.pipe: t];
  external target : t => ReasonJs.Document.element = "" [@@bs.get];

  external timeStamp : t => float = "" [@@bs.get];
  external _type : t => string = "type" [@@bs.get];

  external persist : unit = "" [@@bs.send.pipe: t];

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

module Focus: {
  type tag;
  type t = synthetic tag;

  external bubbles : t => bool = "" [@@bs.get];
  external cancelable : t => bool = "" [@@bs.get];
  external currentTarget : t => ReasonJs.Document.element = "" [@@bs.get];
  external defaultPrevented : t => bool = "" [@@bs.get];
  external eventPhase : t => int = "" [@@bs.get];
  external isTrusted : t => bool = "" [@@bs.get];
  external nativeEvent : t => Js.t {..} = "" [@@bs.get];

  external preventDefault : unit = "" [@@bs.send.pipe: t];
  external isDefaultPrevented : bool = "" [@@bs.send.pipe: t];
  external stopPropagation : unit = "" [@@bs.send.pipe: t];
  external isPropagationStopped : bool = "" [@@bs.send.pipe: t];
  external target : t => ReasonJs.Document.element = "" [@@bs.get];

  external timeStamp : t => float = "" [@@bs.get];
  external _type : t => string = "type" [@@bs.get];

  external persist : unit = "" [@@bs.send.pipe: t];

  external relatedTarget : t => ReasonJs.Document.element = "" [@@bs.get]; /* Should return Dom.eventTarget */
};

module Form: {
  type tag;
  type t = synthetic tag;

  external bubbles : t => bool = "" [@@bs.get];
  external cancelable : t => bool = "" [@@bs.get];
  external currentTarget : t => ReasonJs.Document.element = "" [@@bs.get];
  external defaultPrevented : t => bool = "" [@@bs.get];
  external eventPhase : t => int = "" [@@bs.get];
  external isTrusted : t => bool = "" [@@bs.get];
  external nativeEvent : t => Js.t {..} = "" [@@bs.get];

  external preventDefault : unit = "" [@@bs.send.pipe: t];
  external isDefaultPrevented : bool = "" [@@bs.send.pipe: t];
  external stopPropagation : unit = "" [@@bs.send.pipe: t];
  external isPropagationStopped : bool = "" [@@bs.send.pipe: t];
  external target : t => ReasonJs.Document.element = "" [@@bs.get];

  external timeStamp : t => float = "" [@@bs.get];
  external _type : t => string = "type" [@@bs.get];

  external persist : unit = "" [@@bs.send.pipe: t];
};

module Mouse: {
  type tag;
  type t = synthetic tag;

  external bubbles : t => bool = "" [@@bs.get];
  external cancelable : t => bool = "" [@@bs.get];
  external currentTarget : t => ReasonJs.Document.element = "" [@@bs.get];
  external defaultPrevented : t => bool = "" [@@bs.get];
  external eventPhase : t => int = "" [@@bs.get];
  external isTrusted : t => bool = "" [@@bs.get];
  external nativeEvent : t => Js.t {..} = "" [@@bs.get];

  external preventDefault : unit = "" [@@bs.send.pipe: t];
  external isDefaultPrevented : bool = "" [@@bs.send.pipe: t];
  external stopPropagation : unit = "" [@@bs.send.pipe: t];
  external isPropagationStopped : bool = "" [@@bs.send.pipe: t];
  external target : t => ReasonJs.Document.element = "" [@@bs.get];

  external timeStamp : t => float = "" [@@bs.get];
  external _type : t => string = "type" [@@bs.get];

  external persist : unit = "" [@@bs.send.pipe: t];

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

module Selection: {
  type tag;
  type t = synthetic tag;

  external bubbles : t => bool = "" [@@bs.get];
  external cancelable : t => bool = "" [@@bs.get];
  external currentTarget : t => ReasonJs.Document.element = "" [@@bs.get];
  external defaultPrevented : t => bool = "" [@@bs.get];
  external eventPhase : t => int = "" [@@bs.get];
  external isTrusted : t => bool = "" [@@bs.get];
  external nativeEvent : t => Js.t {..} = "" [@@bs.get];

  external preventDefault : unit = "" [@@bs.send.pipe: t];
  external isDefaultPrevented : bool = "" [@@bs.send.pipe: t];
  external stopPropagation : unit = "" [@@bs.send.pipe: t];
  external isPropagationStopped : bool = "" [@@bs.send.pipe: t];
  external target : t => ReasonJs.Document.element = "" [@@bs.get];

  external timeStamp : t => float = "" [@@bs.get];
  external _type : t => string = "type" [@@bs.get];

  external persist : unit = "" [@@bs.send.pipe: t];
};

module Touch: {
  type tag;
  type t = synthetic tag;

  external bubbles : t => bool = "" [@@bs.get];
  external cancelable : t => bool = "" [@@bs.get];
  external currentTarget : t => ReasonJs.Document.element = "" [@@bs.get];
  external defaultPrevented : t => bool = "" [@@bs.get];
  external eventPhase : t => int = "" [@@bs.get];
  external isTrusted : t => bool = "" [@@bs.get];
  external nativeEvent : t => Js.t {..} = "" [@@bs.get];

  external preventDefault : unit = "" [@@bs.send.pipe: t];
  external isDefaultPrevented : bool = "" [@@bs.send.pipe: t];
  external stopPropagation : unit = "" [@@bs.send.pipe: t];
  external isPropagationStopped : bool = "" [@@bs.send.pipe: t];
  external target : t => ReasonJs.Document.element = "" [@@bs.get];

  external timeStamp : t => float = "" [@@bs.get];
  external _type : t => string = "type" [@@bs.get];

  external persist : unit = "" [@@bs.send.pipe: t];

  external altKey : t => bool = "" [@@bs.get];
  external changedTouches : t => Js.t {..} = "" [@@bs.get]; /* Should return Dom.touchList */
  external ctrlKey : t => bool = "" [@@bs.get];
  external getModifierState : string => bool = "" [@@bs.send.pipe: t];
  external metaKey : t => bool = "" [@@bs.get];
  external shiftKey : t => bool = "" [@@bs.get];
  external targetTouches : t => Js.t {..} = "" [@@bs.get]; /* Should return Dom.touchList */
  external touches : t => Js.t {..} = "" [@@bs.get]; /* Should return Dom.touchList */
};

module UI: {
  type tag;
  type t = synthetic tag;

  external bubbles : t => bool = "" [@@bs.get];
  external cancelable : t => bool = "" [@@bs.get];
  external currentTarget : t => ReasonJs.Document.element = "" [@@bs.get];
  external defaultPrevented : t => bool = "" [@@bs.get];
  external eventPhase : t => int = "" [@@bs.get];
  external isTrusted : t => bool = "" [@@bs.get];
  external nativeEvent : t => Js.t {..} = "" [@@bs.get];

  external preventDefault : unit = "" [@@bs.send.pipe: t];
  external isDefaultPrevented : bool = "" [@@bs.send.pipe: t];
  external stopPropagation : unit = "" [@@bs.send.pipe: t];
  external isPropagationStopped : bool = "" [@@bs.send.pipe: t];
  external target : t => ReasonJs.Document.element = "" [@@bs.get];

  external timeStamp : t => float = "" [@@bs.get];
  external _type : t => string = "type" [@@bs.get];

  external persist : unit = "" [@@bs.send.pipe: t];

  external detail : t => int = "" [@@bs.get];
  external view : t => ReasonJs.Window.t = "" [@@bs.get]; /* Should return DOMAbstractView/WindowProxy */
};

module Wheel: {
  type tag;
  type t = synthetic tag;

  external bubbles : t => bool = "" [@@bs.get];
  external cancelable : t => bool = "" [@@bs.get];
  external currentTarget : t => ReasonJs.Document.element = "" [@@bs.get];
  external defaultPrevented : t => bool = "" [@@bs.get];
  external eventPhase : t => int = "" [@@bs.get];
  external isTrusted : t => bool = "" [@@bs.get];
  external nativeEvent : t => Js.t {..} = "" [@@bs.get];

  external preventDefault : unit = "" [@@bs.send.pipe: t];
  external isDefaultPrevented : bool = "" [@@bs.send.pipe: t];
  external stopPropagation : unit = "" [@@bs.send.pipe: t];
  external isPropagationStopped : bool = "" [@@bs.send.pipe: t];
  external target : t => ReasonJs.Document.element = "" [@@bs.get];

  external timeStamp : t => float = "" [@@bs.get];
  external _type : t => string = "type" [@@bs.get];

  external persist : unit = "" [@@bs.send.pipe: t];

  external deltaMode : t => int = "" [@@bs.get];
  external deltaX : t => float = "" [@@bs.get];
  external deltaY : t => float = "" [@@bs.get];
  external deltaZ : t => float = "" [@@bs.get];
};

module Media: {
  type tag;
  type t = synthetic tag;

  external bubbles : t => bool = "" [@@bs.get];
  external cancelable : t => bool = "" [@@bs.get];
  external currentTarget : t => ReasonJs.Document.element = "" [@@bs.get];
  external defaultPrevented : t => bool = "" [@@bs.get];
  external eventPhase : t => int = "" [@@bs.get];
  external isTrusted : t => bool = "" [@@bs.get];
  external nativeEvent : t => Js.t {..} = "" [@@bs.get];

  external preventDefault : unit = "" [@@bs.send.pipe: t];
  external isDefaultPrevented : bool = "" [@@bs.send.pipe: t];
  external stopPropagation : unit = "" [@@bs.send.pipe: t];
  external isPropagationStopped : bool = "" [@@bs.send.pipe: t];
  external target : t => ReasonJs.Document.element = "" [@@bs.get];

  external timeStamp : t => float = "" [@@bs.get];
  external _type : t => string = "type" [@@bs.get];

  external persist : unit = "" [@@bs.send.pipe: t];
};

module Image: {
  type tag;
  type t = synthetic tag;

  external bubbles : t => bool = "" [@@bs.get];
  external cancelable : t => bool = "" [@@bs.get];
  external currentTarget : t => ReasonJs.Document.element = "" [@@bs.get];
  external defaultPrevented : t => bool = "" [@@bs.get];
  external eventPhase : t => int = "" [@@bs.get];
  external isTrusted : t => bool = "" [@@bs.get];
  external nativeEvent : t => Js.t {..} = "" [@@bs.get];

  external preventDefault : unit = "" [@@bs.send.pipe: t];
  external isDefaultPrevented : bool = "" [@@bs.send.pipe: t];
  external stopPropagation : unit = "" [@@bs.send.pipe: t];
  external isPropagationStopped : bool = "" [@@bs.send.pipe: t];
  external target : t => ReasonJs.Document.element = "" [@@bs.get];

  external timeStamp : t => float = "" [@@bs.get];
  external _type : t => string = "type" [@@bs.get];

  external persist : unit = "" [@@bs.send.pipe: t];
};

module Animation: {
  type tag;
  type t = synthetic tag;

  external bubbles : t => bool = "" [@@bs.get];
  external cancelable : t => bool = "" [@@bs.get];
  external currentTarget : t => ReasonJs.Document.element = "" [@@bs.get];
  external defaultPrevented : t => bool = "" [@@bs.get];
  external eventPhase : t => int = "" [@@bs.get];
  external isTrusted : t => bool = "" [@@bs.get];
  external nativeEvent : t => Js.t {..} = "" [@@bs.get];

  external preventDefault : unit = "" [@@bs.send.pipe: t];
  external isDefaultPrevented : bool = "" [@@bs.send.pipe: t];
  external stopPropagation : unit = "" [@@bs.send.pipe: t];
  external isPropagationStopped : bool = "" [@@bs.send.pipe: t];
  external target : t => ReasonJs.Document.element = "" [@@bs.get];

  external timeStamp : t => float = "" [@@bs.get];
  external _type : t => string = "type" [@@bs.get];

  external persist : unit = "" [@@bs.send.pipe: t];

  external animationName : t => string = "" [@@bs.get];
  external pseudoElement : t => string = "" [@@bs.get];
  external elapsedTime : t => float = "" [@@bs.get];
};

module Transition: {
  type tag;
  type t = synthetic tag;

  external bubbles : t => bool = "" [@@bs.get];
  external cancelable : t => bool = "" [@@bs.get];
  external currentTarget : t => ReasonJs.Document.element = "" [@@bs.get];
  external defaultPrevented : t => bool = "" [@@bs.get];
  external eventPhase : t => int = "" [@@bs.get];
  external isTrusted : t => bool = "" [@@bs.get];
  external nativeEvent : t => Js.t {..} = "" [@@bs.get];

  external preventDefault : unit = "" [@@bs.send.pipe: t];
  external isDefaultPrevented : bool = "" [@@bs.send.pipe: t];
  external stopPropagation : unit = "" [@@bs.send.pipe: t];
  external isPropagationStopped : bool = "" [@@bs.send.pipe: t];
  external target : t => ReasonJs.Document.element = "" [@@bs.get];

  external timeStamp : t => float = "" [@@bs.get];
  external _type : t => string = "type" [@@bs.get];

  external persist : unit = "" [@@bs.send.pipe: t];

  external propertyName : t => string = "" [@@bs.get];
  external pseudoElement : t => string = "" [@@bs.get];
  external elapsedTime : t => float = "" [@@bs.get];
};
