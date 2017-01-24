external render : ReactRe.reactElement => ReasonJs.Document.element => unit =
  "render" [@@bs.val] [@@bs.module "react-dom"];

external unmountComponentAtNode : ReasonJs.Document.element => unit =
  "unmountComponentAtNode" [@@bs.val] [@@bs.module "react-dom"];

external findDOMNode : ReactRe.reactRef => ReasonJs.Document.element =
  "findDOMNode" [@@bs.val] [@@bs.module "react-dom"];

external domElementToObj : ReasonJs.Document.element => Js.t {..} = "%identity";

type reactDOMProps;

external props :
  key::string? =>
  ref::(ReactRe.reactRef => unit)? =>
  /* svg */
  clipRule::string? =>
  cx::string? =>
  cy::string? =>
  d::string? =>
  fill::string? =>
  fillRule::string? =>
  points::string? =>
  r::string? =>
  stroke::string? =>
  strokeLinecap::string? =>
  strokeLinejoin::string? =>
  strokeMiterlimit::string? =>
  strokeWidth::string? =>
  transform::string? =>
  version::string? =>
  viewBox::string? =>
  width::string? =>
  /* normal attributes */
  autoFocus::Js.boolean? =>
  checked::Js.boolean? =>
  className::string? =>
  height::string? =>
  href::string? =>
  id::string? =>
  placeholder::string? =>
  role::string? =>
  style::Js.t {..}? =>
  tabIndex::string? =>
  type_::string? =>
  value::string? =>
  /* events */
  onBlur::(ReactRe.event => unit)? =>
  onChange::(ReactRe.event => unit)? =>
  onClick::(ReactRe.event => unit)? =>
  onDoubleClick::(ReactRe.event => unit)? =>
  onDragEnter::(ReactRe.event => unit)? =>
  onDragOver::(ReactRe.event => unit)? =>
  onDrop::(ReactRe.event => unit)? =>
  onKeyDown::(ReactRe.event => unit)? =>
  onKeyPress::(ReactRe.event => unit)? =>
  onMouseDown::(ReactRe.event => unit)? =>
  onMouseUp::(ReactRe.event => unit)? =>
  onScroll::(ReactRe.event => unit)? =>
  unit =>
  reactDOMProps =
  "" [@@bs.obj];

external createElement :
  string => props::reactDOMProps? => array ReactRe.reactElement => ReactRe.reactElement =
  "createElement" [@@bs.splice] [@@bs.val] [@@bs.module "react"];
