[%bs.raw {|require('./index.css')|}];

external register_service_worker : unit => unit =
  "default" [@@bs.module "./registerServiceWorker"];

open App;

ReactDOMRe.renderToElementWithId
  <App /> "root";

register_service_worker ();
