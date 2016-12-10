include ReactRe.StatelessComponent;

type props = unit;

let render _ => <div> (ReactRe.toElement "Hello!") </div>;

let (comp, wrapProps) =
  createClass
    name::"Logo"
    ::getInstanceVariables
    ::componentDidMount
    ::componentWillReceiveProps
    ::componentDidUpdate
    ::componentWillUnmount
    render;

let createElement ::ref=? ::key=? children => wrapProps ::ref ::key ::children ();
