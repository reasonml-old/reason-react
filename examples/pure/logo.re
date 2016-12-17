/**
 * Logo component.
 */
module Logo = {
  include ReactRe.StatelessComponent;
  type props = {message: string};
  let name = "Logo";
  let render {props} => <div> (ReactRe.toElement props.message) </div>;
};

include ReactRe.CreateComponent Logo;

let createElement ::message children => wrapProps {message: message} children;
