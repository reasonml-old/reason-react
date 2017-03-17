external renderToString : ReactRe.reactElement => string =
  "renderToString" [@@bs.val] [@@bs.module "react-dom/server"];

external renderToStaticMarkup : ReactRe.reactElement => string =
  "renderToStaticMarkup" [@@bs.val] [@@bs.module "react-dom/server"];
