[%bs.raw {|require('./app.css')|}];

type action =
  | Click;
type state = { count: int };

let component = ReasonReact.reducerComponent "App";

let make _children => {
  ...component,
  initialState: fun () => { count: 0 },
  reducer: fun action state =>
    switch action {
    | Click => ReasonReact.Update {...state, count: state.count + 1}
  },
  render: fun { state, reduce } => {
    let greeting = "clicked " ^ (string_of_int state.count) ^ " time(s)!";
    <div className="App">
      <div className="App-header">
        <Button
          onClick=(reduce (fun _event => Click))
          title="Click"
        />
        (ReasonReact.stringToElement greeting)
      </div>
    </div>
  }
};
