include ReactRe.StatelessComponent;

type props = {message: string};

let render {props} => <div> (ReactRe.toElement props.message) </div>;

let (comp, wrapProps) =
  createClass
    name::"Logo"
    ::getInstanceVariables
    ::componentDidMount
    ::componentWillReceiveProps
    ::componentDidUpdate
    ::componentWillUnmount
    render;

let createElement ::ref=? ::key=? ::message children =>
  wrapProps ::ref ::key ::children {message: message};
