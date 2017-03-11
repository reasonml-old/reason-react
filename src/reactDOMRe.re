external render : ReactRe.reactElement => ReasonJs.Document.element => unit =
  "render" [@@bs.val] [@@bs.module "react-dom"];

external unmountComponentAtNode : ReasonJs.Document.element => unit =
  "unmountComponentAtNode" [@@bs.val] [@@bs.module "react-dom"];

external findDOMNode : ReactRe.reactRef => ReasonJs.Document.element =
  "findDOMNode" [@@bs.val] [@@bs.module "react-dom"];

external domElementToObj : ReasonJs.Document.element => Js.t {..} = "%identity";

type reactDOMProps;

/* This list isn't exhaustive. We'll add more as we go. */
external props :
  key::string? =>
  ref::(ReactRe.reactRef => unit)? =>

  /* global html attributes */
  accessKey::string? =>
  className::string? => /* substitute for "class" */
  contentEditable::Js.boolean? =>
  contextMenu::string? =>
  dir::string? => /* "ltr", "rtl" or "auto" */
  draggable::Js.boolean? =>
  hidden::Js.boolean? =>
  id::string? =>
  lang::string? =>
  role::string? => /* ARIA role */
  style::Js.t {..}? =>
  spellCheck::Js.boolean? =>
  tabIndex::int? =>
  title::string? =>

  /* html5 microdata */
  itemID::string? =>
  itemProp::string? =>
  itemRef::string? =>
  itemScope::Js.boolean? =>
  itemType::string? => /* uri */


  /* tag-specific html attributes */
  accept::string? =>
  acceptCharset::string? =>
  action::string? => /* uri */
  alt::string? =>
  async::Js.boolean? =>
  autoComplete::string? => /* has a fixed, but large-ish, set of possible values */
  autoFocus::Js.boolean? =>
  autoPlay::Js.boolean? =>
  challenge::string? =>
  charSet::string? =>
  checked::Js.boolean? =>
  cite::string? => /* uri */
  cols::int? =>
  colSpan::int? =>
  content::string? =>
  controls::Js.boolean? =>
  coords::string? => /* set of values specifying the coordinates of a region */
  data::string? => /* uri */
  dateTime::string? => /* "valid date string with optional time" */
  default::Js.boolean? =>
  defer::Js.boolean? =>
  disabled::Js.boolean? =>
  download::string? => /* should really be either a boolean, signifying presence, or a string */
  encType::string? => /* "application/x-www-form-urlencoded", "multipart/form-data" or "text/plain" */
  form::string? =>
  formAction::string? => /* uri */
  headers::string? =>
  height::string? => /* in html5 this can only be a number, but in html4 it can ba a percentage as well */
  high::int? =>
  href::string? => /* uri */
  hrefLang::string? =>
  htmlFor::string? => /* substitute for "for" */
  httpEquiv::string? => /* has a fixed set of possible values */
  icon::string? => /* uri? */
  integrity::string? =>
  keyType::string? =>
  kind::string? => /* has a fixed set of possible values */
  label::string? =>
  list::string? =>
  low::int? =>
  manifest::string? => /* uri */
  max::string? => /* should be int or Js.Date.t */
  maxLength::int? =>
  media::string? => /* a valid media query */
  method::string? => /* "post" or "get" */
  min::int? =>
  minLength::int? =>
  multiple::Js.boolean? =>
  muted::Js.boolean? =>
  name::string? =>
  noValidate::Js.boolean? =>
  open::Js.boolean? =>
  optimum::int? =>
  pattern::string? => /* valid Js RegExp */
  placeholder::string? =>
  poster::string? => /* uri */
  preload::string? => /* "none", "metadata" or "auto" (and "" as a synonym for "auto") */
  radioGroup::string? =>
  readOnly::Js.boolean? =>
  rel::string? => /* a space- or comma-separated (depending on the element) list of a fixed set of "link types" */
  required::Js.boolean? =>
  reversed::Js.boolean? =>
  rows::int? =>
  rowSpan::int? =>
  sandbox::string? => /* has a fixed set of possible values */
  scope::string? => /* has a fixed set of possible values */
  scoped::Js.boolean? =>
  scrolling::string? => /* html4 only, "auto", "yes" or "no" */
  /* seamless - supported by React, but removed from the html5 spec */
  selected::Js.boolean? =>
  shape::string? =>
  size::int? =>
  sizes::string? =>
  span::int? =>
  src::string? => /* uri */
  srcDoc::string? =>
  srcLang::string? =>
  srcSet::string? =>
  start::int? =>
  step::int? =>
  summary::string? => /* deprecated */
  target::string? =>
  _type::string? => /* has a fixed but large-ish set of possible values */
  useMap::string? =>
  value::string? =>
  width::string? => /* in html5 this can only be a number, but in html4 it can ba a percentage as well */
  wrap::string? => /* "hard" or "soft" */

  /* Clipboard events */
  onCopy::(ReactRe.clipboardEvent => unit)? =>
  onCut::(ReactRe.clipboardEvent => unit)? =>
  onPaste::(ReactRe.clipboardEvent => unit)? =>

  /* Composition events */
  onCompositionEnd::(ReactRe.compositionEvent => unit)? =>
  onCompositionStart::(ReactRe.compositionEvent => unit)? =>
  onCompositionUpdate::(ReactRe.compositionEvent => unit)? =>

  /* Keyboard events */
  onKeyDown::(ReactRe.keyboardEvent => unit)? =>
  onKeyPress::(ReactRe.keyboardEvent => unit)? =>
  onKeyUp::(ReactRe.keyboardEvent => unit)? =>

  /* Focus events */
  onFocus::(ReactRe.focusEvent => unit)? =>
  onBlur::(ReactRe.focusEvent => unit)? =>

  /* Form events */
  onChange::(ReactRe.formEvent => unit)? =>
  onInput::(ReactRe.formEvent => unit)? =>
  onSubmit::(ReactRe.formEvent => unit)? =>

  /* Mouse events */
  onClick::(ReactRe.mouseEvent => unit)? =>
  onContextMenu::(ReactRe.mouseEvent => unit)? =>
  onDoubleClick::(ReactRe.mouseEvent => unit)? =>
  onDrag::(ReactRe.mouseEvent => unit)? =>
  onDragEnd::(ReactRe.mouseEvent => unit)? =>
  onDragEnter::(ReactRe.mouseEvent => unit)? =>
  onDragExit::(ReactRe.mouseEvent => unit)? =>
  onDragLeave::(ReactRe.mouseEvent => unit)? =>
  onDragOver::(ReactRe.mouseEvent => unit)? =>
  onDragStart::(ReactRe.mouseEvent => unit)? =>
  onDrop::(ReactRe.mouseEvent => unit)? =>
  onMouseDown::(ReactRe.mouseEvent => unit)? =>
  onMouseEnter::(ReactRe.mouseEvent => unit)? =>
  onMouseLeave::(ReactRe.mouseEvent => unit)? =>
  onMouseMove::(ReactRe.mouseEvent => unit)? =>
  onMouseOut::(ReactRe.mouseEvent => unit)? =>
  onMouseOver::(ReactRe.mouseEvent => unit)? =>
  onMouseUp::(ReactRe.mouseEvent => unit)? =>

  /* Selection events */
  onSelect::(ReactRe.selectionEvent => unit)? =>

  /* Touch events */
  onTouchCancel::(ReactRe.touchEvent => unit)? =>
  onTouchEnd::(ReactRe.touchEvent => unit)? =>
  onTouchMove::(ReactRe.touchEvent => unit)? =>
  onTouchStart::(ReactRe.touchEvent => unit)? =>

  /* UI events */
  onScroll::(ReactRe.uiEvent => unit)? =>

  /* Wheel events */
  onWheel::(ReactRe.wheelEvent => unit)? =>

  /* Media events */
  onAbort::(ReactRe.mediaEvent => unit)? =>
  onCanPlay::(ReactRe.mediaEvent => unit)? =>
  onCanPlayThrough::(ReactRe.mediaEvent => unit)? =>
  onDurationChange::(ReactRe.mediaEvent => unit)? =>
  onEmptied::(ReactRe.mediaEvent => unit)? =>
  onEncrypetd::(ReactRe.mediaEvent => unit)? =>
  onEnded::(ReactRe.mediaEvent => unit)? =>
  onError::(ReactRe.mediaEvent => unit)? =>
  onLoadedData::(ReactRe.mediaEvent => unit)? =>
  onLoadedMetadata::(ReactRe.mediaEvent => unit)? =>
  onLoadStart::(ReactRe.mediaEvent => unit)? =>
  onPause::(ReactRe.mediaEvent => unit)? =>
  onPlay::(ReactRe.mediaEvent => unit)? =>
  onPlaying::(ReactRe.mediaEvent => unit)? =>
  onProgress::(ReactRe.mediaEvent => unit)? =>
  onRateChange::(ReactRe.mediaEvent => unit)? =>
  onSeeked::(ReactRe.mediaEvent => unit)? =>
  onSeeking::(ReactRe.mediaEvent => unit)? =>
  onStalled::(ReactRe.mediaEvent => unit)? =>
  onSuspend::(ReactRe.mediaEvent => unit)? =>
  onTimeUpdate::(ReactRe.mediaEvent => unit)? =>
  onVolumeChange::(ReactRe.mediaEvent => unit)? =>
  onWaiting::(ReactRe.mediaEvent => unit)? =>

  /* Image events */
  onLoad::(ReactRe.imageEvent => unit)? =>
  /*onError::(ReactRe.imageEvent => unit)? =>*/ /* duplicate */

  /* Animation events */
  onAnimationStart::(ReactRe.animationEvent => unit)? =>
  onAnimationEnd::(ReactRe.animationEvent => unit)? =>
  onAnimationIteration::(ReactRe.animationEvent => unit)? =>

  /* Transition events */
  onTransitionEnd::(ReactRe.transitionEvent => unit)? =>

  /* svg */
  accentHeight::string? =>
  accumulate::string? =>
  additive::string? =>
  alignmentBaseline::string? =>
  allowReorder::string? =>
  alphabetic::string? =>
  amplitude::string? =>
  arabicForm::string? =>
  ascent::string? =>
  attributeName::string? =>
  attributeType::string? =>
  autoReverse::string? =>
  azimuth::string? =>
  baseFrequency::string? =>
  baseProfile::string? =>
  baselineShift::string? =>
  bbox::string? =>
  begin::string? =>
  bias::string? =>
  by::string? =>
  calcMode::string? =>
  capHeight::string? =>
  clip::string? =>
  clipPath::string? =>
  clipPathUnits::string? =>
  clipRule::string? =>
  colorInterpolation::string? =>
  colorInterpolationFilters::string? =>
  colorProfile::string? =>
  colorRendering::string? =>
  contentScriptType::string? =>
  contentStyleType::string? =>
  cursor::string? =>
  cx::string? =>
  cy::string? =>
  d::string? =>
  decelerate::string? =>
  descent::string? =>
  diffuseConstant::string? =>
  direction::string? =>
  display::string? =>
  divisor::string? =>
  dominantBaseline::string? =>
  dur::string? =>
  dx::string? =>
  dy::string? =>
  edgeMode::string? =>
  elevation::string? =>
  enableBackground::string? =>
  end::string? =>
  exponent::string? =>
  externalResourcesRequired::string? =>
  fill::string? =>
  fillOpacity::string? =>
  fillRule::string? =>
  filter::string? =>
  filterRes::string? =>
  filterUnits::string? =>
  floodColor::string? =>
  floodOpacity::string? =>
  focusable::string? =>
  fontFamily::string? =>
  fontSize::string? =>
  fontSizeAdjust::string? =>
  fontStretch::string? =>
  fotStyle::string? =>
  fontVariant::string? =>
  fontWeight::string? =>
  fomat::string? =>
  from::string? =>
  fx::string? =>
  fy::string? =>
  g1::string? =>
  g2::string? =>
  glyphName::string? =>
  glyphOrientationHorizontal::string? =>
  glyphOrientationVertical::string? =>
  glyphRef::string? =>
  gradientTransform::string? =>
  gradientUnits::string? =>
  hanging::string? =>
  horizAdvX::string? =>
  horizOriginX::string? =>
  ideographic::string? =>
  imageRendering::string? =>
  in::string? =>
  in2::string? =>
  intercept::string? =>
  k::string? =>
  k1::string? =>
  k2::string? =>
  k3::string? =>
  k4::string? =>
  kernelMatrix::string? =>
  kernelUnitLength::string? =>
  kerning::string? =>
  keyPoints::string? =>
  keySplines::string? =>
  keyTimes::string? =>
  lengthAdjust::string? =>
  letterSpacing::string? =>
  lightingColor::string? =>
  limitingConeAngle::string? =>
  local::string? =>
  markerEnd::string? =>
  markerHeight::string? =>
  markerMid::string? =>
  markerStart::string? =>
  markerUnits::string? =>
  markerWidth::string? =>
  mask::string? =>
  maskContentUnits::string? =>
  maskUnits::string? =>
  mathematical::string? =>
  mode::string? =>
  numOctaves::string? =>
  offset::string? =>
  opacity::string? =>
  operator::string? =>
  order::string? =>
  orient::string? =>
  orientation::string? =>
  origin::string? =>
  overflow::string? =>
  overlinePosition::string? =>
  overlineThickness::string? =>
  paintOrder::string? =>
  panose1::string? =>
  pathLength::string? =>
  patternContentUnits::string? =>
  patternTransform::string? =>
  patternUnits::string? =>
  pointerEvents::string? =>
  points::string? =>
  pointsAtX::string? =>
  pointsAtY::string? =>
  pointsAtZ::string? =>
  preserveAlpha::string? =>
  preserveAspectRatio::string? =>
  primitiveUnits::string? =>
  r::string? =>
  radius::string? =>
  refX::string? =>
  refY::string? =>
  renderingIntent::string? =>
  repeatCount::string? =>
  repeatDur::string? =>
  requiredExtensions::string? =>
  requiredFeatures::string? =>
  restart::string? =>
  result::string? =>
  rotate::string? =>
  rx::string? =>
  ry::string? =>
  scale::string? =>
  seed::string? =>
  shapeRendering::string? =>
  slope::string? =>
  spacing::string? =>
  specularConstant::string? =>
  specularExponent::string? =>
  speed::string? =>
  spreadMethod::string? =>
  startOffset::string? =>
  stdDeviation::string? =>
  stemh::string? =>
  stemv::string? =>
  stitchTiles::string? =>
  stopColor::string? =>
  stopOpacity::string? =>
  strikethroughPosition::string? =>
  strikethroughThickness::string? =>
  string::string? =>
  stroke::string? =>
  strokeDasharray::string? =>
  strokeDashoffset::string? =>
  strokeLinecap::string? =>
  strokeLinejoin::string? =>
  strokeMiterlimit::string? =>
  strokeOpacity::string? =>
  strokeWidth::string? =>
  surfaceScale::string? =>
  systemLanguage::string? =>
  tableValues::string? =>
  targetX::string? =>
  targetY::string? =>
  textAnchor::string? =>
  textDecoration::string? =>
  textLength::string? =>
  textRendering::string? =>
  _to::string? =>
  transform::string? =>
  u1::string? =>
  u2::string? =>
  underlinePosition::string? =>
  underlineThickness::string? =>
  unicode::string? =>
  unicodeBidi::string? =>
  unicodeRange::string? =>
  unitsPerEm::string? =>
  vAlphabetic::string? =>
  vHanging::string? =>
  vIdeographic::string? =>
  vMathematical::string? =>
  values::string? =>
  vectorEffect::string? =>
  version::string? =>
  vertAdvX::string? =>
  vertAdvY::string? =>
  vertOriginX::string? =>
  vertOriginY::string? =>
  viewBox::string? =>
  viewTarget::string? =>
  visibility::string? =>
  /*width::string? =>*/
  widths::string? =>
  wordSpacing::string? =>
  writingMode::string? =>
  x::string? =>
  x1::string? =>
  x2::string? =>
  xChannelSelector::string? =>
  xHeight::string? =>
  xlinkActuate::string? =>
  xlinkArcrole::string? =>
  xlinkHref::string? =>
  xlinkRole::string? =>
  xlinkShow::string? =>
  xlinkTitle::string? =>
  xlinkType::string? =>
  xmlns::string? =>
  xmlnsXlink::string? =>
  xmlBase::string? =>
  xmlLang::string? =>
  xmlSpace::string? =>
  y::string? =>
  y1::string? =>
  y2::string? =>
  yChannelSelector::string? =>
  z::string? =>
  zoomAndPan::string? =>

  /* RDFa */
  about::string? =>
  datatype::string? =>
  inlist::string? =>
  prefix::string? =>
  property::string? =>
  resource::string? =>
  typeof::string? =>
  vocab::string? =>

  /* react-specific */
  dangerouslySetInnerHTML::string? =>
  suppressContentEditableWarning::Js.boolean? =>

  unit =>
  reactDOMProps =
  "" [@@bs.obj];

external createElement :
  string => props::reactDOMProps? => array ReactRe.reactElement => ReactRe.reactElement =
  "createElement" [@@bs.splice] [@@bs.val] [@@bs.module "react"];
