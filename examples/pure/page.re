include ReactRe.Component;

type props = unit;

type state = {clicks: int};

let getInitialState props => {clicks: 0};

let handleClick event {state} => Some {clicks: state.clicks + 1};

let render {state, updater} =>
  <div>
    <button onClick=(updater handleClick)>
      (ReactRe.toElement ("Clicked " ^ string_of_int state.clicks ^ " time(s)"))
    </button>
    <Logo message="Hello!" />
  </div>;

let (comp, wrapProps) =
  createClass
    name::"Page"
    ::getInitialState
    ::getInstanceVariables
    ::componentDidMount
    ::componentWillReceiveProps
    ::componentDidUpdate
    ::componentWillUnmount
    render;

let createElement ::ref=? ::key=? children => wrapProps ::ref ::key ::children ();
