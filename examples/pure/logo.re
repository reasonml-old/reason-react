/**
 * Logo component.
 */
module Logo = {
  type logoProps = {message: string};
  include ReactRe.StatelessComponent;
  type props = logoProps;
  let name = "Logo";
  let render {ReactRe.Component.props: props} => <div> (ReactRe.toElement props.message) </div>;
};

include ReactRe.CreateComponent Logo;

let createElement ::message children => wrapProps {message: message} children;
