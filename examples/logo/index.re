open ReasonJs;

switch (document |> Document.getElementById "index") {
  | Some element => ReactDOMRe.render <Logo message="REASON REACT" /> element
  | None => raise (Invalid_argument "#index not found")
}
