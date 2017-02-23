open ReasonJs;

switch (document |> Document.getElementById "index") {
  | Some element => ReactDOMRe.render <Logo message="REASON REACT" /> element
  | None => raise Not_found
}
