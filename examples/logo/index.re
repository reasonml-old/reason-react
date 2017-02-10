open ReasonJs;

switch (document |> Document.getElementById "index") {
| Some root => ReactDOMRe.render <Logo message="REASON REACT" /> root;
| None => raise Not_found;
};
