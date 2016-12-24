/**
 * Logo component.
 * vim: set ft=rust:
 * vim: set ft=reason:
 */
module Logo = {

  /**
   * Includes StatelessComponentJs instead of StatelessComponent so that it
   * can convert from js prop types.
   */
  include ReactRe.Component.JsProps;
  type props = {message: string};
  let name = "Logo";
  let render {props} => <div> (ReactRe.toElement props.message) </div>;
  type jsProps = Js.t {. message : string};
  let jsPropsToReasonProps = Some (fun props => {message: props##message});
};

include ReactRe.CreateComponent Logo;

let createElement ::message children => wrapProps {message: message} children;
