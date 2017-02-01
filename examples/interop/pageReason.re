module PageReason = {
  include ReactRe.Component.JsProps;
  type props = {message: string};
  let name = "PageReason";
  let handleClick {props} event => {
    Js.log "clicked!";
    None
  };
  let render {props, updater} =>
    <div onClick=(updater handleClick)> (ReactRe.stringToElement props.message) </div>;
  type jsProps = Js.t {.
    message: string
  };
  let jsPropsToReasonProps = Some (fun jsProps => {
    message: jsProps##message
  });
};

include ReactRe.CreateComponent PageReason;

let createElement ::message => wrapProps {message: message};
