external render : ReactRe.reactElement => ReasonJs.Document.element => unit =
  "render" [@@bs.val] [@@bs.module "react-dom"];

external unmountComponentAtNode : ReasonJs.Document.element => unit =
  "unmountComponentAtNode" [@@bs.val] [@@bs.module "react-dom"];

external findDOMNode : ReactRe.reactRef => ReasonJs.Document.element =
  "findDOMNode" [@@bs.val] [@@bs.module "react-dom"];

external domElementToObj : ReasonJs.Document.element => Js.t {..} = "%identity";

type reactDOMProps;

type style;

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
  style::style? =>
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
  type_::string? => /* has a fixed but large-ish set of possible values */
  useMap::string? =>
  value::string? =>
  width::string? => /* in html5 this can only be a number, but in html4 it can ba a percentage as well */
  wrap::string? => /* "hard" or "soft" */

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

  /* RDFa? */

  /* react-specific */
  dangerouslySetInnerHTML::string? =>
  suppressContentEditableWarning::Js.boolean? =>

  unit =>
  reactDOMProps =
  "" [@@bs.obj];

external createElement :
  string => props::reactDOMProps? => array ReactRe.reactElement => ReactRe.reactElement =
  "createElement" [@@bs.splice] [@@bs.val] [@@bs.module "react"];

module Style = {
  type t = style;

  external make :

    /* CSS2Properties: https://www.w3.org/TR/DOM-Level-2-Style/css.html#CSS-CSS2Properties */
    azimuth::string? =>
    background::string? =>
    backgroundAttachment::string? =>
    backgroundColor::string? =>
    backgroundImage::string? =>
    backgroundPosition::string? =>
    backgroundRepeat::string? =>
    border::string? =>
    borderCollapse::string? =>
    borderColor::string? =>
    borderSpacing::string? =>
    borderStyle::string? =>
    borderTop::string? =>
    borderRight::string? =>
    borderBottom::string? =>
    borderLeft::string? =>
    borderTopColor::string? =>
    borderRightColor::string? =>
    borderBottomColor::string? =>
    borderLeftColor::string? =>
    borderTopStyle::string? =>
    borderRightStyle::string? =>
    borderBottomStyle::string? =>
    borderLeftStyle::string? =>
    borderTopWidth::string? =>
    borderRightWidth::string? =>
    borderBottomWidth::string? =>
    borderLeftWidth::string? =>
    borderWidth::string? =>
    bottom::string? =>
    captionSide::string? =>
    clear::string? =>
    clip::string? =>
    color::string? =>
    content::string? =>
    counterIncrement::string? =>
    counterReset::string? =>
    cue::string? =>
    cueAfter::string? =>
    cueBefore::string? =>
    cursor::string? =>
    direction::string? =>
    display::string? =>
    elevation::string? =>
    emptyCells::string? =>
    cssFloat::string? =>
    font::string? =>
    fontFamily::string? =>
    fontSize::string? =>
    fontSizeAdjust::string? =>
    fontStretch::string? =>
    fontStyle::string? =>
    fontVariant::string? =>
    fontWeight::string? =>
    height::string? =>
    left::string? =>
    letterSpacing::string? =>
    lineHeight::string? =>
    listStyle::string? =>
    listStyleImage::string? =>
    listStylePosition::string? =>
    listStyleType::string? =>
    margin::string? =>
    marginTop::string? =>
    marginRight::string? =>
    marginBottom::string? =>
    marginLeft::string? =>
    markerOffset::string? =>
    marks::string? =>
    maxHeight::string? =>
    maxWidth::string? =>
    minHeight::string? =>
    minWidth::string? =>
    orphans::string? =>
    outline::string? =>
    outlineColor::string? =>
    outlineStyle::string? =>
    outlineWidth::string? =>
    overflow::string? =>
    padding::string? =>
    paddingTop::string? =>
    paddingRight::string? =>
    paddingBottom::string? =>
    paddingLeft::string? =>
    page::string? =>
    pageBreakAfter::string? =>
    pageBreakBefore::string? =>
    pageBreakInside::string? =>
    pause::string? =>
    pauseAfter::string? =>
    pauseBefore::string? =>
    pitch::string? =>
    pitchRange::string? =>
    playDuring::string? =>
    position::string? =>
    quotes::string? =>
    richness::string? =>
    right::string? =>
    size::string? =>
    speak::string? =>
    speakHeader::string? =>
    speakNumeral::string? =>
    speakPunctuation::string? =>
    speechRate::string? =>
    stress::string? =>
    tableLayout::string? =>
    textAlign::string? =>
    textDecoration::string? =>
    textIndent::string? =>
    textShadow::string? =>
    textTransform::string? =>
    top::string? =>
    unicodeBidi::string? =>
    verticalAlign::string? =>
    visibility::string? =>
    voiceFamily::string? =>
    volume::string? =>
    whiteSpace::string? =>
    widows::string? =>
    width::string? =>
    wordSpacing::string? =>
    zIndex::string? =>

    /* Below properties based on https://www.w3.org/Style/CSS/all-properties */

    /* Color Level 3 - REC */
    opacity::string? =>

    /* Backgrounds and Borders Level 3 - CR */
    backgroundRepeat::string? =>
    backgroundAttachment::string? =>
    backgroundOrigin::string? =>
    backgroundSize::string? =>
    backgroundClip::string? =>
    borderRadius::string? =>
    borderTopLeftRadius::string? =>
    borderTopRightRadius::string? =>
    borderBottomLeftRadius::string? =>
    borderBottomRightRadius::string? =>
    borderImage::string? =>
    borderImageSource::string? =>
    borderImageSlice::string? =>
    borderImageWidth::string? =>
    borderImageOutset::string? =>
    borderImageRepeat::string? =>
    boxShadow::string? =>

    /* Multi-column Layout - CR */
    columns::string? =>
    columnCount::string? =>
    columnFill::string? =>
    columnGap::string? =>
    columnRule::string? =>
    columnRuleColor::string? =>
    columnRuleStyle::string? =>
    columnRuleWidth::string? =>
    columnSpan::string? =>
    columnWidth::string? =>
    breakAfter::string? =>
    breakBefore::string? =>
    breakInside::string? =>

    /* Speech - CR */
    rest::string? =>
    restAfter::string? =>
    restBefore::string? =>
    speakAs::string? =>
    voiceBalance::string? =>
    voiceDuration::string? =>
    voicePitch::string? =>
    voiceRange::string? =>
    voiceRate::string? =>
    voiceStress::string? =>
    voiceVolume::string? =>

    /* Image Values and Replaced Content Level 3 - CR */
    objectFit::string? =>
    objectPosition::string? =>
    imageResolution::string? =>
    imageOrientation::string? =>

    /* Flexible Box Layout - CR */
    alignContent::string? =>
    alignItems::string? =>
    alignSelf::string? =>
    flex::string? =>
    flexBasis::string? =>
    flexDirection::string? =>
    flexFlow::string? =>
    flexGrow::string? =>
    flexShrink::string? =>
    flexWrap::string? =>
    justifyContent::string? =>
    order::string? =>

    /* Text Decoration Level 3 - CR */
    textDecoration::string? =>
    textDecorationColor::string? =>
    textDecorationLine::string? =>
    textDecorationSkip::string? =>
    textDecorationStyle::string? =>
    textEmphasis::string? =>
    textEmphasisColor::string? =>
    textEmphasisPosition::string? =>
    textEmphasisStyle::string? =>
    textShadow::string? =>
    textUnderlinePosition::string? =>

    /* Fonts Level 3 - CR */
    fontFeatureSettings::string? =>
    fontKerning::string? =>
    fontLanguageOverride::string? =>
    fontSizeAdjust::string? =>
    fontStretch::string? =>
    fontSynthesis::string? =>
    forntVariantAlternates::string? =>
    fontVariantCaps::string? =>
    fontVariantEastAsian::string? =>
    fontVariantLigatures::string? =>
    fontVariantNumeric::string? =>
    fontVariantPosition::string? =>

    /* Cascading and Inheritance Level 3 - CR */
    all::string? =>

    /* Writing Modes Level 3 - CR */
    glyphOrientationVertical::string? =>
    textCombineUpright::string? =>
    textOrientation::string? =>
    writingMode::string? =>

    /* Shapes Level 1 - CR */
    shapeImageThreshold::string? =>
    shapeMargin::string? =>
    shapeOutside::string? =>

    /* Masking Level 1 - CR */
    clipPath::string? =>
    clipRule::string? =>
    mask::string? =>
    maskBorder::string? =>
    maskBorderMode::string? =>
    maskBorderOutset::string? =>
    maskBorderRepeat::string? =>
    maskBorderSlice::string? =>
    maskBorderSource::string? =>
    maskBorderWidth::string? =>
    maskClip::string? =>
    maskComposite::string? =>
    maskImage::string? =>
    maskMode::string? =>
    maskOrigin::string? =>
    maskPosition::string? =>
    maskRepeat::string? =>
    maskSize::string? =>
    maskType::string? =>

    /* Compositing and Blending Level 1 - CR */
    backgroundBlendMode::string? =>
    isolation::string? =>
    mixBlendMode::string? =>

    /* Fragmentation Level 3 - CR */
    boxDecorationBreak::string? =>
    /* breakAfter - already defined by Multi-column Layout */
    /* breakBefore - already defined by Multi-column Layout */
    /* breakInside - already defined by Multi-column Layout */

    /* Basic User Interface Level 3 - CR */
    boxSizing::string? =>
    caretColor::string? =>
    navDown::string? =>
    navLeft::string? =>
    navRight::string? =>
    navUp::string? =>
    outlineOffset::string? =>
    resize::string? =>
    textOverflow::string? =>

    /* Grid Layout Level 1 - CR */
    grid::string? =>
    gridArea::string? =>
    gridAutoColumns::string? =>
    gridAutoFlow::string? =>
    gridAutoRows::string? =>
    gridColumn::string? =>
    gridColumnEnd::string? =>
    gridColumnGap::string? =>
    gridColumnStart::string? =>
    gridGap::string? =>
    gridRow::string? =>
    gridRowEnd::string? =>
    gridRowGap::string? =>
    gridRowStart::string? =>
    gridTemplate::string? =>
    gridTempalteAreas::string? =>
    gridTemplateColumns::string? =>
    gridTemplateRows::string? =>

    /* Will Change Level 1 - CR */
    willChange::string? =>

    /* Text Level 3 - LC */
    hangingPunctuation::string? =>
    hyphens::string? =>
    letterSpacing::string? =>
    lineBreak::string? =>
    overflowWrap::string? =>
    tabSize::string? =>
    textAlign::string? =>
    textAlignLast::string? =>
    textJustify::string? =>
    wordBreak::string? =>
    wordWrap::string? =>

    /* Animations - WD */
    animation::string? =>
    animationDelay::string? =>
    animationDirection::string? =>
    anumationDuration::string? =>
    animationFillMode::string? =>
    animationIterationCount::string? =>
    animationName::string? =>
    animationPlayState::string? =>
    animationTimingFunction::string? =>

    /* Transitions - WD */
    transition::string? =>
    transitionDelay::string? =>
    transitionDuration::string? =>
    transitionProperty::string? =>
    transitionTimingFunction::string? =>

    /* Transforms Level 1 - WD */
    backfaceVisibility::string? =>
    perspective::string? =>
    perspectiveOrigin::string? =>
    transform::string? =>
    transformOrigin::string? =>
    transformStyle::string? =>

    /* Box Alignment Level 3 - WD */
    alignContent::string? =>
    alignItems::string? =>
    justifyItems::string? =>
    justifySelf::string? =>
    placeContent::string? =>
    placeItems::string? =>
    placeSelf::string? =>

    /* Basic User Interface Level 4 - FPWD */
    appearance::string? =>
    caret::string? =>
    caretAnimation::string? =>
    caretShape::string? =>
    userSelect::string? =>

    /* Overflow Level 3 - WD */
    maxLines::string? =>

    /* Basix Box Model - WD */
    marqueeDirection::string? =>
    marqueeLoop::string? =>
    marqueeSpeed::string? =>
    marqueeStyle::string? =>
    overflowStyle::string? =>
    rotation::string? =>
    rotationPoint::string? =>

    /* Not added yet
     * -------------
     * Generated Content for Paged Media - WD
     * Generated Content Level 3 - WD
     * Line Grid Level 1 - WD
     * Regions - WD
     * Inline Layout Level 3 - WD
     * Round Display Level 1 - WD
     * Ruby Layout Level 1 - WD
     * Inline Layout Level 3 - WD
     * Image Values and Replaced Content Level 4 - WD
     * Positioned Layout Level 3 - WD
     * Filter Effects Level 1 -  -WD
     * Lists and Counters Level 3 - WD
     * Exclusions Level 1 - WD
     * Text Level 4 - FPWD
     * SVG Markers - FPWD
     * Motion Path Level 1 - FPWD
     * Color Level 4 - FPWD
     * SVG Strokes - FPWD
     * Table Level 3 - FPWD
     */

    unit =>
    style = "" [@@bs.obj];

    let combine : style => style => style = [%bs.raw {|
      function (a, b) {
        return Object.assign({}, a, b);
      }
    |}];

}
