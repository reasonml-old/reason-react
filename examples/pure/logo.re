include ReactRe.StatelessComponent;

type props = {message: string};

let render {props} => <div> (ReactRe.toElement props.message) </div>;

/* This part is the secret sauce that briges to Reactjs. It's a bit verbose (but consistentt) right now; We'll
   find a way to make it shorter in the future. */
let (comp, wrapProps) =
  createClass
    name::"Logo"
    ::getInstanceVariables
    ::componentDidMount
    ::componentWillReceiveProps
    ::componentDidUpdate
    ::componentWillUnmount
    render;

let createElement ::message => wrapProps {message: message};
