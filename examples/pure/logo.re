/**
 * Logo component.
 */
open ReactRe;

type logoProps = {message: string};

include ReactRe.CreateComponent {
  include ReactRe.StatelessComponent;
  type props = logoProps;
  let name = "Logo";
  let render {props} => <div> (ReactRe.toElement props.message) </div>;
  /* let createElement = fun wrapProps => (fun ::message children => wrapProps {message: message} children); */
  let createElement = fun wrapProps => fun ::message children => wrapProps {message: message} children;
};

let createElement ::message children => wrapProps {message: message} children;
