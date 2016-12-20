/**
 * Logo component.
 */
module Logo = {

  /**
   * Includes StatelessComponentJs instead of StatelessComponent so that it
   * can convert from js prop types.
   */
  include ReactRe.StatelessComponentJs;
  type jsProps = Js.t {. message : string};
  type props = {message: string};
  let name = "Logo";
  let render {props} => <div> (ReactRe.toElement props.message) </div>;
  let jsPropsToReasonProps = Some (fun props => {message: props##message});
};

include ReactRe.CreateComponent Logo;

let createElement ::message children => wrapProps {message: message} children;
