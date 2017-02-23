Js.log "Do you see this message? If you do, then things should work!";

open ReasonJs;

switch (document |> Document.getElementById "index") {
  | Some element => ReactDOMRe.render <Page message="Hello!" /> element
  | None => raise Not_found
}
